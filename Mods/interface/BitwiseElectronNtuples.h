#ifndef MIT_TAGANDPROBE_MODS_BITWISE_ELECTRON_NTUPLES_MOD_H
#define MIT_TAGANDPROBE_MODS_BITWISE_ELECTRON_NTUPLES_MOD_H
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
  
  class BitwiseElectronNtuples : public BaseMod {
  public:
    BitwiseElectronNtuples(char const* name = "BitwiseElectronNtuples", char const* title = "Flat-tree ntuples producer");
    void SetAllElectronsName(char const* _name) { fAllElectronsName = _name; }
    void SetTriggerObjectsName(char const* _name) { fTriggerObjectsName = _name; }
    void SetPVName(const char *n)             { fPVName = n;                }
    void AddIdFlag(std::string name, ElectronTools::EElIdType IdType);
    void AddIsoFlag(std::string name, ElectronTools::EElIsoType IsoType);
  protected:
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    TString fAllElectronsName;
    TString fTriggerObjectsName;
    TString fPVName;  
    TTree* fNtuplesTree;
    TTree* fPropertiesTree;
    TH1F* fIdHisto, *fIsoHisto;
    
    vector<std::string> ElIdTypeNames;
    vector<std::string> ElIsoTypeNames;
    vector<ElectronTools::EElIdType> ElIdTypes;
    vector<ElectronTools::EElIsoType> ElIsoTypes;
    vector< vector<bool> > ElIdTypeBits_;
    vector< vector<bool> > ElIsoTypeBits_;
    unsigned int NIdTypes    = 0; 
    unsigned int NIsoTypes   = 0;
    
    unsigned int runNum, lumiSec, evtNum; 
    unsigned int npv;                     
    std::vector<int> charge_;             
    std::vector<TLorentzVector*> fourMomentum_;
    ClassDef(BitwiseElectronNtuples, 0)
  };

}

#endif
