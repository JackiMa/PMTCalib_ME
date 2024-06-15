// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME PMTCalibDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "src/DFTmethod.h"
#include "src/NumIntegration.h"
#include "src/PMT.h"
#include "src/PMTModel.h"
#include "src/PMTStyle.h"
#include "src/PMType.h"
#include "src/Pedestal.h"
#include "src/SPEFitter.h"
#include "src/SPEResponse.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace PMType {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *PMType_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("PMType", 0 /*version*/, "PMType.h", 5,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &PMType_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *PMType_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace PMTStyle {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *PMTStyle_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("PMTStyle", 0 /*version*/, "PMTStyle.h", 12,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &PMTStyle_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *PMTStyle_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static void *new_SPEResponse(void *p = nullptr);
   static void *newArray_SPEResponse(Long_t size, void *p);
   static void delete_SPEResponse(void *p);
   static void deleteArray_SPEResponse(void *p);
   static void destruct_SPEResponse(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SPEResponse*)
   {
      ::SPEResponse *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SPEResponse >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SPEResponse", ::SPEResponse::Class_Version(), "SPEResponse.h", 11,
                  typeid(::SPEResponse), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SPEResponse::Dictionary, isa_proxy, 4,
                  sizeof(::SPEResponse) );
      instance.SetNew(&new_SPEResponse);
      instance.SetNewArray(&newArray_SPEResponse);
      instance.SetDelete(&delete_SPEResponse);
      instance.SetDeleteArray(&deleteArray_SPEResponse);
      instance.SetDestructor(&destruct_SPEResponse);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SPEResponse*)
   {
      return GenerateInitInstanceLocal(static_cast<::SPEResponse*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SPEResponse*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_DFTmethod(void *p = nullptr);
   static void *newArray_DFTmethod(Long_t size, void *p);
   static void delete_DFTmethod(void *p);
   static void deleteArray_DFTmethod(void *p);
   static void destruct_DFTmethod(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DFTmethod*)
   {
      ::DFTmethod *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::DFTmethod >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("DFTmethod", ::DFTmethod::Class_Version(), "DFTmethod.h", 21,
                  typeid(::DFTmethod), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::DFTmethod::Dictionary, isa_proxy, 4,
                  sizeof(::DFTmethod) );
      instance.SetNew(&new_DFTmethod);
      instance.SetNewArray(&newArray_DFTmethod);
      instance.SetDelete(&delete_DFTmethod);
      instance.SetDeleteArray(&deleteArray_DFTmethod);
      instance.SetDestructor(&destruct_DFTmethod);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DFTmethod*)
   {
      return GenerateInitInstanceLocal(static_cast<::DFTmethod*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::DFTmethod*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_NumIntegration(void *p = nullptr);
   static void *newArray_NumIntegration(Long_t size, void *p);
   static void delete_NumIntegration(void *p);
   static void deleteArray_NumIntegration(void *p);
   static void destruct_NumIntegration(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::NumIntegration*)
   {
      ::NumIntegration *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::NumIntegration >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("NumIntegration", ::NumIntegration::Class_Version(), "NumIntegration.h", 21,
                  typeid(::NumIntegration), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::NumIntegration::Dictionary, isa_proxy, 4,
                  sizeof(::NumIntegration) );
      instance.SetNew(&new_NumIntegration);
      instance.SetNewArray(&newArray_NumIntegration);
      instance.SetDelete(&delete_NumIntegration);
      instance.SetDeleteArray(&deleteArray_NumIntegration);
      instance.SetDestructor(&destruct_NumIntegration);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::NumIntegration*)
   {
      return GenerateInitInstanceLocal(static_cast<::NumIntegration*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::NumIntegration*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Pedestal(void *p = nullptr);
   static void *newArray_Pedestal(Long_t size, void *p);
   static void delete_Pedestal(void *p);
   static void deleteArray_Pedestal(void *p);
   static void destruct_Pedestal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pedestal*)
   {
      ::Pedestal *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Pedestal >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Pedestal", ::Pedestal::Class_Version(), "Pedestal.h", 13,
                  typeid(::Pedestal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Pedestal::Dictionary, isa_proxy, 4,
                  sizeof(::Pedestal) );
      instance.SetNew(&new_Pedestal);
      instance.SetNewArray(&newArray_Pedestal);
      instance.SetDelete(&delete_Pedestal);
      instance.SetDeleteArray(&deleteArray_Pedestal);
      instance.SetDestructor(&destruct_Pedestal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pedestal*)
   {
      return GenerateInitInstanceLocal(static_cast<::Pedestal*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Pedestal*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PMT(void *p = nullptr);
   static void *newArray_PMT(Long_t size, void *p);
   static void delete_PMT(void *p);
   static void deleteArray_PMT(void *p);
   static void destruct_PMT(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PMT*)
   {
      ::PMT *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PMT >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("PMT", ::PMT::Class_Version(), "PMT.h", 17,
                  typeid(::PMT), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PMT::Dictionary, isa_proxy, 4,
                  sizeof(::PMT) );
      instance.SetNew(&new_PMT);
      instance.SetNewArray(&newArray_PMT);
      instance.SetDelete(&delete_PMT);
      instance.SetDeleteArray(&deleteArray_PMT);
      instance.SetDestructor(&destruct_PMT);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PMT*)
   {
      return GenerateInitInstanceLocal(static_cast<::PMT*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::PMT*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PMTModel(void *p = nullptr);
   static void *newArray_PMTModel(Long_t size, void *p);
   static void delete_PMTModel(void *p);
   static void deleteArray_PMTModel(void *p);
   static void destruct_PMTModel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PMTModel*)
   {
      ::PMTModel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PMTModel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("PMTModel", ::PMTModel::Class_Version(), "PMTModel.h", 11,
                  typeid(::PMTModel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PMTModel::Dictionary, isa_proxy, 4,
                  sizeof(::PMTModel) );
      instance.SetNew(&new_PMTModel);
      instance.SetNewArray(&newArray_PMTModel);
      instance.SetDelete(&delete_PMTModel);
      instance.SetDeleteArray(&deleteArray_PMTModel);
      instance.SetDestructor(&destruct_PMTModel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PMTModel*)
   {
      return GenerateInitInstanceLocal(static_cast<::PMTModel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::PMTModel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SPEFitter(void *p = nullptr);
   static void *newArray_SPEFitter(Long_t size, void *p);
   static void delete_SPEFitter(void *p);
   static void deleteArray_SPEFitter(void *p);
   static void destruct_SPEFitter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SPEFitter*)
   {
      ::SPEFitter *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SPEFitter >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SPEFitter", ::SPEFitter::Class_Version(), "SPEFitter.h", 27,
                  typeid(::SPEFitter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SPEFitter::Dictionary, isa_proxy, 4,
                  sizeof(::SPEFitter) );
      instance.SetNew(&new_SPEFitter);
      instance.SetNewArray(&newArray_SPEFitter);
      instance.SetDelete(&delete_SPEFitter);
      instance.SetDeleteArray(&deleteArray_SPEFitter);
      instance.SetDestructor(&destruct_SPEFitter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SPEFitter*)
   {
      return GenerateInitInstanceLocal(static_cast<::SPEFitter*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SPEFitter*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr SPEResponse::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SPEResponse::Class_Name()
{
   return "SPEResponse";
}

//______________________________________________________________________________
const char *SPEResponse::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SPEResponse*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SPEResponse::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SPEResponse*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SPEResponse::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SPEResponse*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SPEResponse::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SPEResponse*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr DFTmethod::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *DFTmethod::Class_Name()
{
   return "DFTmethod";
}

//______________________________________________________________________________
const char *DFTmethod::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DFTmethod*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int DFTmethod::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DFTmethod*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *DFTmethod::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DFTmethod*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *DFTmethod::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DFTmethod*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr NumIntegration::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *NumIntegration::Class_Name()
{
   return "NumIntegration";
}

//______________________________________________________________________________
const char *NumIntegration::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::NumIntegration*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int NumIntegration::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::NumIntegration*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *NumIntegration::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::NumIntegration*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *NumIntegration::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::NumIntegration*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Pedestal::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Pedestal::Class_Name()
{
   return "Pedestal";
}

//______________________________________________________________________________
const char *Pedestal::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Pedestal*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Pedestal::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Pedestal*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Pedestal::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Pedestal*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Pedestal::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Pedestal*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PMT::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *PMT::Class_Name()
{
   return "PMT";
}

//______________________________________________________________________________
const char *PMT::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PMT*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int PMT::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PMT*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PMT::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PMT*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PMT::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PMT*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PMTModel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *PMTModel::Class_Name()
{
   return "PMTModel";
}

//______________________________________________________________________________
const char *PMTModel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PMTModel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int PMTModel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PMTModel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PMTModel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PMTModel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PMTModel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PMTModel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SPEFitter::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SPEFitter::Class_Name()
{
   return "SPEFitter";
}

//______________________________________________________________________________
const char *SPEFitter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SPEFitter*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SPEFitter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SPEFitter*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SPEFitter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SPEFitter*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SPEFitter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SPEFitter*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void SPEResponse::Streamer(TBuffer &R__b)
{
   // Stream an object of class SPEResponse.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SPEResponse::Class(),this);
   } else {
      R__b.WriteClassBuffer(SPEResponse::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SPEResponse(void *p) {
      return  p ? new(p) ::SPEResponse : new ::SPEResponse;
   }
   static void *newArray_SPEResponse(Long_t nElements, void *p) {
      return p ? new(p) ::SPEResponse[nElements] : new ::SPEResponse[nElements];
   }
   // Wrapper around operator delete
   static void delete_SPEResponse(void *p) {
      delete (static_cast<::SPEResponse*>(p));
   }
   static void deleteArray_SPEResponse(void *p) {
      delete [] (static_cast<::SPEResponse*>(p));
   }
   static void destruct_SPEResponse(void *p) {
      typedef ::SPEResponse current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SPEResponse

//______________________________________________________________________________
void DFTmethod::Streamer(TBuffer &R__b)
{
   // Stream an object of class DFTmethod.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(DFTmethod::Class(),this);
   } else {
      R__b.WriteClassBuffer(DFTmethod::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_DFTmethod(void *p) {
      return  p ? new(p) ::DFTmethod : new ::DFTmethod;
   }
   static void *newArray_DFTmethod(Long_t nElements, void *p) {
      return p ? new(p) ::DFTmethod[nElements] : new ::DFTmethod[nElements];
   }
   // Wrapper around operator delete
   static void delete_DFTmethod(void *p) {
      delete (static_cast<::DFTmethod*>(p));
   }
   static void deleteArray_DFTmethod(void *p) {
      delete [] (static_cast<::DFTmethod*>(p));
   }
   static void destruct_DFTmethod(void *p) {
      typedef ::DFTmethod current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::DFTmethod

//______________________________________________________________________________
void NumIntegration::Streamer(TBuffer &R__b)
{
   // Stream an object of class NumIntegration.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(NumIntegration::Class(),this);
   } else {
      R__b.WriteClassBuffer(NumIntegration::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_NumIntegration(void *p) {
      return  p ? new(p) ::NumIntegration : new ::NumIntegration;
   }
   static void *newArray_NumIntegration(Long_t nElements, void *p) {
      return p ? new(p) ::NumIntegration[nElements] : new ::NumIntegration[nElements];
   }
   // Wrapper around operator delete
   static void delete_NumIntegration(void *p) {
      delete (static_cast<::NumIntegration*>(p));
   }
   static void deleteArray_NumIntegration(void *p) {
      delete [] (static_cast<::NumIntegration*>(p));
   }
   static void destruct_NumIntegration(void *p) {
      typedef ::NumIntegration current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::NumIntegration

//______________________________________________________________________________
void Pedestal::Streamer(TBuffer &R__b)
{
   // Stream an object of class Pedestal.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Pedestal::Class(),this);
   } else {
      R__b.WriteClassBuffer(Pedestal::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pedestal(void *p) {
      return  p ? new(p) ::Pedestal : new ::Pedestal;
   }
   static void *newArray_Pedestal(Long_t nElements, void *p) {
      return p ? new(p) ::Pedestal[nElements] : new ::Pedestal[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pedestal(void *p) {
      delete (static_cast<::Pedestal*>(p));
   }
   static void deleteArray_Pedestal(void *p) {
      delete [] (static_cast<::Pedestal*>(p));
   }
   static void destruct_Pedestal(void *p) {
      typedef ::Pedestal current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Pedestal

//______________________________________________________________________________
void PMT::Streamer(TBuffer &R__b)
{
   // Stream an object of class PMT.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PMT::Class(),this);
   } else {
      R__b.WriteClassBuffer(PMT::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PMT(void *p) {
      return  p ? new(p) ::PMT : new ::PMT;
   }
   static void *newArray_PMT(Long_t nElements, void *p) {
      return p ? new(p) ::PMT[nElements] : new ::PMT[nElements];
   }
   // Wrapper around operator delete
   static void delete_PMT(void *p) {
      delete (static_cast<::PMT*>(p));
   }
   static void deleteArray_PMT(void *p) {
      delete [] (static_cast<::PMT*>(p));
   }
   static void destruct_PMT(void *p) {
      typedef ::PMT current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::PMT

//______________________________________________________________________________
void PMTModel::Streamer(TBuffer &R__b)
{
   // Stream an object of class PMTModel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PMTModel::Class(),this);
   } else {
      R__b.WriteClassBuffer(PMTModel::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PMTModel(void *p) {
      return  p ? new(p) ::PMTModel : new ::PMTModel;
   }
   static void *newArray_PMTModel(Long_t nElements, void *p) {
      return p ? new(p) ::PMTModel[nElements] : new ::PMTModel[nElements];
   }
   // Wrapper around operator delete
   static void delete_PMTModel(void *p) {
      delete (static_cast<::PMTModel*>(p));
   }
   static void deleteArray_PMTModel(void *p) {
      delete [] (static_cast<::PMTModel*>(p));
   }
   static void destruct_PMTModel(void *p) {
      typedef ::PMTModel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::PMTModel

//______________________________________________________________________________
void SPEFitter::Streamer(TBuffer &R__b)
{
   // Stream an object of class SPEFitter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SPEFitter::Class(),this);
   } else {
      R__b.WriteClassBuffer(SPEFitter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SPEFitter(void *p) {
      return  p ? new(p) ::SPEFitter : new ::SPEFitter;
   }
   static void *newArray_SPEFitter(Long_t nElements, void *p) {
      return p ? new(p) ::SPEFitter[nElements] : new ::SPEFitter[nElements];
   }
   // Wrapper around operator delete
   static void delete_SPEFitter(void *p) {
      delete (static_cast<::SPEFitter*>(p));
   }
   static void deleteArray_SPEFitter(void *p) {
      delete [] (static_cast<::SPEFitter*>(p));
   }
   static void destruct_SPEFitter(void *p) {
      typedef ::SPEFitter current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SPEFitter

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = nullptr);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 425,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<double>","std::vector<double, std::allocator<double> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<double>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<double>*>(nullptr))->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete (static_cast<vector<double>*>(p));
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] (static_cast<vector<double>*>(p));
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace {
  void TriggerDictionaryInitialization_libPMTCalib_Impl() {
    static const char* headers[] = {
"src/DFTmethod.h",
"src/NumIntegration.h",
"src/PMT.h",
"src/PMTModel.h",
"src/PMTStyle.h",
"src/PMType.h",
"src/Pedestal.h",
"src/SPEFitter.h",
"src/SPEResponse.h",
nullptr
    };
    static const char* includePaths[] = {
"/opt/root/include/",
"//root/code/src/",
"/usr/include",
"/usr/include/gsl",
"/opt/root/include/",
"/root/code/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libPMTCalib dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$SPEResponse.h")))  __attribute__((annotate("$clingAutoload$src/DFTmethod.h")))  SPEResponse;
class __attribute__((annotate("$clingAutoload$src/DFTmethod.h")))  DFTmethod;
class __attribute__((annotate("$clingAutoload$src/NumIntegration.h")))  NumIntegration;
class __attribute__((annotate("$clingAutoload$Pedestal.h")))  __attribute__((annotate("$clingAutoload$src/PMT.h")))  Pedestal;
class __attribute__((annotate("$clingAutoload$src/PMT.h")))  PMT;
class __attribute__((annotate("$clingAutoload$src/PMTModel.h")))  PMTModel;
class __attribute__((annotate("$clingAutoload$src/SPEFitter.h")))  SPEFitter;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libPMTCalib dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "src/DFTmethod.h"
#include "src/NumIntegration.h"
#include "src/PMT.h"
#include "src/PMTModel.h"
#include "src/PMTStyle.h"
#include "src/PMType.h"
#include "src/Pedestal.h"
#include "src/SPEFitter.h"
#include "src/SPEResponse.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"DFTmethod", payloadCode, "@",
"NumIntegration", payloadCode, "@",
"PMT", payloadCode, "@",
"PMTModel", payloadCode, "@",
"Pedestal", payloadCode, "@",
"SPEFitter", payloadCode, "@",
"SPEResponse", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libPMTCalib",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libPMTCalib_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libPMTCalib_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libPMTCalib() {
  TriggerDictionaryInitialization_libPMTCalib_Impl();
}
