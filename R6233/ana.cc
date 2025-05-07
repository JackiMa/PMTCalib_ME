#include "TApplication.h"
#include "iostream"
#include "iomanip"
#include "fstream"
#include "TCanvas.h"
#include "PMTStyle.h"
#include "PMType.h"
#include "Pedestal.h"
#include "SPEResponse.h"
#include "PMT.h"
#include "PMTModel.h"
#include "SPEFitter.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TSystem.h"
#include <vector>
#include <sstream>
#include <algorithm>

#include <nlohmann/json.hpp> // 读取配置文件

using namespace std;

// 配置文件相关的数据结构
struct FitParams
{
    Double_t mu;
    Double_t Q0;
    Double_t s0;
    Double_t Q1;
    Double_t s1;
    Double_t alpha;
    Double_t w;
};
struct FitRange
{
    Double_t xmin;
    Double_t xmax;
};

class Config
{
public:
    TString dataFileName;
    FitRange fitRange;
    FitParams guessValue;
    TString pdfName;
    Bool_t drawComponents;     // 是否绘制光电子组分
    Int_t componentsNumber;    // 绘制的光电子组分数量
};

Config read_config(TString filename)
{
    std::ifstream file(filename);
    nlohmann::json j;
    file >> j;

    Config config;
    TString DataFileName = j["DataFileName"].get<std::string>().c_str();
    TArrayD FitRange(2, j["FitRange"].get<std::vector<Double_t>>().data());
    TArrayD GuessValue(7, j["GuessValue"].get<std::vector<Double_t>>().data());
    TString pdfName = j["PdfName"].get<std::string>().c_str();

    // 读取组分绘制相关的配置
    Bool_t drawComponents = true;  // 默认值为true
    Int_t componentsNumber = 5;    // 默认值为5
    
    // 检查配置文件中是否存在这些项目
    if (j.contains("DrawComponents")) {
        drawComponents = j["DrawComponents"].get<bool>();
    }
    
    if (j.contains("ComponentsNumber")) {
        componentsNumber = j["ComponentsNumber"].get<int>();
    }

    config.dataFileName = DataFileName;
    config.fitRange.xmin = FitRange[0];
    config.fitRange.xmax = FitRange[1];
    config.guessValue.mu = GuessValue[0];
    config.guessValue.Q0 = GuessValue[1];
    config.guessValue.s0 = GuessValue[2];
    config.guessValue.Q1 = GuessValue[3];
    config.guessValue.s1 = GuessValue[4];
    config.guessValue.alpha = GuessValue[5];
    config.guessValue.w = GuessValue[6];
    config.pdfName = pdfName;
    config.drawComponents = drawComponents;
    config.componentsNumber = componentsNumber;
    
    cout << "DataFileName: " << DataFileName << endl;
    cout << "FitRange: " << FitRange[0] << ", " << FitRange[1] << endl;
    cout << "GuessValue: ";
    for (Int_t i = 0; i < 7; i++)
    {
        cout << GuessValue[i] << ", ";
    }
    cout << endl;
    cout << "DrawComponents: " << (drawComponents ? "true" : "false") << endl;
    cout << "ComponentsNumber: " << componentsNumber << endl;
    
    return config;
}

/**
 * @brief Replace all commas in a string with spaces.
 * @param a Reference to the input string.
 */
void stripCommas(string &a)
{
    size_t pos;
    while ((pos = a.find_first_of(",")) != string::npos)
    {
        a.replace(pos, 1, " ");
    }
}

class Data
{
public:
    Double_t xmin;
    Double_t xmax;
    Double_t ymin;
    Double_t ymax;
    Int_t nbins;
    std::vector<Double_t> xdata;
    std::vector<Double_t> ydata;
};

// 用于从线性左边换算XLinear-YLog左边，便于在画布上定位
struct Position
{
    Double_t x1, y1, x2, y2;
};

Position convertToAbsolutePosition(Double_t relX1, Double_t relY1, Double_t relX2, Double_t relY2, Double_t xmin, Double_t xmax, Double_t ymin, Double_t ymax)
{
    Position pos;
    pos.x1 = relX1 * (xmax - xmin) + xmin;
    pos.x2 = relX2 * (xmax - xmin) + xmin;
    pos.y1 = pow(10, relY1 * log10(ymax - ymin));
    pos.y2 = pow(10, relY2 * log10(ymax - ymin));
    return pos;
}

