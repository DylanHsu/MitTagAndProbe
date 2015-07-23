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
  char* inputFile,
  char* outputFile,
  string tagIdType    ="Tight",
  string tagIsoType   ="NoIso",
  string probeIdType  ="Loose",
  string probeIsoType ="NoIso"
) {
//void makePairs() {
  bool debug=true;
  double deltaRthreshold=0.001;

  //TFile *inputFileHandler=TFile::Open(inputFile,"READ");
  TFile *inputFileHandler = new TFile("/mnt/hscratch/dhsu/Zuu_13TeV_2015-07-22_bitwise.root");
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
  int tagIdKey=-1, tagIsoKey=-1, probeIdKey=-1, probeIsoKey=-1;
  unsigned int indexId=0, indexIso=0;
  for(std::vector<string>::iterator it = vectorIdNames->begin(); it!=vectorIdNames->end(); ++it) {
    if(debug) printf("Checking %s Id\n",(*it).c_str());
    
    if(*it == tagIdType) {
      printf("Found tagIdType \"%s\" in bit names, key is %d\n", probeIdType.c_str(), indexId);
      tagIdKey=indexId;
    }
    if(*it == probeIdType) {
      printf("Found probeIdType \"%s\" in bit names, key is %d\n", probeIdType.c_str(), indexId);
      probeIdKey=indexId;
    }
    if(tagIdKey > 0 && probeIdKey > 0) break;
    indexId++;
  }
  if(tagIdKey<0 || probeIdKey<0) {
    printf("Could not find IdTypes \"%s\", \"%s\" in bit names, exiting", tagIdType.c_str(), probeIdType.c_str());
    return;
  } 
  for(std::vector<string>::iterator it = vectorIsoNames->begin(); it!=vectorIsoNames->end(); ++it) {
    if(debug) printf("Checking %s Iso\n",(*it).c_str());
    
    if(*it == tagIsoType) {
      printf("Found tagIsoType \"%s\" in bit names, key is %d\n", probeIsoType.c_str(), indexIso);
      tagIsoKey=indexIso;
    }
    if(*it == probeIsoType) {
      printf("Found probeIsoType \"%s\" in bit names, key is %d\n", probeIsoType.c_str(), indexIso);
      probeIsoKey=indexIso;
    }
    if(tagIsoKey > 0 && probeIsoKey > 0) break;
    indexIso++;
  }
  if(tagIsoKey<0 || probeIsoKey<0) {
    printf("Could not find IsoTypes \"%s\", \"%s\" in bit names, exiting", tagIsoType.c_str(), probeIsoType.c_str());
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
  TFile *outputFileHandler=TFile::Open("/tmp/dhsu/outputPairNtuple.root","RECREATE");
  //outputFileHandler->SetCompressionLevel(9);
  TTree *pairTree = new TTree("Events", "Tag and probe events with 2 muons for Kevin's script");
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

    unsigned int j=0; // index for tags
    for(std::vector<TLorentzVector*>::iterator itTag = vectorFourMomentum->begin(); itTag!=vectorFourMomentum->end(); ++itTag) {

      // check Id and Iso for the tag candidate
      if(!( (*vectorIdBits)[j][tagIdKey] && (*vectorIsoBits)[j][tagIsoKey]) ) continue;      
      
      unsigned int k=0; // index for probes
      for(std::vector<TLorentzVector*>::iterator itProbe = vectorFourMomentum->begin(); itProbe!=vectorFourMomentum->end(); ++itProbe) {
        // compute delta-R to see if the tag and probe are the same particle
        double deltaR = sqrt( 
          pow((*itTag)->Eta() - (*itProbe)->Eta(), 2) +
          pow((*itTag)->Phi() - (*itProbe)->Phi(), 2)
        );
        if(deltaR < deltaRthreshold) continue;
        
        // check Id and Iso for the probe candidate
        pass=0;
        if( (*vectorIdBits)[j][probeIdKey] && (*vectorIsoBits)[j][probeIsoKey])  pass=1;
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
        TLorentzVector pairSystemTLV = *probeTLV + *tagTLV;
        mass = pairSystemTLV.M();
         
        //TLorentzVector *fourMomentum = *it;
        //printf("item has energy %f and charge %d\n", (*it)->E(), (*vectorCharge)[j]);
        //printf("Id = %s, Iso = %s\n", (*vectorIdBits)[j][keyId] ? "true" : "false", (*vectorIsoBits)[j][keyIso] ? "true" : "false");
        
        pairTree->Fill(); 
        k++; 
      }
      j++;
    }
  }
  printf("Input tree has %lld entries using %lld bytes\n", nentries,nbytes);
  printf("Trying to write to file\n");
  pairTree->Write();
  printf("Wrote to file\n");
  outputFileHandler->Close();
  inputFileHandler->Close();
}
