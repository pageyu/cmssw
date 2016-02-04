import FWCore.ParameterSet.Config as cms

SeedFromConsecutiveHitsCreator = cms.PSet(
  ComponentName = cms.string('SeedFromConsecutiveHitsCreator'),
  propagator = cms.string('PropagatorWithMaterial'),
  SeedMomentumForBOFF = cms.double(5.0)
)
