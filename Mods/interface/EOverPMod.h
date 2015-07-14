#ifndef MITEXAMPLE_MODS_EOVERPMOD_H
#define MITEXAMPLE_MODS_EOVERPMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/ElectronCol.h"

#include "TH1D.h"
#include "TString.h"

namespace mithep {
  
  class EOverPMod : public BaseMod {
  public:
    EOverPMod(char const* name = "EOverPMod", char const* title = "E/P plot");
    ~EOverPMod();

  protected:
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    TString fElectronsName;

    mithep::ElectronCol const* fElectrons;

    TH1D* hAbsence;
    TH1D* hEOverP;

    ClassDef(EOverPMod, 0)
  };

}

#endif
