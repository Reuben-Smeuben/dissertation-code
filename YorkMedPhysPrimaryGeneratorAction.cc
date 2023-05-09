#include "YorkMedPhysPrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ios.hh" //added
#include <fstream> //added

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysPrimaryGeneratorAction::YorkMedPhysPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(nullptr)
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  outfile.open("profile.txt");

  // default particle kinematic
  //
  G4ParticleDefinition* particleDefinition
    = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1,0.,0));
  fParticleGun->SetParticleEnergy(1.0*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysPrimaryGeneratorAction::~YorkMedPhysPrimaryGeneratorAction()
{
  //outfile.close();
  delete fParticleGun;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void YorkMedPhysPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) //moved away then moved back
{
  // This function is called at the begining of an event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore
  //
  G4double worldZHalfLength = 0.;
  G4LogicalVolume* worldLogVol =
   G4LogicalVolumeStore::GetInstance()->GetVolume("World");

  // Check that the world volume has box shape
  G4Box* worldBox = nullptr;

  if (worldLogVol) worldBox = dynamic_cast<G4Box*>(worldLogVol->GetSolid());

  if (worldBox) worldZHalfLength = worldBox->GetZHalfLength();

  else
  {
    G4ExceptionDescription msg;
    msg << "World volume of box shape not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be placed in the center.";
    G4Exception("YorkMedPhysPrimaryGeneratorAction::GeneratePrimaries()",
      "MyCode0002", JustWarning, msg);
  }

  std::ofstream outfile; //added
  //G4RunManager* runManager = new G4RunManager(); //added

//We need to do changes here
//Step 1 Generate random number
double alpha=0.04;
double rndm=-1;
double myy=-10;
double myx=0;
while (myy<rndm){
  myx=G4UniformRand()*90.0+10.0;
  myy=exp(-alpha*myx);
  rndm=G4UniformRand()*exp(-alpha*10.0);
  //G4cout<<" My random is "<<x<<" My y value is "<<myy<<G4endl;
}
if (!outfile.is_open())
outfile.open("profile.txt",std::ios_base::app);

  //G4cout << myy << " " << myx << " " << rndm << " " << alpha << G4endl;
  outfile << myx << " " << myy << " " << rndm << " " << alpha << G4endl;
//end of added

//G4cout<<" My random is "<<x<<" My y value is "<<myy<<G4endl;
  // Set gun position
  //fParticleGun = new G4ParticleGun(nofParticles); //added

  fParticleGun->SetParticlePosition(G4ThreeVector(-30.0*cm,0.0,0.0));
  fParticleGun->SetParticleEnergy(myx*MeV); //myx
  fParticleGun->GeneratePrimaryVertex(anEvent);

  //need to output these variables in order to build a histogram in analysis.C
  //std::ofstream outfile;
  //int main() {

//  }
}
