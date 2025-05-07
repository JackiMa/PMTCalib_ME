#include "SPEFitter.h"

using namespace std;

// 全局变量，用于拟合函数
Int_t N;                  // 数据点数量
double xx0[7500];         // 数据点x坐标数组
double yy0[7500];         // 数据点y坐标数组

double wbin0;             // bin宽度

NumIntegration num0;      // 数值积分方法实例
DFTmethod dft0;           // 离散傅里叶变换方法实例
PMTModel mod0;            // PMT模型实例

Int_t Nb;                 // 有效bin数量(y>0)

/**
 * @brief 数值积分方法的拟合函数
 * @param x 参数数组
 * @return 卡方值
 * 
 * 该函数使用数值积分方法计算模型值，并与数据比较计算卡方
 */
double fit_func_num( const double *x )
{
  double result = 0.0;

  num0.wbin = wbin0;
  
  double Norm = x[0]; 
  num0.Norm = Norm;
  
  double Q0 = x[1];
  num0.Q0 = Q0;
  double s0 = x[2];
  num0.s0 = s0;
  
  double mu = x[3];
  num0.mu = mu;
    
  double params0[20];
  for( Int_t i=0; i<num0.spef.nparams; i++ ) params0[i] = x[i+4];
  num0.spef.SetParams( params0 );
  
  num0.CalculateValues();

  // 计算卡方
  for ( Int_t i=0; i<N; i++ )
    {
      if ( yy0[i]>0 )
	{
	  Double_t val = num0.GetValue( xx0[i] );
	  if ( val<1.0e-5 ) val = 1.0e-5;
	  
	  result += pow( val-yy0[i], 2.0 )/( yy0[i] );

	}
      
    }
  
  return result;
  
}

/**
 * @brief 离散傅里叶变换方法的拟合函数
 * @param x 参数数组
 * @return 卡方值
 * 
 * 该函数使用离散傅里叶变换方法计算模型值，并与数据比较计算卡方
 */
double fit_func_fft( const double *x )
{
  double result = 0.0;

  dft0.wbin = wbin0;
  
  double Norm = x[0]; 
  dft0.Norm = Norm;
  
  double Q0 = x[1];
  dft0.Q0 = Q0;
  double s0 = x[2];
  dft0.s0 = s0;
  
  double mu = x[3];
  dft0.mu = mu;
    
  double params0[20];
  for( Int_t i=0; i<dft0.spef.nparams; i++ ) params0[i] = x[i+4];
  dft0.spef.SetParams( params0 );
  
  dft0.CalculateValues();

  for ( Int_t i=0; i<N; i++ )
    {
      if ( yy0[i]>0 )
	{
	  Double_t val = dft0.GetValue( xx0[i] );
	  if ( val<1.0e-5 ) val = 1.0e-5;
	  
	  result += pow( val-yy0[i], 2.0 )/( yy0[i] );

	}
      
    }
    
  return result;
  
}

/**
 * @brief PMT模型方法的拟合函数
 * @param x 参数数组
 * @return 卡方值
 * 
 * 该函数使用PMT模型计算模型值，并与数据比较计算卡方
 */
double fit_func_mod( const double *x )
{
  double result = 0.0;

  mod0.wbin = wbin0;
      
  double params0[20];
  for( Int_t i=0; i<mod0.nparams; i++ ) params0[i] = x[i];
  mod0.SetParams( params0 );
  
  for ( Int_t i=0; i<N; i++ )
    {
      if ( yy0[i]>0 )
	{
	  Double_t val = mod0.GetValue( xx0[i] );
	  if ( val<1.0e-5 ) val = 1.0e-5;
      
	  result += pow( val-yy0[i], 2.0 )/( yy0[i] );

	}
      
    }
    
  return result;
  
}

/**
 * @brief 高斯函数，用于基座拟合
 * @param x 电荷值
 * @param par 参数数组
 * @return 高斯函数值
 * 
 * 用于拟合基座(pedestal)的标准高斯函数
 */
