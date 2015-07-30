#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLorentzVector.h"

void sameSign(string leptonTeVPt, Double_t ptMin, Double_t ptMax, string inputFile)
{

  string sameSignFilename = "/tmp/gteix/" + leptonTeVPt + "SameSignPairNtuple.root";
  string oppositeSignFilename = "/tmp/gteix/" + leptonTeVPt + "OppositeSignPairNtuple.root";
  string allLeptonFilename = "/tmp/gteix/" + leptonTeVPt + "AllPairNtuple.root";

  TFile *f = TFile::Open(inputFile.c_str());
  TTree *tree = (TTree*)f->Get("Events");

  unsigned int runNum, lumiSec, evtNum, npv, pass;
  float npu=0, scale1fb=1, mass;
  int qtag, qprobe;
  TLorentzVector *tagTLV=0, *probeTLV=0;

  tree->Branch("runNum", &runNum, "runNum/i");
  tree->Branch("lumiSec", &lumiSec, "lumiSec/i");
  tree->Branch("evtNum", &evtNum, "evtNum/i");
  tree->Branch("npv", &npv, "npv/i");
  tree->Branch("pass", &pass, "pass/i");
  tree->Branch("npu", &npu, "npu/F");
  tree->Branch("scale1fb", &scale1fb, "scale1fb/F");
  tree->Branch("mass", &mass, "mass/F");
  tree->Branch("qtag", &qtag, "qtag/I");
  tree->Branch("qprobe", &qprobe, "qprobe/I");
  tree->Branch("tag", "TLorentzVector", &tagTLV);
  tree->Branch("probe", "TLorentzVector", &probeTLV);
  tree->SetBranchAddress("runNum", &runNum);
  tree->SetBranchAddress("lumiSec", &lumiSec);
  tree->SetBranchAddress("evtNum", &evtNum);
  tree->SetBranchAddress("npv", &npv);
  tree->SetBranchAddress("pass", &pass);
  tree->SetBranchAddress("npu", &npu);
  tree->SetBranchAddress("scale1fb", &scale1fb);
  tree->SetBranchAddress("mass", &mass);
  tree->SetBranchAddress("qtag", &qtag);
  tree->SetBranchAddress("qprobe", &qprobe);
  tree->SetBranchAddress("tag", &tagTLV);
  tree->SetBranchAddress("probe", &probeTLV);

  TFile *sameSignOutput = TFile::Open(sameSignFilename.c_str(),"RECREATE");
  TTree *sameSignLeptonTree = new TTree("Events", "Same sign muon pairs with Z_pt > 100GeV");
  sameSignLeptonTree->Branch("runNum", &runNum, "runNum/i");
  sameSignLeptonTree->Branch("lumiSec", &lumiSec, "lumiSec/i");
  sameSignLeptonTree->Branch("evtNum", &evtNum, "evtNum/i");
  sameSignLeptonTree->Branch("npv", &npv, "npv/i");
  sameSignLeptonTree->Branch("pass", &pass, "pass/i");
  sameSignLeptonTree->Branch("npu", &npu, "npu/F");
  sameSignLeptonTree->Branch("scale1fb", &scale1fb, "scale1fb/F");
  sameSignLeptonTree->Branch("mass", &mass, "mass/F");
  sameSignLeptonTree->Branch("qtag", &qtag, "qtag/I");
  sameSignLeptonTree->Branch("qprobe", &qprobe, "qprobe/I");
  sameSignLeptonTree->Branch("tag", "TLorentzVector", &tagTLV);
  sameSignLeptonTree->Branch("probe", "TLorentzVector", &probeTLV);
  sameSignLeptonTree->SetBranchAddress("runNum", &runNum);
  sameSignLeptonTree->SetBranchAddress("lumiSec", &lumiSec);
  sameSignLeptonTree->SetBranchAddress("evtNum", &evtNum);
  sameSignLeptonTree->SetBranchAddress("npv", &npv);
  sameSignLeptonTree->SetBranchAddress("pass", &pass);
  sameSignLeptonTree->SetBranchAddress("npu", &npu);
  sameSignLeptonTree->SetBranchAddress("scale1fb", &scale1fb);
  sameSignLeptonTree->SetBranchAddress("mass", &mass);
  sameSignLeptonTree->SetBranchAddress("qtag", &qtag);
  sameSignLeptonTree->SetBranchAddress("qprobe", &qprobe);
  sameSignLeptonTree->SetBranchAddress("tag", &tagTLV);
  sameSignLeptonTree->SetBranchAddress("probe", &probeTLV);

  TFile *oppositeSignOutput = TFile::Open(oppositeSignFilename.c_str(),"RECREATE");
  TTree *oppositeSignLeptonTree = new TTree("Events", "Opposite sign muon pairs with Z_pt > 100GeV");
  oppositeSignLeptonTree->Branch("runNum", &runNum, "runNum/i");
  oppositeSignLeptonTree->Branch("lumiSec", &lumiSec, "lumiSec/i");
  oppositeSignLeptonTree->Branch("evtNum", &evtNum, "evtNum/i");
  oppositeSignLeptonTree->Branch("npv", &npv, "npv/i");
  oppositeSignLeptonTree->Branch("pass", &pass, "pass/i");
  oppositeSignLeptonTree->Branch("npu", &npu, "npu/F");
  oppositeSignLeptonTree->Branch("scale1fb", &scale1fb, "scale1fb/F");
  oppositeSignLeptonTree->Branch("mass", &mass, "mass/F");
  oppositeSignLeptonTree->Branch("qtag", &qtag, "qtag/I");
  oppositeSignLeptonTree->Branch("qprobe", &qprobe, "qprobe/I");
  oppositeSignLeptonTree->Branch("tag", "TLorentzVector", &tagTLV);
  oppositeSignLeptonTree->Branch("probe", "TLorentzVector", &probeTLV);
  oppositeSignLeptonTree->SetBranchAddress("runNum", &runNum);
  oppositeSignLeptonTree->SetBranchAddress("lumiSec", &lumiSec);
  oppositeSignLeptonTree->SetBranchAddress("evtNum", &evtNum);
  oppositeSignLeptonTree->SetBranchAddress("npv", &npv);
  oppositeSignLeptonTree->SetBranchAddress("pass", &pass);
  oppositeSignLeptonTree->SetBranchAddress("npu", &npu);
  oppositeSignLeptonTree->SetBranchAddress("scale1fb", &scale1fb);
  oppositeSignLeptonTree->SetBranchAddress("mass", &mass);
  oppositeSignLeptonTree->SetBranchAddress("qtag", &qtag);
  oppositeSignLeptonTree->SetBranchAddress("qprobe", &qprobe);
  oppositeSignLeptonTree->SetBranchAddress("tag", &tagTLV);
  oppositeSignLeptonTree->SetBranchAddress("probe", &probeTLV);

  TFile *allLeptonOutput = TFile::Open(allLeptonFilename.c_str(),"RECREATE");
  TTree *allLeptonTree = new TTree("Events", "Leptonon pairs with Z_pt > 100GeV");
  allLeptonTree->Branch("runNum", &runNum, "runNum/i");
  allLeptonTree->Branch("lumiSec", &lumiSec, "lumiSec/i");
  allLeptonTree->Branch("evtNum", &evtNum, "evtNum/i");
  allLeptonTree->Branch("npv", &npv, "npv/i");
  allLeptonTree->Branch("pass", &pass, "pass/i");
  allLeptonTree->Branch("npu", &npu, "npu/F");
  allLeptonTree->Branch("scale1fb", &scale1fb, "scale1fb/F");
  allLeptonTree->Branch("mass", &mass, "mass/F");
  allLeptonTree->Branch("qtag", &qtag, "qtag/I");
  allLeptonTree->Branch("qprobe", &qprobe, "qprobe/I");
  allLeptonTree->Branch("tag", "TLorentzVector", &tagTLV);
  allLeptonTree->Branch("probe", "TLorentzVector", &probeTLV);
  allLeptonTree->SetBranchAddress("runNum", &runNum);
  allLeptonTree->SetBranchAddress("lumiSec", &lumiSec);
  allLeptonTree->SetBranchAddress("evtNum", &evtNum);
  allLeptonTree->SetBranchAddress("npv", &npv);
  allLeptonTree->SetBranchAddress("pass", &pass);
  allLeptonTree->SetBranchAddress("npu", &npu);
  allLeptonTree->SetBranchAddress("scale1fb", &scale1fb);
  allLeptonTree->SetBranchAddress("mass", &mass);
  allLeptonTree->SetBranchAddress("qtag", &qtag);
  allLeptonTree->SetBranchAddress("qprobe", &qprobe);
  allLeptonTree->SetBranchAddress("tag", &tagTLV);
  allLeptonTree->SetBranchAddress("probe", &probeTLV);


  Long64_t nentries = tree->GetEntries();

  for (Long64_t i=0; i<nentries; i++) {
    tree->GetEntry(i);
    TLorentzVector pairSystemTLV = *probeTLV + *tagTLV;
    if (ptMin < pairSystemTLV.Pt() < ptMax) {
      allLeptonTree->Fill();
      if (qtag+qprobe!=0) {
        sameSignLeptonTree->Fill();
      } else {
        oppositeSignLeptonTree->Fill();
      }
    }
  }

  sameSignOutput->cd();
  sameSignLeptonTree->Write();
  oppositeSignOutput->cd();
  oppositeSignLeptonTree->Write();
  allLeptonOutput->cd();
  allLeptonTree->Write();
  allLeptonOutput->Close();
  sameSignOutput->Close();
  oppositeSignOutput->Close();

}
