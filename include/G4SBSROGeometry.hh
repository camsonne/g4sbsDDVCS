#ifndef G4SBSCalHit_h
#define G4SBSCalHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4SBSROGeometry : public  G4VReadoutGeometry 
{
  public:
  G4SBSROGeometry();
  ~G4SBSROGeometry();
  G4VPhysicalVolume* build()
  {
    
    
  }

}
