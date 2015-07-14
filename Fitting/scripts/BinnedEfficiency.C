#include "TFile.h"
#include "TSystem.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1D.h"
#include "TFitResultPtr.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TTree.h"

bool efficiency_fit( TH1D *h_mass_passing, TH1D *h_mass_failing, TH1D *h_mass_all, Double_t *efficiency_info,  const char* fit_options="M0QS", bool draw=false) {
    // Function for fitting to the three invariant mass spectra {passing probe, failing probe, & both}
    // Takes 3 histos
    // Returns the efficiency and the error in an array
    
    TF1 *model_passing  = new TF1("model_passing","[0]*TMath::BreitWigner(x,[1],[2])+[3]*exp([4]*(x-[5]))",0,300);
    TF1 *model_failing  = new TF1("model_failing","[0]*TMath::BreitWigner(x,[1],[2])+[3]*exp([4]*(x-[5]))",0,300);
    TF1 *model_all      = new TF1("model_all","[0]*TMath::BreitWigner(x,[1],[2])+[3]*exp([4]*(x-[5]))",0,300);
    // Get nice fits/functions
    model_passing   ->SetNpx(10000);
    model_failing   ->SetNpx(10000);
    model_all       ->SetNpx(10000);
    model_passing   ->SetNumberFitPoints(10000);
    model_failing   ->SetNumberFitPoints(10000);
    model_all       ->SetNumberFitPoints(10000);
    // Interpolate noise bkg at max point
    h_mass_failing->SetAxisRange(0,70);
    Double_t x = h_mass_failing->GetBinCenter(h_mass_failing->GetMaximumBin());
    Double_t hx = h_mass_failing->GetBinContent(h_mass_failing->GetMaximumBin());
    h_mass_failing->SetAxisRange(0,300);
    // Calculate BW peak value
    Double_t M_mu=91.1;
    Double_t Y=10;
    Double_t y = sqrt(M_mu*M_mu*(M_mu*M_mu + Y*Y));
    Double_t k = sqrt(8)*M_mu*Y*y/(3.14159*sqrt(M_mu*M_mu+y));
    Double_t peak = k / (M_mu*M_mu*Y*Y);
    Double_t passing_amplitude = h_mass_passing->GetBinContent(h_mass_passing->GetMaximumBin()) / peak;
    // Initialize params
    Double_t params_passing[6]={passing_amplitude,M_mu,Y,.1*hx,-1,0};
    Double_t params_failing[6]={.1*passing_amplitude,91.1,10,hx,-1,x};
    model_passing->SetParameters(params_passing);
    model_failing->SetParameters(params_failing);
    
    model_passing->SetParLimits(0,0,pow(10,12));
    model_failing->SetParLimits(0,0,pow(10,12));
    model_all->SetParLimits(0,0,pow(10,12));
    
    model_passing->SetParLimits(1,80,100);
    model_failing->SetParLimits(1,80,100);
    model_all->SetParLimits(1,80,100);
    
    model_passing->SetParLimits(5,0,80);
    model_failing->SetParLimits(5,0,80);
    

    TFitResultPtr frp_failing = h_mass_failing->Fit(model_failing,fit_options,"",x,300);
    TFitResultPtr frp_passing = h_mass_passing->Fit(model_passing,fit_options,"",x,300);
    TF1 *signal_passing  = new TF1("signal_passing","[0]*TMath::BreitWigner(x,[1],[2])+[3]*exp([4]*(x-[5]))",0,300);
    signal_passing->SetParameter(0, model_passing->GetParameter(0));
    signal_passing->SetParameter(1, model_passing->GetParameter(1));
    signal_passing->SetParameter(2, model_passing->GetParameter(2));
    signal_passing->SetParameter(3, 0);
    // Use parameters from individual passing/failing fits to inform the combined fit
    model_all->SetParameter(0,  model_passing->GetParameter(0)  );
    model_all->SetParameter(1,  model_passing->GetParameter(1)  );   
    model_all->SetParameter(2,  model_passing->GetParameter(2)  );   
    model_all->SetParameter(3,  model_failing->GetParameter(3)  );   
    model_all->SetParameter(4,  model_failing->GetParameter(4)  );   
    model_all->SetParameter(5,  model_failing->GetParameter(5)  );  
    TFitResultPtr frp_all = h_mass_all->Fit(model_all,fit_options,"",x,300);
    TF1 *signal_all  = new TF1("signal_all","[0]*TMath::BreitWigner(x,[1],[2])+[3]*exp([4]*(x-[5]))",0,300);
    signal_all->SetParameter(0, model_all->GetParameter(0));
    signal_all->SetParameter(1, model_all->GetParameter(1));
    signal_all->SetParameter(2, model_all->GetParameter(2));
    signal_all->SetParameter(3, 0);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // get the signal yields, errors, efficiency
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Double_t epsilon = pow(10,-10);
    Double_t A_par,Gamma_par,dI_dA,dI_dGamma,sigma_A,sigma_Gamma;
    
    // Get first order passing error
    Double_t  passing_yield = signal_passing->Integral(0,300);

    A_par       = model_passing->GetParameter(0);
    Gamma_par   = model_passing->GetParameter(2);
    sigma_A     = model_passing->GetParError(0);
    sigma_Gamma = model_passing->GetParError(2);

    signal_passing->SetParameter(0,A_par+epsilon);
    dI_dA = ( signal_passing->Integral(0,300) - passing_yield ) / epsilon;
    signal_passing->SetParameter(0,A_par);
    signal_passing->SetParameter(2,Gamma_par+epsilon);
    dI_dGamma = ( signal_passing->Integral(0,300) - passing_yield ) / epsilon;
    signal_passing->SetParameter(2,Gamma_par);

    Double_t passing_error = fabs(dI_dA)*sigma_A + fabs(dI_dGamma)*sigma_Gamma;
    
    printf("Passing error = %f * %f + %f * %f = %f\n",fabs(dI_dA),sigma_A,fabs(dI_dGamma),sigma_Gamma,passing_error);
    
    // Get first order error for all pairs
    Double_t all_yield = signal_all->Integral(0,300);
    A_par       = model_all->GetParameter(0);
    Gamma_par   = model_all->GetParameter(2);
    sigma_A     = model_all->GetParError(0);
    sigma_Gamma = model_all->GetParError(2);
    signal_all->SetParameter(0,A_par+epsilon);
    dI_dA = ( signal_all->Integral(0,300) - all_yield ) / epsilon;
    signal_all->SetParameter(0,A_par);
    signal_all->SetParameter(2,Gamma_par+epsilon);
    dI_dGamma = ( signal_all->Integral(0,300) - all_yield ) / epsilon;
    signal_all->SetParameter(2,Gamma_par);

    Double_t all_error = fabs(dI_dA)*sigma_A + fabs(dI_dGamma)*sigma_Gamma;
    printf("All error = %f * %f + %f * %f = %f\n",fabs(dI_dA),sigma_A,fabs(dI_dGamma),sigma_Gamma,all_error);
    
    // Compute efficiency
    Double_t efficiency = passing_yield/all_yield;
    Double_t efficiency_error = efficiency * sqrt(pow(all_error/all_yield, 2) + pow(passing_error/passing_yield,2) );
    printf("Calculated efficiency of %f +/- %f\n",efficiency,efficiency_error);

    if(draw) {
        TCanvas *c_passing=new TCanvas("c_passing","Pairs passing probe");
        h_mass_passing->Draw();
        model_passing->Draw("SAME");
        TCanvas *c_failing=new TCanvas("c_failing","Pairs failing probe");
        h_mass_failing->Draw();
        model_failing->Draw("SAME");
        TCanvas *c_all=new TCanvas("c_all","All pairs");
        h_mass_all->Draw();
        model_all->Draw("SAME");
        c_all->WaitPrimitive();
    }
    efficiency_info[0]=efficiency;
    efficiency_info[1]=efficiency_error;
    return true;
}

