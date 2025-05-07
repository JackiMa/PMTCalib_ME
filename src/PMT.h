#ifndef PMT_H
#define PMT_H

#include "iostream"
#include "iomanip"

#include "TObject.h"
#include "TMath.h"
#include "TH1.h"
#include "TF1.h"
#include "TRandom3.h"

#include "Pedestal.h"
#include "SPEResponse.h"

/**
 * @class PMT
 * @brief PMT模拟类
 * 
 * 该类用于模拟PMT的电荷响应谱，可以生成包含基座和单光电子响应的完整谱
 * 模拟基于泊松分布和单光电子响应函数的卷积
 */
class PMT : public TObject
{
 private:
  
  TH1D *spectrum;      // 电荷谱直方图
  
  Int_t nbins;         // 直方图bin数量
  Double_t min;        // x轴最小值
  Double_t max;        // x轴最大值
  
  Pedestal ped;        // 基座(pedestal)对象
  SPEResponse res;     // 单光电子响应对象
  
  
 public:
  
  PMT();
  
  virtual ~PMT();
  
  /**
   * @brief 构造函数
   * @param _nbins bin数量
   * @param _min x轴最小值
   * @param _max x轴最大值
   * @param _ped 基座对象
   * @param _res 单光电子响应对象
   */
  PMT( Int_t _nbins, Double_t _min, Double_t _max, Pedestal _ped, SPEResponse _res );
      
  /**
   * @brief 生成PMT电荷谱
   * @param ntot 事件总数
   * @param mu 平均光电子数
   * 
   * 使用Monte Carlo方法生成PMT电荷谱，包括基座和单光电子响应的卷积
   */
  void GenSpectrum( Int_t ntot, Double_t mu );
  
  /**
   * @brief 获取电荷谱直方图
   * @return 电荷谱直方图指针
   */
  TH1D* GetSpectrum(){ return spectrum; };
  
  /**
   * @brief 绘制电荷谱
   */
  void DrawSpectrum()
  {
    //spectrum->SetMaximum( 1.2*spectrum->GetBinContent( spectrum->GetMaximumBin() ) );
    spectrum->Draw( "PEZ" );
      
  };
    
  ClassDef( PMT, 1 )
    
};

#endif
