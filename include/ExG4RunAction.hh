/* This file is a part of a GEANT4 model of farPPD at BNO */
/* Creator: Artem, lab assistant of Low Backgound Measurement Laboatory, PNPI */

/// \file ExG4RunAction.hh
/// \brief Definition of the ExG4RunAction class

#ifndef ExG4RunAction_h
#define ExG4RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class ExG4RunAction: public G4UserRunAction
{
  public:
    ExG4RunAction();
    virtual ~ExG4RunAction();
    
    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};
#endif

