# input data

# testFile = '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000012/AOD.pool.root'
# import AthenaPoolCnvSvc.ReadAthenaPool
# ServiceMgr.EventSelector.InputCollections = [testFile]

import AthenaPoolCnvSvc.ReadAthenaPool

# ServiceMgr.EventSelector.InputCollections = ['/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000001/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000010/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000012/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000014/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000015/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000016/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000017/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000018/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000019/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Jpsi/Jpsi_000020/AOD.pool.root']

# ServiceMgr.EventSelector.InputCollections = ['/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Jpsi/Jpsi_000001/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Jpsi/Jpsi_000010/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Jpsi/Jpsi_000012/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Jpsi/Jpsi_000014/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Jpsi/Jpsi_000015/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Jpsi/Jpsi_000016/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Jpsi/Jpsi_000017/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Jpsi/Jpsi_000018/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Jpsi/Jpsi_000019/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Jpsi/Jpsi_000020/AOD.pool.root']

# ServiceMgr.EventSelector.InputCollections = ['/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/def_Zmumu/Zmumu_000001/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/def_Zmumu/Zmumu_000002/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/def_Zmumu/Zmumu_000003/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/def_Zmumu/Zmumu_000004/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/def_Zmumu/Zmumu_000005/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/def_Zmumu/Zmumu_000006/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/def_Zmumu/Zmumu_000007/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/def_Zmumu/Zmumu_000008/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/def_Zmumu/Zmumu_000009/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/def_Zmumu/Zmumu_000010/AOD.pool.root']

# ServiceMgr.EventSelector.InputCollections = ['/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/Onesector_Zmumu/Zmumu_000001/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/Onesector_Zmumu/Zmumu_000002/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/Onesector_Zmumu/Zmumu_000003/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/Onesector_Zmumu/Zmumu_000004/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/Onesector_Zmumu/Zmumu_000005/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/Onesector_Zmumu/Zmumu_000006/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/Onesector_Zmumu/Zmumu_000007/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/Onesector_Zmumu/Zmumu_000008/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/Onesector_Zmumu/Zmumu_000009/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230220_sectorOverlap/Onesector_Zmumu/Zmumu_000010/AOD.pool.root']

# ServiceMgr.EventSelector.InputCollections = ['/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Zmumu/Zmumu_000001/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Zmumu/Zmumu_000002/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Zmumu/Zmumu_000003/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Zmumu/Zmumu_000004/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Zmumu/Zmumu_000005/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Zmumu/Zmumu_000006/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Zmumu/Zmumu_000007/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Zmumu/Zmumu_000008/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Zmumu/Zmumu_000009/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/mod_Zmumu/Zmumu_000010/AOD.pool.root']

# ServiceMgr.EventSelector.InputCollections = ['/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Zmumu/Zmumu_000001/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Zmumu/Zmumu_000002/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Zmumu/Zmumu_000003/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Zmumu/Zmumu_000004/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Zmumu/Zmumu_000005/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Zmumu/Zmumu_000006/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Zmumu/Zmumu_000007/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Zmumu/Zmumu_000008/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Zmumu/Zmumu_000009/AOD.pool.root',
#                                              '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/20230317_L2SApTResolModel/noextr_Zmumu/Zmumu_000010/AOD.pool.root']

# ServiceMgr.EventSelector.InputCollections = ['/gpfs/fs7001/youhei/L2MuonSA/dataset_aod/AOD.atr-27406_mod.pool.root']

# ServiceMgr.EventSelector.InputCollections = [
#     '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14651_r14652_tid33311798_00/AOD.33311798._000003.pool.root.1',
#     '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14651_r14652_tid33311798_00/AOD.33311798._000022.pool.root.1',
#     '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14651_r14652_tid33311798_00/AOD.33311798._000087.pool.root.1',
#     '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14651_r14652_tid33311798_00/AOD.33311798._000337.pool.root.1',
#     '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14651_r14652_tid33311798_00/AOD.33311798._000423.pool.root.1',
#     '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14651_r14652_tid33311798_00/AOD.33311798._000441.pool.root.1',
#     '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14651_r14652_tid33311798_00/AOD.33311798._001101.pool.root.1',
#     '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14651_r14652_tid33311798_00/AOD.33311798._001239.pool.root.1',
#     '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14651_r14652_tid33311798_00/AOD.33311798._001270.pool.root.1',
#     '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14651_r14652_tid33311798_00/AOD.33311798._001330.pool.root.1']