Double_t m_g( Double_t *x, Double_t *par )
{
  Double_t xx = x[0];

  Double_t Norm = par[0];
  
  Double_t Q_0 = par[1];
  Double_t s_0 = par[2];
        
  Double_t arg = 0.0; 
  if ( s_0!=0.0 ) arg = ( xx - Q_0 )/s_0;    
  else cout << "Error: The code tries to divide by zero." << endl;
  
  Double_t result = 1.0/( sqrt( 2 * TMath::Pi() ) * s_0 ) * TMath::Exp( -0.5*arg*arg );
  result *= ( Norm*wbin0 );
    
  return result;
  
}

ClassImp( SPEFitter )


SPEFitter::SPEFitter()
{}

SPEFitter::~SPEFitter()
{}

void SPEFitter::SetNummethod( NumIntegration _num )
{
  num = _num;

  num0 = _num;
  
}

void SPEFitter::SetDFTmethod( DFTmethod _dft )
{
  dft = _dft;

  dft0 = _dft;
  
}

void SPEFitter::SetPMTModel( PMTModel _mod )
{
  mod = _mod;

  mod0 = _mod;
  
}

/**
 * @brief 估计平均光电子数μ
 * @param hspec 电荷谱直方图
 * @param _Q0 基座中心位置
 * @param _s0 基座宽度
 * @return 估计的平均光电子数μ
 * 
 * 通过拟合基座并计算基座与总电荷谱的比例来估计μ值
 * μ = ln(Ntot/Nped)，基于泊松分布中0光电子的概率P(0)=e^(-μ)
 */
Double_t SPEFitter::FindMu( TH1 *hspec, Double_t _Q0, Double_t _s0 )
{
  // 创建基座拟合函数
  ped_func = new TF1( "pmt_ped", m_g, _Q0-5.0*_s0, _Q0-5.0*_s0, 3 );
  ped_func->SetParNames( "Norm", "Q", "#sigma" );
  ped_func->SetLineColor( kRed );
  ped_func->SetNpx( 10000 );
  
  wbin0 = hspec->GetXaxis()->GetBinWidth(1);
  
  Double_t Norm = hspec->Integral();
  
  // 设置拟合初始参数
  ped_func->SetParameter( 0, Norm );
  ped_func->SetParLimits( 0, Norm*0.01, Norm*100.0 );

  ped_func->SetParameter( 1, _Q0 ); ped_func->SetParLimits( 1, _Q0-2.0*_s0, _Q0+2.0*_s0 );
  ped_func->SetParameter( 2, _s0 ); ped_func->SetParLimits( 2, _s0*0.9, _s0*1.1 );
  
  // 拟合基座区域
  hspec->Fit( "pmt_ped", "Q0", "", _Q0-3.0*_s0, _Q0+1.8*_s0 );  
  
  Double_t *pars0 = ped_func->GetParameters();
  // 计算μ = ln(Ntot/Nped)
  Double_t _mu = TMath::Log( Norm/pars0[0] );
      
  return _mu;
  
}

/**
 * @brief 估计PMT增益
 * @param hspec 电荷谱直方图
 * @param _Q0 基座中心位置
 * @param _mu 平均光电子数
 * @return 估计的PMT增益
 * 
 * 通过谱的平均值与基座位置的差除以平均光电子数来估计增益
 * G = (Mean - Q0)/μ
 */
Double_t SPEFitter::FindG( TH1 *hspec, Double_t _Q0, Double_t _mu )
{
  Double_t G = ( hspec->GetMean()-_Q0 )/_mu;
  
  return G;
  
}

/**
 * @brief 使用数值积分方法进行拟合
 * @param hspec 电荷谱直方图
 * 
 * 使用数值积分方法对PMT电荷谱进行完整拟合，提取所有参数
 */
