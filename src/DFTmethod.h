#ifndef DFTMETHOD_H
#define DFTMETHOD_H

#include "iostream"
#include "iomanip"
#include <math.h>

#include "TObject.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TColor.h"

#include "SPEResponse.h"

#include "fftw3.h"


class DFTmethod : public TObject
{
 private:

  Int_t nbins;
  
  Double_t xmin;
  Double_t xmax;

  Double_t step;
      
  unsigned int N;
  unsigned int M;
  
  std::vector<Double_t> xvalues;
  std::vector<Double_t> yvalues;
    
  Double_t edge;

  TGraph *gr;
  
 public:
  
  DFTmethod();
  
  virtual ~DFTmethod();
  
  DFTmethod( Int_t _nbins, Double_t _xmin, Double_t _xmax, SPEResponse _spef );

  SPEResponse spef;
  
  Double_t wbin;
  
  Double_t Norm;

  Double_t Q0;
  Double_t s0;

  Double_t mu;
  
  Double_t fftPhase( Double_t vy, Double_t vz );
  void CalculateValues();
  Double_t GetValue( Double_t xx );

  // 获取特定光电子数量n的组分在位置x处的值
  Double_t GetComponentValue( Double_t xx, Int_t n );

  TGraph* GetGraph();
  TGraph* GetGraphN( Int_t n );
    
  ClassDef( DFTmethod, 1 )
        
};

#endif
