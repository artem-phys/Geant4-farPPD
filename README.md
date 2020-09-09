# Geant4-farPPD
Geant4 Monte Carlo simulation for farPPD detector in Baksano Neutrino Observatory


The farPPD facility is located in BNO and looks as shown in the photo:

![Facility](https://github.com/artem-phys/Geant4-farPPD/raw/master/Photos/Facility.jpg){:height="100px" width="100px"}

The experimental installation consists of coating with borated polyethylene, lead coating, and copper housing inside. 
The detector is located in the inner chamber, the air from which is not pumped out. 
![Scheme](https://github.com/artem-phys/Geant4-farPPD/raw/master/Photos/Scheme.jpg){:height="100px" width="100px"}
![Scheme precisely](https://github.com/artem-phys/Geant4-farPPD/raw/master/Photos/farPPD_size.jpg){:height="100px" width="100px"}

It's not what you thought, it's an experimental sample:
![Sample](https://github.com/artem-phys/Geant4-farPPD/raw/master/Photos/Sample.jpg){:height="100px" width="100px"}

The bag is placed on the movable parts of the experimental installation, that can be lifted back
![Placement](https://github.com/artem-phys/Geant4-farPPD/raw/master/Photos/Placement.jpg){:height="100px" width="100px"}

The sample is contaminated with americium, and thus, isotropically emits gamma particles of energy E=59.5409 keV. 
The decsription of particle generations is located in ExG4PrimaryGeneratorAction01.cpp

If you run the project without command line args, the visualisation starts:
![Vis](https://github.com/artem-phys/Geant4-farPPD/raw/master/Visualisation/Visualisation.jpg){:height="100px" width="100px"}

A slight dead layer, that is not sensitive in the detector, present in this modeling. Also, you can see tracks of the particles in the following screenshot:
![Tracks](https://github.com/artem-phys/Geant4-farPPD/raw/master/Visualisation/Tracks.jpg){:height="100px" width="100px"}

Simulation data scores in a ROOT file for further analysis
