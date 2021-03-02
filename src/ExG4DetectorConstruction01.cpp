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
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "ExG4EnergyDeposit.hh"


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
  G4double world_size = 1*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Box* solidWorld = new G4Box("World", 0.5*world_size, 0.5*world_size, 0.5*world_size);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");                      
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);

  // POLY COVER
  G4double poly_sizeXY = 92*cm;
  G4double poly_sizeZ = 96*cm;
  G4Material* poly_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Box* solidPoly = new G4Box("Poly", 0.5*poly_sizeXY, 0.5*poly_sizeXY, 0.5*poly_sizeZ);
  G4LogicalVolume* logicPoly  = new G4LogicalVolume(solidPoly , poly_mat, "Poly");
  new G4PVPlacement(0, G4ThreeVector(), logicPoly, "Poly", logicWorld, false, 0, checkOverlaps);

  // CADMIUM LAYER
  G4double cadmium_sizeXY = 82.15*cm;
  G4double cadmium_sizeZ = 86.15*cm;
  G4Material* cadmium_mat = nist->FindOrBuildMaterial("G4_Cd");
  G4Box* solidCadmium = new G4Box("Cadmium", 0.5*cadmium_sizeXY, 0.5*cadmium_sizeXY, 0.5*cadmium_sizeZ);
  G4LogicalVolume* logicCadmium  = new G4LogicalVolume(solidCadmium , cadmium_mat, "Cadmium");
  new G4PVPlacement(0, G4ThreeVector(), logicCadmium, "Cadmium", logicPoly, false, 0, checkOverlaps);

  // PLUMBUM COVER
  G4double plumbum_sizeXY = 82*cm;
  G4double plumbum_sizeZ = 86*cm;
  G4Material* plumbum_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4Box* solidPlumbum = new G4Box("Plumbum", 0.5*plumbum_sizeXY, 0.5*plumbum_sizeXY, 0.5*plumbum_sizeZ);
  G4LogicalVolume* logicPlumbum = new G4LogicalVolume(solidPlumbum, plumbum_mat, "Plumbum");
  new G4PVPlacement(0, G4ThreeVector(), logicPlumbum, "Plumbum", logicCadmium, false, 0, checkOverlaps);                

  // COPPER INSIDE
  G4double copper_sizeXY = 50*cm;
  G4double copper_sizeZ = 54*cm;
  G4Material* copper_mat = nist->FindOrBuildMaterial("G4_Cu");
  G4Box* solidCopper = new G4Box("Copper ", 0.5*copper_sizeXY, 0.5*copper_sizeXY, 0.5*copper_sizeZ);
  G4LogicalVolume* logicCopper = new G4LogicalVolume(solidCopper , copper_mat, "Copper");
  new G4PVPlacement(0, G4ThreeVector(), logicCopper, "Plumbum", logicPlumbum, false, 0, checkOverlaps);  

  // AIR CHAMBER
  G4double hollow_R = 85*mm;
  G4double hollow_H = 220*mm;
  G4double main_chamber_R = 150*mm;
  G4double main_chamber_H = 110*mm;
  G4Material* chamber_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Tubs* cryostat_hollow = new G4Tubs("Hollow", 0, hollow_R, 0.5*hollow_H,0,360.*deg);
  G4Tubs* mainChamber = new G4Tubs("mainChamber", 0, main_chamber_R, 0.5*main_chamber_H,0,360.*deg);
  G4UnionSolid* solidChamber = new G4UnionSolid("Chamber", mainChamber, cryostat_hollow, 0, G4ThreeVector(0,0,8.5*cm));

  G4LogicalVolume* logicChamber = new G4LogicalVolume(solidChamber, chamber_mat, "Chamber");
  new G4PVPlacement(0,  G4ThreeVector(0,0,-4.5*cm), logicChamber, "Chamber", logicCopper, false, 0, checkOverlaps);  
  
  // CRYOSTAT
  G4double cryostat_R = 84*mm;
  G4double cryostat_H = 108*mm;
  G4Material* cryostat_mat = nist->FindOrBuildMaterial("G4_Cu");                    
  G4Tubs* solidCryostat = new G4Tubs("Сryostat", 0, cryostat_R, 0.5*cryostat_H,0,360.*deg);
  G4LogicalVolume* logicCryostat = new G4LogicalVolume(solidCryostat, cryostat_mat, "Сryostat");
  new G4PVPlacement(0, G4ThreeVector(0,0,6*cm), logicCryostat, "Сryostat", logicChamber, false, 0, checkOverlaps);

  // CRYOCHAMBER
  G4double thickness = 0.6*mm;
  G4double cryochamber_R = cryostat_R-thickness;
  G4double cryochamber_H = cryostat_H-thickness;
  G4Material* cryochamber_mat = nist->FindOrBuildMaterial("G4_AIR");          
  G4Tubs* solidCryochamber = new G4Tubs("Cryochamber", 0, cryochamber_R, 0.5*cryochamber_H,0,360.*deg);
  G4LogicalVolume* logicCryochamber = new G4LogicalVolume(solidCryochamber, cryochamber_mat, "Cryochamber");
  new G4PVPlacement(0, G4ThreeVector(), logicCryochamber, "Cryochamber", logicCryostat, false, 0, checkOverlaps);

  // DETECTOR
  G4double det_R = 65*mm;
  G4double det_H = 54*mm; 
  G4Material* det_mat = nist->FindOrBuildMaterial("G4_Ge");                    
  G4Tubs* solidDet = new G4Tubs("Detector", 0, det_R, 0.5*det_H,0,360.*deg);
  G4LogicalVolume* logicDet = new G4LogicalVolume(solidDet, det_mat, "Detector");
  new G4PVPlacement(0, G4ThreeVector(0,0,-2.6*cm), logicDet, "Detector", logicCryochamber, false, 0, checkOverlaps);

  // DEAD LAYER   
  G4double dead_layer_thickness = 0.5*mm;               
  G4Tubs* solidDead = new G4Tubs("Dead", 0, det_R, 0.5*dead_layer_thickness,0,360.*deg);
  G4LogicalVolume* logicDead = new G4LogicalVolume(solidDead, det_mat, "Dead");
  new G4PVPlacement(0, G4ThreeVector(0,0,-(det_H-dead_layer_thickness)/2), logicDead, "Dead", logicDet, false, 0, checkOverlaps);


  return physWorld;
}

void ExG4DetectorConstruction01::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  //Initialisisation of Detector volume as a MultiFunctionalDetector
  G4MultiFunctionalDetector* GeDet = new G4MultiFunctionalDetector("Detector");
  G4SDManager::GetSDMpointer()->AddNewDetector(GeDet);

  
  G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep");
  GeDet->RegisterPrimitive(primitiv1);
  SetSensitiveDetector("Detector", GeDet);

  //Initialisisation of World volume as a MultiFunctionalDetector
  G4MultiFunctionalDetector* WorldDet = new G4MultiFunctionalDetector("World");
  G4SDManager::GetSDMpointer()->AddNewDetector(WorldDet);
}