// 读取数据文件，跳过文件头。判断数据的标准：连续三行首字符为数字或负号
void skipUntilDataStarts(std::ifstream &input)
{
    std::string sline;
    Int_t consecutiveNumericLines = 0;
    Int_t totalLines = 0;

    while (std::getline(input, sline))
    {
        totalLines++;
        if (std::isdigit(sline[0]) || sline[0] == '-')
        {
            consecutiveNumericLines++;
            if (consecutiveNumericLines == 3)
            {
                break;
            }
        }
        else
        {
            consecutiveNumericLines = 0;
        }
    }

    input.clear();
    input.seekg(0, std::ios::beg);

    for (Int_t i = 0; i < totalLines - 3; i++)
    {
        std::getline(input, sline);
    }
}

/**
 * @brief Read data from the input file.
 * @param file Path to the input file.
 * @param fitRange Range of x values to fit.
 * @return Data object containing the read data.
 * 
 * 读取并解析数据文件，支持多种分隔符格式，并应用拟合范围过滤
 */
Data getData(TString file, FitRange fitRange)
{
    std::ifstream input;
    std::string sline;
    std::istringstream iss;
    Double_t var1, var2;

    input.open(file, std::ios::in);

    skipUntilDataStarts(input);

    Data data;
    data.xmin = std::numeric_limits<Double_t>::max();
    data.xmax = std::numeric_limits<Double_t>::lowest();

    data.ymin = std::numeric_limits<Double_t>::max();
    data.ymax = std::numeric_limits<Double_t>::lowest();

    while (std::getline(input, sline))
    {
        std::string token1, token2;
        char sep = ',';
        if (std::count(sline.begin(), sline.end(), ',') == 1)
        {
            sep = ',';
        }
        else if (std::count(sline.begin(), sline.end(), ';') == 1)
        {
            sep = ';';
        }
        else if (std::count(sline.begin(), sline.end(), '\t') == 1)
        {
            sep = '\t';
        }

        std::istringstream iss(sline);
        std::getline(iss, token1, sep);
        std::getline(iss, token2, sep);

        var1 = std::stod(token1) * 1e9; // convert the unit into nVs
        var2 = std::stod(token2);

        if ((fitRange.xmin == 0 || var1 > fitRange.xmin) && (fitRange.xmax == 0 || var1 < fitRange.xmax))
        {
            data.xdata.push_back(var1);
            data.ydata.push_back(var2);

            if (var1 < data.xmin)
            {
                data.xmin = var1;
            }
            if (var1 > data.xmax)
            {
                data.xmax = var1;
            }
            if (var2 < data.ymin)
            {
                data.ymin = var2;
            }
            if (var2 > data.ymax)
            {
                data.ymax = var2;
            }
        }
    }

    data.nbins = data.xdata.size();

    input.close();
    input.clear();

    return data;
}

/**
 * @brief Create a histogram from the input file.
 * @param nbins Number of bins.
 * @param xmin Minimum x value.
 * @param xmax Maximum x value.
 * @param file Path to the input file.
 * @return Pointer to the created histogram.
 * 
 * 根据数据创建直方图，设置适当的样式和误差
 */
TH1D *get_histo(Data &data, Double_t wbin)
{

    TH1D *histo = new TH1D("histo", "; Charge in nVs; Entries", data.nbins, data.xmin - wbin / 2.0, data.xmax + wbin / 2.0);

    cout << "Here is get_histo:" << endl;
    // Fill the histogram with data from the file
    for (size_t i = 0; i < data.xdata.size(); i++)
    {
        Double_t var1 = data.xdata[i];
        Double_t var2 = data.ydata[i];

        histo->Fill(var1, var2);
    }

    // Set bin errors based on the square root of bin content
    for (Int_t i = 1; i <= data.nbins; i++)
    {
        histo->SetBinError(i, sqrt(histo->GetBinContent(i)));
    }

    histo->SetMarkerStyle(20);
    histo->SetMarkerSize(0.75);
    histo->SetLineColor(kBlack);
    histo->SetMarkerColor(kBlack);
    histo->Draw("PEZ");

    return histo;
}

/**
 * @brief Main function to process and fit histograms.
 * @return Status code.
 * 
 * 完整的PMT电荷谱拟合流程，包括数据读取、参数估计、拟合和结果绘制
 */
