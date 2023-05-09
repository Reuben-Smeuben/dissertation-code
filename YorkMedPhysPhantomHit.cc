/// \file YorkMedPhysPhantomHit.cc
/// \brief Implementation of the YorkMedPhysPhantomHit class

#include "YorkMedPhysPhantomHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<YorkMedPhysPhantomHit>* YorkMedPhysPhantomHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysPhantomHit::YorkMedPhysPhantomHit()
 : G4VHit(),
   fEdep(0.),
   fTrackLength(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysPhantomHit::~YorkMedPhysPhantomHit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YorkMedPhysPhantomHit::YorkMedPhysPhantomHit(const YorkMedPhysPhantomHit& right)
  : G4VHit()
{
  fEdep = right.fEdep;
  fTrackLength = right.fTrackLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const YorkMedPhysPhantomHit&
 YorkMedPhysPhantomHit::operator=(const YorkMedPhysPhantomHit& right)
{
  fEdep = right.fEdep;
  fTrackLength = right.fTrackLength;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int YorkMedPhysPhantomHit::operator==(const YorkMedPhysPhantomHit& right) const
{
  return (this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YorkMedPhysPhantomHit::Print()
{
//  G4cout
//     << "Edep: "
//     << std::setw(7) << G4BestUnit(fEdep, "Energy")
//     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
