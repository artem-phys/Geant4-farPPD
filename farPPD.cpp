/* This file is a part of a GEANT4 model of farPPD at BNO */
/* Creator: Artem, lab assistant of Low Backgound Measurement Laboatory, PNPI */

#include "G4ScoringManager.hh"
#include "g4root.hh"
#include "G4TScoreNtupleWriter.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "ExG4DetectorConstruction01.hh"
#include "Shielding.hh"
#include "ExG4ActionInitialization01.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc,char** argv)
{

//Run manager
G4RunManager* runManager = new G4RunManager;
runManager->SetUserInitialization(new ExG4DetectorConstruction01);
runManager->SetUserInitialization(new Shielding);
runManager->SetUserInitialization(new ExG4ActionInitialization01);
runManager->Initialize();//geant4 cernel initialisation

//Visualisation and UI
G4VisManager* visManager = new G4VisExecutive;
visManager->Initialize(); //visualisation manager initialisation
G4UImanager* UImanager = G4UImanager::GetUIpointer();

//Score ntuple writer activation
G4TScoreNtupleWriter<G4AnalysisManager> scoreNtupleWriter;
scoreNtupleWriter.SetVerboseLevel(1);

if ( argc == 1 ) 
{
//Visualisation
G4UIExecutive* ui = new G4UIExecutive(argc, argv);//UI creation
UImanager->ApplyCommand("/control/execute vis.mac");//Run macros vis.mac 
ui->SessionStart(); //UI start
delete ui;
}

else 
{
//Name of required macros to execute given through command line
G4String command = "/control/execute ";
G4String fileName = argv[1];
UImanager->ApplyCommand(command+fileName);
}

delete runManager;
return 0;
}
