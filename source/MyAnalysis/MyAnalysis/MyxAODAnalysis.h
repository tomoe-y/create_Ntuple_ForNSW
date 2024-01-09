#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <TrigConfInterfaces/ITrigConfigTool.h>
#include <TrigDecisionTool/TrigDecisionTool.h>
#include <MuonSelectorTools/MuonSelectionTool.h>
#include "xAODTrigMuon/L2StandAloneMuonContainer.h"
#include "xAODTrigMuon/L2CombinedMuonContainer.h"
#include "xAODTrigger/MuonRoIContainer.h"
#include "TruthClassification/TruthClassificationTool.h"
#include "TrkExInterfaces/IExtrapolator.h"

class MyxAODAnalysis : public EL::AnaAlgorithm
{
public:
  // this is a standard algorithm constructor
  MyxAODAnalysis (const std::string& name, ISvcLocator* pSvcLocator);

  // these are the functions inherited from Algorithm
  virtual StatusCode initialize () override;
  virtual StatusCode execute () override;
  virtual StatusCode finalize () override;

private:

  /* ToolHandle<TrigConf::ITrigConfigTool> m_trigConfigTool; */
  ToolHandle<Trig::TrigDecisionTool> m_trigDecisionTool;
  ToolHandle<CP::MuonSelectionTool> m_selTool;
  ToolHandle<CP::IClassificationTool> m_truthClassificationTool;
  ToolHandle<Trk::IExtrapolator> m_extrapolator;

  SG::ReadHandleKey<xAOD::EventInfo> m_eventInfo{this, "EventInfoContName", "EventInfo", "event info key"};

  SG::ReadHandleKey<xAOD::L2CombinedMuonContainer> m_L2CBIOKey{this, "xAODL2CBContainer_IO", "HLT_MuonL2CBInfoIOmode", "Name of L2CBIOContainer object"};
  SG::ReadHandleKey<xAOD::L2StandAloneMuonContainer> m_L2SAMTKey{this, "xAODL2SAContainer_MT", "HLT_MuonL2SAInfol2mtmode", "Name of L2SAMTContainer object"};
  SG::ReadHandleKey<xAOD::MuonRoIContainer> m_roiKey{this, "L1ROI", "LVL1MuonRoIs", ""};

  unsigned int m_runNumber = 0;
  unsigned int m_lumiBlock = 0;
  unsigned long long m_eventNumber = 0;
  float m_mcEventWeight = 0;
  float m_actualInteractionsPerCrossing = 0;
  float m_averageInteractionsPerCrossing = 0;
  bool m_pass_HLT_mu10_l2mt_L1MU10BOM = 0;
  bool m_pass_HLT_2mu10_l2mt_L1MU10BOM = 0;
  bool m_pass_HLT_2mu10_bJpsimumu_L12MU8F = 0;
  bool m_pass_HLT_mu24_ivarmedium_L1MU14FCH = 0;
  bool m_pass_HLT_2mu14_L12MU8F = 0;

  std::vector<float> m_b_extPosition;

  std::unique_ptr<std::vector<float>> m_muon_e;
  std::unique_ptr<std::vector<float>> m_muon_pt;
  std::unique_ptr<std::vector<float>> m_muon_eta;
  std::unique_ptr<std::vector<float>> m_muon_phi;
  std::unique_ptr<std::vector<float>> m_muon_charge;
  std::unique_ptr<std::vector<int>> m_muon_quality;
  std::unique_ptr<std::vector<bool>> m_muon_isBadMuon_other;
  std::unique_ptr<std::vector<int>> m_muon_truthType;
  std::unique_ptr<std::vector<int>> m_muon_truthTypeMCTC;
  std::unique_ptr<std::vector<int>> m_muon_truthOriginMCTC;
  std::unique_ptr<std::vector<int>> m_muon_IFFtruthType;
  std::unique_ptr<std::vector<int>> m_muon_muonType;
  std::unique_ptr<std::vector<int>> m_muon_author;

  std::unique_ptr<std::vector<float>> m_truthmuon_e;
  std::unique_ptr<std::vector<float>> m_truthmuon_pt;
  std::unique_ptr<std::vector<float>> m_truthmuon_eta;
  std::unique_ptr<std::vector<float>> m_truthmuon_phi;
  std::unique_ptr<std::vector<int>> m_truthmuon_pdgId;
  std::unique_ptr<std::vector<float>> m_muon_mePt;
  std::unique_ptr<std::vector<float>> m_muon_idPt;
  std::unique_ptr<std::vector<float>> m_muon_cbPt;
  std::unique_ptr<std::vector<float>> m_muon_meP;
  std::unique_ptr<std::vector<float>> m_muon_idP;
  std::unique_ptr<std::vector<float>> m_muon_etaMS;
  std::unique_ptr<std::vector<float>> m_muon_phiMS;

