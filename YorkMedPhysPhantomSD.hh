//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: YorkMedPhysPhantomSD.hh 100946 2016-11-03 11:28:08Z gcosmo $
//
/// \file YorkMedPhysPhantomSD.hh
/// \brief Definition of the YorkMedPhysPhantomSD class

#ifndef YorkMedPhysPhantomSD_h
#define YorkMedPhysPhantomSD_h 1

#include "G4VSensitiveDetector.hh"

#include "YorkMedPhysPhantomHit.hh"
#include "YorkMedPhysAnalysis.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"



#include <vector>

class G4Step;
class G4HCofThisEvent;


/// Phantom sensitive detector class
///
/// In Initialize(), it creates one hit for each calorimeter layer and one more
/// hit for accounting the total quantities in all layers.
///
/// The values are accounted in hits in ProcessHits() function which is called
/// by Geant4 kernel at each step.

class YorkMedPhysPhantomSD : public G4VSensitiveDetector
{
  public:
    YorkMedPhysPhantomSD(const G4String& name,
     const G4String& hitsCollectionName, G4int nofCells);
    virtual ~YorkMedPhysPhantomSD();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:
    YorkMedPhysPhantomHitsCollection* fHitsCollection;
    G4int  fNofCells;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

