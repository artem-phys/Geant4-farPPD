//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
//
// G4PSEnergyDeposit
#include "ExG4EnergyDeposit.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring energy deposit.
// 
// Created: 2005-11-14  Tsukasa ASO, Akinori Kimura.
// 2010-07-22   Introduce Unit specification.
// 
///////////////////////////////////////////////////////////////////////////////

ExG4EnergyDeposit::ExG4EnergyDeposit(G4String name, G4int depth)
  :G4VPrimitiveScorer(name,depth),HCID(-1),EvtMap(0)
{
  SetUnit("keV");
}

ExG4EnergyDeposit::ExG4EnergyDeposit(G4String name, const G4String& unit, 
				     G4int depth)
  :G4VPrimitiveScorer(name,depth),HCID(-1),EvtMap(0)
{
  SetUnit(unit);
}

ExG4EnergyDeposit::~ExG4EnergyDeposit()
{;}

G4bool ExG4EnergyDeposit::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4Track * track = aStep->GetTrack();
  G4double time = track->GetGlobalTime();


  if (time > 2629743.83*s) 
  {
    track->SetTrackStatus(fStopAndKill);
  }
  return TRUE;
}

void ExG4EnergyDeposit::Initialize(G4HCofThisEvent* HCE)
{
  EvtMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(),
				    GetName());
  if(HCID < 0) {HCID = GetCollectionID(0);}
  HCE->AddHitsCollection(HCID, (G4VHitsCollection*)EvtMap);
}

void ExG4EnergyDeposit::EndOfEvent(G4HCofThisEvent*)
{;}

void ExG4EnergyDeposit::clear()
{
  EvtMap->clear();
}

void ExG4EnergyDeposit::DrawAll()
{;}

void ExG4EnergyDeposit::PrintAll()
{
  G4cout << " MultiFunctionalDet  " << detector->GetName() << G4endl;
  G4cout << " PrimitiveScorer " << GetName() << G4endl;
  G4cout << " Number of entries " << EvtMap->entries() << G4endl;
  std::map<G4int,G4double*>::iterator itr = EvtMap->GetMap()->begin();
  for(; itr != EvtMap->GetMap()->end(); itr++) {
    G4cout << "  copy no.: " << itr->first
	   << "  energy deposit: " 
	   << *(itr->second)/GetUnitValue()
	   << " [" << GetUnit()<<"]"
	   << G4endl;
  }
}

void ExG4EnergyDeposit::SetUnit(const G4String& unit)
{
	CheckAndSetUnit(unit,"Energy");
}