void SPEFitter::FitwNummethod( TH1 *hspec )
{
  // 获取直方图信息
  N = hspec->GetXaxis()->GetNbins();
  wbin0 = hspec->GetXaxis()->GetBinWidth(1);

  
  fit_status=-1;
  
  Nb=0;
  
  // 提取数据点
  for ( Int_t i=0; i<N; i++ )
    {
      xx0[i] = hspec->GetXaxis()->GetBinCenter( i+1 );
      yy0[i] = hspec->GetBinContent( i+1 );

      if ( yy0[i]>0 ) Nb++;
      
    }

  // 创建Minuit2优化器进行拟合
  mNum = new ROOT::Minuit2::Minuit2Minimizer();
  
  ROOT::Math::Functor FCA;
  FCA = ROOT::Math::Functor( &fit_func_num, num.spef.nparams+4 );
  
  mNum->SetFunction(FCA);
  
  // 设置拟合参数
  mNum->SetLimitedVariable( 0, "Norm", num.Norm, num.Norm*0.01, num.Norm*0.75, num.Norm*1.25 ); // !!!
  mNum->SetLimitedVariable( 1, "Q0", num.Q0, TMath::Abs( num.Q0 )*0.01+0.001*num.s0, num.Q0-0.5*num.s0, num.Q0+0.5*num.s0 );
  mNum->SetLimitedVariable( 2, "s0", num.s0, num.s0*0.01, num.s0*0.5, num.s0*1.5 );
  
  mNum->SetLimitedVariable( 3, "mu", num.mu, 0.01, num.mu*0.5, num.mu*2.0 );
  
  mNum->SetLimitedVariable( 4, "PAR1", num.spef.params[0], num.spef.params[0]*0.001, num.spef.params[0]*0.3, num.spef.params[0]*3.0 );
  mNum->SetLimitedVariable( 5, "PAR2", num.spef.params[1], num.spef.params[1]*0.001, num.spef.params[1]*0.1, num.spef.params[1]*8.0 );
  mNum->SetLimitedVariable( 6, "PAR3", num.spef.params[2], num.spef.params[2]*0.001, num.spef.params[2]*0.01, num.spef.params[2]*5.0 );
  mNum->SetLimitedVariable( 7, "PAR4", num.spef.params[3], 0.01, 0.0, 0.65 );
  
  // 配置优化器
  mNum->SetMaxFunctionCalls(1.E9);
  mNum->SetMaxIterations(1.E9);
  mNum->SetTolerance(0.01);
  mNum->SetStrategy(2);
  mNum->SetErrorDef(1.0);
  mNum->Minimize();
  mNum->Hesse();
  
  // 尝试多次拟合以获得更好结果
  Int_t ifits = 0;
  while( mNum->Status()!=0 && ifits<4 )
    { 
      mNum->Minimize();
      mNum->Hesse();
      ifits++;
      
    }
  
  if( mNum->Status()!=0 )
    {
      cout << " * " << endl;
      cout << " * The fit has failed ! " << endl;
      cout << " * " << endl;
      
      return;

    }

  fit_status = mNum->Status();
  
  // 输出拟合结果
  cout << " * " << endl;
  cout << " * Minimization results "  << endl;
  cout << " * " << endl;

  cout << " * " << setw(10)  << "Calls" << " : " << mNum->NCalls() << endl;
  cout << " * " << setw(10)  << "Status" << " : " << fit_status << endl;
  cout << " * " << endl;
    
  Int_t ndim = mNum->NDim();
  const double *pars = mNum->X();  
  const double *erpars = mNum->Errors();
    
  // 保存拟合参数及误差
  for ( int i=0; i<ndim; i++ )
    {
      cout << " * " << setw(10)  << mNum->VariableName(i) << " : " << Form( "%.5f", pars[i] ) << " +/- " << Form( "%.5f", erpars[i] ) << endl; 
      cout << " * " << endl;

      vals[i]=pars[i];
      errs[i]=erpars[i];
            
    }

  // 计算拟合优度
  ndof = Nb-num.spef.nparams-4; 
  cout << " * " << setw(10) << "NDOF" << " : " << ndof << endl;
  
  chi2r = mNum->MinValue()/( ndof );
  cout << " * " << setw(10) << "chi2/NDOF" << " : " << Form( "%.2f", chi2r ) << endl;
  cout << " * " << endl;
    
  cout << "" << endl;
    
  return;

}

/**
 * @brief 使用离散傅里叶变换方法进行拟合
 * @param hspec 电荷谱直方图
 * 
 * 使用离散傅里叶变换方法对PMT电荷谱进行完整拟合，提取所有参数
 */
