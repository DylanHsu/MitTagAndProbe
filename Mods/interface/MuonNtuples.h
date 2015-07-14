#ifndef MITEXAMPLE_MODS_NTUPLESMOD_H
#define MITEXAMPLE_MODS_NTUPLESMOD_H
#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/MuonCol.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#include "MitPhysics/Utils/interface/MuonTools.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitAna/DataTree/interface/VertexFwd.h" 
#include "TLorentzVector.h"
#include "TTree.h"
#include "TString.h"

namespace mithep {
  
  class MuonNtuples : public BaseMod {
  public:
    MuonNtuples(char const* name = "MuonNtuples", char const* title = "Flat-tree ntuples producer");
    void SetTagMuonsName(char const* _name) { fTagMuonsName = _name; }
    void SetProbeMuonsName(char const* _name) { fProbeMuonsName = _name; }
    void SetAllMuonsName(char const* _name) { fAllMuonsName = _name; }
    void SetTriggerObjectsName(char const* _name) { fTriggerObjectsName = _name; }
    void SetTriggerMatchName(char const* _name) { fTriggerMatchName = _name; }
    void SetPVName(const char *n)             { fPVName = n;                }

  protected:
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    TString fTagMuonsName;
    TString fProbeMuonsName;
    TString fAllMuonsName;
    TString fTriggerObjectsName;
    TString fTriggerMatchName;
    TString fPVName;  

    //TnPEvent fPassingEvent;
    //TnPEvent fAllEvent;
    //TTree* fPassingNtuples;
    //TTree* fAllNtuples;
    TTree* fNtuplesTree;
    unsigned int runNum, lumiSec, evtNum;   // event ID
    unsigned int npv;                       // number of primary vertices
    unsigned int pass;                      // whether probe passes requirements
    float        npu;                       // mean number of expected pileup
    float        scale1fb;                  // event weight per 1/fb
    float        mass;                      // tag-probe mass
    int          qtag, qprobe;              // tag, probe charge
    TLorentzVector *tagTLV=0, *probeTLV=0;        // tag, probe 4-vector
    ClassDef(MuonNtuples, 0)
  };

}

#endif
