#include "G4SBSMessenger.hh"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"

#include "G4SBSDetectorConstruction.hh"
#include "G4SBSIO.hh"
#include "G4SBSEventGen.hh"
#include "G4SBSEventAction.hh"
#include "G4SBSBigBiteField.hh"
#include "G4SBSPrimaryGeneratorAction.hh"

#include "G4UImanager.hh"
#include "G4RunManager.hh"

#include "G4GDMLParser.hh"
#include "G4VPhysicalVolume.hh"

G4SBSMessenger::G4SBSMessenger(){
    fExpType = kNeutronExp;

    runCmd = new G4UIcmdWithAnInteger("/g4sbs/run",this);
    runCmd->SetGuidance("Run simulation with x events");
    runCmd->SetParameterName("nevt", false);

    gemconfigCmd = new G4UIcmdWithAnInteger("/g4sbs/gemconfig",this);
    gemconfigCmd->SetGuidance("Change between GEM configurations");
    gemconfigCmd->SetParameterName("gemconfig", false);

    fileCmd = new G4UIcmdWithAString("/g4sbs/filename",this);
    fileCmd->SetGuidance("Output filename");
    fileCmd->SetParameterName("filename", false);

    sigfileCmd = new G4UIcmdWithAString("/g4sbs/sigmafile",this);
    sigfileCmd->SetGuidance("GEM Sigma filename");
    sigfileCmd->SetParameterName("sigmafile", false);

    tgtCmd = new G4UIcmdWithAString("/g4sbs/target",this);
    tgtCmd->SetGuidance("Target type from LH2, LD2, H2, 3He");
    tgtCmd->SetParameterName("targtype", false);

    kineCmd = new G4UIcmdWithAString("/g4sbs/kine",this);
    kineCmd->SetGuidance("Kinematic type");
    kineCmd->SetParameterName("kinetype", false);

    expCmd = new G4UIcmdWithAString("/g4sbs/exp",this);
    expCmd->SetGuidance("Experiment type");
    expCmd->SetParameterName("exptype", false);

    geantinoCmd = new G4UIcmdWithABool("/g4sbs/shootgeantino", this);
    geantinoCmd->SetGuidance("Shoot a geantino instead of e-");
    geantinoCmd->SetParameterName("shootgeantino", false);

    tgtLenCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/targlen",this);
    tgtLenCmd->SetGuidance("Target length");
    tgtLenCmd->SetParameterName("targlen", false);

    tgtDenCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/targden",this);
    tgtDenCmd->SetGuidance("Target density");
    tgtDenCmd->SetParameterName("targden", false);

    tgtPresCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/targpres",this);
    tgtPresCmd->SetGuidance("Gaseous Target pressure");
    tgtPresCmd->SetParameterName("targpres", false);

    beamcurCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/beamcur",this);
    beamcurCmd->SetGuidance("Beam current");
    beamcurCmd->SetParameterName("beamcur", false);

    runtimeCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/runtime",this);
    runtimeCmd->SetGuidance("Run time");
    runtimeCmd->SetParameterName("runtime", false);

    rasterxCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/rasterx",this);
    rasterxCmd->SetGuidance("Raster x size");
    rasterxCmd->SetParameterName("size", false);

    rasteryCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/rastery",this);
    rasteryCmd->SetGuidance("Raster y size");
    rasteryCmd->SetParameterName("size", false);

    beamECmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/beamE",this);
    beamECmd->SetGuidance("Beam Energy");
    beamECmd->SetParameterName("energy", false);

    bbangCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/bbang",this);
    bbangCmd->SetGuidance("BigBite angle");
    bbangCmd->SetParameterName("angle", false);

    bbdistCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/bbdist",this);
    bbdistCmd->SetGuidance("BigBite distance");
    bbdistCmd->SetParameterName("dist", false);

    hcalangCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/hcalang",this);
    hcalangCmd->SetGuidance("HCAL angle");
    hcalangCmd->SetParameterName("angle", false);

    hcaldistCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/hcaldist",this);
    hcaldistCmd->SetGuidance("HCAL distance");
    hcaldistCmd->SetParameterName("dist", false);

    hmagdistCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/48D48dist",this);
    hmagdistCmd->SetGuidance("48D48 distance");
    hmagdistCmd->SetParameterName("dist", false);

    hmagangCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/48D48ang",this);
    hmagangCmd->SetGuidance("48D48 angle");
    hmagangCmd->SetParameterName("angle", false);

    gemresCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/gemres",this);
    gemresCmd->SetGuidance("GEM resolution");
    gemresCmd->SetParameterName("dist", false);

    // Detector position commands

    cerDisCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/cerdist",this);
    cerDisCmd->SetGuidance("Cerenkov distance from front GEM");
    cerDisCmd->SetParameterName("dist", false);

    cerDepCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/cerdepth",this);
    cerDepCmd->SetGuidance("Cerenkov gas depth");
    cerDepCmd->SetParameterName("dist", false);

    gemSepCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/gemsep",this);
    gemSepCmd->SetGuidance("GEM separation from front to back set");
    gemSepCmd->SetParameterName("dist", false);

    bbCalDistCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/bbcaldist",this);
    bbCalDistCmd->SetGuidance("BigBite caloriter distance from front GEM");
    bbCalDistCmd->SetParameterName("dist", false);

    thminCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/thmin",this);
    thminCmd->SetGuidance("Minimum electron generation polar angle");
    thminCmd->SetParameterName("angle", false);

    thmaxCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/thmax",this);
    thmaxCmd->SetGuidance("Maximum electron generation polar angle");
    thmaxCmd->SetParameterName("angle", false);

    phminCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/phmin",this);
    phminCmd->SetGuidance("Minimum electron generation azimuthal angle");
    phminCmd->SetParameterName("angle", false);

    phmaxCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/phmax",this);
    phmaxCmd->SetGuidance("Maximum electron generation azimuthal angle");
    phmaxCmd->SetParameterName("angle", false);
 
    pairECmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/pairE",this);
    pairECmd->SetGuidance("Pair Energy");
    pairECmd->SetParameterName("energy", false);

    pairPartCmd = new G4UIcmdWithAString("/g4sbs/pairPart",this);
    pairPartCmd->SetGuidance("Pair Particle");
    pairPartCmd->SetParameterName("particle", false);

    pairCAngleCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/pairCAngle",this);
    pairCAngleCmd->SetGuidance("Pair Central angle");
    pairCAngleCmd->SetParameterName("angle in degree", false);
    
    pairPhiAngleCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/pairPhiAngle",this);
    pairPhiAngleCmd->SetGuidance("Pair Phi angle");
    pairPhiAngleCmd->SetParameterName("angle in degree", false);

     pairRotAngleCmd = new G4UIcmdWithADoubleAndUnit("/g4sbs/pairRotAngle",this);
    pairRotAngleCmd->SetGuidance("Pair Rot angle");
    pairRotAngleCmd->SetParameterName("angle in degree", false);

}

