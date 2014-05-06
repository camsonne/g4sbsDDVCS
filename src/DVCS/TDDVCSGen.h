#include <TLorentzVector.h>
#include <TRandom3.h>
#include <iostream>
#ifndef _TDDVCSGEN_
#define _TDDVCSGEN_

using namespace std;

class T3DArrow : public TPolyLine3D
{
 public:

 protected:

}

class TGenPart:public TLorentzVector
{
  public:
  TGenPart& operator= (const TGenPart &b)
    {
      TLorentzVector * here = this;
      const TLorentzVector * there = & b;
      *here = * there;
      fMass=b.fMass;
      fThMin=b.fThMin;
      fThMax=b.fThMax;
      fPhMin=b.fPhMin;
      fPhMax=b.fPhMax;
      fEMin=b.fEMin;
      fEMax=b.fEMax;
    }
  TGenPart operator+ (TGenPart b){ 
    TLorentzVector * here = this;
    TLorentzVector * there = & b;
    *here += * there;
    fMass+=b.fMass;
    fThMin+=b.fThMin;
    fThMax+=b.fThMax;
    fPhMin+=b.fPhMin;
    fPhMax+=b.fPhMax;
    fEMin+=b.fEMin;
    fEMax+=b.fEMax; 
  }
  
 TGenPart operator* (Double_t b)
{ 
  TLorentzVector * here = this;
  (*here)*=b;
  fMass*=b;
  fThMin*=b;
  fThMax*=b;
  fPhMin*=b;
  fPhMax*=b;
  fEMin*=b;
  fEMax*=b;
}


  TGenPart operator- ()
 {
   *this = (*this)*-1.;
 }
  TGenPart operator- (TGenPart b)
  { 
    *this = (*this)+ b*-1.;
  }
  TGenPart operator* (TGenPart b){ this->TLorentzVector::operator*(b);}
 
  TGenPart operator/ (Double_t b){ this->TLorentzVector::operator*(1/b);}
  
  // friend TGenPart Double_t operator* (Double_t v ,TGenPart b){ return TLorentzVector::operator*(b*v);}

 TGenPart():fRGen(0),TLorentzVector()
  {
   
   fMass=0;
   fThMin=0;
   fThMax=10;
   fPhMin=0;
   fPhMax=10;
   fEMin=1;
   fEMax=2;
  }

 TGenPart(const TGenPart & b): TLorentzVector ()
  {
    TLorentzVector * here = this;
    const TLorentzVector * there = & b;
    *here = * there;
   fMass=b.fMass;
   fThMin=b.fThMin;
   fThMax=b.fThMax;
   fPhMin=b.fPhMin;
   fPhMax=b.fPhMax;
   fEMin=b.fEMin;
   fEMax=b.fEMax;
  }

  ~TGenPart()
    {
    }
  void SetMass(Double_t v)
  { 

  }
  void Print();
    void Generate();
  Double_t SetLimits(Double_t thetamin,Double_t thetamax,Double_t phimin,Double_t phimax,Double_t pmin,Double_t pmax)
  {
   
  }
  Double_t SetThMin(Double_t v) 
  {
    fThMin=v;
  }
  Double_t SetThMax(Double_t v) {
    fThMax=v;
  }
  Double_t SetPhiMin(Double_t v) {
    fPhMin=v;
  }
  Double_t SetPhiMax(Double_t v) {
    fPhMax=v;
  }
  Double_t SetEMin(Double_t v) {
    fEMin=v;
  }
  Double_t SetEMax(Double_t v) {
    fEMax=v;
  }
  // protected:
  TRandom3 fRGen; 
  Double_t fMass;
  Double_t fThMin,fThMax,fPhMin,fPhMax,fEMin,fEMax;
   TVector3 fVect;
   TLorentzVector & LVect() {return (TLorentzVector &) *this;};
   ClassDef(TGenPart,1)
};

class TDDVCSGen : public TObject
{

 public:
  TDDVCSGen();
  ~TDDVCSGen();
  void  GenerateDDVCS();
  void GenerateDDVCSFlat();
  TLorentzVector SetFourVect ( Double_t E, Double_t kx, Double_t  ky, Double_t kz ){TLorentzVector v(kx,ky,kz,E);return v;};
  TLorentzVector SetBeam();
  TLorentzVector SetScattered();
  void GenerateEvent();
  void GenerateScattered();
  void GenerateQ2();
  TLorentzVector Q(){fq = fk-fkp; return fq;};
  TLorentzVector Delta(){fDelta =(fq2 + fq1)*0.5; return fDelta;}
  TLorentzVector P(){fp = (fpi+fpf)*0.5; return fp;};
   Double_t Xi(){return fXi;};
   Double_t Eta(){return fEta;};
  Double_t Q2() {return fQ2;}
  Double_t xbj(){return fxbj; };
  void Compute();
  //protected:
  TGenPart fk,fkp,fpi,fpf,fp,fq1,fq2,fq,fL1,fL2,fDelta;
  Double_t fDThetaE,fDPhiE,fDPE;
  Double_t fDThetaQ2,fDPhiQ2;
  Double_t fQ2,fxbj,fEta,fXi;
  Double_t fMTarg;
  ClassDef (TDDVCSGen,1);
}
;
#endif
