/* This file is a part of a GEANT4 model of farPPD at BNO */
/* Creator: Artem, lab assistant of Low Backgound Measurement Laboatory, PNPI */

/// \file ExG4RunAction.cc
/// \brief Implementation of the ExG4RunAction class

#include "ExG4RunAction.hh"
#include "ExG4Run.hh"
#include "ExG4PrimaryGeneratorAction01.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

ExG4RunAction::ExG4RunAction(): 
G4UserRunAction()
{ }

ExG4RunAction::~ExG4RunAction()
{ }

G4Run* ExG4RunAction::GenerateRun()
{ return new ExG4Run; }

void ExG4RunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
  
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

void ExG4RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  
  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const ExG4PrimaryGeneratorAction01* generatorAction
    = static_cast<const ExG4PrimaryGeneratorAction01*>(
        G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String partName;
  if (generatorAction) 
  {
    G4ParticleDefinition* particle 
      = generatorAction->GetParticleGun()->GetParticleDefinition();
    partName = particle->GetParticleName();
  }  
  
  //results
  //
  const ExG4Run* b3Run = static_cast<const ExG4Run*>(run);
  G4int nbGoodEvents = b3Run->GetNbGoodEvents();
  G4double sumDose   = b3Run->GetSumDose();
  G4StatAnalysis statDose = b3Run->GetStatDose();
        
  //print
  //
  if (1)
  {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------"
     << G4endl
     << "  The run was " << nofEvents << " events ";
  }
  else
  {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------"
     << G4endl
     << "  The run was " << nofEvents << " "<< partName;
  }      
  statDose /= gray;
  G4cout
     << "; Nb of 'good' e+ annihilations: " << nbGoodEvents  << G4endl
     << " Total dose in patient : " << G4BestUnit(sumDose, "Dose") << G4endl
     << " Total dose in patient : " << statDose << " Gy" << G4endl
     << "------------------------------------------------------------" << G4endl 
     << G4endl;
     
}