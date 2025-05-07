#ifndef SPEFITTER_H
#define SPEFITTER_H

#include "TObject.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1.h"
#include "TH1D.h"

#include "NumIntegration.h"
#include "DFTmethod.h"
#include "PMTModel.h"

#include "TMinuit.h"
#include "Minuit2/Minuit2Minimizer.h"
#include "Minuit2/FunctionMinimum.h" 
#include "Minuit2/MnMigrad.h" 
#include "Minuit2/MnUserParameters.h" 
#include "Minuit2/MnPrint.h" 
#include "Minuit2/FCNBase.h" 
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

/**
 * @class SPEFitter
 * @brief 单光电子(SPE)响应谱拟合类
 * 
 * 该类提供了多种方法拟合PMT的单光电子响应谱，包括：
 * 1. 数值积分法（NumIntegration）
 * 2. 离散傅立叶变换法（DFTmethod）
 * 3. PMT模型法（PMTModel）
 * 
 * 可以通过这些方法提取PMT的关键参数，如增益、单光电子响应特性等。
 */
class SPEFitter : public TObject
{
 private:

  NumIntegration num;   // 数值积分方法对象
  
  DFTmethod dft;        // 离散傅立叶变换方法对象
  //ROOT::Minuit2::Minuit2Minimizer *mFFT;
    
  PMTModel mod;         // PMT模型对象
  ROOT::Minuit2::Minuit2Minimizer *mMOD;  // PMT模型优化器
  
  TF1 *ped_func;        // 基座（pedestal）拟合函数
  
 public:
  
  SPEFitter();
  
  virtual ~SPEFitter();

  // 数值积分和FFT方法的优化器
  ROOT::Minuit2::Minuit2Minimizer *mNum;
  ROOT::Minuit2::Minuit2Minimizer *mFFT;

  Int_t fit_status;     // 拟合状态，0表示成功
  
  Double_t vals[20];    // 拟合结果参数数组
  Double_t errs[20];    // 拟合参数误差数组

  Double_t ndof;        // 自由度数
  Double_t chi2r;       // 简约卡方值(χ²/ndof)

  /**
   * @brief 估计平均光电子数
   * @param hspec 电荷谱直方图
   * @param _Q0 基座中心位置
   * @param _s0 基座宽度
   * @return 估计的平均光电子数μ
   */
  Double_t FindMu( TH1 *hspec, Double_t _Q0, Double_t _s0 );
  
  /**
   * @brief 估计PMT增益
   * @param hspec 电荷谱直方图
   * @param _Q0 基座中心位置
   * @param _mu 平均光电子数
   * @return 估计的PMT增益
   */
  Double_t FindG( TH1 *hspec, Double_t _Q0, Double_t _mu );

  /**
   * @brief 设置数值积分方法
   * @param _num 数值积分方法对象
   */
  void SetNummethod( NumIntegration _num );
  
  /**
   * @brief 使用数值积分方法进行拟合
   * @param hspec 电荷谱直方图
   */
  void FitwNummethod( TH1 *hspec );
  
  /**
   * @brief 设置离散傅立叶变换方法
   * @param _dft 离散傅立叶变换方法对象
   */
  void SetDFTmethod( DFTmethod _dft );
  
  /**
   * @brief 使用离散傅立叶变换方法进行拟合
   * @param hspec 电荷谱直方图
   */
  void FitwDFTmethod( TH1 *hspec );
  
  /**
   * @brief 设置PMT模型
   * @param _mod PMT模型对象
   */
  void SetPMTModel( PMTModel _mod );
  
  /**
   * @brief 使用PMT模型进行拟合
   * @param hspec 电荷谱直方图
   */
  void FitwPMTModel( TH1 *hspec );
  
  ClassDef( SPEFitter, 1 )
    
};

#endif
