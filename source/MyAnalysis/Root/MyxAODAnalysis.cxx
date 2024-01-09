#include <AsgMessaging/MessageCheck.h>
#include <MyAnalysis/MyxAODAnalysis.h>

#include <TH1.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODTrigMuon/L2StandAloneMuonContainer.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODTruth/TruthParticleContainer.h>
#include <xAODTruth/xAODTruthHelpers.h>
 #include "xAODTrigMuon/TrigMuonDefs.h"

MyxAODAnalysis :: MyxAODAnalysis (const std::string& name,
                                  ISvcLocator *pSvcLocator)
  : EL::AnaAlgorithm (name, pSvcLocator),
    // m_trigConfigTool ("TrigConf::xAODConfigTool/xAODConfigTool",this),
    m_trigDecisionTool ("Trig::TrigDecisionTool/TrigDecisionTool",this),
    m_selTool ("CP::MuonSelectionTool", this),
    m_truthClassificationTool("TruthClassificationTool/TruthClassificationTool", this),
    m_extrapolator("Trk::Extrapolator/AtlasExtrapolator", this)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  This is also where you
  // declare all properties for your algorithm.  Note that things like
  // resetting statistics variables or booking histograms should
  // rather go into the initialize() function.

  // declareProperty("trigConfigTool", m_trigConfigTool, "the TrigConf::xAODConfig tool");
  declareProperty("trigDecisionTool", m_trigDecisionTool, "the TrigDecisio tool");
  declareProperty("MuonSelTool", m_selTool, "The muon selection tool");
  declareProperty("truthClassificationTool", m_truthClassificationTool, "IFF TruthClassification");
  declareProperty("TrackExtrapolator", m_extrapolator, "Track Extrapolator");

}



StatusCode MyxAODAnalysis :: initialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  ANA_CHECK (book (TH1F ("h_HLT_mu4_l2io_L1MU3V", "pass HLT_mu4_l2io_L1MU3V", 2, -0.5, 1.5)));
  ANA_CHECK (book (TH1F ("h_HLT_2mu14_l2io_L12MU8F", "pass HLT_2mu14_l2io_L12MU8F", 2, -0.5, 1.5)));
  ANA_CHECK (book (TH1F ("h_HLT_2mu6_l2io_L12MU5VF", "pass HLT_2mu6_l2io_L12MU5VF", 2, -0.5, 1.5)));
  ANA_CHECK (book (TH1F ("h_HLT_mu26_ivarmedium_mu6_probe_L1MU14FCH", "pass HLT_mu26_ivarmedium_mu6_probe_L1MU14FCH", 2, -0.5, 1.5)));
  ANA_CHECK (book (TH1F ("h_HLT_mu26_ivarmedium_mu6_l2io_probe_L1MU14FCH", "pass HLT_mu26_ivarmedium_mu6_l2io_probe_L1MU14FCH", 2, -0.5, 1.5)));
  ANA_CHECK (book (TH1F ("h_HLT_mu26_ivarmedium_mu6_l2mt_probe_L1MU14FCH", "pass HLT_mu26_ivarmedium_mu6_l2mt_probe_L1MU14FCH", 2, -0.5, 1.5)));
  ANA_CHECK (book (TH1F ("h_HLT_mu26_ivarmedium_L1MU14FCH", "pass HLT_mu26_ivarmedium_L1MU14FCH", 2, -0.5, 1.5)));

  ANA_CHECK (book (TH1F ("h_CutFlow_HLT_mu4_l2io_L1MU3V", "CutFlow HLT_mu4_l2io_L1MU3V", 10, -0.5, 9.5)));
  ANA_CHECK (book (TH1F ("h_CutFlow_HLT_2mu14_l2io_L12MU8F", "CutFlow HLT_2mu14_l2io_L12MU8F", 10, -0.5, 9.5)));
  ANA_CHECK (book (TH1F ("h_CutFlow_HLT_2mu6_l2io_L12MU5VF", "CutFlow HLT_2mu6_l2io_L12MU5VF", 10, -0.5, 9.5)));
  ANA_CHECK (book (TH1F ("h_CutFlow_HLT_mu6_L1MU5VF", "CutFlow HLT_mu6_L1MU5VF", 10, -0.5, 9.5)));
  ANA_CHECK (book (TH1F ("h_CutFlow_HLT_mu4_L1MU4", "CutFlow HLT_mu4_L1MU4", 10, -0.5, 9.5)));
  ANA_CHECK (book (TH1F ("h_CutFlow_HLT_mu6_L1MU6", "CutFlow HLT_mu6_L1MU6", 10, -0.5, 9.5)));

  // ANA_CHECK( m_trigConfigTool.retrieve() );
  ANA_CHECK( m_trigDecisionTool.retrieve() );
  ANA_CHECK( m_selTool.retrieve() );

  ATH_CHECK( m_truthClassificationTool.retrieve() );
