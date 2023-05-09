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
// $Id: YorkMedPhysDetectorConstruction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file YorkMedPhysDetectorConstruction.hh
/// \brief Definition of the YorkMedPhysDetectorConstruction class

#ifndef YorkMedPhysDetectorConstruction_h
#define YorkMedPhysDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.
/// The phantom is a box made of a liquid water.
///
/// Four parameters define the geometry of the phantom:
///
/// - the size along X and Y axis,
/// - the thickness - size along Z axes,
/// - the material,
///
/// In ConstructSDandField() sensitive detectors of YorkMedPhysPhantomSD type
/// are created and associated with the Phantom volumes.
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class YorkMedPhysDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    YorkMedPhysDetectorConstruction();
    virtual ~YorkMedPhysDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
     
  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger

    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
    G4int   fNofLayers;     // number of layers
    G4UserLimits* fStepLimit;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