G4SBSMessenger::~G4SBSMessenger(){
}


void G4SBSMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue){
    char cmdstr[255];

    if( cmd == runCmd ){
	// Save geometry to GDML file
	G4GDMLParser parser;
	G4VPhysicalVolume* pWorld;

	G4int nevt = runCmd->GetNewIntValue(newValue);
	fevgen->SetNevents(nevt);
	
	if( fExpType == kGEp ){
	    G4RunManager::GetRunManager()->DefineWorldVolume(pWorld = fdetcon->ConstructAllGEp());
	} else {
	    G4RunManager::GetRunManager()->DefineWorldVolume(pWorld = fdetcon->ConstructAll());
	}

	// Clobber old gdml if it exists and write out the
	// present geometry
	unlink("g4sbs.gdml");
	parser.Write("g4sbs.gdml", pWorld);

	// Run the simulation
	G4UImanager * UImanager = G4UImanager::GetUIpointer();
	sprintf(cmdstr, "/run/beamOn %d", nevt);
	UImanager->ApplyCommand(cmdstr);
    }

    if( cmd == fileCmd ){
	fIO->SetFilename(newValue.data());
    }

    if( cmd == sigfileCmd ){
	fevact->LoadSigmas(newValue.data());
    }

    if( cmd == gemconfigCmd ){
	int gemconfval = gemconfigCmd->GetNewIntValue(newValue);
	fdetcon->SetGEMConfig(gemconfval);
    }

    if( cmd == kineCmd ){
	bool validcmd = false;
	if( newValue.compareTo("elastic") == 0 ){
	    fevgen->SetKine(kElastic);
	    validcmd = true;
	}
	if( newValue.compareTo("inelastic") == 0 ){
	    fevgen->SetKine(kInelastic);
	    validcmd = true;
	}
	if( newValue.compareTo("flat") == 0 ){
	    fevgen->SetKine(kFlat);
	    validcmd = true;
	}
	if( newValue.compareTo("dis") == 0 ){
	    fevgen->SetKine(kDIS);
	    validcmd = true;
	}
	if( newValue.compareTo("pair") == 0 ){
	    fevgen->SetKine(kPair);
	    validcmd = true;
	}

	if( newValue.compareTo("beam") == 0 ){
	    fevgen->SetKine(kBeam);
	    validcmd = true;
	}
	if( !validcmd ){
	    fprintf(stderr, "%s: %s line %d - Error: kinematic type %s not valid\n", __PRETTY_FUNCTION__, __FILE__, __LINE__, newValue.data());
	    exit(1);
	}
    }

    if( cmd == expCmd ){
	bool validcmd = false;
	if( newValue.compareTo("gep") == 0 ){
	    fExpType = kGEp;
	    validcmd = true;
	}
	if( newValue.compareTo("gmn") == 0 ){
	    fExpType = kNeutronExp;
	    validcmd = true;
	}
	if( newValue.compareTo("gen") == 0 ){
	    fExpType = kNeutronExp;
	    validcmd = true;
	}
	if( newValue.compareTo("a1n") == 0 ){
	    fExpType = kNeutronExp;
	    validcmd = true;
	}
	if( !validcmd ){
	    fprintf(stderr, "%s: %s line %d - Error: kinematic type %s not valid\n", __PRETTY_FUNCTION__, __FILE__, __LINE__, newValue.data());
	    exit(1);
	}
    }



    if( cmd == tgtCmd ){
	bool validcmd = false;
	if( newValue.compareTo("LH2") == 0 ){
	    fevgen->SetTarget(kLH2);
	    fdetcon->SetTarget(kLH2);

	    G4double den = (0.071*g/cm3)*Avogadro/(1.008*g/mole);
	    fevgen->SetTargDen(den);
	    fdetcon->SetTargDen(den);
	    validcmd = true;
	}
	if( newValue.compareTo("H2") == 0 ){
	    fevgen->SetTarget(kH2);
	    fdetcon->SetTarget(kH2);

	    G4double den = 10.0*atmosphere/(296.0*kelvin*k_Boltzmann);
	    fevgen->SetTargDen(den);
	    fdetcon->SetTargDen(den);
	    validcmd = true;
	}
	if( newValue.compareTo("LD2") == 0 ){
	    fevgen->SetTarget(kLD2);
	    fdetcon->SetTarget(kLD2);

	    G4double den = (162.4*kg/m3)*Avogadro/(2.014*g/mole);
	    fevgen->SetTargDen(den);
	    fdetcon->SetTargDen(den);
	    validcmd = true;
	}
	if( newValue.compareTo("3He") == 0 ){
	    fevgen->SetTarget(k3He);
	    fdetcon->SetTarget(k3He);

	    G4double den = 10.0*atmosphere/(296.0*kelvin*k_Boltzmann);
	    fevgen->SetTargDen(den);
	    fdetcon->SetTargDen(den);
	    validcmd = true;

	}
	if( newValue.compareTo("Neutron") == 0 ){
	    fevgen->SetTarget(kNeutTarg);
	    fdetcon->SetTarget(kNeutTarg);

	    G4double den = 10.0*atmosphere/(296.0*kelvin*k_Boltzmann);
	    fevgen->SetTargDen(den);
	    fdetcon->SetTargDen(den);
	    validcmd = true;
	}

	if( !validcmd ){
	    fprintf(stderr, "%s: %s line %d - Error: target type %s not valid\n", __PRETTY_FUNCTION__, __FILE__, __LINE__, newValue.data());
	    exit(1);
	}

    }

    if( cmd == geantinoCmd ){
	G4bool b = geantinoCmd->GetNewBoolValue(newValue);
	fprigen->SetUseGeantino(b);
	fdetcon->GetBBField()->SetUseGeantino(b);
    }

    if( cmd == tgtLenCmd ){
	G4double len = tgtLenCmd->GetNewDoubleValue(newValue);
	fevgen->SetTargLen(len);
	fdetcon->SetTargLen(len);
    }

    if( cmd == tgtDenCmd ){
	G4double den = tgtDenCmd->GetNewDoubleValue(newValue);
	fevgen->SetTargDen(den);
	fdetcon->SetTargDen(den);
    }
    if( cmd == tgtPresCmd ){
	G4double pre = tgtPresCmd->GetNewDoubleValue(newValue);
	G4double den = pre/(296.0*kelvin*k_Boltzmann);
	fevgen->SetTargDen(den);
	fdetcon->SetTargDen(den);
    }

    if( cmd == beamcurCmd ){
	G4double v = beamcurCmd->GetNewDoubleValue(newValue);
	printf("Setting beam current to %f uA\n", v/microampere);
	fevgen->SetBeamCur(v);
    }
    if( cmd == runtimeCmd ){
	G4double v = runtimeCmd->GetNewDoubleValue(newValue);
	fevgen->SetRunTime(v);
    }

    if( cmd == rasterxCmd ){
	G4double v = rasterxCmd->GetNewDoubleValue(newValue);
	fevgen->SetRasterX(v);
    }

    if( cmd == rasteryCmd ){
	G4double v = rasteryCmd->GetNewDoubleValue(newValue);
	fevgen->SetRasterY(v);
    }

    if( cmd == beamECmd ){
	G4double v = beamECmd->GetNewDoubleValue(newValue);
	fevgen->SetBeamE(v);
	fIO->SetBeamE(v);
    }

    if( cmd == pairECmd ){
      G4double v = pairECmd->GetNewDoubleValue(newValue);
      fevgen->SetPairE(v);
      //fIO->SetBeamE(v);
    }

      if( cmd == pairCAngleCmd ){
      G4double v = pairECmd->GetNewDoubleValue(newValue);
      fevgen->SetPairCAngle(v);
      printf ("Pair central angle : %f\n",  fevgen->GetPairCAngle());
      //fIO->SetBeamE(v);
    }

          if( cmd == pairPhiAngleCmd ){
      G4double v = pairECmd->GetNewDoubleValue(newValue);
      fevgen->SetPairPhiAngle(v);
      printf ("Pair phi angle : %f\n",  fevgen->GetPairPhiAngle());
      //fIO->SetBeamE(v);
    }

	    if( cmd == pairRotAngleCmd ){
      G4double v = pairRotAngleCmd->GetNewDoubleValue(newValue);
      fevgen->SetPairRotAngle(v);
      printf ("Pair Rot angle : %f\n",  fevgen->GetPairRotAngle());
      //fIO->SetBeamE(v);
    }

     if( cmd == pairPartCmd ){
      fprigen->SetPairPart(newValue.data());
      //fIO->SetBeamE(v);
    }



    if( cmd == bbangCmd ){
	G4double v = bbangCmd->GetNewDoubleValue(newValue);
	printf("Setting BB ang to %f deg\n", v/deg);
	fdetcon->SetBBAng(v);
	fIO->SetBigBiteTheta(v);
    }

    if( cmd == bbdistCmd ){
	G4double v = bbdistCmd->GetNewDoubleValue(newValue);
	fdetcon->SetBBDist(v);
	fIO->SetBigBiteDist(v);
    }

    if( cmd == hcalangCmd ){
	G4double v = hcalangCmd->GetNewDoubleValue(newValue);
	fdetcon->SetHCALAng(v);
	fIO->SetHcalTheta(v);
    }

    if( cmd == hcaldistCmd ){
	G4double v = hcaldistCmd->GetNewDoubleValue(newValue);
	fdetcon->SetHCALDist(v);
	fevgen->SetHCALDist(v);
	fIO->SetHcalDist(v);
    }

    if( cmd == hcalangCmd ){
      G4double v = hcalangCmd->GetNewDoubleValue(newValue);
      fdetcon->SetHCALAng(v);
      fIO->SetHcalTheta(v);
    }
    
    if( cmd == hmagdistCmd ){
	G4double v = hmagdistCmd->GetNewDoubleValue(newValue);
	fdetcon->Set48D48Dist(v);
    }

    if( cmd == hmagangCmd ){
      G4double v = hmagdistCmd->GetNewDoubleValue(newValue);
      fdetcon->Set48D48Ang(v);
      fevgen->SetPairCAngle(v);
    }


    if( cmd == cerDepCmd ){
	G4double v = cerDepCmd->GetNewDoubleValue(newValue);
	fdetcon->SetCerDepth(v);
    }

    if( cmd == cerDisCmd ){
	G4double v = cerDisCmd->GetNewDoubleValue(newValue);
	fdetcon->SetCerDist(v);
    }

    if( cmd == gemSepCmd ){
	G4double v = gemSepCmd->GetNewDoubleValue(newValue);
	fdetcon->SetGEMSep(v);
    }

    if( cmd == bbCalDistCmd ){
	G4double v = bbCalDistCmd->GetNewDoubleValue(newValue);
	fdetcon->SetBBCalDist(v);
    }

    if( cmd == thminCmd ){
	G4double v = thminCmd->GetNewDoubleValue(newValue);
	fevgen->SetThMin(v);
    }
    if( cmd == thmaxCmd ){
	G4double v = thmaxCmd->GetNewDoubleValue(newValue);
	fevgen->SetThMax(v);
    }
    if( cmd == phminCmd ){
	G4double v = phminCmd->GetNewDoubleValue(newValue);
	fevgen->SetPhMin(v);
    }
    if( cmd == phmaxCmd ){
	G4double v = phmaxCmd->GetNewDoubleValue(newValue);
	fevgen->SetPhMax(v);
    }

    if( cmd == gemresCmd ){
	G4double v = gemresCmd->GetNewDoubleValue(newValue);
	fevact->SetGEMRes(v);
    }


}