/*
  //ATH_CHECK( m_extrapolator.retrieve() );
  if (!m_extrapolator.empty())
    ATH_CHECK(m_extrapolator.retrieve());
  else
    m_extrapolator.disable();
*/
  ATH_CHECK(m_eventInfo.initialize());

  ANA_CHECK( m_L2CBIOKey.initialize() );
  ANA_CHECK( m_L2SAMTKey.initialize() );
  ANA_CHECK( m_roiKey.initialize() );



  ANA_CHECK (book (TTree ("analysis", "My analysis tree")));
  TTree* mytree = tree ("analysis");
  mytree->Branch ("RunNumber", &m_runNumber);
  mytree->Branch ("LumiBlock", &m_lumiBlock);
  mytree->Branch ("EventNumber", &m_eventNumber);
  mytree->Branch ("mcEventWeight", &m_mcEventWeight);
  mytree->Branch ("actualInteractionsPerCrossing", &m_actualInteractionsPerCrossing);
  mytree->Branch ("averageInteractionsPerCrossing", &m_averageInteractionsPerCrossing);
  mytree->Branch ("pass_HLT_mu10_l2mt_L1MU10BOM", &m_pass_HLT_mu10_l2mt_L1MU10BOM);
  mytree->Branch ("pass_HLT_2mu10_l2mt_L1MU10BOM", &m_pass_HLT_2mu10_l2mt_L1MU10BOM);
  mytree->Branch ("pass_HLT_2mu10_bJpsimumu_L12MU8F", &m_pass_HLT_2mu10_bJpsimumu_L12MU8F);
  mytree->Branch ("pass_HLT_mu24_ivarmedium_L1MU14FCH", &m_pass_HLT_mu24_ivarmedium_L1MU14FCH);
  mytree->Branch ("pass_HLT_2mu14_L12MU8F", &m_pass_HLT_2mu14_L12MU8F);

  m_muon_e = std::make_unique<std::vector<float>>();
  m_muon_pt = std::make_unique<std::vector<float>>();
  m_muon_eta = std::make_unique<std::vector<float>>();
  m_muon_phi = std::make_unique<std::vector<float>>();
  m_muon_charge = std::make_unique<std::vector<float>>();
  m_muon_quality = std::make_unique<std::vector<int>>();
  m_muon_isBadMuon_other = std::make_unique<std::vector<bool>>();
  m_muon_truthType = std::make_unique<std::vector<int>>();
  m_muon_truthTypeMCTC = std::make_unique<std::vector<int>>();
  m_muon_truthOriginMCTC = std::make_unique<std::vector<int>>();
  m_muon_IFFtruthType = std::make_unique<std::vector<int>>();
  m_muon_muonType = std::make_unique<std::vector<int>>();
  m_muon_author = std::make_unique<std::vector<int>>();

  m_truthmuon_e = std::make_unique<std::vector<float>>();
  m_truthmuon_pt = std::make_unique<std::vector<float>>();
  m_truthmuon_eta = std::make_unique<std::vector<float>>();
  m_truthmuon_phi = std::make_unique<std::vector<float>>();
  m_truthmuon_pdgId = std::make_unique<std::vector<int>>();
  m_muon_mePt = std::make_unique<std::vector<float>>();
  m_muon_idPt = std::make_unique<std::vector<float>>();
  m_muon_cbPt = std::make_unique<std::vector<float>>();
  m_muon_meP = std::make_unique<std::vector<float>>();
  m_muon_idP = std::make_unique<std::vector<float>>();
  m_muon_etaMS = std::make_unique<std::vector<float>>();
  m_muon_phiMS = std::make_unique<std::vector<float>>();

  m_muon_innerSmallHits = std::make_unique<std::vector<int>>();
  m_muon_innerLargeHits = std::make_unique<std::vector<int>>();
  m_muon_middleSmallHits = std::make_unique<std::vector<int>>();
  m_muon_middleLargeHits = std::make_unique<std::vector<int>>();
  m_muon_outerSmallHits = std::make_unique<std::vector<int>>();
  m_muon_outerLargeHits = std::make_unique<std::vector<int>>();
  m_muon_extendedSmallHits = std::make_unique<std::vector<int>>();
  m_muon_extendedLargeHits = std::make_unique<std::vector<int>>();

  m_mu_ext_b_targetEtaVec = std::make_unique<std::vector<std::vector<float>>>();
  m_mu_ext_b_targetPhiVec = std::make_unique<std::vector<std::vector<float>>>();

  // sTGC
  m_muon_phiLayer1STGCHits = std::make_unique<std::vector<uint8_t>>();
  m_muon_phiLayer2STGCHits = std::make_unique<std::vector<uint8_t>>();
  m_muon_etaLayer1STGCHits = std::make_unique<std::vector<uint8_t>>();
  m_muon_etaLayer2STGCHits = std::make_unique<std::vector<uint8_t>>();
  m_muon_phiLayer1STGCHoles = std::make_unique<std::vector<uint8_t>>();
  m_muon_phiLayer2STGCHoles = std::make_unique<std::vector<uint8_t>>();
  m_muon_etaLayer1STGCHoles = std::make_unique<std::vector<uint8_t>>();
  m_muon_etaLayer2STGCHoles = std::make_unique<std::vector<uint8_t>>();

  // MM
  m_muon_MMHits = std::make_unique<std::vector<uint8_t>>();
  m_muon_MMHoles = std::make_unique<std::vector<uint8_t>>();

  // segment
  m_muon_nSegments = std::make_unique<std::vector<size_t>>();
  m_muon_seg_chiSquared = std::make_unique<std::vector<std::vector<float>>>();
  m_muon_seg_numberDoF = std::make_unique<std::vector<std::vector<float>>>();
  m_muon_seg_sector = std::make_unique<std::vector<std::vector<int>>>();
  m_muon_seg_chamberIndex = std::make_unique<std::vector<std::vector<int>>>();
  m_muon_seg_nPrecisionHits = std::make_unique<std::vector<std::vector<int>>>();
  m_muon_seg_nPhiLayers = std::make_unique<std::vector<std::vector<int>>>();
  m_muon_seg_nTrigEtaLayers = std::make_unique<std::vector<std::vector<int>>>();
  m_muon_seg_x = std::make_unique<std::vector<std::vector<float>>>();
  m_muon_seg_y = std::make_unique<std::vector<std::vector<float>>>();
  m_muon_seg_z = std::make_unique<std::vector<std::vector<float>>>();
  m_muon_seg_px = std::make_unique<std::vector<std::vector<float>>>();
  m_muon_seg_py = std::make_unique<std::vector<std::vector<float>>>();
  m_muon_seg_pz = std::make_unique<std::vector<std::vector<float>>>();

  // muon RoI
  m_roi_eta = std::make_unique<std::vector<float>>();
  m_roi_phi = std::make_unique<std::vector<float>>();
  m_roi_thrNumber = std::make_unique<std::vector<short>>();
  m_roi_RoINumber = std::make_unique<std::vector<short>>();
  m_roi_sectorAddress = std::make_unique<std::vector<short>>();
  m_roi_source = std::make_unique<std::vector<short>>();
  m_roi_hemisphere = std::make_unique<std::vector<short>>();
  m_roi_firstCandidate = std::make_unique<std::vector<short>>();
  m_roi_moreCandInRoI = std::make_unique<std::vector<short>>();
  m_roi_moreCandInSector = std::make_unique<std::vector<short>>();
  m_roi_charge = std::make_unique<std::vector<short>>();
  m_roi_BW3coin = std::make_unique<std::vector<short>>();
  m_roi_InnerCoin = std::make_unique<std::vector<short>>();
  m_roi_GoodMF = std::make_unique<std::vector<short>>();
  m_roi_vetoed = std::make_unique<std::vector<short>>();

  m_l2sa_e = std::make_unique<std::vector<float>>();
  m_l2sa_pt = std::make_unique<std::vector<float>>();
  m_l2sa_eta = std::make_unique<std::vector<float>>();
  m_l2sa_phi = std::make_unique<std::vector<float>>();
  m_l2sa_etaMS = std::make_unique<std::vector<float>>();
  m_l2sa_phiMS = std::make_unique<std::vector<float>>();
  m_l2sa_pass = std::make_unique<std::vector<bool>>();

  m_l2sa_superPointR = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_superPointZ = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_superPointSlope = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_superPointIntercept = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_superPointChi2 = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_stgcClusterLayer = std::make_unique<std::vector<std::vector<unsigned int>>>();
  m_l2sa_stgcClusterIsOutlier = std::make_unique<std::vector<std::vector<int>>>();
  m_l2sa_stgcClusterType = std::make_unique<std::vector<std::vector<int>>>();
  m_l2sa_stgcClusterEta = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_stgcClusterPhi = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_stgcClusterR = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_stgcClusterZ = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_stgcClusterResidualR = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_stgcClusterResidualPhi = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_stgcClusterStationEta = std::make_unique<std::vector<std::vector<int>>>();
  m_l2sa_stgcClusterStationPhi = std::make_unique<std::vector<std::vector<int>>>();
  m_l2sa_stgcClusterStationName = std::make_unique<std::vector<std::vector<int>>>();
  m_l2sa_mmClusterLayer = std::make_unique<std::vector<std::vector<unsigned int>>>();
  m_l2sa_mmClusterIsOutlier = std::make_unique<std::vector<std::vector<int>>>();
  m_l2sa_mmClusterEta = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_mmClusterPhi = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_mmClusterR = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_mmClusterZ = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_mmClusterResidualR = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_mmClusterResidualPhi = std::make_unique<std::vector<std::vector<float>>>();
  m_l2sa_mmClusterStationEta = std::make_unique<std::vector<std::vector<int>>>();
  m_l2sa_mmClusterStationPhi = std::make_unique<std::vector<std::vector<int>>>();
  m_l2sa_mmClusterStationName = std::make_unique<std::vector<std::vector<int>>>();

  m_l2sa_ptEndcapAlpha = std::make_unique<std::vector<float>>();
  m_l2sa_ptEndcapBeta = std::make_unique<std::vector<float>>();

  m_l2cb_e = std::make_unique<std::vector<float>>();
  m_l2cb_pt = std::make_unique<std::vector<float>>();
  m_l2cb_eta = std::make_unique<std::vector<float>>();
  m_l2cb_phi = std::make_unique<std::vector<float>>();
  m_l2cb_pass = std::make_unique<std::vector<bool>>();

  m_l1_eta = std::make_unique<std::vector<float>>();
  m_l1_phi = std::make_unique<std::vector<float>>();
  m_l1_dRoff = std::make_unique<std::vector<float>>();
  m_l1_BOM = std::make_unique<std::vector<int>>();
  m_l1_thrNum = std::make_unique<std::vector<int>>();
  m_l1_roiNum = std::make_unique<std::vector<int>>();


  m_chain = std::make_unique<std::vector<std::string>>();
  m_typeVec = std::make_unique<std::vector<std::vector<int>>>();
  m_ptVec = std::make_unique<std::vector<std::vector<float>>>();
  m_etaVec = std::make_unique<std::vector<std::vector<float>>>();
  m_phiVec = std::make_unique<std::vector<std::vector<float>>>();

  // RPC position
	m_b_extPosition.clear();
	m_b_extPosition.push_back(6880.);
	m_b_extPosition.push_back(7500.);
	m_b_extPosition.push_back(7860.);
	m_b_extPosition.push_back(8420.);
	m_b_extPosition.push_back(9880.);
	m_b_extPosition.push_back(10260.);

  mytree->Branch ("muon_e", &*m_muon_e);
  mytree->Branch ("muon_pt", &*m_muon_pt);
  mytree->Branch ("muon_eta", &*m_muon_eta);
  mytree->Branch ("muon_phi", &*m_muon_phi);
  mytree->Branch ("muon_charge", &*m_muon_charge);
  mytree->Branch ("muon_quality", &*m_muon_quality);
  mytree->Branch ("muon_isBadMuon_other", &*m_muon_isBadMuon_other);
  mytree->Branch ("muon_truthType", &*m_muon_truthType);
  mytree->Branch ("muon_truthTypeMCTC", &*m_muon_truthTypeMCTC);
  mytree->Branch ("muon_truthOriginMCTC", &*m_muon_truthOriginMCTC);
  mytree->Branch ("muon_IFFtruthType", &*m_muon_IFFtruthType);
  mytree->Branch ("muon_muonType", &*m_muon_muonType);
  mytree->Branch ("muon_author", &*m_muon_author);

  mytree->Branch ("truthmuon_e", &*m_truthmuon_e);
  mytree->Branch ("truthmuon_pt", &*m_truthmuon_pt);
  mytree->Branch ("truthmuon_eta", &*m_truthmuon_eta);
  mytree->Branch ("truthmuon_phi", &*m_truthmuon_phi);
  mytree->Branch ("truthmuon_pdgId", &*m_truthmuon_pdgId);
  mytree->Branch ("muon_mePt", &*m_muon_mePt);
  mytree->Branch ("muon_idPt", &*m_muon_idPt);
  mytree->Branch ("muon_cbPt", &*m_muon_cbPt);
  mytree->Branch ("muon_meP", &*m_muon_meP);
  mytree->Branch ("muon_idP", &*m_muon_idP);
  mytree->Branch ("muon_etaMS", &*m_muon_etaMS);
  mytree->Branch ("muon_phiMS", &*m_muon_phiMS);

  mytree->Branch ("muon_innerSmallHits", &*m_muon_innerSmallHits);
  mytree->Branch ("muon_innerLargeHits", &*m_muon_innerLargeHits);
  mytree->Branch ("muon_middleSmallHits", &*m_muon_middleSmallHits);
  mytree->Branch ("muon_middleLargeHits", &*m_muon_middleLargeHits);
  mytree->Branch ("muon_outerSmallHits", &*m_muon_outerSmallHits);
  mytree->Branch ("muon_outerLargeHits", &*m_muon_outerLargeHits);
  mytree->Branch ("muon_extendedSmallHits", &*m_muon_extendedSmallHits);
  mytree->Branch ("muon_extendedLargeHits", &*m_muon_extendedLargeHits);

  mytree->Branch ("mu_ext_b_targetEtaVec", &*m_mu_ext_b_targetEtaVec);
  mytree->Branch ("mu_ext_b_targetPhiVec", &*m_mu_ext_b_targetPhiVec);

  // sTGC
  mytree->Branch ("muon_phiLayer1STGCHits", &*m_muon_phiLayer1STGCHits);
  mytree->Branch ("muon_phiLayer2STGCHits", &*m_muon_phiLayer2STGCHits);
  mytree->Branch ("muon_etaLayer1STGCHits", &*m_muon_etaLayer1STGCHits);
  mytree->Branch ("muon_etaLayer2STGCHits", &*m_muon_etaLayer2STGCHits);
  mytree->Branch ("muon_phiLayer1STGCHoles", &*m_muon_phiLayer1STGCHoles);
  mytree->Branch ("muon_phiLayer2STGCHoles", &*m_muon_phiLayer2STGCHoles);
  mytree->Branch ("muon_etaLayer1STGCHoles", &*m_muon_etaLayer1STGCHoles);
  mytree->Branch ("muon_etaLayer2STGCHoles", &*m_muon_etaLayer2STGCHoles);

  // MM
  mytree->Branch ("muon_MMHits", &*m_muon_MMHits);
  mytree->Branch ("muon_MMHoles", &*m_muon_MMHoles);

  // segment
  mytree->Branch ("muon_nSegments", &*m_muon_nSegments);
  mytree->Branch ("muon_seg_chiSquared", &*m_muon_seg_chiSquared);
  mytree->Branch ("muon_seg_numberDoF", &*m_muon_seg_numberDoF);
  mytree->Branch ("muon_seg_sector", &*m_muon_seg_sector);
  mytree->Branch ("muon_seg_chamberIndex", &*m_muon_seg_chamberIndex);
  mytree->Branch ("muon_seg_nPrecisionHits", &*m_muon_seg_nPrecisionHits);
  mytree->Branch ("muon_seg_nPhiLayers", &*m_muon_seg_nPhiLayers);
  mytree->Branch ("muon_seg_nTrigEtaLayers", &*m_muon_seg_nTrigEtaLayers);
  mytree->Branch ("muon_seg_x", &*m_muon_seg_x);
  mytree->Branch ("muon_seg_y", &*m_muon_seg_y);
  mytree->Branch ("muon_seg_z", &*m_muon_seg_z);
  mytree->Branch ("muon_seg_px", &*m_muon_seg_px);
  mytree->Branch ("muon_seg_py", &*m_muon_seg_py);
  mytree->Branch ("muon_seg_pz", &*m_muon_seg_pz);

  mytree->Branch ("trig_L1_mu_eta", &*m_roi_eta);
  mytree->Branch ("trig_L1_mu_phi", &*m_roi_phi);
  mytree->Branch ("trig_L1_mu_thrNumber", &*m_roi_thrNumber);
  mytree->Branch ("trig_L1_mu_RoINumber", &*m_roi_RoINumber);
  mytree->Branch ("trig_L1_mu_sectorAddress", &*m_roi_sectorAddress);
  mytree->Branch ("trig_L1_mu_source", &*m_roi_source);
  mytree->Branch ("trig_L1_mu_hemisphere", &*m_roi_hemisphere);
  mytree->Branch ("trig_L1_mu_firstCandidate", &*m_roi_firstCandidate);
  mytree->Branch ("trig_L1_mu_moreCandInRPCPad", &*m_roi_moreCandInRoI);
  mytree->Branch ("trig_L1_mu_moreCandInSector", &*m_roi_moreCandInSector);
  mytree->Branch ("trig_L1_mu_charge", &*m_roi_charge);
  mytree->Branch ("trig_L1_mu_BWcoin", &*m_roi_BW3coin);
  mytree->Branch ("trig_L1_mu_InnerCoin", &*m_roi_InnerCoin);
  mytree->Branch ("trig_L1_mu_GoodMF", &*m_roi_GoodMF);
  mytree->Branch ("trig_L1_mu_vetoed", &*m_roi_vetoed);



 //l2sa
  mytree->Branch ("l2sa_e", &*m_l2sa_e);
  mytree->Branch ("l2sa_pt", &*m_l2sa_pt);
  mytree->Branch ("l2sa_eta", &*m_l2sa_eta);
  mytree->Branch ("l2sa_phi", &*m_l2sa_phi);
  mytree->Branch ("l2sa_etaMS", &*m_l2sa_etaMS);
  mytree->Branch ("l2sa_phiMS", &*m_l2sa_phiMS);
  mytree->Branch ("l2sa_pass", &*m_l2sa_pass);
  mytree->Branch ("l2sa_superPointR", &*m_l2sa_superPointR);
  mytree->Branch ("l2sa_superPointZ", &*m_l2sa_superPointZ);
  mytree->Branch ("l2sa_superPointSlope", &*m_l2sa_superPointSlope);
  mytree->Branch ("l2sa_superPointIntercept", &*m_l2sa_superPointIntercept);
  mytree->Branch ("l2sa_superPointChi2", &*m_l2sa_superPointChi2);
  mytree->Branch ("l2sa_stgcClusterLayer", &*m_l2sa_stgcClusterLayer);
  mytree->Branch ("l2sa_stgcClusterIsOutlier", &*m_l2sa_stgcClusterIsOutlier);
  mytree->Branch ("l2sa_stgcClusterType", &*m_l2sa_stgcClusterType);
  mytree->Branch ("l2sa_stgcClusterEta", &*m_l2sa_stgcClusterEta);
  mytree->Branch ("l2sa_stgcClusterPhi", &*m_l2sa_stgcClusterPhi);
  mytree->Branch ("l2sa_stgcClusterR", &*m_l2sa_stgcClusterR);
  mytree->Branch ("l2sa_stgcClusterZ", &*m_l2sa_stgcClusterZ);
  mytree->Branch ("l2sa_stgcClusterResidualR", &*m_l2sa_stgcClusterResidualR);
  mytree->Branch ("l2sa_stgcClusterResidualPhi", &*m_l2sa_stgcClusterResidualPhi);
  mytree->Branch ("l2sa_stgcClusterStationEta", &*m_l2sa_stgcClusterStationEta);
  mytree->Branch ("l2sa_stgcClusterStationPhi", &*m_l2sa_stgcClusterStationPhi);
  mytree->Branch ("l2sa_stgcClusterStationName", &*m_l2sa_stgcClusterStationName);
  mytree->Branch ("l2sa_mmClusterLayer", &*m_l2sa_mmClusterLayer);
  mytree->Branch ("l2sa_mmClusterIsOutlier", &*m_l2sa_mmClusterIsOutlier);
  mytree->Branch ("l2sa_mmClusterEta", &*m_l2sa_mmClusterEta);
  mytree->Branch ("l2sa_mmClusterPhi", &*m_l2sa_mmClusterPhi);
  mytree->Branch ("l2sa_mmClusterR", &*m_l2sa_mmClusterR);
  mytree->Branch ("l2sa_mmClusterZ", &*m_l2sa_mmClusterZ);
  mytree->Branch ("l2sa_mmClusterResidualR", &*m_l2sa_mmClusterResidualR);
  mytree->Branch ("l2sa_mmClusterResidualPhi", &*m_l2sa_mmClusterResidualPhi);
  mytree->Branch ("l2sa_mmClusterStationEta", &*m_l2sa_mmClusterStationEta);
  mytree->Branch ("l2sa_mmClusterStationPhi", &*m_l2sa_mmClusterStationPhi);
  mytree->Branch ("l2sa_mmClusterStationName", &*m_l2sa_mmClusterStationName);

  mytree->Branch ("l2sa_ptEndcapAlpha", &*m_l2sa_ptEndcapAlpha);
  mytree->Branch ("l2sa_ptEndcapBeta", &*m_l2sa_ptEndcapBeta);



  mytree->Branch ("l1_eta", &*m_l1_eta);
  mytree->Branch ("l1_phi", &*m_l1_phi);
  mytree->Branch ("l1_dRoff", &*m_l1_dRoff);
  mytree->Branch ("l1_BOM", &*m_l1_BOM);
  mytree->Branch ("l1_thrNum", &*m_l1_thrNum);
  mytree->Branch ("l1_roiNum", &*m_l1_roiNum);

  mytree->Branch ("l2cb_e", &*m_l2cb_e);
  mytree->Branch ("l2cb_pt", &*m_l2cb_pt);
  mytree->Branch ("l2cb_eta", &*m_l2cb_eta);
  mytree->Branch ("l2cb_phi", &*m_l2cb_phi);
  mytree->Branch ("l2cb_pass", &*m_l2cb_pass);

  mytree->Branch("trigger_info_chain", &*m_chain);
  mytree->Branch("trigger_info_typeVec", &*m_typeVec);
  mytree->Branch("trigger_info_ptVec", &*m_ptVec);
  mytree->Branch("trigger_info_etaVec", &*m_etaVec);
  mytree->Branch("trigger_info_phiVec", &*m_phiVec);


  return StatusCode::SUCCESS;
}


