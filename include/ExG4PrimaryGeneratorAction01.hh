﻿/* This file is a part of a GEANT4 model of farPPD at BNO */
/* Creator: Artem, lab assistant of Low Backgound Measurement Laboatory, PNPI */

/// \file ExG4PrimaryGeneratorAction01.hh
/// \brief Definition of the ExG4PrimaryGeneratorAction01 class

#ifndef B1PrimaryGeneratorAction_h
#define B1PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

#include "G4IonTable.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

class ExG4PrimaryGeneratorAction01 : public G4VUserPrimaryGeneratorAction
{
  public:
    ExG4PrimaryGeneratorAction01();
    virtual ~ExG4PrimaryGeneratorAction01();

    // Метод из базового класса, задает параметры источника начальных частиц
    virtual void GeneratePrimaries(G4Event*);         
  
    // Метод для доступа к источнику частиц (пушке частиц ;) )
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun; // указатель на источник частиц
    // Временная переменная объема
    G4Box* fEnvelopeBox;
    G4IonTable* ionTable;
    G4ParticleDefinition* ion;
};
#endif