  std::unique_ptr<std::vector<int>> m_muon_innerSmallHits;
  std::unique_ptr<std::vector<int>> m_muon_innerLargeHits;
  std::unique_ptr<std::vector<int>> m_muon_middleSmallHits;
  std::unique_ptr<std::vector<int>> m_muon_middleLargeHits;
  std::unique_ptr<std::vector<int>> m_muon_outerSmallHits;
  std::unique_ptr<std::vector<int>> m_muon_outerLargeHits;
  std::unique_ptr<std::vector<int>> m_muon_extendedSmallHits;
  std::unique_ptr<std::vector<int>> m_muon_extendedLargeHits;

  std::unique_ptr<std::vector<std::vector<float>>> m_mu_ext_b_targetEtaVec;
  std::unique_ptr<std::vector<std::vector<float>>> m_mu_ext_b_targetPhiVec;

  // sTGC
  std::unique_ptr<std::vector< uint8_t>> m_muon_phiLayer1STGCHits;
  std::unique_ptr<std::vector< uint8_t>> m_muon_phiLayer2STGCHits;
  std::unique_ptr<std::vector< uint8_t>> m_muon_etaLayer1STGCHits;
  std::unique_ptr<std::vector< uint8_t>> m_muon_etaLayer2STGCHits;
  std::unique_ptr<std::vector< uint8_t>> m_muon_phiLayer1STGCHoles;
  std::unique_ptr<std::vector< uint8_t>> m_muon_phiLayer2STGCHoles;
  std::unique_ptr<std::vector< uint8_t>> m_muon_etaLayer1STGCHoles;
  std::unique_ptr<std::vector< uint8_t>> m_muon_etaLayer2STGCHoles;

  // MM
  std::unique_ptr<std::vector< uint8_t>> m_muon_MMHits;
  std::unique_ptr<std::vector< uint8_t>> m_muon_MMHoles;

  // segment
  std::unique_ptr<std::vector< size_t>> m_muon_nSegments;
  std::unique_ptr<std::vector< std::vector< float>>> m_muon_seg_chiSquared;
  std::unique_ptr<std::vector< std::vector< float>>> m_muon_seg_numberDoF;
  std::unique_ptr<std::vector< std::vector< int>>> m_muon_seg_sector;
  std::unique_ptr<std::vector< std::vector< int>>> m_muon_seg_chamberIndex;
  std::unique_ptr<std::vector< std::vector< int>>> m_muon_seg_nPrecisionHits;
  std::unique_ptr<std::vector< std::vector< int>>> m_muon_seg_nPhiLayers;
  std::unique_ptr<std::vector< std::vector< int>>> m_muon_seg_nTrigEtaLayers;
  std::unique_ptr<std::vector< std::vector< float>>> m_muon_seg_x;
  std::unique_ptr<std::vector< std::vector< float>>> m_muon_seg_y;
  std::unique_ptr<std::vector< std::vector< float>>> m_muon_seg_z;
  std::unique_ptr<std::vector< std::vector< float>>> m_muon_seg_px;
  std::unique_ptr<std::vector< std::vector< float>>> m_muon_seg_py;
  std::unique_ptr<std::vector< std::vector< float>>> m_muon_seg_pz;

  std::unique_ptr<std::vector<float>> m_roi_eta;
  std::unique_ptr<std::vector<float>> m_roi_phi;
  std::unique_ptr<std::vector<short>> m_roi_thrNumber;
  std::unique_ptr<std::vector<short>> m_roi_RoINumber;
  std::unique_ptr<std::vector<short>> m_roi_sectorAddress;
  std::unique_ptr<std::vector<short>> m_roi_source;
  std::unique_ptr<std::vector<short>> m_roi_hemisphere;
  std::unique_ptr<std::vector<short>> m_roi_moreCandInRoI;
  std::unique_ptr<std::vector<short>> m_roi_firstCandidate;
  std::unique_ptr<std::vector<short>> m_roi_moreCandInSector;
  std::unique_ptr<std::vector<short>> m_roi_charge;
  std::unique_ptr<std::vector<short>> m_roi_BW3coin;
  std::unique_ptr<std::vector<short>> m_roi_InnerCoin;
  std::unique_ptr<std::vector<short>> m_roi_GoodMF;
  std::unique_ptr<std::vector<short>> m_roi_vetoed;

  std::unique_ptr<std::vector<float>> m_l2sa_e;
  std::unique_ptr<std::vector<float>> m_l2sa_pt;
  std::unique_ptr<std::vector<float>> m_l2sa_eta;
  std::unique_ptr<std::vector<float>> m_l2sa_phi;
  std::unique_ptr<std::vector<float>> m_l2sa_etaMS;
  std::unique_ptr<std::vector<float>> m_l2sa_phiMS;
  std::unique_ptr<std::vector<bool>> m_l2sa_pass;

