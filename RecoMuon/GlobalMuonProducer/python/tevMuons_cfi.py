import FWCore.ParameterSet.Config as cms

from RecoMuon.TrackingTools.MuonServiceProxy_cff import *
from RecoMuon.TrackingTools.MuonTrackLoader_cff import *
from RecoMuon.GlobalTrackingTools.GlobalTrajectoryBuilderCommon_cff import *
from RecoMuon.GlobalTrackingTools.GlobalMuonRefitter_cff import *
tevMuons = cms.EDProducer("TevMuonProducer",
    MuonTrackLoaderForGLB,
    #    InputTag MuonCollectionLabel = standAloneMuons:UpdatedAtVtx
    MuonServiceProxy,
    RefitIndex = cms.vint32(1, 2, 3, 4),
    Refits = cms.vstring('default', 
        'firstHit', 
        'picky', 
        'dyt'),
    MuonCollectionLabel = cms.InputTag("globalMuons"),
    RefitterParameters = cms.PSet(
        GlobalMuonRefitter
    )
)



