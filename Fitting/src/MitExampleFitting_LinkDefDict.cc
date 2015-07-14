// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIdhsudIcmsdIcmsswdI041dICMSSW_7_4_6dItmpdIslc6_amd64_gcc491dIMitExampleFitting_LinkDefDict

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
#include "MitTagAndProbe/Fitting/interface/FittingUtils.h"

// Header files passed via #pragma extra_include

namespace mithep {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *mithep_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("mithep", 0 /*version*/, "MitTagAndProbe/Fitting/interface/FittingUtils.h", 8,
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
   static TClass *mithepcLcLFittingUtils_Dictionary();
   static void mithepcLcLFittingUtils_TClassManip(TClass*);
   static void *new_mithepcLcLFittingUtils(void *p = 0);
   static void *newArray_mithepcLcLFittingUtils(Long_t size, void *p);
   static void delete_mithepcLcLFittingUtils(void *p);
   static void deleteArray_mithepcLcLFittingUtils(void *p);
   static void destruct_mithepcLcLFittingUtils(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mithep::FittingUtils*)
   {
      ::mithep::FittingUtils *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::mithep::FittingUtils));
      static ::ROOT::TGenericClassInfo 
         instance("mithep::FittingUtils", "MitTagAndProbe/Fitting/interface/FittingUtils.h", 10,
                  typeid(::mithep::FittingUtils), DefineBehavior(ptr, ptr),
                  &mithepcLcLFittingUtils_Dictionary, isa_proxy, 4,
                  sizeof(::mithep::FittingUtils) );
      instance.SetNew(&new_mithepcLcLFittingUtils);
      instance.SetNewArray(&newArray_mithepcLcLFittingUtils);
      instance.SetDelete(&delete_mithepcLcLFittingUtils);
      instance.SetDeleteArray(&deleteArray_mithepcLcLFittingUtils);
      instance.SetDestructor(&destruct_mithepcLcLFittingUtils);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mithep::FittingUtils*)
   {
      return GenerateInitInstanceLocal((::mithep::FittingUtils*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mithep::FittingUtils*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *mithepcLcLFittingUtils_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::mithep::FittingUtils*)0x0)->GetClass();
      mithepcLcLFittingUtils_TClassManip(theClass);
   return theClass;
   }

   static void mithepcLcLFittingUtils_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_mithepcLcLFittingUtils(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::mithep::FittingUtils : new ::mithep::FittingUtils;
   }
   static void *newArray_mithepcLcLFittingUtils(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::mithep::FittingUtils[nElements] : new ::mithep::FittingUtils[nElements];
   }
   // Wrapper around operator delete
   static void delete_mithepcLcLFittingUtils(void *p) {
      delete ((::mithep::FittingUtils*)p);
   }
   static void deleteArray_mithepcLcLFittingUtils(void *p) {
      delete [] ((::mithep::FittingUtils*)p);
   }
   static void destruct_mithepcLcLFittingUtils(void *p) {
      typedef ::mithep::FittingUtils current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mithep::FittingUtils

namespace {
  void TriggerDictionaryInitialization_MitExampleFitting_LinkDefDict_Impl() {
    static const char* headers[] = {
"MitTagAndProbe/Fitting/interface/FittingUtils.h",
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
namespace mithep{class __attribute__((annotate("$clingAutoload$MitTagAndProbe/Fitting/dict/MitExampleFittingLinkDef.h")))  FittingUtils;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "MitTagAndProbe/Fitting/interface/FittingUtils.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"mithep::FittingUtils", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("MitExampleFitting_LinkDefDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_MitExampleFitting_LinkDefDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_MitExampleFitting_LinkDefDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_MitExampleFitting_LinkDefDict() {
  TriggerDictionaryInitialization_MitExampleFitting_LinkDefDict_Impl();
}