TH1F *BinnedEfficiency(char* filename, char* variable="pt", bool draw=false) {
    if(strcmp(variable,"pt")==0) {
        printf("Binning efficiency as pt\n\n");
    } else if(strcmp(variable,"eta")==0) {
        printf("Binning efficiency as eta\n\n");
    } else if(strcmp(variable, "pv")==0) {
        printf("Binning efficiency as pv\n\n");
    } else {
       printf("Bad variable selected\n\n");
       TH1F *garbage= new TH1F;
       return garbage; 
    }
    
    Float_t d_pt = 20;
    Int_t n_ptbins = 4;
    Float_t pt_0=20;
    Float_t d_eta = 1;
    Int_t n_etabins = 5;
    Float_t eta_0=-2.5;
    Float_t d_pv = 5;
    Int_t n_pvbins = 5;
    Float_t pv_0 = 5;
    
    // Load file and trees
    TFile *file =new TFile(filename);
    TTree *t_passing = (TTree*)file->Get("HLTMod/GoodPVFilterMod/MuonIDMod/MuonIDMod/NtuplesMod/passing_probe_events");
    TTree *t_all = (TTree*)file->Get("HLTMod/GoodPVFilterMod/MuonIDMod/MuonIDMod/NtuplesMod/all_tagged_events");
    // Init. dummy variables
    UInt_t n_pairs, n_Vertices;
    Float_t tag_px[64], tag_py[64], tag_pz[64], tag_E[64], probe_px[64], probe_py[64], probe_pz[64], probe_E[64], probe_pt[64], probe_eta[64]; 

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
    t_passing->SetBranchAddress("nVertices",&n_Vertices);
    t_passing->SetBranchAddress("probe.pt",probe_pt);
    t_passing->SetBranchAddress("probe.eta",probe_eta);
    t_all->SetBranchAddress("tag.px",tag_px); 
    t_all->SetBranchAddress("tag.py",tag_py);
    t_all->SetBranchAddress("tag.pz",tag_pz);
    t_all->SetBranchAddress("tag.energy",tag_E);
    t_all->SetBranchAddress("probe.px",probe_px); 
    t_all->SetBranchAddress("probe.py",probe_py);
    t_all->SetBranchAddress("probe.pz",probe_pz);
    t_all->SetBranchAddress("probe.energy",probe_E);
    t_all->SetBranchAddress("probe.pt",probe_pt);
    t_all->SetBranchAddress("probe.eta",probe_eta);
    t_all->SetBranchAddress("nPairs",&n_pairs);
    t_all->SetBranchAddress("nVertices",&n_Vertices);
    
    // 2D histograms as mass and pt/eta/pv
    TH2F *h_mass_pt_passing = new TH2F("h_mass_pt_passing", "Invariant mass and pt for pairs passing probe", 300, 0, 300, n_ptbins, pt_0, pt_0 + d_pt*n_ptbins);
    TH2F *h_mass_pt_failing = new TH2F("h_mass_pt_failing", "Invariant mass and pt for pairs failing probe", 300, 0, 300, n_ptbins, pt_0, pt_0 + d_pt*n_ptbins);
    TH2F *h_mass_pt_all = new TH2F("h_mass_pt_all", "Invariant mass and pt for all pairs", 300, 0, 300, n_ptbins, pt_0, pt_0 + d_pt*n_ptbins);
    TH2F *h_mass_eta_passing = new TH2F("h_mass_eta_passing", "Invariant mass and eta for pairs passing probe", 300, 0, 300, n_etabins, eta_0, eta_0 + d_eta*n_etabins);
    TH2F *h_mass_eta_failing = new TH2F("h_mass_eta_failing", "Invariant mass and eta for pairs failing probe", 300, 0, 300, n_etabins, eta_0, eta_0 + d_eta*n_etabins);
    TH2F *h_mass_eta_all = new TH2F("h_mass_eta_all", "Invariant mass and eta for all pairs", 300, 0, 300, n_etabins, eta_0, eta_0 + d_eta*n_etabins);
    TH2F *h_mass_pv_passing = new TH2F("h_mass_pv_passing", "Invariant mass and pv for pairs passing probe", 300, 0, 300, n_pvbins, pv_0, pv_0 + d_pv*n_pvbins);
    TH2F *h_mass_pv_failing = new TH2F("h_mass_pv_failing", "Invariant mass and pv for pairs failing probe", 300, 0, 300, n_pvbins, pv_0, pv_0 + d_pv*n_pvbins);
    TH2F *h_mass_pv_all = new TH2F("h_mass_pv_all", "Invariant mass and pv for all pairs", 300, 0, 300, n_pvbins, pv_0, pv_0 + d_pv*n_pvbins);

    // Global spectra
    // TH1F *h_global_mass_passing = new TH1F("h_global_mass_passing","Invariant mass for pairs passing probe",300,0,300);
    // TH1F *h_global_mass_failing = new TH1F("h_global_mass_failing","Invariant mass for pairs failing probe",300,0,300);
    // TH1F *h_global_mass_all = new TH1F("h_global_mass_all","Invariant mass for all pairs",300,0,300);
 
    // fill invariant mass histogram for passing probe
    Int_t N_passing = (Int_t)t_passing->GetEntries();
    for(Int_t i=0; i<N_passing; i++) {
        t_passing->GetEntry(i);
        if(n_pairs>0){ for(Int_t j=0; j<n_pairs; j++) {
            Float_t px = tag_px[j] + probe_px[j];
            Float_t py = tag_py[j] + probe_py[j];
            Float_t pz = tag_pz[j] + probe_pz[j];
            Float_t E  = tag_E[j]  + probe_E[j];
            Float_t M = sqrt(E*E - px*px - py*py - pz*pz);
            Float_t pt = probe_pt[j];
            Float_t eta = probe_eta[j];
            Int_t pv = n_Vertices;
            // global mass spectra
            // h_global_mass_passing->Fill(M);
            // mass and pt
            if(variable=="pt") h_mass_pt_passing->Fill(M, pt);
            if(variable=="eta") h_mass_eta_passing->Fill(M, eta);
            if(variable=="pv") h_mass_pv_passing->Fill(M, pv);
        }}
    }

    // fill invariant mass histogram for all pairs
    Int_t N_all = (Int_t)t_all->GetEntries();
    for(Int_t i=0; i<N_all; i++) {
        t_all->GetEntry(i);
        if(n_pairs>0){ for(Int_t j=0; j<n_pairs; j++) {
            Float_t px = tag_px[j] + probe_px[j];
            Float_t py = tag_py[j] + probe_py[j];
            Float_t pz = tag_pz[j] + probe_pz[j];
            Float_t E  = tag_E[j]  + probe_E[j];
            Float_t M = sqrt(E*E - px*px - py*py - pz*pz);
            Float_t pt = probe_pt[j];
            Float_t eta = probe_eta[j];
            Int_t pv = n_Vertices;
            // global mass spectra
            //h_global_mass_all->Fill(M);
            //h_global_mass_failing->Fill(M);
            // mass and pt
            if(variable=="pt") {
                h_mass_pt_failing->Fill(M, pt);
                h_mass_pt_all->Fill(M, pt);
            } else if(variable=="eta") {
                h_mass_eta_failing->Fill(M, eta);
                h_mass_eta_all->Fill(M, eta);
            } else if(variable=="pv") {
                h_mass_pv_failing->Fill(M, pv);
                h_mass_pv_all->Fill(M, pv);
            }
        }}
    }
    //h_global_mass_failing->Add(h_global_mass_passing,-1); // all minus pass
    h_mass_pt_failing->Add(h_mass_pt_passing,-1); // all minus pass
    h_mass_eta_failing->Add(h_mass_eta_passing,-1); // all minus pass
    h_mass_pv_failing->Add(h_mass_pv_passing,-1); // all minus pass

    //Compute the Efficiency of each Pt bin
    if(variable=="pt") {
        TH1F *efficiency_pt = new TH1F("efficiency_pt","Efficiency as function of p_{T}",n_ptbins, pt_0, pt_0 + d_pt*n_ptbins);
        for(Int_t nbin=1; nbin <= n_ptbins; nbin++) {
            // Slice as pt
            TH1D *h_mass_passing = h_mass_pt_passing->ProjectionX("h_mass_passing", nbin, nbin,"o");
            TH1D *h_mass_failing = h_mass_pt_failing->ProjectionX("h_mass_failing", nbin, nbin,"o");
            TH1D *h_mass_all     = h_mass_pt_all->ProjectionX("h_mass_all", nbin, nbin,"o");
            char passing_title[256],failing_title[256],all_title[256],slice_range[128];
            sprintf(slice_range,"(p_{T} range [ %.2f, %.2f ] )", pt_0 + (nbin-1)*d_pt, pt_0 + nbin*d_pt);
            sprintf(passing_title,"Invariant mass for pairs passing probe %s",slice_range);
            sprintf(failing_title,"Invariant mass for pairs failing probe %s",slice_range);
            sprintf(all_title,"Invariant mass for all pairs %s",slice_range); 
            h_mass_passing->SetTitle(passing_title);
            h_mass_failing->SetTitle(failing_title);
            h_mass_all    ->SetTitle(all_title);
            if(nbin <= n_ptbins) {
                printf("Fitting for pt in [ %f, %f ] GeV\n",pt_0 + (nbin-1)*d_pt, pt_0 + nbin*d_pt);
            } else {
                printf("Overflow bin: Fitting for pt in [ %f, inf ) GeV\n",(nbin)*d_pt);
            }
    
            Double_t efficiency_info[2];
            efficiency_fit(h_mass_passing,h_mass_failing,h_mass_all,efficiency_info,"M0S",draw);
            efficiency_pt->SetBinContent(nbin, efficiency_info[0]);
            efficiency_pt->SetBinError(nbin, efficiency_info[1]);
            delete h_mass_passing;
            delete h_mass_failing;
            delete h_mass_all;
    
        }
        return efficiency_pt;
    }
    // Compute the efficiency of each Eta bin
    if(variable=="eta") {
        TH1F *efficiency_eta = new TH1F("efficiency_eta", "Efficiency as function of #eta", n_etabins, eta_0, eta_0+n_etabins*d_eta);
        for(Int_t nbin=1; nbin<=n_etabins; nbin++) {
            // Slice as eta
            TH1D *h_mass_passing = h_mass_eta_passing->ProjectionX("h_mass_passing", nbin, nbin,"o");
            TH1D *h_mass_failing = h_mass_eta_failing->ProjectionX("h_mass_failing", nbin, nbin,"o");
            TH1D *h_mass_all = h_mass_eta_all->ProjectionX("h_mass_all", nbin, nbin,"o");
            char passing_title[256],failing_title[256],all_title[256],slice_range[128];
            sprintf(slice_range,"(#eta range [ %.2f, %.2f ] )", eta_0 + (nbin-1)*d_eta, eta_0 + nbin*d_eta);
            sprintf(passing_title,"Invariant mass for pairs passing probe %s",slice_range);
            sprintf(failing_title,"Invariant mass for pairs failing probe %s",slice_range);
            sprintf(all_title,"Invariant mass for all pairs %s",slice_range); 
            h_mass_passing->SetTitle(passing_title);
            h_mass_failing->SetTitle(failing_title);
            h_mass_all    ->SetTitle(all_title);
            printf("Fitting for eta in [ %f, %f ] GeV\n",(nbin-1)*d_eta, nbin*d_eta);
            Double_t efficiency_info[2];
            efficiency_fit(h_mass_passing,h_mass_failing,h_mass_all,efficiency_info,"M0S",draw);
            efficiency_eta->SetBinContent(nbin, efficiency_info[0]);
            efficiency_eta->SetBinError(nbin, efficiency_info[1]);
            delete h_mass_passing;
            delete h_mass_failing;
            delete h_mass_all;
    
        }
        return efficiency_eta;
    }
    // Compute the efficiency of each Pv bin
    if(variable=="pv") {
        TH1F *efficiency_pv = new TH1F("efficiency_pv","Efficiency as function of n_{PV}",n_pvbins, pv_0, pv_0 + d_pv*n_pvbins);
        for(Int_t nbin=1; nbin <= n_pvbins; nbin++) {
            // Slice as pv
            TH1D *h_mass_passing = h_mass_pv_passing->ProjectionX("h_mass_passing", nbin, nbin,"o");
            TH1D *h_mass_failing = h_mass_pv_failing->ProjectionX("h_mass_failing", nbin, nbin,"o");
            TH1D *h_mass_all     = h_mass_pv_all->ProjectionX("h_mass_all", nbin, nbin,"o");
            char passing_title[256],failing_title[256],all_title[256],slice_range[128];
            sprintf(slice_range,"(PV range [ %.2f, %.2f ] )", pv_0 + (nbin-1)*d_pv, pv_0 + nbin*d_pv);
            sprintf(passing_title,"Invariant mass for pairs passing probe %s",slice_range);
            sprintf(failing_title,"Invariant mass for pairs failing probe %s",slice_range);
            sprintf(all_title,"Invariant mass for all pairs %s",slice_range); 
            h_mass_passing->SetTitle(passing_title);
            h_mass_failing->SetTitle(failing_title);
            h_mass_all    ->SetTitle(all_title);
            printf("Fitting for pv in [ %f, %f ] GeV\n",pv_0 + (nbin-1)*d_pv, pv_0 + nbin*d_pv);
            Double_t efficiency_info[2];
            efficiency_fit(h_mass_passing,h_mass_failing,h_mass_all,efficiency_info,"M0S",draw);
            efficiency_pv->SetBinContent(nbin, efficiency_info[0]);
            efficiency_pv->SetBinError(nbin, efficiency_info[1]);
            delete h_mass_passing;
            delete h_mass_failing;
            delete h_mass_all;
    
        }
        return efficiency_pv;
    }
}

