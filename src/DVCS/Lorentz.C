
void Lorentz()
{
  // gamma + p -> gamma ' + p '
  TLorentzVector proton(0,0,0,0.938);
  TLorentzVector photon(1,0,0,2);
  proton.Print();
  photon.Print();
  TLorentzVector CM=proton+photon;
  CM.Print();
  CM.Vect().Print();
  v= CM.Vect();
  TLorentzVector protonCM;
  TLorentzVector photonCM;
  protonCM=proton;
  protonCM.Boost(-v);
  photonCM=photon;
  photonCM.Boost(-v);
  protonCM.Print();
  photonCM.Print();
}
