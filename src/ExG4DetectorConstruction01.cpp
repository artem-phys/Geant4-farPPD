/* This file is a part of a GEANT4 model of farPPD at BNO */
/* Creator: Artem, lab assistant of Low Backgound Measurement Laboatory, PNPI */

/// \file ExG4DetectorConstruction01.cpp
/// \brief Implementation of the ExG4DetectorConstruction01 class

#include "ExG4DetectorConstruction01.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4VisAttributes.hh"

ExG4DetectorConstruction01::ExG4DetectorConstruction01()
: G4VUserDetectorConstruction()
{ }

ExG4DetectorConstruction01::~ExG4DetectorConstruction01()
{ }

G4VPhysicalVolume* ExG4DetectorConstruction01::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();

  G4bool checkOverlaps = true;


  // WORLD
  G4double world_size = 2.2*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Box* solidWorld = new G4Box("World", 0.5*world_size, 0.5*world_size, 0.5*world_size);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");                      
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);

  // POLY COVER
  G4double poly_sizeXY = 1.7*m;
  G4double poly_sizeZ = 2*m;
  G4Material* poly_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Box* solidPoly = new G4Box("Poly ", 0.5*poly_sizeXY, 0.5*poly_sizeXY, 0.5*poly_sizeZ);
  G4LogicalVolume* logicPoly  = new G4LogicalVolume(solidPoly , poly_mat, "Poly");                      
  new G4PVPlacement(0, G4ThreeVector(), logicPoly, "Poly", logicWorld, false, 0, checkOverlaps);

  // PLUMBUM COVER
  G4double plumbum_sizeXY = 1*m;
  G4double plumbum_sizeZ = 1.5*m;
  G4Material* plumbum_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4Box* solidPlumbum = new G4Box("Plumbum", 0.5*plumbum_sizeXY, 0.5*plumbum_sizeXY, 0.5*plumbum_sizeZ);
  G4LogicalVolume* logicPlumbum = new G4LogicalVolume(solidPlumbum, plumbum_mat, "Plumbum");
  new G4PVPlacement(0, G4ThreeVector(), logicPlumbum, "Plumbum", logicPoly, false, 0, checkOverlaps);                

  // COPPER INSIDE
  G4double copper_sizeXY = 0.35*m;
  G4double copper_sizeZ = 0.7*m;
  G4Material* copper_mat = nist->FindOrBuildMaterial("G4_Cu");
  G4Box* solidCopper = new G4Box("Copper ", 0.5*copper_sizeXY, 0.5*copper_sizeXY, 0.5*copper_sizeZ);
  G4LogicalVolume* logicCopper = new G4LogicalVolume(solidCopper , copper_mat, "Copper");
  new G4PVPlacement(0, G4ThreeVector(), logicCopper, "Plumbum", logicPlumbum, false, 0, checkOverlaps);  

  // AIR CHAMBER
  G4double chamber_R = 0.1*m;
  G4double chamber_H = 0.4*m;
  G4Material* chamber_mat = nist->FindOrBuildMaterial("G4_AIR");                    
  G4Tubs* solidChamber = new G4Tubs("Chamber", 0, chamber_R, 0.5*chamber_H,0,2*3.141592653979);
  G4LogicalVolume* logicChamber = new G4LogicalVolume(solidChamber, chamber_mat, "Chamber");
  new G4PVPlacement(0, G4ThreeVector(), logicChamber, "Chamber", logicCopper, false, 0, checkOverlaps);  

  // DETECTOR
  G4double det_R = 0.05*m;
  G4double det_H = 0.05*m;
  G4Material* det_mat = nist->FindOrBuildMaterial("G4_Ge");                    
  G4Tubs* solidDet = new G4Tubs("Detector", 0, det_R, 0.5*det_H,0,2*3.141592653979);
  G4LogicalVolume* logicDet = new G4LogicalVolume(solidDet, det_mat, "Detector");
  new G4PVPlacement(0, G4ThreeVector(0,0,0.15*m), logicDet, "Detector", logicChamber, false, 0, checkOverlaps);  


  return physWorld;
}

void ExG4DetectorConstruction01::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  //Initialisisation of Detector volume as a MultiFunctionalDetector
  G4MultiFunctionalDetector* GeDet = new G4MultiFunctionalDetector("Detector");
  G4SDManager::GetSDMpointer()->AddNewDetector(GeDet);

  //Add primitive scorers
  G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep");
  GeDet->RegisterPrimitive(primitiv1);
  SetSensitiveDetector("Detector",GeDet);
}