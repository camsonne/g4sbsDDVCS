#include "TDDVCSGen.h"

TDDVCSGen::TDDVCSGen()
{
  fMTarg = 0.938;//GeV
  fGkp=new TGenPart(&fkp);
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
  fGkp->Generate(0,3);//scattered electron
  fq1 = fk - fkp;
  fGq2->Generate(0.5,fq1.E());//generate virtual photon
  fpf= (fp+fq1-fq2); // proton takes rest of impulsion
  fGL1->SetThMin(fq2.Theta()-10);
  fGL1->SetThMax(fq2.Theta()-10);
  fGL1->SetThMin(fq2.Theta()+10);
  fGL1->SetThMax(fq2.Theta()+10);
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
    fk.SetPxPyPzE(0,0,-E,E);
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
  cout<<"Q2:"<<fQ2<<" xbj:"<<"Q2:"<<fQ2<<" xbj:"<<endl;
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

void TGenPart::Generate(Double_t Emin,Double_t Emax)
{
   
   Double_t Th,Ph,En;
   Th = Uniform(fThMin/180*TMath::Pi(),fThMax/180*TMath::Pi());
   Ph = Uniform(fPhMin/180*TMath::Pi(),fPhMax/180*TMath::Pi());
   En = Uniform(Emin,Emax);
    TVector3 Vect;
   Vect.SetMagThetaPhi(En,Th,Ph);
   if (fLorVect)
     {
       fLorVect->SetVectMag(Vect,TMath::Sqrt(En*En+fMass*fMass));
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
