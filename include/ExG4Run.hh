/* This file is a part of a GEANT4 model of farPPD at BNO */
/* Creator: Artem, lab assistant of Low Backgound Measurement Laboatory, PNPI */

/// \file ExG4Run.hh
/// \brief Definition of the ExG4Run class

#ifndef ExG4Run_h
#define ExG4Run_h 1

#include "G4Run.hh"
#include "globals.hh"
#include "G4StatAnalysis.hh"

/// Run class
///
/// In RecordEvent() there is collected information event per event 
/// from Hits Collections, and accumulated statistic for the run 

class ExG4Run : public G4Run
{
  public:
    ExG4Run();
    virtual ~ExG4Run();

    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);
    
  public:
    G4int GetNbGoodEvents() const { return fGoodEvents; }
    G4double GetSumDose()   const { return fSumDose; }    
    G4StatAnalysis GetStatDose() const { return fStatDose; }

  private:
    G4int fCollID_cryst;
    G4int fCollID_patient;   
    G4int fPrintModulo;
    G4int fGoodEvents;
    G4double fSumDose;
    G4StatAnalysis fStatDose;
};

#endif

    