  std::unique_ptr<std::vector< std::vector< float >>> m_l2sa_superPointR;
  std::unique_ptr<std::vector< std::vector< float >>> m_l2sa_superPointZ;
  std::unique_ptr<std::vector< std::vector< float >>> m_l2sa_superPointSlope;
  std::unique_ptr<std::vector< std::vector< float >>> m_l2sa_superPointIntercept;
  std::unique_ptr<std::vector< std::vector< float >>> m_l2sa_superPointChi2;

  // sTGC clusters
  std::unique_ptr<std::vector< std::vector< unsigned int >>> m_l2sa_stgcClusterLayer;
  std::unique_ptr<std::vector< std::vector< int >>>          m_l2sa_stgcClusterIsOutlier;
  std::unique_ptr<std::vector< std::vector< int >>>          m_l2sa_stgcClusterType;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_stgcClusterEta;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_stgcClusterPhi;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_stgcClusterR;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_stgcClusterZ;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_stgcClusterResidualR;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_stgcClusterResidualPhi;
  std::unique_ptr<std::vector< std::vector< int >>>          m_l2sa_stgcClusterStationEta;
  std::unique_ptr<std::vector< std::vector< int >>>          m_l2sa_stgcClusterStationPhi;
  std::unique_ptr<std::vector< std::vector< int >>>          m_l2sa_stgcClusterStationName;

  // MM clusters
  std::unique_ptr<std::vector< std::vector< unsigned int >>> m_l2sa_mmClusterLayer;
  std::unique_ptr<std::vector< std::vector< int >>>          m_l2sa_mmClusterIsOutlier;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_mmClusterEta;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_mmClusterPhi;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_mmClusterR;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_mmClusterZ;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_mmClusterResidualR;
  std::unique_ptr<std::vector< std::vector< float >>>        m_l2sa_mmClusterResidualPhi;
  std::unique_ptr<std::vector< std::vector< int >>>          m_l2sa_mmClusterStationEta;
  std::unique_ptr<std::vector< std::vector< int >>>          m_l2sa_mmClusterStationPhi;
  std::unique_ptr<std::vector< std::vector< int >>>          m_l2sa_mmClusterStationName;

  std::unique_ptr<std::vector<float>> m_l2sa_ptEndcapAlpha;
  std::unique_ptr<std::vector<float>> m_l2sa_ptEndcapBeta;

  std::unique_ptr<std::vector<float>> m_l1_eta;
  std::unique_ptr<std::vector<float>> m_l1_phi;
  std::unique_ptr<std::vector<float>> m_l1_dRoff;
  std::unique_ptr<std::vector<int>>   m_l1_BOM;
  std::unique_ptr<std::vector<int>>   m_l1_thrNum;
  std::unique_ptr<std::vector<int>>   m_l1_roiNum;

  std::unique_ptr<std::vector<float>> m_l2cb_e;
  std::unique_ptr<std::vector<float>> m_l2cb_pt;
  std::unique_ptr<std::vector<float>> m_l2cb_eta;
  std::unique_ptr<std::vector<float>> m_l2cb_phi;
  std::unique_ptr<std::vector<bool>> m_l2cb_pass;

  std::unique_ptr<std::vector<std::string>>                  m_chain;
  std::unique_ptr<std::vector< std::vector<int>>>            m_typeVec;
  std::unique_ptr<std::vector< std::vector<float>>>          m_ptVec;
  std::unique_ptr<std::vector< std::vector<float>>>          m_etaVec;
  std::unique_ptr<std::vector< std::vector<float>>>          m_phiVec;

  /* std::unique_ptr<std::vector<float>> m_road_Aw; */
  /* std::unique_ptr<std::vector<float>> m_road_Bw; */
  /* std::unique_ptr<std::vector<float>> m_road_R; */
  /* std::unique_ptr<std::vector<float>> m_road_Z; */
  /* std::unique_ptr<std::vector<float>> m_road_eta; */
  /* std::unique_ptr<std::vector<float>> m_road_phi; */

  /* std::unique_ptr<std::vector<float>> m_tgcHitEta; */
  /* std::unique_ptr<std::vector<float>> m_tgcHitPhi; */
  /* std::unique_ptr<std::vector<float>> m_tgcHitR; */
  /* std::unique_ptr<std::vector<float>> m_tgcHitZ; */
  /* std::unique_ptr<std::vector<int>> m_tgcHitStationNum; */
  /* std::unique_ptr<std::vector<bool>> m_tgcHitIsStrip; */
  /* std::unique_ptr<std::vector<int>> m_tgcHitBCTag; */
  /* std::unique_ptr<std::vector<bool>> m_tgcHitInRoad; */

};

#endif
