#include "TDDVCSGen.h"

#define deg 1./180.*TMath::Pi()
#define rad 180./TMath::Pi()

TDDVCSGen::TDDVCSGen()
{
  TGenPart * pGp;
  fMTarg = 0.938;//GeV
  fGkp=new TGenPart(&fkp);
  pGp= fGkp;
  pGp->SetThMin(-1);
  pGp->SetThMax(1);
  pGp->SetPhiMin(28);
  pGp->SetPhiMax(32);
  pGp->SetEMin(1);
  pGp->SetEMax(1.5);
  fGq2=new TGenPart(&fq2);
  fGL1=new TGenPart(&fL1);
  
  fk.SetPxPyPzE(0,0,-11,11);
  fpi.SetXYZM(0,0,0,0.938);
}

TDDVCSGen::~TDDVCSGen()
{
  delete  fGkp;
  delete  fGq2;
  delete  fGL1;
}

 void  TDDVCSGen::GenerateDDVCS()
{
  //fGkp->Generate(0,3);//scattered electron
  fq1 = fk - fkp;
  Double_t DTheta = 0.001;
  Double_t DPhi = 1;
  fGq2->SetThMin(fq1.Theta()/TMath::Pi()*180+DTheta);
  fGq2->SetThMax(fq1.Theta()/TMath::Pi()*180-DTheta);
  fGq2->SetPhiMin(fq1.Phi()/TMath::Pi()*180-DPhi);
  fGq2->SetPhiMax(fq1.Phi()/TMath::Pi()*180+DPhi);
  fGq2->Generate(8,fq1.E());//generate virtual photon
  fpf= (fpi+fq1-fq2); // proton takes rest of impulsion
  DTheta = 0.01;
  DPhi = 10;
  fGL1->SetThMin(fq2.Theta()/TMath::Pi()*180+DTheta);
  fGL1->SetThMax(fq2.Theta()/TMath::Pi()*180-DTheta);
  fGL1->SetPhiMin(fq2.Phi()/TMath::Pi()*180-DPhi);
  fGL1->SetPhiMax(fq2.Phi()/TMath::Pi()*180+DPhi);
  fGL1->Generate(1,fq2.E());
  fL2 = fq2 - fL1;
  Compute();
}
  void TDDVCSGen:: GenerateDDVCSFlat(){}
  TLorentzVector TDDVCSGen::SetBeam(TLorentzVector & v)
  {
    fk = v;
  }
  TLorentzVector TDDVCSGen::SetBeam(Double_t px,Double_t py,Double_t pz,Double_t E)
  {
    fk.SetPxPyPzE(px,py,px,E);
  }
  TLorentzVector TDDVCSGen::SetScattered(Double_t px,Double_t py,Double_t pz,Double_t E)
  {
    fkp.SetPxPyPzE(px,py,px,E);
  }

 TLorentzVector TDDVCSGen::SetBeam(Double_t E)
  {
    fk.SetPxPyPzE(0,E,0,E);
  }

  TLorentzVector TDDVCSGen::SetScattered(TLorentzVector & v)
  {
    fkp = v;
  }
  void TDDVCSGen::GenerateEvent(){}
  void TDDVCSGen::Compute()
  {

    fQ2 = -Q1().Mag2();
    fxbj = fQ2 / (2*fMTarg*(fk.E()-fkp.E()));
    fEta = Delta()*Q()/(P()*Q());
    fXi = Q().Mag2()/(P()*Q());
  }
  void TDDVCSGen::GenerateScattered()
{
  fGkp->Generate();
}
  void TDDVCSGen::GenerateQ2(){}

void TDDVCSGen::Print()
{
  cout<<"Q2:"<<fQ2<<" xbj:"<<fxbj<<endl;
  cout<<"fk :";fk.Print();
  cout<<"fkp :";fkp.Print();
  cout<<"fq1 :";fq1.Print();
  cout<<"fq2 :";fq2.Print();
  cout<<"fpi :";fpi.Print();
  cout<<"fpf :";fpf.Print();
  cout<<"fp :";fp.Print();
  cout<<"fq :";fq.Print();
  cout<<"fL1 :";fL1.Print();
  cout<<"fL2 :";fL2.Print();
  cout<<"fDelta :"; fDelta.Print();
  cout<<"fk :";fk.Vect().Print();
  cout<<"fkp :";fkp.Vect().Print();
  cout<<"fq1 :";fq1.Vect().Print();
  cout<<"fq2 :";fq2.Vect().Print();
  cout<<"fpi :";fpi.Vect().Print();
  cout<<"fpf :";fpf.Vect().Print();
  cout<<"fp :";fp.Vect().Print();
  cout<<"fq :";fq.Vect().Print();
  cout<<"fL1 :";fL1.Vect().Print();
  cout<<"fL2 :";fL2.Vect().Print();
  cout<<"fDelta :"; fDelta.Vect().Print();
}

ClassImp(TDDVCSGen)





void TGenPart::Generate()
{
   
   Double_t Th,Ph,En;
   Th = Uniform(fThMin/180*TMath::Pi(),fThMax/180*TMath::Pi());
   Ph = Uniform(fPhMin/180*TMath::Pi(),fPhMax/180*TMath::Pi());
   En = Uniform(fEMin,fEMax);
   TVector3 Vect;
   Vect.SetMagThetaPhi(En,Th,Ph);
   if (fLorVect)
     {
       fLorVect->SetVectMag(Vect,TMath::Sqrt(En*En+fMass*fMass));
     }
}

void TGenPart::GenerateDir(TVector3 dir )
{
   
   Double_t Th,Ph,En;
   Th = Uniform(-fThMin/180*TMath::Pi()+dir.Theta(),fThMax/180*TMath::Pi()+dir.Theta());
   Ph = Uniform(-fPhMin/180*TMath::Pi()+dir.Phi(),fPhMax/180*TMath::Pi()+dir.Phi());
   En = Uniform(fEMin,fEMax);
   TVector3 Vect;
   Vect.SetMagThetaPhi(En,Th,Ph);
   if (fLorVect)
     {
       fLorVect->SetVectMag(Vect,TMath::Sqrt(En*En+fMass*fMass));
     }
}


void TGenPart::Generate(Double_t Emin,Double_t Emax)
{
   
   Double_t Th,Ph,En;
   if (fThMin!=0 && fThMin!=0)      
       Th = Uniform(fThMin/180*TMath::Pi(),fThMax/180*TMath::Pi());
   if (fPhMin!=0 && fPhMin!=0)      
     Ph = Uniform(fPhMin/180*TMath::Pi(),fPhMax/180*TMath::Pi());
   En = Uniform(Emin,Emax);
    TVector3 Vect;
   Vect.SetMagThetaPhi(En,Th,Ph);
   if (fLorVect)
     {
       fLorVect->SetVectMag(Vect,fMass);
     }
}

void TGenPart::Print()
{
  
  if (fLorVect)
    {
      fLorVect->Print();
      cout<<"(x,y,z,t)=("<<fLorVect->X()<<","<<fLorVect->Y()<<","<<fLorVect->Z()<<","<<fLorVect->T()<<") "<<"(P,eta,phi,E)=("<<fLorVect->P()<<","<<fLorVect->Theta()/TMath::Pi()*180.<<","<<fLorVect->Phi()/TMath::Pi()*180.<<","<<fLorVect->E()<<") "<<endl;

    }
}
ClassImp(TGenPart)