#ServiceMgr.EventSelector.InputCollections = [
#    '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.merge.AOD.r14651_r14652_p5664_tid33311800_00/AOD.33311800._000006.pool.root.1',
#    '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.merge.AOD.r14651_r14652_p5664_tid33311800_00/AOD.33311800._000014.pool.root.1',
#    '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.merge.AOD.r14651_r14652_p5664_tid33311800_00/AOD.33311800._000022.pool.root.1',
#    '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.merge.AOD.r14651_r14652_p5664_tid33311800_00/AOD.33311800._000027.pool.root.1',
#    '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.merge.AOD.r14651_r14652_p5664_tid33311800_00/AOD.33311800._000058.pool.root.1',
#    '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.merge.AOD.r14651_r14652_p5664_tid33311800_00/AOD.33311800._000064.pool.root.1',
#    '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.merge.AOD.r14651_r14652_p5664_tid33311800_00/AOD.33311800._000085.pool.root.1',
#    '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.merge.AOD.r14651_r14652_p5664_tid33311800_00/AOD.33311800._000115.pool.root.1',
#    '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.merge.AOD.r14651_r14652_p5664_tid33311800_00/AOD.33311800._000129.pool.root.1',
#    '/gpfs/fs7001/youhei/L2MuonSA/dataset_aod_official/data22_13p6TeV.00440499.physics_EnhancedBias.merge.AOD.r14651_r14652_p5664_tid33311800_00/AOD.33311800._000139.pool.root.1']

#ServiceMgr.EventSelector.InputCollections = [
#    '/gpfs/fs8001/toyamash/valid1.601190.PhPy8EG_AZNLO_Zmumu.recon.AOD.e8514_e8528_s4111_s4114_r14706_tid33639678_00/AOD.33639678._000001.pool.root.1',
#    '/gpfs/fs8001/toyamash/valid1.601190.PhPy8EG_AZNLO_Zmumu.recon.AOD.e8514_e8528_s4111_s4114_r14706_tid33639678_00/AOD.33639678._000001.poo2.root.1',
#    '/gpfs/fs8001/toyamash/valid1.601190.PhPy8EG_AZNLO_Zmumu.recon.AOD.e8514_e8528_s4111_s4114_r14706_tid33639678_00/AOD.33639678._000001.poo3.root.1',
#    '/gpfs/fs8001/toyamash/valid1.601190.PhPy8EG_AZNLO_Zmumu.recon.AOD.e8514_e8528_s4111_s4114_r14706_tid33639678_00/AOD.33639678._000001.poo4.root.1',
#    '/gpfs/fs8001/toyamash/valid1.601190.PhPy8EG_AZNLO_Zmumu.recon.AOD.e8514_e8528_s4111_s4114_r14706_tid33639678_00/AOD.33639678._000001.poo5.root.1',
#    '/gpfs/fs8001/toyamash/valid1.601190.PhPy8EG_AZNLO_Zmumu.recon.AOD.e8514_e8528_s4111_s4114_r14706_tid33639678_00/AOD.33639678._000001.poo6.root.1',
#    '/gpfs/fs8001/toyamash/valid1.601190.PhPy8EG_AZNLO_Zmumu.recon.AOD.e8514_e8528_s4111_s4114_r14706_tid33639678_00/AOD.33639678._000001.poo7.root.1',
#    '/gpfs/fs8001/toyamash/valid1.601190.PhPy8EG_AZNLO_Zmumu.recon.AOD.e8514_e8528_s4111_s4114_r14706_tid33639678_00/AOD.33639678._000001.poo8.root.1',
#    '/gpfs/fs8001/toyamash/valid1.601190.PhPy8EG_AZNLO_Zmumu.recon.AOD.e8514_e8528_s4111_s4114_r14706_tid33639678_00/AOD.33639678._000001.poo9.root.1',
#    '/gpfs/fs8001/toyamash/valid1.601190.PhPy8EG_AZNLO_Zmumu.recon.AOD.e8514_e8528_s4111_s4114_r14706_tid33639678_00/AOD.33639678._000001.poo10.root.1']

#ServiceMgr.EventSelector.InputCollections = [
#    '/gpfs/fs8001/toyamash/L2mt/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185._lb0296._0011.1']
#    '/gpfs/fs8001/toyamash/L2mt/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185._lb0423._0011.1',
#    '/gpfs/fs8001/toyamash/L2mt/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185._lb0704._0007.1',
#    '/gpfs/fs8001/toyamash/L2mt/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185._lb0366._0001.1',
#    '/gpfs/fs8001/toyamash/L2mt/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185._lb0500._0007.1',
#    '/gpfs/fs8001/toyamash/L2mt/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185._lb0782._0001.1',
#    '/gpfs/fs8001/toyamash/L2mt/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185._lb0394._0001.1',
#    '/gpfs/fs8001/toyamash/L2mt/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185._lb0623._0004.1',
#    '/gpfs/fs8001/toyamash/L2mt/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185._lb0411._0011.1',
#    '/gpfs/fs8001/toyamash/L2mt/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185/data23_13p6TeV.00456164.physics_Main.merge.AOD.f1369_m2185._lb0630._0010.1']