StatusCode MyxAODAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  // if(!m_trigDecisionTool->isPassed("HLT_mu24_ivarmedium_L1MU14FCH"))
  //   return StatusCode::SUCCESS;


  const float ZERO_LIMIT = 0.00001;


  // Get the truth Muons from the event:
  // const xAOD::TruthParticleContainer* truthmuons = 0;
  // ANA_CHECK(evtStore()->retrieve( truthmuons, "TruthMuons" ) );
  SG::ReadHandle<xAOD::EventInfo> eventInfo(m_eventInfo);
  bool isMC = eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION );

  m_runNumber = eventInfo->runNumber();
  m_lumiBlock = eventInfo->lumiBlock();
  m_eventNumber = eventInfo->eventNumber();
  m_mcEventWeight = eventInfo->mcEventWeight();
  m_actualInteractionsPerCrossing = eventInfo->averageInteractionsPerCrossing();
  m_averageInteractionsPerCrossing = eventInfo->actualInteractionsPerCrossing();
  
  m_pass_HLT_mu10_l2mt_L1MU10BOM = m_trigDecisionTool->isPassed("HLT_mu10_l2mt_L1MU10BOM");
  m_pass_HLT_2mu10_l2mt_L1MU10BOM = m_trigDecisionTool->isPassed("HLT_2mu10_l2mt_L1MU10BOM");
  m_pass_HLT_2mu10_bJpsimumu_L12MU8F = m_trigDecisionTool->isPassed("HLT_2mu10_bJpsimumu_L12MU8F");
  m_pass_HLT_mu24_ivarmedium_L1MU14FCH = m_trigDecisionTool->isPassed("HLT_mu24_ivarmedium_L1MU14FCH");
  m_pass_HLT_2mu14_L12MU8F = m_trigDecisionTool->isPassed("HLT_2mu14_L12MU8F");

  // Muons
  m_muon_e->clear();
  m_muon_pt->clear();
  m_muon_eta->clear();
  m_muon_phi->clear();
  m_muon_charge->clear();
  m_muon_quality->clear();
  m_muon_isBadMuon_other->clear();
  m_muon_truthType->clear();
  m_muon_truthTypeMCTC->clear();
  m_muon_truthOriginMCTC->clear();
  m_muon_IFFtruthType->clear();
  m_muon_muonType->clear();
  m_muon_author->clear();
  m_truthmuon_e->clear();
  m_truthmuon_pt->clear();
  m_truthmuon_eta->clear();
  m_truthmuon_phi->clear();
  m_truthmuon_pdgId->clear();
  m_muon_mePt->clear();
  m_muon_idPt->clear();
  m_muon_cbPt->clear();
  m_muon_meP->clear();
  m_muon_idP->clear();
  m_muon_etaMS->clear();
  m_muon_phiMS->clear();
  m_muon_innerSmallHits->clear();
  m_muon_innerLargeHits->clear();
  m_muon_middleSmallHits->clear();
  m_muon_middleLargeHits->clear();
  m_muon_outerSmallHits->clear();
  m_muon_outerLargeHits->clear();
  m_muon_extendedSmallHits->clear();
  m_muon_extendedLargeHits->clear();
  m_mu_ext_b_targetEtaVec->clear();
  m_mu_ext_b_targetPhiVec->clear();
  m_muon_phiLayer1STGCHits->clear();
  m_muon_phiLayer2STGCHits->clear();
  m_muon_etaLayer1STGCHits->clear();
  m_muon_etaLayer2STGCHits->clear();
  m_muon_phiLayer1STGCHoles->clear();
  m_muon_phiLayer2STGCHoles->clear();
  m_muon_etaLayer1STGCHoles->clear();
  m_muon_etaLayer2STGCHoles->clear();
  m_muon_MMHits->clear();
  m_muon_MMHoles->clear();
  m_muon_nSegments->clear();
  m_muon_seg_chiSquared->clear();
  m_muon_seg_numberDoF->clear();
  m_muon_seg_sector->clear();
  m_muon_seg_chamberIndex->clear();
  m_muon_seg_nPrecisionHits->clear();
  m_muon_seg_nPhiLayers->clear();
  m_muon_seg_nTrigEtaLayers->clear();
  m_muon_seg_x->clear();
  m_muon_seg_y->clear();
  m_muon_seg_z->clear();
  m_muon_seg_px->clear();
  m_muon_seg_py->clear();
  m_muon_seg_pz->clear();

  m_roi_eta->clear();
  m_roi_phi->clear();
  m_roi_thrNumber->clear();
  m_roi_RoINumber->clear();
  m_roi_sectorAddress->clear();
  m_roi_source->clear();
  m_roi_hemisphere->clear();
  m_roi_firstCandidate->clear();
  m_roi_moreCandInRoI->clear();
  m_roi_moreCandInSector->clear();
  m_roi_charge->clear();
  m_roi_BW3coin->clear();
  m_roi_InnerCoin->clear();
  m_roi_GoodMF->clear();
  m_roi_vetoed->clear();


  m_l1_eta->clear();
  m_l1_phi->clear();
  m_l1_dRoff->clear();
  m_l1_BOM->clear();
  m_l1_thrNum->clear();
  m_l1_roiNum->clear();

  m_l2sa_e->clear();
  m_l2sa_pt->clear();
  m_l2sa_eta->clear();
  m_l2sa_phi->clear();
  m_l2sa_etaMS->clear();
  m_l2sa_phiMS->clear();
  m_l2sa_pass->clear();
  m_l2sa_superPointR->clear();
  m_l2sa_superPointZ->clear();
  m_l2sa_superPointSlope->clear();
  m_l2sa_superPointIntercept->clear();
  m_l2sa_superPointChi2->clear();
  m_l2sa_stgcClusterLayer->clear();
  m_l2sa_stgcClusterIsOutlier->clear();
  m_l2sa_stgcClusterType->clear();
  m_l2sa_stgcClusterEta->clear();
  m_l2sa_stgcClusterPhi->clear();
  m_l2sa_stgcClusterR->clear();
  m_l2sa_stgcClusterZ->clear();
  m_l2sa_stgcClusterResidualR->clear();
  m_l2sa_stgcClusterResidualPhi->clear();
  m_l2sa_stgcClusterStationEta->clear();
  m_l2sa_stgcClusterStationPhi->clear();
  m_l2sa_stgcClusterStationName->clear();
  m_l2sa_mmClusterLayer->clear();
  m_l2sa_mmClusterIsOutlier->clear();
  m_l2sa_mmClusterEta->clear();
  m_l2sa_mmClusterPhi->clear();
  m_l2sa_mmClusterR->clear();
  m_l2sa_mmClusterZ->clear();
  m_l2sa_mmClusterResidualR->clear();
  m_l2sa_mmClusterResidualPhi->clear();
  m_l2sa_mmClusterStationEta->clear();
  m_l2sa_mmClusterStationPhi->clear();
  m_l2sa_mmClusterStationName->clear();

  m_l2sa_ptEndcapAlpha->clear();
  m_l2sa_ptEndcapBeta->clear();

  m_l2cb_e->clear();
  m_l2cb_pt->clear();
  m_l2cb_eta->clear();
  m_l2cb_phi->clear();
  m_l2cb_pass->clear();

  m_chain->clear();
  m_typeVec->clear();
  m_ptVec->clear();
  m_etaVec->clear();
  m_phiVec->clear();


  const xAOD::MuonContainer* muons = nullptr;
  ANA_CHECK(evtStore()->retrieve(muons, "Muons"));



  // reco-muon to reco-muon overlap removal
  std::vector<float> prompt_reco_dR;
  std::vector<int> matchedreco_idx;
  float dR = 999;
  size_t reco_idx = -1;
  for( reco_idx = 0; reco_idx < muons->size(); reco_idx++ ) {

    if(muons->at(reco_idx)->muonType()>xAOD::Muon::MuonType::Combined) continue; // combined muon only
    // if(!m_selTool->accept(*muons->at(reco_idx))) continue;
    if(muons->at(reco_idx)->author()!=1) continue; // MuidCo only

    const xAOD::TrackParticle* reco_MS_track = nullptr;
    if (muons->at(reco_idx)->isAvailable<ElementLink<xAOD::TrackParticleContainer> >("muonSpectrometerTrackParticleLink") &&
	(muons->at(reco_idx)->muonSpectrometerTrackParticleLink()).isValid())
      reco_MS_track = muons->at(reco_idx)->trackParticle(xAOD::Muon::MuonSpectrometerTrackParticle);

    bool removed = false;
    float dRmin = 999;

    for( size_t ref_idx = 0; ref_idx < muons->size(); ref_idx++ ) {

      if(reco_idx == ref_idx) continue;

      if(muons->at(ref_idx)->muonType()>xAOD::Muon::MuonType::Combined) continue; // combined muon only
      // if(!m_selTool->accept(*muons->at(ref_idx))) continue;
      if(muons->at(ref_idx)->author()!=1) continue; // MuidCo only

      const xAOD::TrackParticle* ref_MS_track = nullptr;
      if (muons->at(ref_idx)->isAvailable<ElementLink<xAOD::TrackParticleContainer> >("muonSpectrometerTrackParticleLink") &&
      (muons->at(ref_idx)->muonSpectrometerTrackParticleLink()).isValid())
      ref_MS_track = muons->at(ref_idx)->trackParticle(xAOD::Muon::MuonSpectrometerTrackParticle);

      dR = reco_MS_track->p4().DeltaR(ref_MS_track->p4());
      if(dR < dRmin)
        dRmin = dR;

      if(dR < 0.2) {
        removed = true;
      }
    }

    if(!removed) {
      matchedreco_idx.push_back(reco_idx);
      prompt_reco_dR.push_back(dRmin);
    }

  }


  reco_idx = -1;


  for (const xAOD::Muon* muon : *muons) {
    reco_idx++;

    //------------------------------------
    // Truth matching
    //std::vector<int>::iterator itr = std::find(matchedreco_idx.begin(), matchedreco_idx.end(), reco_idx);
    //if (itr == matchedreco_idx.end()) {
    //  continue;
    //}
    //------------------------------------


    if(muon->muonType()>xAOD::Muon::MuonType::Combined) continue; // combined muon only
    // if(!m_selTool->accept(*muon)) continue;
    if(muon->author()!=1) continue; // MuidCo only

    ANA_MSG_DEBUG ("  muon pt/eta/phi = " << muon->pt()*0.001 << "/" << muon->eta() << "/" << muon->phi());

    uint8_t innerSmallHits(0), innerLargeHits(0), middleSmallHits(0), middleLargeHits(0),
      outerSmallHits(0), outerLargeHits(0), extendedSmallHits(0), extendedLargeHits(0);
    if (!muon->summaryValue(innerSmallHits, xAOD::MuonSummaryType::innerSmallHits) ||
        !muon->summaryValue(innerLargeHits, xAOD::MuonSummaryType::innerLargeHits) ||
        !muon->summaryValue(middleSmallHits, xAOD::MuonSummaryType::middleSmallHits) ||
        !muon->summaryValue(middleLargeHits, xAOD::MuonSummaryType::middleLargeHits) ||
        !muon->summaryValue(outerSmallHits, xAOD::MuonSummaryType::outerSmallHits) ||
        !muon->summaryValue(outerLargeHits, xAOD::MuonSummaryType::outerLargeHits) ||
        !muon->summaryValue(extendedSmallHits, xAOD::MuonSummaryType::extendedSmallHits) ||
        !muon->summaryValue(extendedLargeHits, xAOD::MuonSummaryType::extendedLargeHits)) {
        ATH_MSG_WARNING("MS hits information missing!!!");
    }


    float etaMS = -999;
    float phiMS = -999;
    const xAOD::TrackParticle* MS_track = nullptr;

    if (muon->isAvailable<ElementLink<xAOD::TrackParticleContainer> >("muonSpectrometerTrackParticleLink") &&
	(muon->muonSpectrometerTrackParticleLink()).isValid())
      MS_track = muon->trackParticle(xAOD::Muon::MuonSpectrometerTrackParticle);
    else {
      ATH_MSG_VERBOSE("passedHighPtCuts - No MS track available for muon. Using combined track.");
      MS_track = muon->trackParticle(xAOD::Muon::CombinedTrackParticle);
    }
    if (MS_track) {
      etaMS = MS_track->eta();
      phiMS = MS_track->phi();
    }

    float mePt = -999999., idPt = -999999.;
    float meP = -999999., idP = -999999.;
    const xAOD::TrackParticle* idtrack = muon->trackParticle(xAOD::Muon::InnerDetectorTrackParticle);
    const xAOD::TrackParticle* metrack = muon->trackParticle(xAOD::Muon::ExtrapolatedMuonSpectrometerTrackParticle);
    if (idtrack && metrack && metrack->definingParametersCovMatrix()(4, 4) > 0) {

      // mePt = mePt_acc(mu);
      // idPt = idPt_acc(mu);
      mePt = metrack->pt();
      idPt = idtrack->pt();

      meP = 1.0 / (std::sin(metrack->theta()) / mePt);
      idP = 1.0 / (std::sin(idtrack->theta()) / idPt);

    } else {
      ATH_MSG_VERBOSE("Muon missing ID or ME tracks - fail high-pT");
    }

    unsigned int IFFtype(0);
    float truth_e = -99999, truth_pt = -99999, truth_eta = -99999, truth_phi = -99999;
    int truth_pdgId = -99999;
    int truthTypeMCTC(-99999);
    int truthOriginMCTC(-99999);
    if(isMC) {
      ATH_CHECK(m_truthClassificationTool->classify(*muon, IFFtype));

      const xAOD::TruthParticle* truth_muon = xAOD::TruthHelpers::getTruthParticle(*muon);
      if(truth_muon) {
        ATH_MSG_DEBUG("Truth Muon pt/eta/phi = " << truth_muon->pt()*0.001 << "/" << truth_muon->eta() << "/" << truth_muon->phi() << " pdgId = " << truth_muon->pdgId());

        truth_e = truth_muon->e();
        truth_pt = truth_muon->pt();
        truth_eta = truth_muon->eta();
        truth_phi = truth_muon->phi();
        truth_pdgId = truth_muon->pdgId();
      }


      // MCTC
      truthTypeMCTC = muon->auxdata<int>("truthType");
      truthOriginMCTC = muon->auxdata<int>("truthOrigin");

    }

    uint8_t phiLayer1STGCHits(0), phiLayer2STGCHits(0), etaLayer1STGCHits(0), etaLayer2STGCHits(0), phiLayer1STGCHoles(0), phiLayer2STGCHoles(0), etaLayer1STGCHoles(0), etaLayer2STGCHoles(0);
    if (!muon->summaryValue(phiLayer1STGCHits, xAOD::MuonSummaryType::phiLayer1STGCHits) ||
        !muon->summaryValue(phiLayer2STGCHits, xAOD::MuonSummaryType::phiLayer2STGCHits) ||
        !muon->summaryValue(etaLayer1STGCHits, xAOD::MuonSummaryType::etaLayer1STGCHits) ||
        !muon->summaryValue(etaLayer2STGCHits, xAOD::MuonSummaryType::etaLayer2STGCHits) ||
        !muon->summaryValue(phiLayer1STGCHoles, xAOD::MuonSummaryType::phiLayer1STGCHoles) ||
        !muon->summaryValue(phiLayer2STGCHoles, xAOD::MuonSummaryType::phiLayer2STGCHoles) ||
        !muon->summaryValue(etaLayer1STGCHoles, xAOD::MuonSummaryType::etaLayer1STGCHoles) ||
        !muon->summaryValue(etaLayer2STGCHoles, xAOD::MuonSummaryType::etaLayer2STGCHoles)) {
      ATH_MSG_WARNING("STGC hits missing!!!...");
    }

    uint8_t MMHits(0), MMHoles(0);
    if (!muon->summaryValue(MMHits, xAOD::MuonSummaryType::MMHits) ||
        !muon->summaryValue(MMHoles, xAOD::MuonSummaryType::MMHoles)) {
      ATH_MSG_WARNING("MM hits missing!!!...");
    }

    size_t nSegments = muon->nMuonSegments(); 
    std::vector<float > seg_chiSquared;
    std::vector<float > seg_numberDoF;
    std::vector<int > seg_sector;
    std::vector<int > seg_chamberIndex;
    std::vector<int > seg_nPrecisionHits;
    std::vector<int > seg_nPhiLayers;
    std::vector<int > seg_nTrigEtaLayers;
    std::vector<float > seg_x;
    std::vector<float > seg_y;
    std::vector<float > seg_z;
    std::vector<float > seg_px;
    std::vector<float > seg_py;
    std::vector<float > seg_pz;
    for(size_t i=0; i<nSegments; i++ ) {
      const xAOD::MuonSegment* muonSegment = muon->muonSegment(i);
      seg_chiSquared.push_back(muonSegment->chiSquared());
      seg_numberDoF.push_back(muonSegment->numberDoF());
      seg_sector.push_back(muonSegment->sector());
      seg_chamberIndex.push_back(muonSegment->chamberIndex());
      seg_nPrecisionHits.push_back(muonSegment->nPrecisionHits());
      seg_nPhiLayers.push_back(muonSegment->nPhiLayers());
      seg_nTrigEtaLayers.push_back(muonSegment->nTrigEtaLayers());
      seg_x.push_back(muonSegment->x());
      seg_y.push_back(muonSegment->y());
      seg_z.push_back(muonSegment->z());
      seg_px.push_back(muonSegment->px());
      seg_py.push_back(muonSegment->py());
      seg_pz.push_back(muonSegment->pz());
    }

    // extrapolate
		std::vector<float> targetbarrelEta;
		std::vector<float> targetbarrelPhi;

/*
    // endcap or barrel flag
    bool flag_barrel = std::abs(muon->eta()) < 1.5;
        
    // only barrel and reasonably-high-pT muons
    if (!flag_barrel) {
      m_mu_ext_b_targetEtaVec->push_back(targetbarrelEta);
      m_mu_ext_b_targetPhiVec->push_back(targetbarrelPhi);
    }
    if (flag_barrel){
      for (const auto &R : m_b_extPosition){
        auto trk = muon->primaryTrackParticle();
        ATH_MSG_DEBUG("extTrackToRPC");
        if(!trk) Trk::TrackParameters* extBarrelParams = NULL;
        std::unique_ptr<Trk::CylinderSurface> barrel(new Trk::CylinderSurface( R, 15000. ));
        const bool boundaryCheck = true;

        //const Trk::TrackParameters* extBarrelParams = m_extrapolator->extrapolate(Gaudi::Hive::currentContext(),
        const auto extBarrelParams = m_extrapolator->extrapolate(Gaudi::Hive::currentContext(),
                                                                      *trk,
                                                                      *barrel,
                                                                      Trk::alongMomentum,
                                                                      boundaryCheck,
                                                                      Trk::muon);
        if (extBarrelParams != nullptr){
          targetbarrelEta.push_back(extBarrelParams->position().eta());
          targetbarrelPhi.push_back(extBarrelParams->position().phi());
        }
      }
      m_mu_ext_b_targetEtaVec->push_back(targetbarrelEta);
      m_mu_ext_b_targetPhiVec->push_back(targetbarrelPhi);
    }
*/

    m_muon_e->push_back (muon->e() * 0.001); // GeV
    m_muon_pt->push_back (muon->pt() * 0.001); // GeV
    m_muon_eta->push_back (muon->eta());
    m_muon_phi->push_back (muon->phi());
    m_muon_charge->push_back (muon->charge());
    m_muon_quality->push_back (m_selTool->getQuality(*muon));
    m_muon_isBadMuon_other->push_back (m_selTool->isBadMuon(*muon));
    // m_muon_truthType->push_back ();
    m_muon_truthTypeMCTC->push_back (truthTypeMCTC);
    m_muon_truthOriginMCTC->push_back (truthOriginMCTC);
    m_muon_IFFtruthType->push_back (IFFtype);
    m_muon_muonType->push_back (muon->muonType());
    m_muon_author->push_back (muon->author());

    m_truthmuon_e->push_back (truth_e * 0.001); // GeV
    m_truthmuon_pt->push_back (truth_pt * 0.001); // GeV
    m_truthmuon_eta->push_back (truth_eta);
    m_truthmuon_phi->push_back (truth_phi);
    m_truthmuon_pdgId->push_back (truth_pdgId);

    m_muon_mePt->push_back (mePt*0.001);
    m_muon_idPt->push_back (idPt*0.001);
    // m_muon_cbPt->push_back ();
    m_muon_meP->push_back (meP);
    m_muon_idP->push_back (idP);
    m_muon_innerSmallHits->push_back (innerSmallHits);
    m_muon_innerLargeHits->push_back (innerLargeHits);
    m_muon_middleSmallHits->push_back (middleSmallHits);
    m_muon_middleLargeHits->push_back (middleLargeHits);
    m_muon_outerSmallHits->push_back (outerSmallHits);
    m_muon_outerLargeHits->push_back (outerLargeHits);
    m_muon_extendedSmallHits->push_back (extendedSmallHits);
    m_muon_extendedLargeHits->push_back (extendedLargeHits);
    m_muon_etaMS->push_back (etaMS);
    m_muon_phiMS->push_back (phiMS);

    // Hits
    // sTGC
    m_muon_phiLayer1STGCHits->push_back (phiLayer1STGCHits);
    m_muon_phiLayer2STGCHits->push_back (phiLayer2STGCHits);
    m_muon_etaLayer1STGCHits->push_back (etaLayer1STGCHits);
    m_muon_etaLayer2STGCHits->push_back (etaLayer2STGCHits);
    m_muon_phiLayer1STGCHoles->push_back (phiLayer1STGCHoles);
    m_muon_phiLayer2STGCHoles->push_back (phiLayer2STGCHoles);
    m_muon_etaLayer1STGCHoles->push_back (etaLayer1STGCHoles);
    m_muon_etaLayer2STGCHoles->push_back (etaLayer2STGCHoles);
    // MM
    m_muon_MMHits->push_back (MMHits);
    m_muon_MMHoles->push_back (MMHoles);

    // segment
    m_muon_nSegments->push_back (nSegments);
    m_muon_seg_chiSquared->push_back(seg_chiSquared);
    m_muon_seg_numberDoF->push_back(seg_numberDoF);
    m_muon_seg_sector->push_back(seg_sector);
    m_muon_seg_chamberIndex->push_back(seg_chamberIndex);
    m_muon_seg_nPrecisionHits->push_back(seg_nPrecisionHits);
    m_muon_seg_nPhiLayers->push_back(seg_nPhiLayers);
    m_muon_seg_nTrigEtaLayers->push_back(seg_nTrigEtaLayers);
    m_muon_seg_x->push_back(seg_x);
    m_muon_seg_y->push_back(seg_y);
    m_muon_seg_z->push_back(seg_z);
    m_muon_seg_px->push_back(seg_px);
    m_muon_seg_py->push_back(seg_py);
    m_muon_seg_pz->push_back(seg_pz);

  }

  SG::ReadHandle<xAOD::MuonRoIContainer> rh_roi(m_roiKey);
  if (!rh_roi.isValid()) {
    ATH_MSG_FATAL("could not find " << rh_roi.name());
    return StatusCode::FAILURE;
  }
  const xAOD::MuonRoIContainer* container = rh_roi.get();

  for (xAOD::MuonRoIContainer::const_iterator roi_it = container->begin(); roi_it != container->end(); roi_it++) {
    const xAOD::MuonRoI* roi = *roi_it;

    if (roi->isRun3() == false) {
      ATH_MSG_ERROR("The RoI word does not indicate the Run-3 format!");
      return StatusCode::FAILURE;
    }

    m_roi_eta->push_back(roi->eta());
    m_roi_phi->push_back(roi->phi());
    m_roi_thrNumber->push_back(roi->getThrNumber());
    m_roi_RoINumber->push_back(roi->getRoI());
    m_roi_sectorAddress->push_back(roi->getSectorAddress());
    m_roi_source->push_back(static_cast<short>(roi->getSource()));   // Barrel:0, Endcap:1, Forward:2
    m_roi_hemisphere->push_back(static_cast<short>(roi->getHemisphere()));   // A-side:0, C-side:1
    m_roi_firstCandidate->push_back(roi->isFirstCandidate());
    m_roi_moreCandInRoI->push_back(roi->isMoreCandInRoI());
    m_roi_moreCandInSector->push_back(roi->isMoreCandInSector());
    m_roi_charge->push_back(static_cast<short>(roi->getCharge()));   // 0:Neg, 1:Pos, 100:undef
    m_roi_BW3coin->push_back(roi->getBW3Coincidence());
    m_roi_InnerCoin->push_back(roi->getInnerCoincidence());
    m_roi_GoodMF->push_back(roi->getGoodMF());
    m_roi_vetoed->push_back(roi->isVetoed());
  }


  // auto chainGroup = m_trigDecisionTool->getChainGroup("HLT_mu.*");
  // std::map<std::string,int> triggerCounts;
  // for(auto &trig : chainGroup->getListOfTriggers()) {
  //   auto cg = m_trigDecisionTool->getChainGroup(trig);
  //   std::string thisTrig = trig;
  //   ANA_MSG_INFO ("execute(): " << thisTrig << ", chain passed(1)/failed(0) = " << cg->isPassed() << ", total chain prescale (L1*HLT) = " << cg->getPrescale());
  // }

  // ATH_MSG_INFO( m_trigDecisionTool->getNavigationFormat() );



  const std::string targetTrig = "HLT_mu24_ivarmedium_L1MU14FCH"; //"HLT_mu24_ivarmedium_mu4_probe_L1MU14FCH"; //"HLT_mu10_L1MU8F";//"HLT_mu60_0eta105_msonly_L1MU14FCH";//"HLT_mu6_L1MU5VF"; //
  //const std::string targetTrig_forl2mt = "HLT_2mu10_l2mt_L1MU10BOM"; //"HLT_mu24_ivarmedium_mu4_probe_L1MU14FCH"; //"HLT_mu10_L1MU8F";//"HLT_mu60_0eta105_msonly_L1MU14FCH";//"HLT_mu6_L1MU5VF"; //
  const std::string targetTrig_forl2mt = "HLT_mu10_l2mt_L1MU10BOM"; //"HLT_mu24_ivarmedium_mu4_probe_L1MU14FCH"; //"HLT_mu10_L1MU8F";//"HLT_mu60_0eta105_msonly_L1MU14FCH";//"HLT_mu6_L1MU5VF"; //

  // const int legIndex = 1; // probe leg!!!!
  // std::vector< TrigCompositeUtils::LinkInfo<xAOD::L2StandAloneMuonContainer> > l2saLinks = m_trigDecisionTool->features<xAOD::L2StandAloneMuonContainer>( targetTrig, TrigDefs::includeFailedDecisions, "HLT_MuonL2SAInfo", TrigDefs::lastFeatureOfType, TrigCompositeUtils::featureString(), legIndex );
  std::vector< TrigCompositeUtils::LinkInfo<xAOD::L2StandAloneMuonContainer> > l2saLinks = m_trigDecisionTool->features<xAOD::L2StandAloneMuonContainer>( targetTrig, TrigDefs::includeFailedDecisions, "HLT_MuonL2SAInfo" );
  // std::vector< TrigCompositeUtils::LinkInfo<xAOD::L2StandAloneMuonContainer> > l2saLinks = m_trigDecisionTool->features<xAOD::L2StandAloneMuonContainer>( "HLT_mu26_ivarmedium_mu6_probe_L1MU14FCH", TrigDefs::includeFailedDecisions, "HLT_MuonL2SAInfoIOmode" );
  for(const TrigCompositeUtils::LinkInfo<xAOD::L2StandAloneMuonContainer>& l2saLinkInfo : l2saLinks){
    if( !l2saLinkInfo.isValid() ) continue;
    const ElementLink<xAOD::L2StandAloneMuonContainer> l2sa = l2saLinkInfo.link;
    if( !l2sa.isValid() ) continue;

    bool pass = ( l2saLinkInfo.state == TrigCompositeUtils::ActiveState::ACTIVE );//hypo information


    auto l1muonLinkInfo = TrigCompositeUtils::findLink<xAOD::MuonRoIContainer>(l2saLinkInfo.source, "initialRecRoI");
    auto l1muonLink = l1muonLinkInfo.link;
    if(!l1muonLink.isValid()){
      ATH_MSG_ERROR("Invalid link to L1 muon");
      continue;
    }
    const xAOD::MuonRoI* l1muon = *l1muonLink;

    ANA_MSG_INFO ("execute(): " << " L1 eta/phi = " << l1muon->eta() << "/" << l1muon->phi());
    ANA_MSG_INFO ("execute(): " << " L2SA pt/eta/phi/pass = " << (*l2sa)->pt() << "/" << (*l2sa)->eta() << "/" << (*l2sa)->phi() << "/" << pass);

  
  }
