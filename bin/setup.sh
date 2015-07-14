#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Setup the MitPhysics package adjusting things that are needed for it to compile and run properly.
#
#                                                                   Jan 16, 2014 - V0 Christoph Paus
#                                                                   Apr 26, 2015 - V1 Yutaro Iiyama
#---------------------------------------------------------------------------------------------------

echo "*************************"
echo " MitPhysics/bin/setup.sh"
echo "*************************"

# Generate ROOT dictionaries for classes defined in this module
$CMSSW_BASE/src/MitCommon/bin/genDict.sh MitTagAndProbe/Mods MitTagAndProbe/Fitting

exit 0
