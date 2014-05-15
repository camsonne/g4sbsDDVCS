#include "TDDVCSGen.h"

#define deg 1./180.*TMath::Pi()
#define rad 180./TMath::Pi()

TDDVCSGen::TDDVCSGen()
{
  TGenPart * pGp;
  fMTarg = 0.938;//GeV
  fGkp=new TGenPart(&fkp);
  pGp= fGkp;
  pGp->SetThMin(90-60e-3/TMath::Pi()*180);
  pGp->SetThMax(90+60e-3/TMath::Pi()*180);
  pGp->SetPhiMin(90-30-30e-3/TMath::Pi()*180);
  pGp->SetPhiMax(90-30.+30e-3/TMath::Pi()*180);
  pGp->SetEMin(4.);
  pGp->SetEMax(4.2);
  pGp->SetMass(0.000511);
  fGq2=new TGenPart(&fq2);
  fGL1=new TGenPart(&fL1);
  
  fk.SetPxPyPzE(0,11,0,11);
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
  fGkp->Generate();//scattered electron
  fGkp->Generate(4,4.2);//scattered electron
  fq1 = fk - fkp;
  Double_t DTheta = 12.2;
  Double_t DPhi = 5;
  Double_t Mq=fGq2->Uniform(1,fq1.M()-1);
  fGq2->SetThMin(fq1.Theta()/TMath::Pi()*180-DTheta);
  fGq2->SetThMax(fq1.Theta()/TMath::Pi()*180+DTheta);
  fGq2->SetPhiMin(fq1.Phi()/TMath::Pi()*180-DPhi);
  fGq2->SetPhiMax(fq1.Phi()/TMath::Pi()*180+DPhi);
  fGq2->Generate(5,sqrt(fq1.E()*fq1.E()-Mq*Mq));//generate virtual photon
  fq2.SetE(sqrt(fq2.E()+Mq*Mq));
  fpf= (fpi+fq1-fq2); // proton takes rest of impulsion
  DTheta = 0.01;
  DPhi = 10;
  fGL1->SetThMin(fq2.Theta()/TMath::Pi()*180-DTheta);
  fGL1->SetThMax(fq2.Theta()/TMath::Pi()*180+DTheta);
  fGL1->SetPhiMin(fq2.Phi()/TMath::Pi()*180-DPhi);
  fGL1->SetPhiMax(fq2.Phi()/TMath::Pi()*180+DPhi);
  fGL1->Generate(1,sqrt(fq2.E()*fq2.E()-(2*0.110*2*0.110)));
  fL1.SetE(sqrt(fL1.E()*fL1.E()+0.110*0.110));
  fL2.SetVectMag(fq2.Vect()-fL1.Vect(),0.110);
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
       fLorVect->SetVectMag(Vect,fMass);
     }
}

void TGenPart::GenerateDir(TVector3 dir )
{
   
   Double_t Th,Ph,En;
   Th = Uniform(fThMin/180*TMath::Pi()+dir.Theta(),fThMax/180*TMath::Pi()+dir.Theta());
   Ph = Uniform(fPhMin/180*TMath::Pi()+dir.Phi(),fPhMax/180*TMath::Pi()+dir.Phi());
   En = Uniform(fEMin,fEMax);
   TVector3 Vect;
   Vect.SetMagThetaPhi(En,Th,Ph);
   if (fLorVect)
     {
       fLorVect->SetVectMag(Vect,fMass);
     }
}


void TGenPart::Generate(Double_t Emin,Double_t Emax)
{
   
   Double_t Th,Ph,En;
   if (fThMin>fThMax) {Th = fThMin ; fThMin=fThMax; fThMax=Th;}   
    if (fPhMin>fPhMax) {Ph = fPhMin ; fPhMin=fPhMax; fPhMax=Th;}   
       Th = Uniform(fThMin,fThMax);
       //if (fPhMin!=0 && fPhMin!=0)      
     Ph = Uniform(fPhMin,fPhMax);
   En = Uniform(Emin,Emax);
    TVector3 Vect;
   
    //   cout<<Th<<" "<<Ph<<" "<< En <<endl;

   Vect.SetMagThetaPhi(En,Th/180*TMath::Pi(),Ph/180*TMath::Pi());
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