Int_t project0(TString ConfigFile)
{
    time_t start;
    time(&start);

    cout << "" << endl;
    cout << " The macro starts ( project0.C ) ... " << endl;
    cout << "" << endl;

    gROOT->Reset();
    PMTStyle::SetDefaultStyle();

    TCanvas *c1 = new TCanvas("c1", "");
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1.0, 1.0);
    pad1->SetBottomMargin(0);
    pad1->Draw();
    pad1->SetLogy();
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1.0, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.4);
    pad2->Draw();

    TH1D *hSG[1];

    // 我们只是保留了run，实际上没有用到。请忽略run的存在
    // 论文原作者用同样的setup改变led测了6组数据，简单统计了这6组数据的gain和chi2
    Int_t run = 0;
    Int_t nbins;
    Double_t xmax;
    Double_t xmin;
    Double_t wbin;

    Config config = read_config(ConfigFile);
    Data data = getData(config.dataFileName, config.fitRange);

    FitParams guessValue = config.guessValue;
    // 是否由配置文件设置xmin/xmax
    xmax = data.xmax;
    xmin = data.xmin;
    nbins = data.nbins;

    nbins /= 1; // Only for even nbins
    wbin = (xmax - xmin) / (1.0 * nbins - 1.0);
    cout << "\n";
    cout << xmin << ", " << xmax << ", " << nbins << ", " << wbin << endl;

    pad1->cd();
    pad1->SetBottomMargin(0.12);

    hSG[run] = get_histo(data, wbin);
    hSG[run]->SetName(Form("hSG_%d", run));
    hSG[run]->GetXaxis()->SetRangeUser(xmin, xmax);
    hSG[run]->SetStats(0);
    hSG[run]->Draw("PEZ");

    pad1->SetBottomMargin(0);
    pad1->cd();

    SPEFitter fit;

    // 将对pedestal的拟合作为后续拟合的初始值
    // Get the pedestal, assuming its peak is the highest overall
    // ped(mean, sigma)
    Double_t QQ = guessValue.Q0 == 0 ? hSG[run]->GetBinCenter(hSG[run]->GetMaximumBin()) : guessValue.Q0;
    Double_t s0 = guessValue.s0 == 0 ? 0.002 : guessValue.s0; // 0.002 by eye
    Pedestal ped(QQ, s0);
    ped.LocatePedestal(hSG[run], QQ, s0);

    // 估计初始参数
    Double_t mu_test = fit.FindMu(hSG[run], ped.Q0, ped.s0);
    Double_t g_test = fit.FindG(hSG[run], ped.Q0, mu_test);
    Double_t p_test[4] = {g_test, 0.3 * g_test, 1.0 / (0.5 * g_test), 0.2};

    // 设置拟合方法和初始参数
    SPEResponse gauss_test(PMType::GAUSS, p_test);
    DFTmethod dft(2.0 * nbins, xmin, xmax, gauss_test);
    dft.wbin = hSG[run]->GetBinWidth(1);
    dft.Norm = hSG[run]->Integral();

    // 是否由配置文件设置这些拟合参数，如果没有，那么按照test拟合的结果作为初始值
    dft.Q0 = guessValue.Q0 == 0 ? ped.Q0 : guessValue.Q0;
    dft.s0 = guessValue.s0 == 0 ? ped.s0 : guessValue.s0;
    dft.mu = guessValue.mu == 0 ? mu_test : guessValue.mu;

    fit.SetDFTmethod(dft);
    fit.FitwDFTmethod(hSG[run]);

    // 提取拟合结果
    dft.Norm = fit.vals[0];
    dft.Q0 = fit.vals[1];
    dft.s0 = fit.vals[2];
    dft.mu = fit.vals[3];

    Double_t p_fit[4] = {fit.vals[4], fit.vals[5], fit.vals[6], fit.vals[7]};
    dft.spef.SetParams(p_fit);

    // 绘制拟合结果
    TGraph *grBF = dft.GetGraph();
    grBF->Draw("SAME,L");
    
    // 根据配置来决定是否添加各个光电子组分曲线
    if (config.drawComponents) {
        // 添加各个光电子组分曲线(使用更粗的灰色虚线)
        Int_t lineWidth = 2;  // 更粗的线宽
        
        // 绘制指定数量的光电子组分
        Int_t maxComponents = config.componentsNumber;
        
        for (Int_t n = 0; n < maxComponents; n++) {
            // 使用GetGraphN获取准确的组分曲线
            TGraph* grN = dft.GetGraphN(n);
            if (!grN) continue;  // 防止空指针
            
            grN->SetLineStyle(2);  // 虚线
            grN->SetLineColor(kGray+1);
            grN->SetLineWidth(lineWidth);
            grN->Draw("SAME,L");
            
            // 这里需要手动删除TGraph对象，因为GetGraphN会在堆上创建新对象
            // 但由于ROOT会管理绘制对象，所以需要使用TGraph::SetDeleteAfterUse
            // 以防止删除正在使用的对象
            grN->SetBit(kCanDelete);  // 让ROOT在不再需要时自动删除此对象
        }
    }
    
    pad2->cd();

    TH1F *hp = new TH1F("pull", "", nbins, xmin, xmax);
    hp->SetLineColor(kBlack);
    hp->SetMinimum(-6);
    hp->SetMaximum(6);
    hp->Sumw2();
    hp->SetStats(0);
    hp->SetMarkerStyle(20);

    // Fill the Residual histogram
    for (Int_t i = 1; i <= nbins; i++)
    {
        float data = hSG[run]->GetBinContent(i);
        float fit = dft.GetValue(hSG[run]->GetBinCenter(i));
        float error = hSG[run]->GetBinError(i);
        float pull;
        if (error > 0)
        {
            pull = (data - fit) / error;
        }
        else
        {
            pull = 0;
        }
        if (i <= 1 || i >= nbins)
        {
            pull = 0;
        }
        hp->SetBinContent(i, pull);
    }
    hp->SetFillColor(kBlack);
    hp->Draw();
    hp->GetXaxis()->SetLabelSize(0.1);
    hp->GetXaxis()->SetTitleSize(0.15);
    hp->GetXaxis()->SetTitleOffset(1.2);
    hp->GetYaxis()->SetLabelSize(0.1);
    hp->GetYaxis()->SetTitle("Pull");
    hp->GetYaxis()->SetTitleSize(0.15);
    hp->GetYaxis()->SetTitleOffset(0.3);
    hp->GetYaxis()->CenterTitle();
    hp->GetYaxis()->SetNdivisions(3);
    hp->GetXaxis()->SetTitle("Charge [nVs]");
    hp->GetXaxis()->SetTitleOffset(1.2);

    TF1 *f1 = new TF1("f1", "3", xmin, xmax);
    f1->SetLineColor(kBlack);
    f1->SetLineStyle(2);
    f1->SetLineWidth(1);
    f1->Draw("same");

    TF1 *f2 = new TF1("f2", "-3", xmin, xmax);
    f2->SetLineColor(kBlack);
    f2->SetLineStyle(2);
    f2->SetLineWidth(1);
    f2->Draw("same");

    pad1->cd();

    Double_t Q = fit.vals[4];
    Double_t s = fit.vals[5];
    Double_t a = fit.vals[6];
    Double_t w = fit.vals[7];

    // 计算修正后的增益
    Double_t gn = 0.5 * TMath::Erfc(-Q / (sqrt(2.0) * s));
    Double_t k = s / gn / sqrt(2.0 * TMath::Pi()) * TMath::Exp(-pow(Q, 2.0) / (2.0 * pow(s, 2.0)));
    Double_t Qf = Q + k;

    cout << " Q  : " << Q << endl;
    cout << " Qf : " << Qf << ", " << (Q / Qf - 1.0) * 100.0 << endl;
    cout << "" << endl;

    Double_t Gfit = w / a + (1.0 - w) * Qf;
    cout << " G  : " << Gfit << endl;
    cout << "    : " << (Q / Gfit - 1.0) * 100.0 << endl;
    cout << "    : " << (Qf / Gfit - 1.0) * 100.0 << endl;
    cout << "" << endl;

    cout << " D. : " << (Gfit / 0.02656 - 1.0) * 100.0 << endl;
    cout << "" << endl;

    Double_t Gain = fit.vals[4] - fit.vals[1];
    cout << " Chi2/ndf : " << fit.chi2r * fit.ndof << " / " << fit.ndof << " = " << fit.chi2r << endl;
    cout << " Gain = Q1 - Q0 : " << Gain << " ± " << sqrt(fit.errs[4] * fit.errs[4] + fit.errs[1] * fit.errs[1]) << "nVs" << endl;
    // 创建 TPaveText 对象，坐标参数为绝对值
    Position pos = convertToAbsolutePosition(0.7, 0.45, 0.97, 1.07, xmin, xmax, data.ymin, data.ymax);
    TPaveText *pt = new TPaveText(pos.x1, pos.y1, pos.x2, pos.y2);
    pt->SetTextAlign(11);  // 设置文本为左对齐
    pt->SetBorderSize(0);  // 设置边框大小为0，即无边框
    pt->SetFillColor(0);   // 设置背景色为白色
    pt->SetFillStyle(0.2); // 设置填充样式透明
    pt->SetTextSize(0.06); // 设置文本大小
    pt->AddText(Form("#font[22]{#scale[0.8]{#mu = %.3f #pm %.3f}}", fit.vals[3], fit.errs[3]));
    pt->AddText(Form("#font[22]{#scale[0.8]{Q0 = %.5f #pm %.5f}}", fit.vals[1], fit.errs[1]));
    pt->AddText(Form("#font[22]{#scale[0.8]{#sigma0 = %.5f #pm %.5f}}", fit.vals[2], fit.errs[2]));
    pt->AddText(Form("#font[22]{#scale[0.8]{Q1 = %.5f #pm %.5f}}", fit.vals[4], fit.errs[4]));
    pt->AddText(Form("#font[22]{#scale[0.8]{#sigma1 = %.5f #pm %.5f}}", fit.vals[5], fit.errs[5]));
    pt->AddText(Form("#font[22]{#scale[0.8]{#alpha = %.0f #pm %.0f}}", fit.vals[6], fit.errs[6]));
    pt->AddText(Form("#font[22]{#scale[0.8]{w = %.3f #pm %.3f}}", fit.vals[7], fit.errs[7]));
    pt->AddText(Form("#font[22]{#scale[0.8]{#chi^{2}/NDOF = %.0f / %.0f}}", fit.chi2r * fit.ndof, fit.ndof));
    // pt->AddText(Form("#font[22]{#scale[0.8]{#mu = %.3f #pm %.3f}}", fit.vals[3], fit.errs[3]));
    // pt->AddText(Form("#font[22]{#scale[0.8]{Gain = %.5f #pm %.5f}}", fit.vals[4]-fit.vals[1],  sqrt(fit.errs[4] * fit.errs[4] + fit.errs[1] * fit.errs[1]));
    pt->Draw();

    TString saveName;
    if (config.pdfName == "" || config.pdfName == "1") // 默认保存文件名
    {
        TString fileName = gSystem->BaseName(config.dataFileName);
        Ssiz_t dotPos = fileName.Last('.');
        if (dotPos != kNPOS)
        {
            fileName.Remove(dotPos);
        }
        saveName = Form("%s_Gain=%fnVs.pdf", fileName.Data(), Gain);
        c1->Print(saveName);
        if (config.pdfName == "1"){     // 如果pdfName为1，那么保存完文件后不交互
            return 0;
        }
    }
    else if (config.pdfName == "-1") // 如果pdfName为-1，不保存文件
    {
        saveName = config.pdfName;
    }
    else
    {
        saveName = config.pdfName;
        c1->Print(saveName);
    }
    
    cout << " ... the macro ends ! " << endl;

    time_t end;
    time(&end);

    Int_t dura = difftime(end, start);
    Int_t min = dura / 60;
    Int_t sec = dura % 60;

    cout << " ---> " << Form("%02d:%02d", min, sec) << endl;
    cout << "" << endl;
    cout << "" << endl;

    // Interact with users
    // 这是一个循坏，会一直等待用户输入，直到退出。所以会非常占用资源。
    // TODO 优化这部分实现逻辑，降低资源占用
    // bool continueLoop = true;
    // while (continueLoop)
    // {
    //     TObject *selectedObject = c1->WaitPrimitive();

    //     if (selectedObject && selectedObject->InheritsFrom(TText::Class()))
    //     {
    //         TText *text = (TText *)selectedObject;
    //         if (std::string(text->GetTitle()) == "exit")
    //         {
    //             continueLoop = false;
    //         }
    //     }

    //     c1->Update();
    // }

    return 0;
}

/**
 * @brief Main entry point of the application.
 * @return Status code.
 */
Int_t main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <config file path>" << std::endl;
        return 1;
    }

    const char *configFilePath = argv[1];

    TApplication theApp("App", &argc, argv);
    Int_t status = project0(configFilePath);
    return status;
}