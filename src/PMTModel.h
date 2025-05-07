#ifndef PMTMODEL_H
#define PMTMODEL_H

#include "TObject.h"
#include "TGraph.h"
#include "TF1.h"

#include "PMType.h"

/**
 * @class PMTModel
 * @brief PMT响应模型类
 * 
 * 实现不同类型的PMT响应模型，支持多种电荷响应模型计算，
 * 可用于模拟PMT响应或对实验数据进行拟合。
 */
class PMTModel : public TObject
{
 private:

  Int_t nbins;       // 直方图bin数量
  
  Double_t xmin;     // x轴最小值
  Double_t xmax;     // x轴最大值

  Double_t step;     // x轴步长
          
 public:
  
  PMTModel();
  
  virtual ~PMTModel();

  /**
   * @brief 构造函数
   * @param _nbins bin数量
   * @param _xmin x轴最小值
   * @param _xmax x轴最大值
   * @param _modtype 模型类型
   */
  PMTModel( Int_t _nbins, Double_t _xmin, Double_t _xmax, PMType::Model _modtype );

  PMType::Model modtype;  // 模型类型
  
  Int_t nparams;          // 参数数量
  Double_t params[20]={-1.0};  // 模型参数数组
  
  Double_t wbin;          // bin宽度
  
  /**
   * @brief 设置模型参数
   * @param _params 参数数组
   */
  void SetParams( Double_t _params[] );
  
  /**
   * @brief 计算给定电荷值的模型响应
   * @param xx 电荷值
   * @return 模型响应值
   */
  Double_t GetValue( Double_t xx );
  
  /**
   * @brief 简单高斯模型计算
   * @param xx 电荷值
   * @return 模型响应值
   */
  Double_t F1( Double_t xx ); // SIMPLE GAUSS 1
  
  /**
   * @brief 截断高斯模型计算
   * @param xx 电荷值
   * @return 模型响应值
   */
  Double_t F2( Double_t xx ); // SIMPLE GAUSS 2
  
  /**
   * @brief 解析截断高斯模型计算
   * @param xx 电荷值
   * @return 模型响应值
   */
  Double_t F3( Double_t xx ); // ANALYTICAL GAUSS 2
  
  /**
   * @brief 显式截断高斯模型计算
   * @param xx 电荷值
   * @return 模型响应值
   */
  Double_t F4( Double_t xx ); // EXPLICIT GAUSS 2
  
  /**
   * @brief 获取模型曲线图形
   * @return 模型曲线图形
   */
  TGraph* GetGraph();
  
  /**
   * @brief 获取特定光电子数的响应曲线(F3模型)
   * @param n 光电子数
   * @return 响应曲线图形
   */
  TGraph* GetGraphN( Int_t n );
  
  /**
   * @brief 获取特定光电子数的响应曲线(F4模型)
   * @param n 光电子数
   * @return 响应曲线图形
   */
  TGraph* GetGraphN2( Int_t n );
  
  ClassDef( PMTModel, 1 )
    
};

#endif