void SPEFitter::FitwDFTmethod( TH1 *hspec )
{
  N = hspec->GetXaxis()->GetNbins();
  wbin0 = hspec->GetXaxis()->GetBinWidth(1);

  
  fit_status=-1;
  
  Nb=0;
  
  for ( Int_t i=0; i<N; i++ )
    {
      xx0[i] = hspec->GetXaxis()->GetBinCenter( i+1 );
      yy0[i] = hspec->GetBinContent( i+1 );

      if ( yy0[i]>0 ) Nb++;
      
    }

  
  mFFT = new ROOT::Minuit2::Minuit2Minimizer();
  
  ROOT::Math::Functor FCA;
  FCA = ROOT::Math::Functor( &fit_func_fft, dft.spef.nparams+4 );
  
  mFFT->SetFunction(FCA);
  
  mFFT->SetLimitedVariable( 0, "Norm", dft.Norm, dft.Norm*0.01, dft.Norm*0.75, dft.Norm*1.25 ); // !!!
  mFFT->SetLimitedVariable( 1, "Q0", dft.Q0, TMath::Abs( dft.Q0 )*0.01+0.001*dft.s0, dft.Q0-0.5*dft.s0, dft.Q0+0.5*dft.s0 );
  mFFT->SetLimitedVariable( 2, "s0", dft.s0, dft.s0*0.01, dft.s0*0.5, dft.s0*1.5 );
  
  mFFT->SetLimitedVariable( 3, "mu", dft.mu, 0.01, dft.mu*0.5, dft.mu*2.0 );
  
  mFFT->SetLimitedVariable( 4, "PAR1", dft.spef.params[0], dft.spef.params[0]*0.001, dft.spef.params[0]*0.3, dft.spef.params[0]*3.0 );
  mFFT->SetLimitedVariable( 5, "PAR2", dft.spef.params[1], dft.spef.params[1]*0.001, dft.spef.params[1]*0.1, dft.spef.params[1]*8.0 );
  mFFT->SetLimitedVariable( 6, "PAR3", dft.spef.params[2], dft.spef.params[2]*0.001, dft.spef.params[2]*0.01, dft.spef.params[2]*5.0 );
  mFFT->SetLimitedVariable( 7, "PAR4", dft.spef.params[3], 0.01, 0.0, 0.65 );
  
  
  mFFT->SetMaxFunctionCalls(1.E9);
  mFFT->SetMaxIterations(1.E9);
  mFFT->SetTolerance(0.01);
  mFFT->SetStrategy(2);
  mFFT->SetErrorDef(1.0);
  mFFT->Minimize();
  mFFT->Hesse();
  
  
  Int_t ifits = 0;
  while( mFFT->Status()!=0 && ifits<4 )
    { 
      mFFT->Minimize();
      mFFT->Hesse();
      ifits++;
      
    }
  
  if( mFFT->Status()!=0 )
    {
      cout << " * " << endl;
      cout << " * The fit has failed ! " << endl;
      cout << " * " << endl;
      
      return;

    }

  fit_status = mFFT->Status();
  
  cout << " * " << endl;
  cout << " * Minimization results "  << endl;
  cout << " * " << endl;

  cout << " * " << setw(10)  << "Calls" << " : " << mFFT->NCalls() << endl;
  cout << " * " << setw(10)  << "Status" << " : " << fit_status << endl;
  cout << " * " << endl;
    
  Int_t ndim = mFFT->NDim();
  const double *pars = mFFT->X();  
  const double *erpars = mFFT->Errors();
    
  for ( int i=0; i<ndim; i++ )
    {
      cout << " * " << setw(10)  << mFFT->VariableName(i) << " : " << Form( "%.5f", pars[i] ) << " +/- " << Form( "%.5f", erpars[i] ) << endl; 
      cout << " * " << endl;

      vals[i]=pars[i];
      errs[i]=erpars[i];
            
    }

  ndof = Nb-dft.spef.nparams-4; 
  cout << " * " << setw(10) << "NDOF" << " : " << ndof << endl;
  
  chi2r = mFFT->MinValue()/( ndof );
  cout << " * " << setw(10) << "chi2/NDOF" << " : " << Form( "%.2f", chi2r ) << endl;
  cout << " * " << endl;
    
  cout << "" << endl;
    
  return;
  
}

/**
 * @brief 使用PMT模型进行拟合
 * @param hspec 电荷谱直方图
 * 
 * 使用PMT模型对电荷谱进行拟合，提取PMT增益及其他参数
 */
