void TestKin()
{
  gROOT->ProcessLine(".L TDDVCSGen.C+");
  TVector3 ekp;
  TDDVCSGen a;
  ekp.SetMagThetaPhi(3,30/180.*TMath::Pi(),0);
  
}
