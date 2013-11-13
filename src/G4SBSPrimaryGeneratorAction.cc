#include "G4SBSPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SBSEventGen.hh"
#include "G4SBSIO.hh"
#include "sbstypes.hh"
#include "globals.hh"
#include <iostream>

G4SBSPrimaryGeneratorAction::G4SBSPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle;

  particle = particleTable->FindParticle(particleName="e-");

  particleGun->SetParticleDefinition(particle);

  particleGun->SetParticleMomentumDirection(G4ThreeVector(sin(-40.0*deg),0.0,cos(-40.0*deg)));
  particleGun->SetParticleEnergy(1.0*GeV);
  particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));

  sbsgen = new G4SBSEventGen();
  sbsgen->SetPairE(1*GeV);
  fPairPart="mu";
  fUseGeantino = false;
}

G4SBSPrimaryGeneratorAction::~G4SBSPrimaryGeneratorAction()
{
  delete particleGun;
}

void G4SBSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle;

  ev_t evdata;

  G4LorentzVector mu1,mu2;
  G4ThreeVector pos(0,0,0);
  

  // Several different types of scattering
  // Let's start with e'N elastic

  //  Roll up random values
  sbsgen->GenerateEvent();

  evdata = sbsgen->GetEventData();
  fIO->SetEventData(evdata);



   Double_t rT =  CLHEP::RandFlat::shoot(0.,0.);
   Double_t rP =  CLHEP::RandFlat::shoot(0.,0.);
   //  mu1.setRThetaPhi(1*m,(fPairCAngle+fPairDAngle)*deg,fPairDPhi*deg);
   // mu2.setRThetaPhi(1*m,(fPairCAngle-fPairDAngle)*deg,(-fPairDPhi)*deg);
   // mu1.setE(sbsgen->GetBeamE());
   // mu2.setE(sbsgen->GetBeamE())
    mu1=sbsgen->GetQM();
   mu2=sbsgen->GetQP();
   printf("Pair angles theta : %f phi : %f \n",sbsgen->GetPairCAngle(),sbsgen->GetPairPhiAngle());
   // mu1.setRThetaPhi(1*m,sbsgen->GetPairCAngle(),sbsgen->GetPairPhiAngle());
   //mu2.setRThetaPhi(1*m,sbsgen->GetPairCAngle(),-sbsgen->GetPairPhiAngle());
   Double_t rE =  CLHEP::RandFlat::shoot(1.,5.);
   // mu1.setE(sbsgen->GetPairE());
   //mu2.setE(sbsgen->GetPairE());
   printf ("part %s\n",(fPairPart+"-").data());
   particle = particleTable->FindParticle(particleName=(fPairPart+"-").data());
   particleGun->SetParticleDefinition(particle);
   particleGun->SetParticleMomentumDirection(mu1.vect().unit());
   particleGun->SetParticleEnergy(mu1.e());
   particleGun->SetParticlePosition(pos);
   particleGun->GeneratePrimaryVertex(anEvent);
  
   particle = particleTable->FindParticle(particleName=(fPairPart+"+").data());
   particleGun->SetParticleDefinition(particle);
   particleGun->SetParticleMomentumDirection(mu2.vect().unit());
   particleGun->SetParticleEnergy(mu2.e());
   particleGun->SetParticlePosition(pos);
   particleGun->GeneratePrimaryVertex(anEvent);


  if( !fUseGeantino ){
      particle = particleTable->FindParticle(particleName="e-");
  } else {
      particle = particleTable->FindParticle(particleName="chargedgeantino");
  }

  particleGun->SetParticleDefinition(particle);

  particleGun->SetParticleMomentumDirection(sbsgen->GetElectronP().unit() );
  particleGun->SetParticleEnergy(sbsgen->GetElectronE());
  particleGun->SetParticlePosition(sbsgen->GetV());
	  
  /*
  particleGun->SetParticleMomentumDirection(G4ThreeVector(sin(-40.0*deg),0.0,cos(-40.0*deg)));
  particleGun->SetParticleEnergy(1.0*GeV);
  particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));
  */

  // Not necessarily kinematically allowed
  particleGun->GeneratePrimaryVertex(anEvent);

  switch( sbsgen->GetFinalNucleon() ){
      case kProton:
	  particle = particleTable->FindParticle(particleName="proton");
	  break;
      case kNeutron:
	  particle = particleTable->FindParticle(particleName="neutron");
	  break;
      default:
	  particle = particleTable->FindParticle(particleName="geantino");
	  break;
  } 
  particleGun->SetParticleDefinition(particle);

  // Ensure we're doing something sensible for Geant4
  if( sbsgen->GetNucleonE()-particle->GetPDGMass() > 0.0 ) {
      particleGun->SetParticleMomentumDirection(sbsgen->GetNucleonP().unit() );
      // This is KINETIC energy
      particleGun->SetParticleEnergy(sbsgen->GetNucleonE()-particle->GetPDGMass());
      particleGun->SetParticlePosition(sbsgen->GetV());
  }

  /*
  particleGun->SetParticleMomentumDirection(G4ThreeVector(sin(39.4*deg),0.0,cos(39.4*deg)));
  particleGun->SetParticleEnergy(1.0*GeV);
  particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));
  */

   // if( sbsgen->GetKine() != kPair ){
   // particle = particleTable->FindParticle(particleName="mu-");
   // particleGun->SetParticleDefinition(particle);
   // particleGun->SetParticleMomentumDirection(sbsgen->GetQM().vect().unit());
   // particleGun->SetParticleEnergy(sbsgen->GetQM().e());
   // particleGun->SetParticlePosition(sbsgen->GetV());
   // particle = particleTable->FindParticle(particleName="mu+");
   // particleGun->SetParticleDefinition(particle);
   // particleGun->SetParticleMomentumDirection(sbsgen->GetQP().vect().unit());
   // particleGun->SetParticleEnergy(sbsgen->GetQP().e());
   // particleGun->SetParticlePosition(sbsgen->GetV());
   // particleGun->GeneratePrimaryVertex(anEvent);
   //  }

  // Only do final nucleon for generators other than
  // the generic beam generator
  if( sbsgen->GetKine() != kBeam ){
      particleGun->GeneratePrimaryVertex(anEvent);
  }

}

G4ParticleGun* G4SBSPrimaryGeneratorAction::GetParticleGun()
{
  return particleGun;
} 

