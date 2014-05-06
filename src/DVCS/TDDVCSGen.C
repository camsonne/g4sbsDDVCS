#include "TDDVCSGen.h"

TDDVCSGen::TDDVCSGen()
{
  fMTarg = 0.938;//GeV
}

TDDVCSGen::~TDDVCSGen()
{

}

 void  TDDVCSGen::GenerateDDVCS(){}
  void TDDVCSGen:: GenerateDDVCSFlat(){}
  TLorentzVector TDDVCSGen::SetBeam(){}
  TLorentzVector TDDVCSGen::SetScattered(){}
  void TDDVCSGen::GenerateEvent(){}
  void TDDVCSGen::Compute()
  {

    fQ2 = fq.Mag2();
    fxbj = fQ2 / (2*fMTarg*(fk.E()-fkp.E()));
    fEta = Delta()*Q()/(P()*Q());
    fXi = Q().Mag2()/(P()*Q());
  }
  void TDDVCSGen::GenerateScattered()
{

}
  void TDDVCSGen::GenerateQ2(){}



ClassImp(TDDVCSGen)





void TGenPart::Generate()
{
   
   Double_t Th,Ph,En;
   Th = fRGen.Uniform(fThMin/180*TMath::Pi(),fThMax/180*TMath::Pi());
   Ph = fRGen.Uniform(fPhMin/180*TMath::Pi(),fPhMax/180*TMath::Pi());
   En = fRGen.Uniform(fEMin,fEMax);
   fVect.SetMagThetaPhi(En,Th,Ph);
   SetVectMag(fVect,TMath::Sqrt(En*En+fMass*fMass));
}

void TGenPart::Print()
{
   
  TLorentzVector::Print();
  cout<<"(x,y,z,t)=("<<X()<<","<<Y()<<","<<Z()<<","<<T()<<") "<<"(P,eta,phi,E)=("<<P()<<","<<Theta()/TMath::Pi()*180.<<","<<Phi()/TMath::Pi()*180.<<","<<E()<<") "<<endl;
}

ClassImp(TGenPart)
