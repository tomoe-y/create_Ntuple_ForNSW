#!/usr/bin/env python

# Read the submission directory as a command line argument. You can
# extend the list of arguments with your private ones later on.
import optparse
parser = optparse.OptionParser()
parser.add_option( '-s', '--submission-dir', dest = 'submission_dir',
                   action = 'store', type = 'string', default = 'submitDir',
                   help = 'Submission directory for EventLoop' )
( options, args ) = parser.parse_args()

# Set up (Py)ROOT.
import ROOT
ROOT.xAOD.Init().ignore()

# Set up the sample handler object. See comments from the C++ macro
# for the details about these lines.
import os
sh = ROOT.SH.SampleHandler()
sh.setMetaString( 'nc_tree', 'CollectionTree' )
# inputFilePath = '/gpfs/fs7001/youhei/AnaTutorial/kek2021/mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.deriv.DAOD_PHYS.e3601_s3126_r12629_r12636_p4619'
# inputFilePath = '/gpfs/fs7001/skanayam/HLT/data18_13TeV.00360026.physics_EnhancedBias.merge.AOD.r13109_p4812_tid26861083_00'
# ROOT.SH.ScanDir().filePattern( '*.pool.root*' ).scan( sh, inputFilePath )
# inputFilePath = '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data18_13TeV.00358031.physics_Main.merge.AOD.f1184_m2066'
inputFilePath = '/gpfs/fs7001/youhei/MuonID/aod/data18_13TeV.00358031.physics_Main.merge.AOD.r13286_p4910/'
# ROOT.SH.ScanDir().filePattern( '*.AOD.*' ).scan( sh, inputFilePath )
ROOT.SH.ScanDir().filePattern( '*root*' ).scan( sh, inputFilePath )
sh.printContent()

# Create an EventLoop job.
job = ROOT.EL.Job()
job.sampleHandler( sh )
job.options().setDouble( ROOT.EL.Job.optMaxEvents, -1 ) # maximum number of events to be analyzed. If you want to see all events, please set it to -1
job.options().setString( ROOT.EL.Job.optSubmitDirMode, 'unique-link')

# later on we'll add some configuration options for our algorithm that go here


# Create the algorithm's configuration.
from AnaAlgorithm.DualUseConfig import createAlgorithm
alg = createAlgorithm ( 'MyxAODAnalysis', 'AnalysisAlg' )

# Add our algorithm to the job
# job.algsAdd( alg )

from AnaAlgorithm.DualUseConfig import addPrivateTool

# add the muon selection tool to the algorithm
addPrivateTool( alg, 'MuonSelTool', 'CP::MuonSelectionTool' )
alg.MuonSelTool.MuQuality = 1 # 0 Tight, 1 Medium, 2 Loose, 3 VeryLoose, 4 HighPt, 5 LowPtEfficiency


# create public tools
from AnaAlgorithm.DualUseConfig import createPublicTool

# trigger configuration tool
xAODConfigTool = createPublicTool( 'TrigConf::xAODConfigTool', 'xAODConfigTool' )

# trigger decision tool
TrigDecisionTool = createPublicTool( 'Trig::TrigDecisionTool', 'TrigDecisionTool' )
TrigDecisionTool.ConfigTool = '%s/%s' %(xAODConfigTool.getType(), xAODConfigTool.getName() )
TrigDecisionTool.TrigDecisionKey = 'xTrigDecision'

from AnaAlgorithm.AnaAlgSequence import AnaAlgSequence
seq = AnaAlgSequence( "MyxAODAnalysisSequence" )

seq.addPublicTool(xAODConfigTool)
seq.addPublicTool(TrigDecisionTool)

# xAODConfigTool.OutputLevel = ROOT.MSG.DEBUG
# TrigDecisionTool.OutputLevel = ROOT.MSG.DEBUG

seq.append(alg, inputPropName = None )

for alg in seq:
    job.algsAdd (alg)
    pass

# Run the job using the direct driver.
driver = ROOT.EL.DirectDriver()
driver.submit( job, options.submission_dir )
