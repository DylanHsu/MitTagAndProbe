#ifndef MIT_TAGANDPROBE_MODS_ELECTRON_NTUPLES_MOD_H
#define MIT_TAGANDPROBE_MODS_ELECTRON_NTUPLES_MOD_H
#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/ElectronCol.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#include "MitPhysics/Utils/interface/ElectronTools.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitAna/DataTree/interface/VertexFwd.h" 
#include "TLorentzVector.h"
#include "TTree.h"
#include "TString.h"

namespace mithep {
  
  class ElectronNtuples : public BaseMod {
  public:
    ElectronNtuples(char const* name = "ElectronNtuples", char const* title = "Flat-tree ntuples producer");
    void SetTagElectronsName(char const* _name) { fTagElectronsName = _name; }
    void SetProbeElectronsName(char const* _name) { fProbeElectronsName = _name; }
    void SetAllElectronsName(char const* _name) { fAllElectronsName = _name; }
    void SetTriggerObjectsName(char const* _name) { fTriggerObjectsName = _name; }
    void SetTriggerMatchName(char const* _name) { fTriggerMatchName = _name; }
    void SetPVName(const char *n)             { fPVName = n;                }

  protected:
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    TString fTagElectronsName;
    TString fProbeElectronsName;
    TString fAllElectronsName;
    TString fTriggerObjectsName;
    TString fTriggerMatchName;
    TString fPVName;  

    TTree* fNtuplesTree;
    unsigned int runNum, lumiSec, evtNum;   // event ID
    unsigned int npv;                       // number of primary vertices
    unsigned int pass;                      // whether probe passes requirements
    float        npu;                       // mean number of expected pileup
    float        scale1fb;                  // event weight per 1/fb
    float        mass;                      // tag-probe mass
    int          qtag, qprobe;              // tag, probe charge
    TLorentzVector *tagTLV=0, *probeTLV=0;        // tag, probe 4-vector
    ClassDef(ElectronNtuples, 0)
  };

}

#endif
