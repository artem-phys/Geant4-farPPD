/* This file is a part of a GEANT4 model of farPPD at BNO */
/* Creator: Artem, lab assistant of Low Backgound Measurement Laboatory, PNPI */

/// \file ExG4ActionInitialization01.cpp
/// \brief Implementation of the ExG4ActionInitialization01 class

#include "ExG4PrimaryGeneratorAction01.hh"
#include "ExG4ActionInitialization01.hh"
#include "ExG4RunAction.hh"

#include "ExG4RunAction.hh"
#include "ExG4Run.hh"
#include "ExG4PrimaryGeneratorAction01.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

ExG4ActionInitialization01::ExG4ActionInitialization01()
 : G4VUserActionInitialization()
{}

ExG4ActionInitialization01::~ExG4ActionInitialization01()
{}

void ExG4ActionInitialization01::Build() const
{
SetUserAction(new ExG4RunAction);
SetUserAction(new ExG4PrimaryGeneratorAction01);
}

void ExG4ActionInitialization01::BuildForMaster() const
{
  SetUserAction(new ExG4RunAction);
}
