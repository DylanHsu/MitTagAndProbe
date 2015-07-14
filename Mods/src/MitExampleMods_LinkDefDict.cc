// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIdhsudIcmsdIcmsswdI041dICMSSW_7_4_6dItmpdIslc6_amd64_gcc491dIMitExampleMods_LinkDefDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
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

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "MitTagAndProbe/Mods/interface/EOverPMod.h"
#include "MitTagAndProbe/Mods/interface/NtuplesMod.h"
#include "MitTagAndProbe/Mods/interface/TriggerEfficiencyMod.h"

// Header files passed via #pragma extra_include

namespace mithep {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *mithep_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("mithep", 0 /*version*/, "MitAna/DataCont/interface/BaseCollection.h", 14,
                     ::ROOT::DefineBehavior((void*)0,(void*)0),
                     &mithep_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *mithep_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static void *new_mithepcLcLEOverPMod(void *p = 0);
   static void *newArray_mithepcLcLEOverPMod(Long_t size, void *p);
   static void delete_mithepcLcLEOverPMod(void *p);
   static void deleteArray_mithepcLcLEOverPMod(void *p);
   static void destruct_mithepcLcLEOverPMod(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mithep::EOverPMod*)
   {
      ::mithep::EOverPMod *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::mithep::EOverPMod >(0);
      static ::ROOT::TGenericClassInfo 
         instance("mithep::EOverPMod", ::mithep::EOverPMod::Class_Version(), "MitTagAndProbe/Mods/interface/EOverPMod.h", 12,
                  typeid(::mithep::EOverPMod), DefineBehavior(ptr, ptr),
                  &::mithep::EOverPMod::Dictionary, isa_proxy, 4,
                  sizeof(::mithep::EOverPMod) );
      instance.SetNew(&new_mithepcLcLEOverPMod);
      instance.SetNewArray(&newArray_mithepcLcLEOverPMod);
      instance.SetDelete(&delete_mithepcLcLEOverPMod);
      instance.SetDeleteArray(&deleteArray_mithepcLcLEOverPMod);
      instance.SetDestructor(&destruct_mithepcLcLEOverPMod);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mithep::EOverPMod*)
   {
      return GenerateInitInstanceLocal((::mithep::EOverPMod*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mithep::EOverPMod*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_mithepcLcLNtuplesMod(void *p = 0);
   static void *newArray_mithepcLcLNtuplesMod(Long_t size, void *p);
   static void delete_mithepcLcLNtuplesMod(void *p);
   static void deleteArray_mithepcLcLNtuplesMod(void *p);
   static void destruct_mithepcLcLNtuplesMod(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mithep::NtuplesMod*)
   {
      ::mithep::NtuplesMod *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::mithep::NtuplesMod >(0);
      static ::ROOT::TGenericClassInfo 
         instance("mithep::NtuplesMod", ::mithep::NtuplesMod::Class_Version(), "MitTagAndProbe/Mods/interface/NtuplesMod.h", 15,
                  typeid(::mithep::NtuplesMod), DefineBehavior(ptr, ptr),
                  &::mithep::NtuplesMod::Dictionary, isa_proxy, 4,
                  sizeof(::mithep::NtuplesMod) );
      instance.SetNew(&new_mithepcLcLNtuplesMod);
      instance.SetNewArray(&newArray_mithepcLcLNtuplesMod);
      instance.SetDelete(&delete_mithepcLcLNtuplesMod);
      instance.SetDeleteArray(&deleteArray_mithepcLcLNtuplesMod);
      instance.SetDestructor(&destruct_mithepcLcLNtuplesMod);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mithep::NtuplesMod*)
   {
      return GenerateInitInstanceLocal((::mithep::NtuplesMod*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mithep::NtuplesMod*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_mithepcLcLTriggerEfficiencyMod(void *p = 0);
   static void *newArray_mithepcLcLTriggerEfficiencyMod(Long_t size, void *p);
   static void delete_mithepcLcLTriggerEfficiencyMod(void *p);
   static void deleteArray_mithepcLcLTriggerEfficiencyMod(void *p);
   static void destruct_mithepcLcLTriggerEfficiencyMod(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mithep::TriggerEfficiencyMod*)
   {
      ::mithep::TriggerEfficiencyMod *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::mithep::TriggerEfficiencyMod >(0);
      static ::ROOT::TGenericClassInfo 
         instance("mithep::TriggerEfficiencyMod", ::mithep::TriggerEfficiencyMod::Class_Version(), "MitTagAndProbe/Mods/interface/TriggerEfficiencyMod.h", 15,
                  typeid(::mithep::TriggerEfficiencyMod), DefineBehavior(ptr, ptr),
                  &::mithep::TriggerEfficiencyMod::Dictionary, isa_proxy, 4,
                  sizeof(::mithep::TriggerEfficiencyMod) );
      instance.SetNew(&new_mithepcLcLTriggerEfficiencyMod);
      instance.SetNewArray(&newArray_mithepcLcLTriggerEfficiencyMod);
      instance.SetDelete(&delete_mithepcLcLTriggerEfficiencyMod);
      instance.SetDeleteArray(&deleteArray_mithepcLcLTriggerEfficiencyMod);
      instance.SetDestructor(&destruct_mithepcLcLTriggerEfficiencyMod);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mithep::TriggerEfficiencyMod*)
   {
      return GenerateInitInstanceLocal((::mithep::TriggerEfficiencyMod*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mithep::TriggerEfficiencyMod*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace mithep {
//______________________________________________________________________________
atomic_TClass_ptr EOverPMod::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EOverPMod::Class_Name()
{
   return "mithep::EOverPMod";
}

//______________________________________________________________________________
const char *EOverPMod::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::mithep::EOverPMod*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EOverPMod::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::mithep::EOverPMod*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EOverPMod::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::mithep::EOverPMod*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EOverPMod::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::mithep::EOverPMod*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace mithep
namespace mithep {
//______________________________________________________________________________
atomic_TClass_ptr NtuplesMod::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *NtuplesMod::Class_Name()
{
   return "mithep::NtuplesMod";
}

//______________________________________________________________________________
const char *NtuplesMod::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::mithep::NtuplesMod*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int NtuplesMod::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::mithep::NtuplesMod*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *NtuplesMod::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::mithep::NtuplesMod*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *NtuplesMod::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::mithep::NtuplesMod*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace mithep
namespace mithep {
//______________________________________________________________________________
atomic_TClass_ptr TriggerEfficiencyMod::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TriggerEfficiencyMod::Class_Name()
{
   return "mithep::TriggerEfficiencyMod";
}

//______________________________________________________________________________
const char *TriggerEfficiencyMod::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::mithep::TriggerEfficiencyMod*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TriggerEfficiencyMod::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::mithep::TriggerEfficiencyMod*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TriggerEfficiencyMod::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::mithep::TriggerEfficiencyMod*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TriggerEfficiencyMod::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::mithep::TriggerEfficiencyMod*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace mithep
namespace mithep {
//______________________________________________________________________________
void EOverPMod::Streamer(TBuffer &R__b)
{
   // Stream an object of class mithep::EOverPMod.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(mithep::EOverPMod::Class(),this);
   } else {
      R__b.WriteClassBuffer(mithep::EOverPMod::Class(),this);
   }
}

} // namespace mithep
namespace ROOT {
   // Wrappers around operator new
   static void *new_mithepcLcLEOverPMod(void *p) {
      return  p ? new(p) ::mithep::EOverPMod : new ::mithep::EOverPMod;
   }
   static void *newArray_mithepcLcLEOverPMod(Long_t nElements, void *p) {
      return p ? new(p) ::mithep::EOverPMod[nElements] : new ::mithep::EOverPMod[nElements];
   }
   // Wrapper around operator delete
   static void delete_mithepcLcLEOverPMod(void *p) {
      delete ((::mithep::EOverPMod*)p);
   }
   static void deleteArray_mithepcLcLEOverPMod(void *p) {
      delete [] ((::mithep::EOverPMod*)p);
   }
   static void destruct_mithepcLcLEOverPMod(void *p) {
      typedef ::mithep::EOverPMod current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mithep::EOverPMod

namespace mithep {
//______________________________________________________________________________
void NtuplesMod::Streamer(TBuffer &R__b)
{
   // Stream an object of class mithep::NtuplesMod.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(mithep::NtuplesMod::Class(),this);
   } else {
      R__b.WriteClassBuffer(mithep::NtuplesMod::Class(),this);
   }
}

} // namespace mithep
namespace ROOT {
   // Wrappers around operator new
   static void *new_mithepcLcLNtuplesMod(void *p) {
      return  p ? new(p) ::mithep::NtuplesMod : new ::mithep::NtuplesMod;
   }
   static void *newArray_mithepcLcLNtuplesMod(Long_t nElements, void *p) {
      return p ? new(p) ::mithep::NtuplesMod[nElements] : new ::mithep::NtuplesMod[nElements];
   }
   // Wrapper around operator delete
   static void delete_mithepcLcLNtuplesMod(void *p) {
      delete ((::mithep::NtuplesMod*)p);
   }
   static void deleteArray_mithepcLcLNtuplesMod(void *p) {
      delete [] ((::mithep::NtuplesMod*)p);
   }
   static void destruct_mithepcLcLNtuplesMod(void *p) {
      typedef ::mithep::NtuplesMod current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mithep::NtuplesMod

namespace mithep {
//______________________________________________________________________________
void TriggerEfficiencyMod::Streamer(TBuffer &R__b)
{
   // Stream an object of class mithep::TriggerEfficiencyMod.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(mithep::TriggerEfficiencyMod::Class(),this);
   } else {
      R__b.WriteClassBuffer(mithep::TriggerEfficiencyMod::Class(),this);
   }
}

} // namespace mithep
namespace ROOT {
   // Wrappers around operator new
   static void *new_mithepcLcLTriggerEfficiencyMod(void *p) {
      return  p ? new(p) ::mithep::TriggerEfficiencyMod : new ::mithep::TriggerEfficiencyMod;
   }
   static void *newArray_mithepcLcLTriggerEfficiencyMod(Long_t nElements, void *p) {
      return p ? new(p) ::mithep::TriggerEfficiencyMod[nElements] : new ::mithep::TriggerEfficiencyMod[nElements];
   }
   // Wrapper around operator delete
   static void delete_mithepcLcLTriggerEfficiencyMod(void *p) {
      delete ((::mithep::TriggerEfficiencyMod*)p);
   }
   static void deleteArray_mithepcLcLTriggerEfficiencyMod(void *p) {
      delete [] ((::mithep::TriggerEfficiencyMod*)p);
   }
   static void destruct_mithepcLcLTriggerEfficiencyMod(void *p) {
      typedef ::mithep::TriggerEfficiencyMod current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mithep::TriggerEfficiencyMod

namespace {
  void TriggerDictionaryInitialization_MitExampleMods_LinkDefDict_Impl() {
    static const char* headers[] = {
"MitTagAndProbe/Mods/interface/EOverPMod.h",
"MitTagAndProbe/Mods/interface/NtuplesMod.h",
"MitTagAndProbe/Mods/interface/TriggerEfficiencyMod.h",
0
    };
    static const char* includePaths[] = {
"/home/dhsu/cms/cmssw/041/CMSSW_7_4_6/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd4/include",
"/home/dhsu/cms/cmssw/041/CMSSW_7_4_6/src/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace mithep{class __attribute__((annotate("$clingAutoload$MitTagAndProbe/Mods/dict/MitExampleModsLinkDef.h")))  EOverPMod;}
namespace mithep{class __attribute__((annotate("$clingAutoload$MitTagAndProbe/Mods/dict/MitExampleModsLinkDef.h")))  NtuplesMod;}
namespace mithep{class __attribute__((annotate("$clingAutoload$MitTagAndProbe/Mods/dict/MitExampleModsLinkDef.h")))  TriggerEfficiencyMod;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "MitTagAndProbe/Mods/interface/EOverPMod.h"
#include "MitTagAndProbe/Mods/interface/NtuplesMod.h"
#include "MitTagAndProbe/Mods/interface/TriggerEfficiencyMod.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"mithep::EOverPMod", payloadCode, "@",
"mithep::NtuplesMod", payloadCode, "@",
"mithep::TriggerEfficiencyMod", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("MitExampleMods_LinkDefDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_MitExampleMods_LinkDefDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_MitExampleMods_LinkDefDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_MitExampleMods_LinkDefDict() {
  TriggerDictionaryInitialization_MitExampleMods_LinkDefDict_Impl();
}
