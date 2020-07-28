# Geant4-farPPD
Geant4 Monte Carlo simulation for farPPD detector in Baksano Neutrino Observatory

farPPD facility, located in BNO, looks like this
![Facility](https://github.com/artem-phys/Geant4-farPPD/raw/master/Photos/Facility.jpg)

This experimental installation consists of coating with borated polyethylene, lead coating, and copper housing inside. 
The detector is located in the inner chamber, the air from which is not pumped out. 
![Scheme](https://github.com/artem-phys/Geant4-farPPD/raw/master/Photos/Scheme.jpg)

The sample is constitutes a bag of powder:
![Sample](https://github.com/artem-phys/Geant4-farPPD/raw/master/Photos/Sample.jpg)

It is placed on the removable parts of the experimental installation, that can be lifted back
![Placement](https://github.com/artem-phys/Geant4-farPPD/raw/master/Photos/Placement.jpg)

The sample is contaminated with americium ,and thus, isotropically emits gamma particles of energy E=59.5409 keV. 
The decsription of particle generations is located in ExG4PrimaryGeneratorAction01.cpp

If you run the project without command line args, the visualisation starts:
![Vis](https://github.com/artem-phys/Geant4-farPPD/raw/master/Visualisation/Visualisation.jpg)

Simulation data scores in a ROOT file for further analysis
