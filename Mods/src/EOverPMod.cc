#include "MitTagAndProbe/Mods/interface/EOverPMod.h"

ClassImp(mithep::EOverPMod)

namespace mithep {

  EOverPMod::EOverPMod(char const* name, char const* title) :
    BaseMod(name, title),
    fElectronsName("Electrons"),
    fElectrons(0),
    hAbsence(0),
    hEOverP(0)
  {
  }

  EOverPMod::~EOverPMod()
  {
  }

  void
  EOverPMod::Process()
  {
    LoadBranch(fElectronsName);

    if (!fElectrons) {
      std::cerr << "Failed to load electrons" << std::endl;
      return;
    }

    for (unsigned iE(0); iE != fElectrons->GetEntries(); ++iE) {
      mithep::Electron const& ele(*fElectrons->At(iE));

      mithep::SuperCluster const* sc(ele.SCluster());
      mithep::Track const* trk(ele.GsfTrk());

      if (sc && trk)
        hEOverP->Fill(sc->Energy() / trk->P());
      else {
        if (!sc && !trk)
          hAbsence->Fill(0);
        else if (!trk)
          hAbsence->Fill(1);
        else
          hAbsence->Fill(2);
      }
    }
  }

  void
  EOverPMod::SlaveBegin()
  {
    AddTH1(hAbsence, "abs", "Missing objects", 3, 0., 3.);
    hAbsence->GetXaxis()->SetBinLabel(1, "!sc && !trk");
    hAbsence->GetXaxis()->SetBinLabel(2, "sc && !trk");
    hAbsence->GetXaxis()->SetBinLabel(3, "!sc && trk");
    AddTH1(hEOverP, "eoverp", "E/P", 100, 0., 3.);
    
    ReqBranch(fElectronsName, fElectrons);
  }

  void
  EOverPMod::SlaveTerminate()
  {
  }

}
