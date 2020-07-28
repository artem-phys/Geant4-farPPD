/* This file is a part of a GEANT4 model of farPPD at BNO */
/* Creator: Artem, lab assistant of Low Backgound Measurement Laboatory, PNPI */

/// \file ExG4ActionInitialization01.hh
/// \brief Definition of the ExG4ActionInitialization01 class

#ifndef ExG4ActionInitialization01_h
#define ExG4ActionInitialization01_h 1

#include "G4VUserActionInitialization.hh"

class ExG4ActionInitialization01 : public G4VUserActionInitialization
{
  public:
    ExG4ActionInitialization01();
    virtual ~ExG4ActionInitialization01();
    virtual void Build() const;
	  virtual void BuildForMaster() const;

};

#endif
