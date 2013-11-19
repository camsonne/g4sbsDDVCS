#include "G4SBSGEMSD.hh"
#include "G4SBSGEMHit.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4Box.hh"

#include <iostream>

G4SBSGEMSD::G4SBSGEMSD( G4String name, G4String colname )
  : G4VSensitiveDetector(name)
{
    collectionName.insert(colname);
}

G4SBSGEMSD::~G4SBSGEMSD()
{
}

void G4SBSGEMSD::Initialize(G4HCofThisEvent*)
{
  hitCollection = new G4SBSGEMHitsCollection(SensitiveDetectorName,collectionName[0]); 
}

G4bool G4SBSGEMSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  double edep = aStep->GetTotalEnergyDeposit();
  const G4ParticleDefinition *particle = aStep->GetTrack()->GetParticleDefinition();
  // Charged geantinos always get tracked
  if( edep <= 0.0 && !(particle->GetParticleName()=="chargedgeantino") ) return false;

  // Only return primary electron hits
  int trid = aStep->GetTrack()->GetParentID();
  // if( trid != 0 ) return false;

//  G4ThreeVector mom = aStep->GetTrack()->GetMomentum();

  G4TouchableHistory* hist = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  hist->MoveUpHistory();
  
  //  This is where the box position will be
  
  G4AffineTransform bTrans = hist->GetHistory()->GetTransform(  hist->GetHistory()->GetDepth()-1 );
  double boxz = bTrans.TransformPoint(hist->GetTranslation()).getZ();

  G4int copyID = hist->GetReplicaNumber();

  //  Go to detector box
  hist->MoveUpHistory();

  double offset = ((G4Box *) hist->GetSolid())->GetZHalfLength();
  boxz += offset;

  G4SBSGEMHit* hit = new G4SBSGEMHit();

  G4AffineTransform aTrans = hist->GetHistory()->GetTopTransform();
  G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();

  pos = aTrans.TransformPoint(pos);


 // G4ThreeVector mom = aStep->GetPreStepPoint()->GetMomentum();
  G4ThreeVector mom = aStep->GetDeltaPosition();

  
  G4ThreeVector thisdelta = aStep->GetPreStepPoint()->GetPosition() + aStep->GetDeltaPosition();
  thisdelta = aTrans.TransformPoint(thisdelta);
  thisdelta -= pos;

//  printf("%f %f %f\n", aStep->GetDeltaPosition().x()/mom.x(), aStep->GetDeltaPosition().y()/mom.y(), aStep->GetDeltaPosition().z()/mom.z());
//  printf("%f %f %f\n", mom.x(), mom.y(), mom.z());
  mom *= aTrans.NetRotation();
  /*
  printf("mom:    %f %f %f\n", mom.unit().x(), mom.unit().y(), mom.unit().z());
  printf("thisdel %f %f %f\n", thisdelta.unit().x(), thisdelta.unit().y(), thisdelta.unit().z());
  */

  //std::cout << aTrans.NetRotation() << std::endl;

//  pos.setZ(  boxz );
  pos.setZ(  pos.getZ() + offset );

  /*
  printf("pos = %f %f %f\n", pos.getX()/m, pos.getY()/m, pos.getZ()/m);
  printf("mom = %f %f %f (%f)\n", mom.getX()/GeV, mom.getY()/GeV, mom.getZ()/GeV, mom.mag()/GeV);
  */


//  printf("Hit by %d at det %d,  (%f %f %f) %f?\n", trid, copyID, pos.getX()/cm, pos.getY()/cm, pos.getZ()/cm, boxz/cm );

  hit->SetPos(pos);
//  hit->SetDir(mom.getX()/mom.getZ(), mom.getY()/mom.getZ());
  hit->SetDir(thisdelta.getX()/thisdelta.getZ(), thisdelta.getY()/thisdelta.getZ());
  hit->SetGEMID(copyID);
  hit->SetE(edep);
  hit->SetID(particle->GetPDGEncoding());
  hitCollection->insert( hit );

  return true;
}

void G4SBSGEMSD::EndOfEvent(G4HCofThisEvent*HCE)
{
    G4int HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    HCE->AddHitsCollection( HCID, hitCollection );
}

void G4SBSGEMSD::clear()
{
} 

void G4SBSGEMSD::DrawAll()
{
} 

void G4SBSGEMSD::PrintAll()
{
} 
