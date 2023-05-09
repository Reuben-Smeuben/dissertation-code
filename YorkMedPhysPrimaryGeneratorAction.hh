// $Id: YorkMedPhysPrimaryGeneratorAction.hh 94808 2015-12-10 08:22:26Z gcosmo $
//
/// \file YorkMedPhysPrimaryGeneratorAction.hh
/// \brief Definition of the YorkMedPhysPrimaryGeneratorAction class

#ifndef YorkMedPhysPrimaryGeneratorAction_h
#define YorkMedPhysPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include <fstream>
class G4ParticleGun;
class G4Event;

/// The primary generator action class with particle gun.
///
/// It defines a single particle which hits the calorimeter
/// perpendicularly to the input face. The type of the particle
/// can be changed via the G4 build-in commands of G4ParticleGun class
/// (see the macros provided with this example).

class YorkMedPhysPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  YorkMedPhysPrimaryGeneratorAction();
  virtual ~YorkMedPhysPrimaryGeneratorAction();
  std::ofstream outfile;
  virtual void GeneratePrimaries(G4Event* event);

  // set methods
  void SetRandomFlag(G4bool value);

private:
  G4ParticleGun*  fParticleGun; // G4 particle gun
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
