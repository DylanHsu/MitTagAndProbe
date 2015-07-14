import re
import os

def bookBranchFunc(obj, varList):
    branchFormat = '  _tree.Branch("%s.%s", %s, "%s[nPairs]/%s");\n'

    text = ''

    for (varType, name) in varList:
        if varType == 'Char_t':
            varChar = 'B'
        elif varType == 'UChar_t':
            varChar = 'b'
        elif varType == 'Short_t':
            varChar = 'S'
        elif varType == 'UShort_t':
            varChar = 's'
        elif varType == 'Int_t':
            varChar = 'I'
        elif varType == 'UInt_t':
            varChar = 'i'
        elif varType == 'Long_t':
            varChar = 'L'
        elif varType == 'ULong_t':
            varChar = 'l'
        elif varType == 'Float_t':
            varChar = 'F'
        elif varType == 'Double_t':
            varChar = 'D'
        elif varType == 'Bool_t':
            varChar = 'O'

        text += branchFormat % (obj, name, obj + name.title(), name, varChar)

    return text

def setAddressFunc(obj, varList):

    setterFormat = '''
  if (_tree.GetBranchStatus("%s"))
    _tree.SetBranchAddress("%s", %s);
  else if (!_tree.GetBranch("%s"))
    notFound.push_back("%s");'''

    text = ''

    for (varType, name) in varList:
        bname = obj + '.' + name
        text += setterFormat % (bname, bname, obj + name.title(), bname, bname)

    return text

varList = {
    'Tag': [],
    'Probe': []
}

for className in ['Tag', 'Probe']:
    varPat = re.compile('^[ ]*(Bool_t|Char_|Short_t|UShort_t|Int_t|UInt_t|Long_t|Float_t|Double64_t)&[ ]+([a-zA-Z_][a-zA-Z0-9_]*);')

    headerFile = open(os.environ['CMSSW_BASE'] + '/src/MitTagAndProbe/DataFormats/interface/' + className + '.h')

    for line in headerFile:
        varMatch = varPat.match(line)
        if varMatch:
            varList[className].append((varMatch.group(1), varMatch.group(2)))
            
    headerFile.close()


    srcText = '''// AUTO-GENERATED CODE - EDIT Tag.h / Probe.h and run scripts/updateClasses.py

'''
    srcText += '#include "MitTagAndProbe/DataFormats/interface/' + className + '.h"\n'
    srcText += '#include "MitTagAndProbe/DataFormats/interface/TnPEvent.h"\n\n'
    srcText += 'mithep::' + className + '::' + className + '(TnPEvent& _evt, UInt_t _idx) :\n'

    for varType, name in varList[className]:
        srcText += '  ' + name + '(_evt.' + className.lower() + name.title() + '[_idx]),\n'

    srcText = srcText.strip(' \n,')
    srcText += '\n{\n}\n'

    with open(os.environ['CMSSW_BASE'] + '/src/MitTagAndProbe/DataFormats/src/' + className + '.cc', 'w') as srcFile:
        srcFile.write(srcText)


evtHeaderText = '''// AUTO-GENERATED CODE - EDIT Tag.h / Probe.h and run scripts/updateClasses.py

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

    TnPPair addNew();

    void clear() { nPairs = 0; }

    void bookBranches(TTree&);
    void setAddress(TTree&);

  private:
    Tag* tag_[NMAX];
    Probe* probe_[NMAX];

  public:
    UInt_t nPairs;
'''

for className in ['Tag', 'Probe']:
    for varType, name in varList[className]:
        evtHeaderText += '    ' + varType + ' ' + className.lower() + name.title() + '[NMAX];\n'

evtHeaderText += '  };\n\n}\n\n#endif'

with open(os.environ['CMSSW_BASE'] + '/src/MitTagAndProbe/DataFormats/interface/TnPEvent.h', 'w') as evtHeaderFile:
    evtHeaderFile.write(evtHeaderText)


evtSrcText = '''// AUTO-GENERATED CODE - EDIT Tag.h / Probe.h and run scripts/updateClasses.py

#include "MitTagAndProbe/DataFormats/interface/TnPEvent.h"

#include "TTree.h"
#include "TString.h"

#include <stdexcept>
#include <vector>
#include <iostream>

mithep::TnPEvent::TnPEvent() :
  nPairs(0)
{
  for (unsigned iP(0); iP != NMAX; ++iP) {
    tag_[iP] = new Tag(*this, iP);
    probe_[iP] = new Probe(*this, iP);
  }
}

mithep::TnPEvent::~TnPEvent()
{
  for (unsigned iP(0); iP != NMAX; ++iP) {
    delete tag_[iP];
    delete probe_[iP];
  }
}

mithep::TnPEvent::TnPPair
mithep::TnPEvent::at(UInt_t _idx) const
{
  if (_idx < nPairs)
    return TnPPair(*tag_[_idx], *probe_[_idx]);
  else
    throw std::out_of_range("TnPEvent::at()");
}

mithep::TnPEvent::TnPPair
mithep::TnPEvent::addNew()
{
  TnPPair pair(*tag_[nPairs], *probe_[nPairs]);
  ++nPairs;

  return pair;
}

void
mithep::TnPEvent::bookBranches(TTree& _tree)
{
  _tree.Branch("nPairs", &nPairs, "nPairs/i");

'''

for className in ['Tag', 'Probe']:
    evtSrcText += bookBranchFunc(className.lower(), varList[className])
    
evtSrcText += '}\n'

evtSrcText += '''
void
mithep::TnPEvent::setAddress(TTree& _tree)
{
  _tree.SetBranchAddress("nPairs", &nPairs);

  std::vector<TString> notFound;
'''

for className in ['Tag', 'Probe']:
    evtSrcText += setAddressFunc(className.lower(), varList[className])

evtSrcText += '''

  for (unsigned iN(0); iN != notFound.size(); ++iN)
    std::cerr << "Branch " << notFound[iN] << " not found in input" << std::endl;
}
'''

with open(os.environ['CMSSW_BASE'] + '/src/MitTagAndProbe/DataFormats/src/TnPEvent.cc', 'w') as evtSrcFile:
    evtSrcFile.write(evtSrcText)