void SPEFitter::FitwPMTModel( TH1 *hspec )
{
  N = hspec->GetXaxis()->GetNbins();
  wbin0 = hspec->GetXaxis()->GetBinWidth(1);

  
  fit_status=-1;

  Nb=0;
  
  for ( Int_t i=0; i<N; i++ )
    {
      xx0[i] = hspec->GetXaxis()->GetBinCenter( i+1 );
      yy0[i] = hspec->GetBinContent( i+1 );

      if ( yy0[i]>0 ) Nb++;
      
    }
  
  mMOD = new ROOT::Minuit2::Minuit2Minimizer();
  
  ROOT::Math::Functor FCA;
  FCA = ROOT::Math::Functor( &fit_func_mod, 8 ); 
  
  mMOD->SetFunction(FCA);

  mMOD->SetLimitedVariable( 0, "Norm", mod.params[0], mod.params[0]*0.01, mod.params[0]*0.75, mod.params[0]*1.25 );
  mMOD->SetLimitedVariable( 1, "Q0", mod.params[1], TMath::Abs( mod.params[1] )*0.01+0.001*dft.s0, mod.params[1]-0.5*mod.params[2], mod.params[1]+0.5*mod.params[2] );
  mMOD->SetLimitedVariable( 2, "s0", mod.params[2], mod.params[2]*0.01, mod.params[2]*0.5, mod.params[2]*1.5 );
  
  mMOD->SetLimitedVariable( 3, "mu", mod.params[3], 0.01, mod.params[3]*0.3, mod.params[3]*3.0 );
  
  mMOD->SetLimitedVariable( 4, "PAR1", mod.params[4], mod.params[4]*0.001, mod.params[4]*0.3, mod.params[4]*3.0 );
  mMOD->SetLimitedVariable( 5, "PAR2", mod.params[5], mod.params[5]*0.01, mod.params[5]*0.1, mod.params[5]*10.0 );
  mMOD->SetLimitedVariable( 6, "PAR3", mod.params[6], mod.params[6]*0.01, mod.params[6]*0.01, mod.params[6]*3.0 );
  mMOD->SetLimitedVariable( 7, "PAR4", mod.params[7], 0.01, 0.0, 0.65 );
  
  
  mMOD->SetMaxFunctionCalls(1.E9);
  mMOD->SetMaxIterations(1.E9);
  mMOD->SetTolerance(0.01);
  mMOD->SetStrategy(2);
  mMOD->SetErrorDef(1.0);
  mMOD->Minimize();
  mMOD->Hesse();
  
  
  Int_t ifits = 0;
  while( mMOD->Status()!=0 && ifits<4 )
    { 
      mMOD->Minimize();
      mMOD->Hesse();
      ifits++;
      
    }
  
  if( mMOD->Status()!=0 )
    {
      cout << " * " << endl;
      cout << " * The fit has failed ! " << endl;
      cout << " * " << endl;
      
      return;

    }
  
  fit_status = mMOD->Status();
  
  cout << " * " << endl;
  cout << " * Minimization results "  << endl;
  cout << " * " << endl;
  
  cout << " * " << setw(10)  << "Calls" << " : " << mMOD->NCalls() << endl;
  cout << " * " << setw(10)  << "Status" << " : " << fit_status << endl;
  cout << " * " << endl;
  
  Int_t ndim = mMOD->NDim();
  const double *pars = mMOD->X();  
  const double *erpars = mMOD->Errors();
    
  for ( int i=0; i<ndim; i++ )
    {
      cout << " * " << setw(10)  << mMOD->VariableName(i) << " : " << Form( "%.5f", pars[i] ) << " +/- " << Form( "%.5f", erpars[i] ) << endl; 
      cout << " * " << endl;

      vals[i]=pars[i];
      errs[i]=erpars[i];
            
    }

  ndof = Nb-mod.nparams;
  cout << " * " << setw(10) << "NDOF" << " : " << ndof << endl;

  chi2r = mMOD->MinValue()/( ndof ); 
  cout << " * " << setw(10) << "chi2/NDOF" << " : " << Form( "%.2f", chi2r ) << endl;
  cout << " * " << endl;
    
  Double_t p[8] = { vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6], vals[7] };
  mod.SetParams( p );
  
  cout << "" << endl;
  
  return;
  
}
