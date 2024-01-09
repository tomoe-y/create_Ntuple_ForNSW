# The name of the package:
atlas_subdir (MyAnalysis)

# Add the shared library:
atlas_add_library (MyAnalysisLib
  MyAnalysis/*.h Root/*.cxx
  PUBLIC_HEADERS 
    MyAnalysis
  LINK_LIBRARIES 
    AnaAlgorithmLib
    TrigConfInterfaces
    TrigDecisionToolLib
    xAODMuon
    MuonSelectorToolsLib
    xAODTrigMuon
    TruthClassificationLib
    TrkExInterfaces)

# Add the dictionary (for AnalysisBase only):
#atlas_add_dictionary (MyAnalysisDict
# MyAnalysis/MyAnalysisDict.h
# MyAnalysis/selection.xml
# LINK_LIBRARIES MyAnalysisLib)

atlas_add_component (MyAnalysis
  src/components/*.cxx
  LINK_LIBRARIES MyAnalysisLib)

# Install files from the package:
atlas_install_scripts( share/*_eljob.py )
atlas_install_joboptions( share/*_jobOptions.py )
