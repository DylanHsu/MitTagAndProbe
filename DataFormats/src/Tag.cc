// AUTO-GENERATED CODE - EDIT Tag.h / Probe.h and run scripts/updateClasses.py

#include "MitTagAndProbe/DataFormats/interface/Tag.h"
#include "MitTagAndProbe/DataFormats/interface/TnPEvent.h"

mithep::Tag::Tag(TnPEvent& _evt, UInt_t _idx) :
  pt(_evt.tagPt[_idx]),
  eta(_evt.tagEta[_idx]),
  phi(_evt.tagPhi[_idx]),
  px(_evt.tagPx[_idx]),
  py(_evt.tagPy[_idx]),
  pz(_evt.tagPz[_idx]),
  energy(_evt.tagEnergy[_idx])
{
}