void *GlobalEfficiency(char *filename,bool draw=true) {
    // Load file and trees
    TFile *file =new TFile(filename);
    TTree *t_passing = (TTree*)file->Get("HLTMod/GoodPVFilterMod/MuonIDMod/MuonIDMod/NtuplesMod/passing_probe_events");
    TTree *t_all = (TTree*)file->Get("HLTMod/GoodPVFilterMod/MuonIDMod/MuonIDMod/NtuplesMod/all_tagged_events");
    // Init. dummy variables
    UInt_t n_pairs;
    Float_t tag_px[64], tag_py[64], tag_pz[64], tag_E[64], probe_px[64], probe_py[64], probe_pz[64], probe_E[64], probe_pt[64], probe_eta[64]; 

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
    t_passing->SetBranchAddress("probe.pt",probe_pt);
    t_passing->SetBranchAddress("probe.eta",probe_eta);
    t_all->SetBranchAddress("tag.px",tag_px); 
    t_all->SetBranchAddress("tag.py",tag_py);
    t_all->SetBranchAddress("tag.pz",tag_pz);
    t_all->SetBranchAddress("tag.energy",tag_E);
    t_all->SetBranchAddress("probe.px",probe_px); 
    t_all->SetBranchAddress("probe.py",probe_py);
    t_all->SetBranchAddress("probe.pz",probe_pz);
    t_all->SetBranchAddress("probe.energy",probe_E);
    t_all->SetBranchAddress("probe.pt",probe_pt);
    t_all->SetBranchAddress("probe.eta",probe_eta);
    t_all->SetBranchAddress("nPairs",&n_pairs);
    
    // Global spectra
    TH1D *h_global_mass_passing = new TH1D("h_global_mass_passing", "Invariant mass for pairs passing probe (Global Fit)",   300,0,300);
    TH1D *h_global_mass_failing = new TH1D("h_global_mass_failing", "Invariant mass for pairs failing probe (Global Fit)",   300,0,300);
    TH1D *h_global_mass_all     = new TH1D("h_global_mass_all",     "Invariant mass for all pairs (Global Fit)",             300,0,300);
 
    // fill invariant mass histogram for passing probe
    Int_t N_passing = (Int_t)t_passing->GetEntries();
    for(Int_t i=0; i<N_passing; i++) {
        t_passing->GetEntry(i);
        if(n_pairs>0){ for(Int_t j=0; j<n_pairs; j++) {
            Float_t px = tag_px[j] + probe_px[j];
            Float_t py = tag_py[j] + probe_py[j];
            Float_t pz = tag_pz[j] + probe_pz[j];
            Float_t E  = tag_E[j]  + probe_E[j];
            Float_t M = sqrt(E*E - px*px - py*py - pz*pz);
            Float_t pt = probe_pt[j];
            Float_t eta = probe_eta[j];
            // global mass spectra
            h_global_mass_passing->Fill(M);
        }}
    }

    // fill invariant mass histogram for all pairs
    Int_t N_all = (Int_t)t_all->GetEntries();
    for(Int_t i=0; i<N_all; i++) {
        t_all->GetEntry(i);
        if(n_pairs>0){ for(Int_t j=0; j<n_pairs; j++) {
            Float_t px = tag_px[j] + probe_px[j];
            Float_t py = tag_py[j] + probe_py[j];
            Float_t pz = tag_pz[j] + probe_pz[j];
            Float_t E  = tag_E[j]  + probe_E[j];
            Float_t M = sqrt(E*E - px*px - py*py - pz*pz);
            Float_t pt = probe_pt[j];
            Float_t eta = probe_eta[j];
            // global mass spectra
            h_global_mass_all->Fill(M);
            h_global_mass_failing->Fill(M);
        }}
    }
    h_global_mass_failing->Add(h_global_mass_passing,-1); // all minus pass

    // Compute the efficiency of entire curve
    Double_t efficiency_info[2];
    efficiency_fit(h_global_mass_passing,h_global_mass_failing,h_global_mass_all,efficiency_info,"M0S",draw);
    printf("Global efficiency is %f +/- %f\n",efficiency_info[0],efficiency_info[1]);
}
