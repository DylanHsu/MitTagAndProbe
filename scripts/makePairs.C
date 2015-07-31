// Makes tag and probe pairs from ntuple of lepton objects
// Needs to be compiled in ROOT e.g. ".L makePairs.C+g"

#include <vector> 
#include <string> 
#include "TFile.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

#ifdef _MAKECINT_ 
    #pragma link C++ class vector<TLorentzVector* >+; 
    #pragma link C++ class vector<vector<bool> >+; 
#else 
    template class std::vector<TLorentzVector* >; 
    template class std::vector<std::vector<bool> >; 
#endif

void makePairs(
  string inputFile,
  string outputFile,
  string tagIdType    ="Pog2015_Tight",  // ID used for the tag
  string tagIsoType   ="PFIso",          // Iso used for the tag
  string probeIdType  ="Pog2015_Loose",  // ID used for selecting probes
  string probeIsoType ="PFIso",          // Iso used for selecting probes
  string passIdType   ="Pog2015_Tight",  // ID used to determine whether probe passes or fails the cut
  string passIsoType  ="PFIso"           // Iso used to determine whether probe passes or fails the cut
) {
//void makePairs() {
  bool debug=true;
  double deltaRthreshold=0.001;

  TFile *inputFileHandler=TFile::Open(inputFile.c_str(),"READ");
  //TFile *inputFileHandler = new TFile("/mnt/hscratch/dhsu/Zuu_13TeV_2015-07-22_bitwise.root");
  //if(inputFileHandler==0) {
  //    printf("Error opening input file \"%s\"\n",inputFile);
  //    return;                                                
  //}                                                          
  // define the trees
  TTree *bitNamesTree=(TTree*)inputFileHandler->Get("BitNames");
  TTree *eventsTree=(TTree*)inputFileHandler->Get("Events");

  // declare leaf types for bitNamesTree
  vector<string> *vectorClassNames=0;
  vector<string> *vectorIdNames=0;
  vector<string> *vectorIsoNames=0;
  // set branch addresses for bitNamesTree
  bitNamesTree->SetBranchAddress( "ClassNames",   &vectorClassNames  );
  bitNamesTree->SetBranchAddress( "IdNames",      &vectorIdNames     );
  bitNamesTree->SetBranchAddress( "IsoNames",     &vectorIsoNames    );
  bitNamesTree->GetEntry(0);

  // Loop over bit names to find the Id and Iso bits we want
  // Throw an error if not found
  int tagIdKey=-1, tagIsoKey=-1, probeIdKey=-1, probeIsoKey=-1, passIdKey=-1, passIsoKey=-1;
  unsigned int indexId=0, indexIso=0, indexPass=0;
  for(std::vector<string>::iterator it = vectorIdNames->begin(); it!=vectorIdNames->end(); ++it) {
    if(debug) printf("Checking %s Id\n",(*it).c_str());
    
    if(*it == tagIdType) {
      printf("Found tagIdType \"%s\" in bit names, key is %d\n", tagIdType.c_str(), indexId);
      tagIdKey=indexId;
    }
    if(*it == probeIdType) {
      printf("Found probeIdType \"%s\" in bit names, key is %d\n", probeIdType.c_str(), indexId);
      probeIdKey=indexId;
    }
    if(*it == passIdType) {
      printf("Found passIdType \"%s\" in bit names, key is %d\n", passIdType.c_str(), indexId);
      passIdKey=indexId;
    }
    if(tagIdKey > 0 && probeIdKey > 0 && passIdKey > 0) break;
    indexId++;
  }
  if(tagIdKey<0 || probeIdKey<0 || passIdKey<0) {
    printf("Could not find IdTypes \"%s\", \"%s\", \"%s\" in bit names, exiting", tagIdType.c_str(), probeIdType.c_str(), passIdType.c_str());
    return;
  } 
  for(std::vector<string>::iterator it = vectorIsoNames->begin(); it!=vectorIsoNames->end(); ++it) {
    if(debug) printf("Checking %s Iso\n",(*it).c_str());
    
    if(*it == tagIsoType) {
      printf("Found tagIsoType \"%s\" in bit names, key is %d\n", tagIsoType.c_str(), indexIso);
      tagIsoKey=indexIso;
    }
    if(*it == probeIsoType) {
      printf("Found probeIsoType \"%s\" in bit names, key is %d\n", probeIsoType.c_str(), indexIso);
      probeIsoKey=indexIso;
    }
    if(*it == passIsoType) {
      printf("Found passIsoType \"%s\" in bit names, key is %d\n", passIsoType.c_str(), indexIso);
      passIsoKey=indexIso;
    }
    if(tagIsoKey > 0 && probeIsoKey > 0 && passIsoKey > 0) break;
    indexIso++;
  }
  if(tagIsoKey<0 || probeIsoKey<0 || passIsoKey<0) {
    printf("Could not find IsoTypes \"%s\", \"%s\", \"%s\" in bit names, exiting", tagIsoType.c_str(), probeIsoType.c_str(), passIsoType.c_str());
    return;
  }

  // declare leaf types for eventsTree
  UInt_t                      runNum;
  UInt_t                      lumiSec;
  UInt_t                      evtNum;
  UInt_t                      npv;
  vector<int>                 *vectorCharge           = 0;
  vector<TLorentzVector*>     *vectorFourMomentum     = 0;
  vector<vector<bool> >       *vectorClassBits        = 0;
  vector<vector<bool> >       *vectorIdBits           = 0;
  vector<vector<bool> >       *vectorIsoBits          = 0;

  // set branch addresses for eventsTree
  eventsTree->SetBranchAddress( "runNum",         &runNum             );
  eventsTree->SetBranchAddress( "lumiSec",        &lumiSec            );
  eventsTree->SetBranchAddress( "evtNum",         &evtNum             );
  eventsTree->SetBranchAddress( "npv",            &npv                );
  eventsTree->SetBranchAddress( "charge",         &vectorCharge       );
  eventsTree->SetBranchAddress( "fourMomentum",   &vectorFourMomentum );
  eventsTree->SetBranchAddress( "ClassBits",      &vectorClassBits    );
  eventsTree->SetBranchAddress( "IdBits",         &vectorIdBits       );
  eventsTree->SetBranchAddress( "IsoBits",        &vectorIsoBits      );

  //     This is the loop skeleton
  //       To read only selected branches, Insert statements like:
  // eventsTree->SetBranchStatus("*",0);  // disable all branches
  // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  // Output tree branch
  TFile *outputFileHandler=TFile::Open(outputFile.c_str(),"RECREATE");
  outputFileHandler->SetCompressionLevel(9);
  TTree *pairTree = new TTree("Events", "");
  unsigned int pass;                      // whether probe passes requirements
  float        npu=0;                       // mean number of expected pileup
  float        scale1fb=1;                  // event weight per 1/fb
  float        mass;                      // tag-probe mass
  int          qtag, qprobe;              // tag, probe charge
  TLorentzVector *tagTLV=0, *probeTLV=0;        // tag, probe 4-vector
  
  pairTree->Branch("runNum",   &runNum,   "runNum/i"   );  
  pairTree->Branch("lumiSec",  &lumiSec,  "lumiSec/i"  );  
  pairTree->Branch("evtNum",   &evtNum,   "evtNum/i"   );  
  pairTree->Branch("npv",      &npv,      "npv/i"      );  
  pairTree->Branch("pass",     &pass,     "pass/i"     );  
  pairTree->Branch("npu",      &npu,      "npu/F"      );  
  pairTree->Branch("scale1fb", &scale1fb, "scale1fb/F" );
  pairTree->Branch("mass",     &mass,     "mass/F"     );  
  pairTree->Branch("qtag",     &qtag,     "qtag/I"     );  
  pairTree->Branch("qprobe",   &qprobe,   "qprobe/I"   );  
  pairTree->Branch("tag",   "TLorentzVector", &tagTLV   );  
  pairTree->Branch("probe", "TLorentzVector", &probeTLV );             
  pairTree->SetBranchAddress("runNum",   &runNum);
  pairTree->SetBranchAddress("lumiSec",  &lumiSec);
  pairTree->SetBranchAddress("evtNum",   &evtNum);
  pairTree->SetBranchAddress("npv",      &npv);
  pairTree->SetBranchAddress("pass",     &pass);
  pairTree->SetBranchAddress("npu",      &npu);
  pairTree->SetBranchAddress("scale1fb", &scale1fb);
  pairTree->SetBranchAddress("mass",     &mass);
  pairTree->SetBranchAddress("qtag",     &qtag);
  pairTree->SetBranchAddress("qprobe",   &qprobe);
  pairTree->SetBranchAddress("tag",      &tagTLV);
  pairTree->SetBranchAddress("probe",    &probeTLV);
 
  // Data Bookkeeping
  Long64_t nentries = eventsTree->GetEntries();
  Long64_t nbytes = 0;
  // Loop over events
  // Within events, loop over tags {j} probes {k} and make pairs
  for (Long64_t i=0; i<nentries;i++) {
  //for (Long64_t i=0; i<5;i++) {
    nbytes += eventsTree->GetEntry(i);
    // klugey implementation of golden runs list
    bool isGoodRun=false;
    switch(runNum) {    
      case 251244:
        if(
          lumiSec >= 85 && lumiSec <= 86 ||
          lumiSec >= 88 && lumiSec <= 93 ||
          lumiSec >= 96 && lumiSec <= 121 ||
          lumiSec >= 123 && lumiSec <= 156 ||
          lumiSec >= 158 && lumiSec <= 428 ||
          lumiSec >= 430 && lumiSec <= 442
        ) isGoodRun=true;
        break;
      case 251251: 
        if(
          lumiSec >= 1 && lumiSec <= 31 ||
          lumiSec >= 33 && lumiSec <= 97 ||
          lumiSec >= 99 && lumiSec <= 167
        ) isGoodRun=true;
        break;
      case 251252: 
        if(
          lumiSec >= 1 && lumiSec <= 283 ||
          lumiSec >= 285 && lumiSec <= 505 ||
          lumiSec >= 507 && lumiSec <= 554
        ) isGoodRun=true;
        break;
      case 251561: 
        if(
          lumiSec >= 1 && lumiSec <= 94
        ) isGoodRun=true;
        break;
      case 251562: 
        if(
          lumiSec >= 1 && lumiSec <= 439 ||
          lumiSec >= 443 && lumiSec <= 691
        ) isGoodRun=true;
        break;
      case 251643: 
        if(
          lumiSec >= 1 && lumiSec <= 216 ||
          lumiSec >= 222 && lumiSec <= 606
        ) isGoodRun=true;
        break;
      case 251721: 
        if(
          lumiSec >= 21 && lumiSec <= 36
        ) isGoodRun=true;
        break;
      case 251883: 
        if(
          lumiSec >= 56 && lumiSec <= 56 ||
          lumiSec >= 58 && lumiSec <= 60 ||
          lumiSec >= 62 && lumiSec <= 144 ||
          lumiSec >= 156 && lumiSec <= 437
        ) isGoodRun=true;
        break;
      default:
        break;
    }
    if(!isGoodRun) continue;
 
    unsigned int j=0; // index for tags
    for(std::vector<TLorentzVector*>::iterator itTag = vectorFourMomentum->begin(); itTag!=vectorFourMomentum->end(); ++itTag) {

      // check Id and Iso for the tag candidate
      if(!( (*vectorIdBits)[j][tagIdKey] && (*vectorIsoBits)[j][tagIsoKey]) ) {
        //printf("failed cuts on tag\n");
        continue;      
      }
      
      unsigned int k=0; // index for probes
      for(std::vector<TLorentzVector*>::iterator itProbe = vectorFourMomentum->begin(); itProbe!=vectorFourMomentum->end(); ++itProbe) {
        //printf("Looking at pair, tag pT = %f, probe candidate pT = %f\n", (*itTag)->Pt(), (*itProbe)->Pt());
        // compute delta-R to see if the tag and probe are the same particle
        double deltaR = sqrt( 
          pow((*itTag)->Eta() - (*itProbe)->Eta(), 2) +
          pow((*itTag)->Phi() - (*itProbe)->Phi(), 2)
        );
        if(deltaR < deltaRthreshold) {
          //printf("delta R cut\n");
          continue;
        }
        
        // check Id and Iso for the probe candidate
        if(!( (*vectorIdBits)[j][probeIdKey] && (*vectorIsoBits)[j][probeIsoKey]) ) {
          //printf("failed probe requirements\n");
          continue;
        }
        // 
        pass=0;
        if( (*vectorIdBits)[j][passIdKey] && (*vectorIsoBits)[j][passIsoKey]) {
          pass=1;
          //printf("probe passed tag!\n");
        }
        tagTLV=new TLorentzVector(
          (*itTag)->Px(),
          (*itTag)->Py(),
          (*itTag)->Pz(),
          (*itTag)->E()
        );  
        probeTLV=new TLorentzVector(
          (*itProbe)->Px(),
          (*itProbe)->Py(),
          (*itProbe)->Pz(),
          (*itProbe)->E()
        );  
        qtag = (*vectorCharge)[j]; 
        qprobe = (*vectorCharge)[k];
        if(qtag+qprobe!=0) {
          //printf("total charge is nonzero (%d), continuing\n",qtag+qprobe);
          continue;
        }
        TLorentzVector pairSystemTLV = *probeTLV + *tagTLV;
        if(pairSystemTLV.Pt() <= 200) {
          //printf(" system pT is too low (%f GeV), continuing\n", pairSystemTLV.Pt());
          continue;
        }
        mass = pairSystemTLV.M();
        pairTree->Fill(); 
        k++; 
      }
      j++;
    }
  }
  printf("Input tree has %lld entries using %lld bytes\n", nentries,nbytes);
  printf("Trying to write to file\n");
  pairTree->Write();
  printf("Wrote %lld entries to file\n", pairTree->GetEntries());
  outputFileHandler->Close();
  inputFileHandler->Close();
}
