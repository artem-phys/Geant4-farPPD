/* This file is a part of a GEANT4 model of farPPD at BNO */
/* Creator: Artem, lab assistant of Low Backgound Measurement Laboatory, PNPI */

/// \file ExG4DetectorConstruction01.hh
/// \brief Definition of the ExG4DetectorConstruction01 class

#ifndef ExG4DetectorConstruction01_h
#define ExG4DetectorConstruction01_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class ExG4DetectorConstruction01 : public G4VUserDetectorConstruction 
{
  public:
    ExG4DetectorConstruction01();
    virtual ~ExG4DetectorConstruction01();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  protected:
};
#endif