ServiceMgr.EventSelector.InputCollections = [
    #'/home/toyamash/NtupleforNSW/run_1206/data23_13p6TeV.00460096.physics_Main.merge.AOD.r15081_r15082_tid35283096_00._0001.pool.root']
    #'/home/toyamash/MakeAODforNSW/run_1218/data23_13p6TeV.00460096.physics_Main.recon.AOD.r15081_r15082_tid35283096_00._0001.pool.root']
    #'/eos/user/t/toyamash/L2mt/data23_13p6TeV.00454083.physics_Main.merge.AOD.f1360_m2179/data23_13p6TeV.00454083.physics_Main.merge.AOD.f1360_m2179._lb1251._0003.1']
    #'/home/toyamash/CreateAODforNSW/run/data23_13p6TeV.00460096.physics_Main.recon.AOD.r15081_r15082_tid35283096_00._0001.pool.root']
    #'/home/toyamash/CreateAODforNSW/test/data23_13p6TeV.00454163.physics_Main.recon.AOD._0001.pool.root']
    #'/home/toyamash/CreateAODforNSW/test_withMM/data23_13p6TeV.00454163.physics_Main.recon.AOD._0001.pool.root']
    '/gpfs/fs8001/toyamash/dataFotNSW/data23_13p6TeV.00454163.physics_Main.merge.AOD.f1360_m2179/data23_13p6TeV.00454163.physics_Main.merge.AOD.f1360_m2179._lb1033._0004.1']
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._001175.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._003014.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._004412.AOD.pool.root',
    
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._028311.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._000935.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._015480.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._009228.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._017839.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._001512.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._011005.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._018799.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._029119.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._011200.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._022911.AOD.pool.root',
    #'/gpfs/fs8001/toyamash/dataFotNSW/user.toyamash.20231218_v2.data22_13p6TeV.00454163.physics_Main.recon.RAW_EXT0/user.toyamash.36254403.EXT0._027511.AOD.pool.root']

# output file
ServiceMgr += CfgMgr.THistSvc()
ServiceMgr.THistSvc.Output += [
    #"ANALYSIS DATAFILE='MyxAODAnalysis_valid1.601190.PhPy8EG_AZNLO_Zmumu.output.root' OPT='RECREATE'"
    "ANALYSIS DATAFILE='MyxAODAnalysis_data23_13p6TeV_0109_v2_withoutMM.00454163.physics_Main.merge.AOD.root' OPT='RECREATE'"
    ]
ServiceMgr.THistSvc.MaxFileSize=-1 #speeds up jobs that output lots of histograms

# Setup TDT
# configTool = CfgMgr.TrigConf__xAODConfigTool("xAODConfigTool")
# ToolSvc += configTool

from TrigDecisionTool.TrigDecisionToolConf import Trig__TrigDecisionTool
tdt = Trig__TrigDecisionTool( "TrigDecisionTool",
                            # ConfigTool = configTool,
                            TrigDecisionKey = "xTrigDecision",
                            HLTSummary = "HLTNav_Summary_AODSlimmed",
                            #OutputLevel = 1 
)
tdt.NavigationFormat = "TrigComposite"
# tdt.NavigationFormat = "TriggerElement"
ToolSvc += tdt

# Create the algorithm's configuration.
from AnaAlgorithm.DualUseConfig import createAlgorithm
alg = createAlgorithm ( 'MyxAODAnalysis', 'AnalysisAlg' )

# Add private tool
from AnaAlgorithm.DualUseConfig import addPrivateTool

# muon ID tool
addPrivateTool( alg, 'MuonSelTool', 'CP::MuonSelectionTool' )
alg.MuonSelTool.MuQuality = 1  #0, 1, 2, 3, 4, 5 correspond to Tight, Medium, Loose, VeryLoose, HighPt, LowPtEfficiency
alg.MuonSelTool.IsRun3Geo = True
alg.MuonSelTool.TurnOffMomCorr = True

addPrivateTool( alg, 'truthClassificationTool', 'TruthClassificationTool' )

# Add our algorithm to the main alg sequence
athAlgSeq += alg
