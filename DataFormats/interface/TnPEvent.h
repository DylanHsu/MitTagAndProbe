// AUTO-GENERATED CODE - EDIT Tag.h / Probe.h and run scripts/updateClasses.py

#ifndef MITEXAMPLE_DATAFORMATS_TNPEVENT_H
#define MITEXAMPLE_DATAFORMATS_TNPEVENT_H

#include "MitTagAndProbe/DataFormats/interface/Tag.h"
#include "MitTagAndProbe/DataFormats/interface/Probe.h"

#include <utility>

class TTree;

namespace mithep {

  class TnPEvent {
  public:
    static UInt_t const NMAX = 64;
    typedef std::pair<Tag, Probe> TnPPair;
    
    TnPEvent();
    ~TnPEvent();

    TnPPair at(UInt_t) const;
    TnPPair operator[](UInt_t _idx) const { return at(_idx); }

    TnPPair addNew(Int_t numberOfGoodVertices);

    void clear() { nPairs = 0; nVertices=0;}

    void bookBranches(TTree&);
    void setAddress(TTree&);

  private:
    Tag* tag_[NMAX];
    Probe* probe_[NMAX];

  public:
    UInt_t nPairs;
    Int_t nVertices;
    Float_t tagPt[NMAX];
    Float_t tagEta[NMAX];
    Float_t tagPhi[NMAX];
    Float_t tagPx[NMAX];
    Float_t tagPy[NMAX];
    Float_t tagPz[NMAX];
    Float_t tagEnergy[NMAX];
    Float_t probePt[NMAX];
    Float_t probeEta[NMAX];
    Float_t probePhi[NMAX];
    Float_t probePx[NMAX];
    Float_t probePy[NMAX];
    Float_t probePz[NMAX];
    Float_t probeEnergy[NMAX];
  };

}

#endif
