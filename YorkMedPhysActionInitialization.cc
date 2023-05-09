// $Id: YorkMedPhysActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file YorkMedPhysActionInitialization.cc
/// \brief Implementation of the YorkMedPhysActionInitialization class

#include "YorkMedPhysActionInitialization.hh"
#include "YorkMedPhysPrimaryGeneratorAction.hh"
#include "YorkMedPhysRunAction.hh"
#include "YorkMedPhysEventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysActionInitialization::YorkMedPhysActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysActionInitialization::~YorkMedPhysActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysActionInitialization::BuildForMaster() const
{
  SetUserAction(new YorkMedPhysRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysActionInitialization::Build() const
{
  SetUserAction(new YorkMedPhysPrimaryGeneratorAction);
  SetUserAction(new YorkMedPhysRunAction);
  SetUserAction(new YorkMedPhysEventAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
