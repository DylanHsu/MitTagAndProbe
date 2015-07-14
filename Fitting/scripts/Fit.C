#include "TFile.h"
#include "TSystem.h"
#include "TMath.h"

void Fit(char* filename) {
    // Load file and trees
    cout << "test0";
    TFile *file = new TFile(filename);
    TTree *t_passing = (TTree*)file->Get("HLTMod/GoodPVFilterMod/MuonIDMod/MuonIDMod/NtuplesMod/passing_probe_events");
    TTree *t_all = (TTree*)file->Get("HLTMod/GoodPVFilterMod/MuonIDMod/MuonIDMod/NtuplesMod/all_tagged_events");
    // Init. dummy variables
    UInt_t n_pairs;
    Float_t tag_px[64], tag_py[64], tag_pz[64], tag_E[64], probe_px[64], probe_py[64], probe_pz[64], probe_E[64]; 

    // set branch addresses for the trees
    // when we read each tree entry, these variables get filled
    t_passing->SetBranchAddress("tag.px",tag_px); 
    t_passing->SetBranchAddress("tag.py",tag_py);
    t_passing->SetBranchAddress("tag.pz",tag_pz);
    t_passing->SetBranchAddress("tag.energy",tag_E);
    t_passing->SetBranchAddress("probe.px",probe_px); 
    t_passing->SetBranchAddress("probe.py",probe_py);
    t_passing->SetBranchAddress("probe.pz",probe_pz);
    t_passing->SetBranchAddress("probe.energy",probe_E);
    t_passing->SetBranchAddress("nPairs",&n_pairs);
    t_all->SetBranchAddress("tag.px",tag_px); 
    t_all->SetBranchAddress("tag.py",tag_py);
    t_all->SetBranchAddress("tag.pz",tag_pz);
    t_all->SetBranchAddress("tag.energy",tag_E);
    t_all->SetBranchAddress("probe.px",probe_px); 
    t_all->SetBranchAddress("probe.py",probe_py);
    t_all->SetBranchAddress("probe.pz",probe_pz);
    t_all->SetBranchAddress("probe.energy",probe_E);
    t_all->SetBranchAddress("nPairs",&n_pairs);
    
    // init. histos
    TH1F *h_mass_passing = new TH1F("h_mass_passing","Invariant mass for pairs passing probe",300,0,300);
    TH1F *h_mass_failing = new TH1F("h_mass_failing","Invariant mass for pairs failing probe",300,0,300);
    TH1F *h_mass_all = new TH1F("h_mass_all","Invariant mass for all pairs",300,0,300);
    
 
    // fill invariant mass histogram for passing probe
    Int_t N_passing = (Int_t)t_passing->GetEntries();
    for(Int_t i=0; i<N_passing; i++) {
        t_passing->GetEntry(i);
        t_passing->GetEntry(i);
        if(n_pairs>0){ for(Int_t j=0; j<n_pairs; j++) {
            Float_t px = tag_px[j] + probe_px[j];
            Float_t py = tag_py[j] + probe_py[j];
            Float_t pz = tag_pz[j] + probe_pz[j];
            Float_t E  = tag_E[j]  + probe_E[j];
            //Float_t M = sqrt(E[j]*E[j] - px[j]*px[j] - py[j]*py[j] - pz[j]*pz[j]);
            Float_t M = sqrt(E*E - px*px - py*py - pz*pz);
            h_mass_passing->Fill(M);
        }}
    }

    // fill invariant mass histogram for all pairs
    Int_t N_all = (Int_t)t_all->GetEntries();
    cout << "start filling some histograms\n" << N_all << " entries in t_all\n\n";
    for(Int_t i=0; i<N_all; i++) {
        t_all->GetEntry(i);
        if(n_pairs>0){ for(Int_t j=0; j<n_pairs; j++) {
            Float_t px = tag_px[j] + probe_px[j];
            Float_t py = tag_py[j] + probe_py[j];
            Float_t pz = tag_pz[j] + probe_pz[j];
            Float_t E  = tag_E[j]  + probe_E[j];
            //Float_t M = sqrt(E[j]*E[j] - px[j]*px[j] - py[j]*py[j] - pz[j]*pz[j]);
            Float_t M = sqrt(E*E - px*px - py*py - pz*pz);
            h_mass_all->Fill(M);
            h_mass_failing->Fill(M);
        }}
    }
    TF1 *model_passing=new TF1("model_passing","[0]*TMath::BreitWigner(x,[1],[2])+[3]*exp([4]*(x-[5]))",0,300);
    TF1 *model_failing=new TF1("model_failing","[0]*TMath::BreitWigner(x,[1],[2])+[3]*exp([4]*(x-[5]))",0,300);
    TF1 *model_all=new TF1("model_all","[0]*TMath::BreitWigner(x,[1],[2])+[3]*exp([4]*(x-[5]))",0,300);
    model_passing->SetNpx(10000);
    model_failing->SetNpx(10000);
    model_all->SetNpx(10000);
    Double_t x = h_mass_failing->GetBinCenter(h_mass_failing->GetMaximumBin());
    Double_t hx = h_mass_failing->GetBinContent(h_mass_failing->GetMaximumBin());
    Double_t M_mu = 91.1;
    Double_t Y  = 10;
    Double_t y = sqrt(M_mu*M_mu*(M_mu*M_mu + Y*Y));
    Double_t k = sqrt(8)*M_mu*Y*y/(3.14159*sqrt(M_mu*M_mu+y));
    Double_t peak = k / (M_mu*M_mu*Y*Y);
    Double_t passing_amplitude = h_mass_passing->GetBinContent(h_mass_passing->GetMaximumBin()) / peak;

    Double_t params_passing[6]={passing_amplitude,M_mu,Y,.1*hx,-1,0};
    Double_t params_failing[6]={.1*passing_amplitude,91.1,10,hx,-1,x};
    model_passing->SetParameters(params_passing);
    model_failing->SetParameters(params_failing);
    //model_failing->FixParameter(0,0);
    h_mass_failing->Add(h_mass_passing,-1);
    
    TCanvas *c1=new TCanvas;
    h_mass_failing->Draw();
    h_mass_failing->Fit(model_failing, "M", "l",x,300);
    
    TCanvas *c2=new TCanvas;
    h_mass_passing->Draw();
    h_mass_passing->Fit(model_passing,"M","l",x,300);
    
    model_all->SetParameter(1, model_passing->GetParameter(1));
    model_all->SetParameter(2, model_passing->GetParameter(2));
    model_all->SetParameter(3, model_passing->GetParameter(3));
    model_all->SetParameter(4, model_failing->GetParameter(4));
    model_all->SetParameter(5, model_failing->GetParameter(5));
    model_all->SetParameter(6, model_failing->GetParameter(6));

    TCanvas *c3=new TCanvas;
    h_mass_all->Draw();
    h_mass_all->Fit(model_all, "M","l",x,300);
    

    TF1 *signal_passing = model_passing;
    TF1 *signal_all = model_all;
    signal_passing->SetParameter(3,0);
    signal_all->SetParameter(3,0);

    Double_t efficiency = signal_passing->Integral(0,300) / signal_all->Integral(0,300);
    cout << "\nCalculated Efficiency: "<<efficiency<<"\n\n";
}