/*
  // for l2mt
  std::vector< TrigCompositeUtils::LinkInfo<xAOD::L2StandAloneMuonContainer> > l2mtLinks = m_trigDecisionTool->features<xAOD::L2StandAloneMuonContainer>( targetTrig_forl2mt, TrigDefs::includeFailedDecisions, "HLT_MuonL2SAInfol2mtmode" );
  for(const TrigCompositeUtils::LinkInfo<xAOD::L2StandAloneMuonContainer>& l2mtLinkInfo : l2mtLinks){
    if( !l2mtLinkInfo.isValid() ) continue;
    const ElementLink<xAOD::L2StandAloneMuonContainer> l2mt = l2mtLinkInfo.link;
    if( !l2mt.isValid() ) continue;

    bool pass = ( l2mtLinkInfo.state == TrigCompositeUtils::ActiveState::ACTIVE );


    auto l1muonLinkInfo = TrigCompositeUtils::findLink<xAOD::MuonRoIContainer>(l2mtLinkInfo.source, "initialRecRoI");
    auto l1muonLink = l1muonLinkInfo.link;
    if(!l1muonLink.isValid()){
      ATH_MSG_ERROR("Invalid link to L1 muon");
      continue;
    }
    const xAOD::MuonRoI* l1muon = *l1muonLink;

    ANA_MSG_INFO ("execute(): " << " L1 eta/phi = " << l1muon->eta() << "/" << l1muon->phi());
    ANA_MSG_INFO ("execute(): " << " L2mt pt/eta/phi/pass = " << (*l2mt)->pt() << "/" << (*l2mt)->eta() << "/" << (*l2mt)->phi() << "/" << pass);
  }
*/

  std::vector< TrigCompositeUtils::LinkInfo<xAOD::L2CombinedMuonContainer> > l2cbLinks = m_trigDecisionTool->features<xAOD::L2CombinedMuonContainer>( targetTrig, TrigDefs::includeFailedDecisions, "HLT_MuonL2CBInfo" );
  // std::vector< TrigCompositeUtils::LinkInfo<xAOD::L2CombinedMuonContainer> > l2cbLinks = m_trigDecisionTool->features<xAOD::L2CombinedMuonContainer>( targetTrig, TrigDefs::includeFailedDecisions, "HLT_MuonL2CBInfo", TrigDefs::lastFeatureOfType, TrigCompositeUtils::featureString(), legIndex );
  for(const TrigCompositeUtils::LinkInfo<xAOD::L2CombinedMuonContainer>& l2cbLinkInfo : l2cbLinks){
    if( !l2cbLinkInfo.isValid() ) continue;
    const ElementLink<xAOD::L2CombinedMuonContainer> l2cb = l2cbLinkInfo.link;
    if( !l2cb.isValid() ) continue;

    bool pass = ( l2cbLinkInfo.state == TrigCompositeUtils::ActiveState::ACTIVE );

    ANA_MSG_INFO ("execute(): " << " L2CB pt/eta/phi/pass = " << (*l2cb)->pt() << "/" << (*l2cb)->eta() << "/" << (*l2cb)->phi() << "/" << pass);
  }

  std::vector< TrigCompositeUtils::LinkInfo<xAOD::L2CombinedMuonContainer> > l2cbmtLinks = m_trigDecisionTool->features<xAOD::L2CombinedMuonContainer>( targetTrig_forl2mt, TrigDefs::includeFailedDecisions, "HLT_MuonL2SAInfol2mtmode" );
  for(const TrigCompositeUtils::LinkInfo<xAOD::L2CombinedMuonContainer>& l2cbmtLinkInfo : l2cbmtLinks){
    if( !l2cbmtLinkInfo.isValid() ) continue;
    const ElementLink<xAOD::L2CombinedMuonContainer> l2cbmt = l2cbmtLinkInfo.link;
    if( !l2cbmt.isValid() ) continue;

    bool pass = ( l2cbmtLinkInfo.state == TrigCompositeUtils::ActiveState::ACTIVE );

    ANA_MSG_INFO ("execute(): " << " L2CBMT pt/eta/phi/pass = " << (*l2cbmt)->pt() << "/" << (*l2cbmt)->eta() << "/" << (*l2cbmt)->phi() << "/" << pass);
  }


  for(size_t off_idx=0; off_idx<m_muon_eta->size(); off_idx++) {

    TLorentzVector tlv_off;
    tlv_off.SetPtEtaPhiE(m_muon_pt->at(off_idx), m_muon_eta->at(off_idx), m_muon_phi->at(off_idx), m_muon_e->at(off_idx));
    TLorentzVector tlv_l1;

    float dRmin = 999;

    float l1_dRoff = 999;
    float l1_eta = 999;
    float l1_phi = 999;

    float l2sa_e = 999;
    float l2sa_pt = 999;
    float l2sa_eta = 999;
    float l2sa_phi = 999;
    float l2sa_etaMS = 999;
    float l2sa_phiMS = 999;
    bool l2sa_pass = false;
    std::vector<float> sp_r, sp_z, sp_slope, sp_intercept, sp_chi2;
    std::vector< unsigned int > l2sa_stgcClusterLayer;
    std::vector< int >          l2sa_stgcClusterIsOutlier;
    std::vector< int >          l2sa_stgcClusterType;
    std::vector< float >        l2sa_stgcClusterEta;
    std::vector< float >        l2sa_stgcClusterPhi;
    std::vector< float >        l2sa_stgcClusterR;
    std::vector< float >        l2sa_stgcClusterZ;
    std::vector< float >        l2sa_stgcClusterResidualR;
    std::vector< float >        l2sa_stgcClusterResidualPhi;
    std::vector< int >          l2sa_stgcClusterStationEta;
    std::vector< int >          l2sa_stgcClusterStationPhi;
    std::vector< int >          l2sa_stgcClusterStationName;
    std::vector< unsigned int > l2sa_mmClusterLayer;
    std::vector< int >          l2sa_mmClusterIsOutlier;
    std::vector< float >        l2sa_mmClusterEta;
    std::vector< float >        l2sa_mmClusterPhi;
    std::vector< float >        l2sa_mmClusterR;
    std::vector< float >        l2sa_mmClusterZ;
    std::vector< float >        l2sa_mmClusterResidualR;
    std::vector< float >        l2sa_mmClusterResidualPhi;
    std::vector< int >          l2sa_mmClusterStationEta;
    std::vector< int >          l2sa_mmClusterStationPhi;
    std::vector< int >          l2sa_mmClusterStationName;
    float l2sa_ptEndcapAlpha = 999;
    float l2sa_ptEndcapBeta = 999;

    uint32_t roiWord = 999;

    float l2cb_e = 999;
    float l2cb_pt = 999;
    float l2cb_eta = 999;
    float l2cb_phi = 999;
    bool l2cb_pass = false;
    float dR = 0;
    float dRreq = 0.08;
    if(tlv_off.Pt() < 10)
      dRreq = 0.18 - 0.01*tlv_off.Pt();

    for(const TrigCompositeUtils::LinkInfo<xAOD::L2StandAloneMuonContainer>& l2saLinkInfo : l2saLinks){
      if( !l2saLinkInfo.isValid() ) continue;
      const ElementLink<xAOD::L2StandAloneMuonContainer> l2sa = l2saLinkInfo.link;
      if( !l2sa.isValid() ) continue;


      auto l1muonLinkInfo = TrigCompositeUtils::findLink<xAOD::MuonRoIContainer>(l2saLinkInfo.source, "initialRecRoI");
      auto l1muonLink = l1muonLinkInfo.link;
      if(!l1muonLink.isValid()){
        ATH_MSG_ERROR("Invalid link to L1 muon");
        continue;
      }
      const xAOD::MuonRoI* l1muon = *l1muonLink;

      tlv_l1.SetPtEtaPhiE(m_muon_pt->at(off_idx), l1muon->eta(), l1muon->phi(), m_muon_e->at(off_idx));

      dR = tlv_l1.DeltaR(tlv_off);

      //if(dR > dRreq) continue;

      //if(dR < dRmin) {

        //dRmin = dR;
        l1_dRoff = dR;
        l1_eta = l1muon->eta();
        l1_phi = l1muon->phi();


        l2sa_e = (*l2sa)->e();
        l2sa_pt = (*l2sa)->pt();
        l2sa_eta = (*l2sa)->eta();
        l2sa_phi = (*l2sa)->phi();
        l2sa_etaMS = (*l2sa)->etaMS();
        l2sa_phiMS = (*l2sa)->phiMS();
        l2sa_pass = ( l2saLinkInfo.state == TrigCompositeUtils::ActiveState::ACTIVE );

        l2sa_stgcClusterLayer = (*l2sa)->stgcClusterLayer();
        l2sa_stgcClusterIsOutlier = (*l2sa)->stgcClusterIsOutlier();
        l2sa_stgcClusterType = (*l2sa)->stgcClusterType();
        l2sa_stgcClusterEta = (*l2sa)->stgcClusterEta();
        l2sa_stgcClusterPhi = (*l2sa)->stgcClusterPhi();
        l2sa_stgcClusterR = (*l2sa)->stgcClusterR();
        l2sa_stgcClusterZ = (*l2sa)->stgcClusterZ();
        l2sa_stgcClusterResidualR = (*l2sa)->stgcClusterResidualR();
        l2sa_stgcClusterResidualPhi = (*l2sa)->stgcClusterResidualPhi();
        l2sa_stgcClusterStationEta = (*l2sa)->stgcClusterStationEta();
        l2sa_stgcClusterStationPhi = (*l2sa)->stgcClusterStationPhi();
        l2sa_stgcClusterStationName = (*l2sa)->stgcClusterStationName();

        l2sa_mmClusterLayer = (*l2sa)->mmClusterLayer();
        l2sa_mmClusterIsOutlier = (*l2sa)->mmClusterIsOutlier();
        l2sa_mmClusterEta = (*l2sa)->mmClusterEta();
        l2sa_mmClusterPhi = (*l2sa)->mmClusterPhi();
        l2sa_mmClusterR = (*l2sa)->mmClusterR();
        l2sa_mmClusterZ = (*l2sa)->mmClusterZ();
        l2sa_mmClusterResidualR = (*l2sa)->mmClusterResidualR();
        l2sa_mmClusterResidualPhi = (*l2sa)->mmClusterResidualPhi();
        l2sa_mmClusterStationEta = (*l2sa)->mmClusterStationEta();
        l2sa_mmClusterStationPhi = (*l2sa)->mmClusterStationPhi();
        l2sa_mmClusterStationName = (*l2sa)->mmClusterStationName();

        l2sa_ptEndcapAlpha = (*l2sa)->ptEndcapAlpha();
        l2sa_ptEndcapBeta = (*l2sa)->ptEndcapBeta();

        sp_r.clear();
        sp_z.clear();
        sp_slope.clear();
        sp_intercept.clear();
        sp_chi2.clear();
        int inner  = 0;
        int middle = 1;
        int outer  = 2;
        if ((*l2sa)->sAddress() == -1) {
          inner  = xAOD::L2MuonParameters::Chamber::EndcapInner;
          middle = xAOD::L2MuonParameters::Chamber::EndcapMiddle;
          outer  = xAOD::L2MuonParameters::Chamber::EndcapOuter;
        } else {
          inner  = xAOD::L2MuonParameters::Chamber::BarrelInner;
          middle = xAOD::L2MuonParameters::Chamber::BarrelMiddle;
          outer  = xAOD::L2MuonParameters::Chamber::BarrelOuter;
        }
        // super point
        if( std::abs((*l2sa)->superPointR(inner)) > ZERO_LIMIT ) {
          sp_r.push_back(         (*l2sa)->superPointR(inner) );
          sp_z.push_back(         (*l2sa)->superPointZ(inner) );
          sp_slope.push_back(     (*l2sa)->superPointSlope(inner) );
          sp_intercept.push_back( (*l2sa)->superPointIntercept(inner) );
          sp_chi2.push_back(      (*l2sa)->superPointChi2(inner) );
        }
        if( std::abs((*l2sa)->superPointR(middle)) > ZERO_LIMIT ) {
          sp_r.push_back(         (*l2sa)->superPointR(middle) );
          sp_z.push_back(         (*l2sa)->superPointZ(middle) );
          sp_slope.push_back(     (*l2sa)->superPointSlope(middle) );
          sp_intercept.push_back( (*l2sa)->superPointIntercept(middle) );
          sp_chi2.push_back(      (*l2sa)->superPointChi2(middle) );
        }
        if( std::abs((*l2sa)->superPointR(outer)) > ZERO_LIMIT ) {
          sp_r.push_back(         (*l2sa)->superPointR(outer) );
          sp_z.push_back(         (*l2sa)->superPointZ(outer) );
          sp_slope.push_back(     (*l2sa)->superPointSlope(outer) );
          sp_intercept.push_back( (*l2sa)->superPointIntercept(outer) );
          sp_chi2.push_back(      (*l2sa)->superPointChi2(outer) );
        }

        roiWord = (*l2sa)->roiWord();
      //}

    }

    m_l1_dRoff->push_back(l1_dRoff);
    m_l1_eta->push_back(l1_eta);
    m_l1_phi->push_back(l1_phi);

    m_l2sa_e->push_back(l2sa_e);
    m_l2sa_pt->push_back(l2sa_pt);
    m_l2sa_eta->push_back(l2sa_eta);
    m_l2sa_phi->push_back(l2sa_phi);
    m_l2sa_etaMS->push_back(l2sa_etaMS);
    m_l2sa_phiMS->push_back(l2sa_phiMS);
    m_l2sa_pass->push_back(l2sa_pass);

    m_l2sa_superPointR->push_back(sp_r);
    m_l2sa_superPointZ->push_back(sp_z);
    m_l2sa_superPointSlope->push_back(sp_slope);
    m_l2sa_superPointIntercept->push_back(sp_intercept);
    m_l2sa_superPointChi2->push_back(sp_chi2);
    m_l2sa_stgcClusterLayer->push_back(l2sa_stgcClusterLayer);
    m_l2sa_stgcClusterIsOutlier->push_back(l2sa_stgcClusterIsOutlier);
    m_l2sa_stgcClusterType->push_back(l2sa_stgcClusterType);
    m_l2sa_stgcClusterEta->push_back(l2sa_stgcClusterEta);
    m_l2sa_stgcClusterPhi->push_back(l2sa_stgcClusterPhi);
    m_l2sa_stgcClusterR->push_back(l2sa_stgcClusterR);
    m_l2sa_stgcClusterZ->push_back(l2sa_stgcClusterZ);
    m_l2sa_stgcClusterResidualR->push_back(l2sa_stgcClusterResidualR);
    m_l2sa_stgcClusterResidualPhi->push_back(l2sa_stgcClusterResidualPhi);
    m_l2sa_stgcClusterStationEta->push_back(l2sa_stgcClusterStationEta);
    m_l2sa_stgcClusterStationPhi->push_back(l2sa_stgcClusterStationPhi);
    m_l2sa_stgcClusterStationName->push_back(l2sa_stgcClusterStationName);
    m_l2sa_mmClusterLayer->push_back(l2sa_mmClusterLayer);
    m_l2sa_mmClusterIsOutlier->push_back(l2sa_mmClusterIsOutlier);
    m_l2sa_mmClusterEta->push_back(l2sa_mmClusterEta);
    m_l2sa_mmClusterPhi->push_back(l2sa_mmClusterPhi);
    m_l2sa_mmClusterR->push_back(l2sa_mmClusterR);
    m_l2sa_mmClusterZ->push_back(l2sa_mmClusterZ);
    m_l2sa_mmClusterResidualR->push_back(l2sa_mmClusterResidualR);
    m_l2sa_mmClusterResidualPhi->push_back(l2sa_mmClusterResidualPhi);
    m_l2sa_mmClusterStationEta->push_back(l2sa_mmClusterStationEta);
    m_l2sa_mmClusterStationPhi->push_back(l2sa_mmClusterStationPhi);
    m_l2sa_mmClusterStationName->push_back(l2sa_mmClusterStationName);

    m_l2sa_ptEndcapAlpha->push_back(l2sa_ptEndcapAlpha);
    m_l2sa_ptEndcapBeta->push_back(l2sa_ptEndcapBeta);

    for(const TrigCompositeUtils::LinkInfo<xAOD::L2CombinedMuonContainer>& l2cbmtLinkInfo : l2cbLinks){
      if( !l2cbmtLinkInfo.isValid() ) continue;
      const ElementLink<xAOD::L2CombinedMuonContainer> l2cbmt = l2cbmtLinkInfo.link;
      if( !l2cbmt.isValid() ) continue;

      if((*l2cbmt)->muSATrack()->roiWord() != roiWord) continue;

      l2cb_e = (*l2cbmt)->e()*0.001;
      l2cb_pt = (*l2cbmt)->pt()*0.001;
      l2cb_eta = (*l2cbmt)->eta();
      l2cb_phi = (*l2cbmt)->phi();
      l2cb_pass = ( l2cbmtLinkInfo.state == TrigCompositeUtils::ActiveState::ACTIVE );

    }

    m_l2cb_e->push_back(l2cb_e);
    m_l2cb_pt->push_back(l2cb_pt);
    m_l2cb_eta->push_back(l2cb_eta);
    m_l2cb_phi->push_back(l2cb_phi);
    m_l2cb_pass->push_back(l2cb_pass);

  }

  const Trig::ChainGroup* chainGroup = m_trigDecisionTool->getChainGroup("HLT_.*");
  if (chainGroup == nullptr) return StatusCode::FAILURE;
  std::vector<std::string> chains = chainGroup->getListOfTriggers();

  if (chains.empty()) return StatusCode::SUCCESS;

  for(const auto& chain : chains) {
    std::string chainname = chain;
    if (m_trigDecisionTool->isPassed(chainname) == false) continue;
    if (chainname.find("mu") == std::string::npos && chainname.find("MU") == std::string::npos) continue;

    std::vector<int> typeVec;
    std::vector<float> ptVec, etaVec, phiVec;

    auto features = m_trigDecisionTool->features<xAOD::MuonContainer>(chainname.data(), TrigDefs::Physics, "HLT_MuonsCB_RoI");
    for(const auto& featurelink : features) {
      if(!featurelink.isValid()) continue;
      auto muEL = featurelink.link;
      if(!muEL.isValid()) continue;
      auto muon = *muEL;
      if(muon == nullptr) continue;
      typeVec.push_back(muon->muonType());
      ptVec.push_back(muon->pt());
      etaVec.push_back(muon->eta());
      phiVec.push_back(muon->phi());
    }

    m_chain->push_back(chainname);
    m_typeVec->push_back(typeVec);
    m_ptVec->push_back(ptVec);
    m_etaVec->push_back(etaVec);
    m_phiVec->push_back(phiVec);
  }

  // const EventContext& ctx = getContext();
  // ATH_MSG_INFO("Get event context << " << ctx );

  // SG::ReadHandle<xAOD::L2CombinedMuonContainer> l2cbio_inCntn( m_L2CBIOKey, ctx );
  // if( l2cbio_inCntn.isValid() ){
  //   ATH_MSG_DEBUG("valid L2CB with tag : " << m_L2CBIOKey);
  //   for(const auto& cbio : *l2cbio_inCntn){
  //     ANA_MSG_INFO ("execute(): " << " L2CBIO in container pt/eta/phi = " << cbio->pt() << "/" << cbio->eta() << "/" << cbio->phi());
  //   }
  // }

  // SG::ReadHandle<xAOD::L2StandAloneMuonContainer> l2samt_inCntn( m_L2SAMTKey, ctx );
  // if( l2samt_inCntn.isValid() ){
  //   ATH_MSG_DEBUG("valid L2SA with tag : " << m_L2SAMTKey);
  //   for(const auto& samt : *l2samt_inCntn){
  //     ANA_MSG_INFO ("execute(): " << " L2SAMT in container pt/eta/phi = " << samt->pt() << "/" << samt->eta() << "/" << samt->phi());
  //   }
  // }


  // const std::string testTrigName = "HLT_mu24_ivarmedium_L1MU14FCH";
  // Trig::FeatureContainer fc = m_trigDecisionTool->features( testTrigName );
  // std::vector<Trig::Feature<xAOD::L2StandAloneMuonContainer> > vec_muons = fc.get<xAOD::L2StandAloneMuonContainer>();
  // // Trig::ExpertMethods* expert = m_trigDecisionTool -> ExperimentalAndExpertMethods();
  // // expert->enable();
  // for (const auto& mufeat : vec_muons) {
  //   ATH_MSG_ERROR(testTrigName << "  vec_muons.size() = " << vec_muons.size()
  // 		 << "  mufeat.cptr()->size() = " << mufeat.cptr()->size());
  //   for (unsigned int i = 0; i < mufeat.cptr()->size(); i++) {
  //     ATH_MSG_ERROR("#####" << testTrigName << "  L2SA feature pt: " << (*mufeat.cptr())[i]->pt()
  // 		   << "   eta: " << (*mufeat.cptr())[i]->eta() << "   phi: " << (*mufeat.cptr())[i]->phi());
  //   }
  // }

  // Trig::FeatureContainer fc_mu6 = m_trigDecisionTool->features("HLT_mu6");
  // std::vector<Trig::Combination> combs_mu6 = fc_mu6.getCombinations();
  // std::vector<Trig::Combination>::const_iterator p_comb_mu6;
  // for(p_comb_mu6=combs_mu6.begin();p_comb_mu6!=combs_mu6.end();++p_comb_mu6) {
  //   std::vector<Trig::Feature<xAOD::L2StandAloneMuonContainer> > fs_MF = 
  //     (*p_comb_mu6).get<xAOD::L2StandAloneMuonContainer>("MuonL2SAInfo",TrigDefs::alsoDeactivateTEs); 
  //   if(!fs_MF.size()) {
  //     continue;
  //   }
  //   const xAOD::L2StandAloneMuonContainer* mf_cont = fs_MF[0];
  //   float pt_mf = mf_cont->at(0)->pt();
  //   float eta_mf = mf_cont->at(0)->eta();
  //   float phi_mf = mf_cont->at(0)->phi();
  //   ANA_MSG_INFO ("execute(): " << " L2SA pt/eta/phi = " << pt_mf << "/" << eta_mf << "/" << phi_mf);
  // }

  // std::vector< TrigCompositeUtils::LinkInfo<xAOD::L2StandAloneMuonContainer> > features_mu6 = m_trigDecisionTool->features<xAOD::L2StandAloneMuonContainer>("HLT_mu6", TrigDefs::includeFailedDecisions, "MuonL2SAInfo");
  // for(const TrigCompositeUtils::LinkInfo<xAOD::L2StandAloneMuonContainer>& muLinkInfo : features_mu6) {
  //   ATH_CHECK( muLinkInfo.isValid() );
  //   const ElementLink<xAOD::L2StandAloneMuonContainer> muEL = muLinkInfo.link;
  //   ATH_MSG_ERROR("#####" << "HLT_mu6" << "  L2SA feature pt/eta/phi: " << (*muEL)->pt()
  // 		  << "/" << (*muEL)->eta() << "/" << (*muEL)->phi());

  // }

  // const auto vec = fc.get<T>();
  // const auto vecbits = fc.get<xAOD::TrigPassBits>();
  // std::string label="";
  // for(const auto& feat:vecbits){
  //   const auto *xbits=feat.cptr();
  //   TrigConf::HLTTriggerElement::getLabel(feat.te()->getId(), label );
  //   const auto *cont=(m_trigDec->ancestor<T>(feat.te())).cptr();

  //   if(cont){
  //     ATH_MSG_INFO("REGTEST TrigPassBits for TE " << label  
  // 		   <<  " size " << cont->size());
  //     if(cont->size()!=xbits->size()) {
  // 	ATH_MSG_WARNING("REGTEST Container and bit size not equal, continue");
  // 	continue;
  //     }
  //     int npassed=0;
  //     for(const auto &ptr:*cont){
  // 	if(xbits->isPassing(ptr,cont))
  // 	  npassed++;
  //     }
  //     ATH_MSG_INFO("REGTEST TrigPassBits for container type " << ClassID_traits< T >::typeName() 
  // 		   <<  " size " << cont->size() << " xbits " << xbits->size() << " selected " << npassed);
  //   }
  // }
  bool pass_L1_MU3V = m_trigDecisionTool->isPassed("L1_MU3V");
  bool pass_L1_2MU8F = m_trigDecisionTool->isPassed("L1_2MU8F");
  bool pass_L1_2MU5VF = m_trigDecisionTool->isPassed("L1_2MU5VF");
  bool pass_L1_MU5VF = m_trigDecisionTool->isPassed("L1_MU5VF");
  bool pass_L1_MU4 = m_trigDecisionTool->isPassed("L1_MU4");
  bool pass_L1_MU6 = m_trigDecisionTool->isPassed("L1_MU6");

  bool pass_HLT_mu4_l2io_L1MU3V = m_trigDecisionTool->isPassed("HLT_mu4_l2io_L1MU3V");
  bool pass_HLT_2mu14_l2io_L12MU8F = m_trigDecisionTool->isPassed("HLT_2mu14_l2io_L12MU8F");
  bool pass_HLT_2mu6_l2io_L12MU5VF = m_trigDecisionTool->isPassed("HLT_2mu6_l2io_L12MU5VF");
  bool pass_HLT_mu6_L1MU5VF = m_trigDecisionTool->isPassed("HLT_mu6_L1MU5VF");
  bool pass_HLT_mu4_L1MU4 = m_trigDecisionTool->isPassed("HLT_mu4");
  bool pass_HLT_mu6_L1MU6 = m_trigDecisionTool->isPassed("HLT_mu6");
  bool pass_HLT_mu26_ivarmedium_mu6_probe_L1MU14FCH = m_trigDecisionTool->isPassed("HLT_mu26_ivarmedium_mu6_probe_L1MU14FCH");
  bool pass_HLT_mu26_ivarmedium_mu6_l2io_probe_L1MU14FCH = m_trigDecisionTool->isPassed("HLT_mu26_ivarmedium_mu6_l2io_probe_L1MU14FCH");
  bool pass_HLT_mu26_ivarmedium_mu6_l2mt_probe_L1MU14FCH = m_trigDecisionTool->isPassed("HLT_mu26_ivarmedium_mu6_l2mt_probe_L1MU14FCH");
  bool pass_HLT_mu26_ivarmedium_L1MU14FCH = m_trigDecisionTool->isPassed("HLT_mu26_ivarmedium_L1MU14FCH");

  ANA_MSG_DEBUG ("execute(): " << "HLT_mu4_l2io_L1MU3V isPass? = " << pass_HLT_mu4_l2io_L1MU3V);
  ANA_MSG_DEBUG ("execute(): " << "HLT_2mu14_l2io_L12MU8F isPass? = " << pass_HLT_2mu14_l2io_L12MU8F);
  ANA_MSG_DEBUG ("execute(): " << "HLT_2mu6_l2io_L12MU5VF isPass? = " << pass_HLT_2mu6_l2io_L12MU5VF);

  hist ("h_CutFlow_HLT_mu4_l2io_L1MU3V")->Fill (0);
  if(pass_L1_MU3V) {
    hist ("h_CutFlow_HLT_mu4_l2io_L1MU3V")->Fill (1);
    if(pass_HLT_mu4_l2io_L1MU3V) {
      hist ("h_CutFlow_HLT_mu4_l2io_L1MU3V")->Fill (2);
    }
  }

  hist ("h_CutFlow_HLT_2mu14_l2io_L12MU8F")->Fill (0);
  if(pass_L1_2MU8F) {
    hist ("h_CutFlow_HLT_2mu14_l2io_L12MU8F")->Fill (1);
    if(pass_HLT_2mu14_l2io_L12MU8F) {
      hist ("h_CutFlow_HLT_2mu14_l2io_L12MU8F")->Fill (2);
    }
  }

  hist ("h_CutFlow_HLT_2mu6_l2io_L12MU5VF")->Fill (0);
  if(pass_L1_2MU5VF) {
    hist ("h_CutFlow_HLT_2mu6_l2io_L12MU5VF")->Fill (1);
    if(pass_HLT_2mu6_l2io_L12MU5VF) {
      hist ("h_CutFlow_HLT_2mu6_l2io_L12MU5VF")->Fill (2);
    }
  }

  hist ("h_CutFlow_HLT_mu6_L1MU5VF")->Fill (0);
  if(pass_L1_MU5VF) {
    hist ("h_CutFlow_HLT_mu6_L1MU5VF")->Fill (1);
    if(pass_HLT_mu6_L1MU5VF) {
      hist ("h_CutFlow_HLT_mu6_L1MU5VF")->Fill (2);
    }
  }

  hist ("h_CutFlow_HLT_mu4_L1MU4")->Fill (0);
  if(pass_L1_MU4) {
    hist ("h_CutFlow_HLT_mu4_L1MU4")->Fill (1);
    if(pass_HLT_mu4_L1MU4) {
      hist ("h_CutFlow_HLT_mu4_L1MU4")->Fill (2);
    }
  }

  hist ("h_CutFlow_HLT_mu6_L1MU6")->Fill (0);
  if(pass_L1_MU6) {
    hist ("h_CutFlow_HLT_mu6_L1MU6")->Fill (1);
    if(pass_HLT_mu6_L1MU6) {
      hist ("h_CutFlow_HLT_mu6_L1MU6")->Fill (2);
    }
  }


  hist ("h_HLT_mu4_l2io_L1MU3V")->Fill (pass_HLT_mu4_l2io_L1MU3V);
  hist ("h_HLT_2mu14_l2io_L12MU8F")->Fill (pass_HLT_2mu14_l2io_L12MU8F);
  hist ("h_HLT_2mu6_l2io_L12MU5VF")->Fill (pass_HLT_2mu6_l2io_L12MU5VF);
  hist ("h_HLT_mu26_ivarmedium_mu6_probe_L1MU14FCH")->Fill (pass_HLT_mu26_ivarmedium_mu6_probe_L1MU14FCH);
  hist ("h_HLT_mu26_ivarmedium_mu6_l2io_probe_L1MU14FCH")->Fill (pass_HLT_mu26_ivarmedium_mu6_l2io_probe_L1MU14FCH);
  hist ("h_HLT_mu26_ivarmedium_mu6_l2mt_probe_L1MU14FCH")->Fill (pass_HLT_mu26_ivarmedium_mu6_l2mt_probe_L1MU14FCH);
  hist ("h_HLT_mu26_ivarmedium_L1MU14FCH")->Fill (pass_HLT_mu26_ivarmedium_L1MU14FCH);

  // Fill the event into the tree:
  tree ("analysis")->Fill ();

  return StatusCode::SUCCESS;
}



StatusCode MyxAODAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.
  return StatusCode::SUCCESS;
}
