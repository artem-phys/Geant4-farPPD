/* This file is a part of a GEANT4 model of farPPD at BNO */
/* Creator: Artem, lab assistant of Low Backgound Measurement Laboatory, PNPI */

/// \file ExG4Run.cc
/// \brief Implementation of the ExG4Run class

#include "ExG4Run.hh"

#include "G4THitsMap.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4SDmessenger.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4VSensitiveDetector.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

ExG4Run::ExG4Run()
 : G4Run(), 
   fCollID_cryst(-1),
   fPrintModulo(10000),
   fGoodEvents(0),
   fSumDose(0.),
   fStatDose(),
   AllEvents(10000000)
{ }

ExG4Run::~ExG4Run()
{ }

void ExG4Run::RecordEvent(const G4Event* event)
{
  if ( fCollID_cryst < 0 ) {
   fCollID_cryst 
     = G4SDManager::GetSDMpointer()->GetCollectionID("Detector/edep"); 
  }

  G4int evtNb = event->GetEventID();
  
  //Progress bar
  if (evtNb%fPrintModulo == 0) { 
    G4cout << G4endl << "Progress " << evtNb << "/" << AllEvents << G4endl;
  }      
  
  //Hits collections
  //  
  G4HCofThisEvent* HCE = event->GetHCofThisEvent();
  if(!HCE) return;
               
  //Energy in crystals : identify 'good events'
  //
  const G4double eThreshold = 1*keV;
  G4int nbOfFired = 0;
   
  G4THitsMap<G4double>* evtMap = 
    static_cast<G4THitsMap<G4double>*>(HCE->GetHC(fCollID_cryst));
               
  std::map<G4int,G4double*>::iterator itr;
  for (itr = evtMap->GetMap()->begin(); itr != evtMap->GetMap()->end(); itr++) {
    G4double edep = *(itr->second);
    if (edep > eThreshold) nbOfFired++;
    G4int copyNb  = (itr->first);
    //G4cout << G4endl << "  cryst" << copyNb << ": " << edep/keV << " keV ";
  }  
  if (nbOfFired == 2) fGoodEvents++;
  
  
  G4Run::RecordEvent(event);  
}  

void ExG4Run::Merge(const G4Run* aRun)
{
  const ExG4Run* localRun = static_cast<const ExG4Run*>(aRun);
  fGoodEvents += localRun->fGoodEvents;
  fSumDose    += localRun->fSumDose;
  G4Run::Merge(aRun);
}
