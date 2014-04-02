
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TString.h"
#include "TSystem.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

#include "LFVPrivate/Tools.h"


void DelphesToNtuple(TString inputfile,TString outputfile)
{
	  gSystem->Load("~/Delphes/Delphes-3.0.12/libDelphes");

	  // Create chain of root trees
	  TChain chain("Delphes");
	  chain.Add("/Users/shikma/ATLAS_SVN/LFV/LFVPrivateAvital/run/"+inputfile);

	  // Create object of class ExRootTreeReader
	  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
	  Long64_t numberOfEntries = treeReader->GetEntries();

	  // Get pointers to branches used in this analysis
	  TClonesArray *branchJet = treeReader->UseBranch("Jet");
	  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
	  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
	  TClonesArray *branchPhoton = treeReader->UseBranch("Photon");
	  TClonesArray *branchMET = treeReader->UseBranch("MissingET");



    const int kMaxTrack = 20;

    int evt = -999;

    int nPhoton = 0;
    float photonPt[kMaxTrack];
    float photonEta[kMaxTrack];
    float photonPhi[kMaxTrack];

    int nElectron = 0;
    float electronPt[kMaxTrack];
    float electronEta[kMaxTrack];
    float electronPhi[kMaxTrack];
    int electronQ[kMaxTrack];
    int electronTag[kMaxTrack];
    float electronCal02[kMaxTrack];
    float electronCal03[kMaxTrack];
    float electronCal04[kMaxTrack];
    float electronTrk02[kMaxTrack];
    float electronTrk03[kMaxTrack];
    float electronTrk04[kMaxTrack];
    float electronSign[kMaxTrack];

    int nMuon = 0;
    float muonPt[kMaxTrack];
    float muonEta[kMaxTrack];
    float muonPhi[kMaxTrack];
    int muonQ[kMaxTrack];
    int muonTag[kMaxTrack];
    float muonCal02[kMaxTrack];
    float muonCal03[kMaxTrack];
    float muonCal04[kMaxTrack];
    float muonTrk02[kMaxTrack];
    float muonTrk03[kMaxTrack];
    float muonTrk04[kMaxTrack];
    float muonSign[kMaxTrack];

    int nTau = 0;
    float tauPt[kMaxTrack];
    float tauEta[kMaxTrack];
    float tauPhi[kMaxTrack];
    int tauQ[kMaxTrack];
    int tauTag[kMaxTrack];
    float tauCal02[kMaxTrack];
    float tauCal03[kMaxTrack];
    float tauCal04[kMaxTrack];
    float tauTrk02[kMaxTrack];
    float tauTrk03[kMaxTrack];
    float tauTrk04[kMaxTrack];
    float tauSign[kMaxTrack];

    int nJet = 0;
    float jetPt[kMaxTrack];
    float jetEta[kMaxTrack];
    float jetPhi[kMaxTrack];
    int jetQ[kMaxTrack];
    int jetTag[kMaxTrack];
    float jetCal02[kMaxTrack];
    float jetCal03[kMaxTrack];
    float jetCal04[kMaxTrack];
    float jetTrk02[kMaxTrack];
    float jetTrk03[kMaxTrack];
    float jetTrk04[kMaxTrack];

    float metPt = -999.;
    float metEta = -999.;
    float metPhi = -999.;

    float sf_mu_reco_eff[kMaxTrack];	// scale factor muon reco efficiency
 	float sf_el_reco_eff[kMaxTrack];	// electron reco efficiency


    TFile f("/Users/shikma/ATLAS_SVN/LFV/LFVPrivateAvital/run/"+outputfile,"recreate");
    TTree *t = new TTree("t","Reconst ntuple");

    t->Branch("evt",&evt,"evt/I");

    t->Branch("nPhoton",&nPhoton,"nPhoton/I");
    t->Branch("photonPt",photonPt,"photonPt[nPhoton]/F");
    t->Branch("photonEta",photonEta,"photonEta[nPhoton]/F");
    t->Branch("photonPhi",photonPhi,"photonPhi[nPhoton]/F");

    t->Branch("nElectron",&nElectron,"nElectron/I");
    t->Branch("electronPt",electronPt,"electronPt[nElectron]/F");
    t->Branch("electronEta",electronEta,"electronEta[nElectron]/F");
    t->Branch("electronPhi",electronPhi,"electronPhi[nElectron]/F");
    t->Branch("electronQ",electronQ,"electronQ[nElectron]/I");
    t->Branch("electronTag",electronTag,"electronTag[nElectron]/I");
    t->Branch("electronCal02",electronCal02,"electronCal02[nElectron]/F");
    t->Branch("electronCal03",electronCal03,"electronCal03[nElectron]/F");
    t->Branch("electronCal04",electronCal04,"electronCal04[nElectron]/F");
    t->Branch("electronTrk02",electronTrk02,"electronTrk02[nElectron]/F");
    t->Branch("electronTrk03",electronTrk03,"electronTrk03[nElectron]/F");
    t->Branch("electronTrk04",electronTrk04,"electronTrk04[nElectron]/F");
    t->Branch("electronSign",electronSign,"electronSign[nElectron]/F");

    t->Branch("nMuon",&nMuon,"nMuon/I");
    t->Branch("muonPt",muonPt,"muonPt[nMuon]/F");
    t->Branch("muonEta",muonEta,"muonEta[nMuon]/F");
    t->Branch("muonPhi",muonPhi,"muonPhi[nMuon]/F");
    t->Branch("muonQ",muonQ,"muonQ[nMuon]/I");
    t->Branch("muonTag",muonTag,"muonTag[nMuon]/I");
    t->Branch("muonCal02",muonCal02,"muonCal02[nMuon]/F");
    t->Branch("muonCal03",muonCal03,"muonCal03[nMuon]/F");
    t->Branch("muonCal04",muonCal04,"muonCal04[nMuon]/F");
    t->Branch("muonTrk02",muonTrk02,"muonTrk02[nMuon]/F");
    t->Branch("muonTrk03",muonTrk03,"muonTrk03[nMuon]/F");
    t->Branch("muonTrk04",muonTrk04,"muonTrk04[nMuon]/F");
    t->Branch("muonSign",muonSign,"muonSign[nMuon]/F");

    t->Branch("nTau",&nTau,"nTau/I");
    t->Branch("tauPt",tauPt,"tauPt[nTau]/F");
    t->Branch("tauEta",tauEta,"tauEta[nTau]/F");
    t->Branch("tauPhi",tauPhi,"tauPhi[nTau]/F");
    t->Branch("tauQ",tauQ,"tauQ[nTau]/I");
    t->Branch("tauTag",tauTag,"tauTag[nTau]/I");
    t->Branch("tauCal02",tauCal02,"tauCal02[nTau]/F");
    t->Branch("tauCal03",tauCal03,"tauCal03[nTau]/F");
    t->Branch("tauCal04",tauCal04,"tauCal04[nTau]/F");
    t->Branch("tauTrk02",tauTrk02,"tauTrk02[nTau]/F");
    t->Branch("tauTrk03",tauTrk03,"tauTrk03[nTau]/F");
    t->Branch("tauTrk04",tauTrk04,"tauTrk04[nTau]/F");
    t->Branch("tauSign",tauSign,"tauSign[nTau]/F");

    t->Branch("nJet",&nJet,"nJet/I");
    t->Branch("jetPt",jetPt,"jetPt[nJet]/F");
    t->Branch("jetEta",jetEta,"jetEta[nJet]/F");
    t->Branch("jetPhi",jetPhi,"jetPhi[nJet]/F");
    t->Branch("jetQ",jetQ,"jetQ[nJet]/I");
    t->Branch("jetTag",jetTag,"jetTag[nJet]/I");
    t->Branch("jetCal02",jetCal02,"jetCal02[nJet]/F");
    t->Branch("jetCal03",jetCal03,"jetCal03[nJet]/F");
    t->Branch("jetCal04",jetCal04,"jetCal04[nJet]/F");
    t->Branch("jetTrk02",jetTrk02,"jetTrk02[nJet]/F");
    t->Branch("jetTrk03",jetTrk03,"jetTrk03[nJet]/F");
    t->Branch("jetTrk04",jetTrk04,"jetTrk04[nJet]/F");

    t->Branch("metPt",&metPt,"metPt/F");
    t->Branch("metEta",&metEta,"metEta/F");
    t->Branch("metPhi",&metPhi,"metPhi/F");


 	t->Branch("sf_mu_reco_eff",sf_mu_reco_eff,"sf_mu_reco_eff[nMuon]/F");	// my branches
 	t->Branch("sf_el_reco_eff",sf_el_reco_eff,"sf_el_reco_eff[nElectron]/F");


 	  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
 	  {
		   //initialize the variables
		   nPhoton = 0;
		   nElectron = 0;
		   nMuon = 0;
		   nTau = 0;
		   nJet = 0;
		   metPt = -999;
		   metEta = -999;
		   metPhi = -999;
		   evt = entry;
		   for(int i=0; i<kMaxTrack; i++)
		   {
			   photonPt[i] = -999.;
			   photonEta[i] = -999.;
			   photonPhi[i] = -999.;

			   electronPt[i] = -999.;
			   electronEta[i] = -999.;
			   electronPhi[i] = -999.;
			   electronQ[i] = -999;
			   electronTag[i] = -999;
			   electronCal02[i] = -999.;
			   electronCal03[i] = -999.;
			   electronCal04[i] = -999.;
			   electronTrk02[i] = -999.;
			   electronTrk03[i] = -999.;
			   electronTrk04[i] = -999.;
			   electronSign[i] = -999;

			   muonPt[i] = -999.;
			   muonEta[i] = -999.;
			   muonPhi[i] = -999.;
			   muonQ[i] = -999;
			   muonTag[i] = -999;
			   muonCal02[i] = -999.;
			   muonCal03[i] = -999.;
			   muonCal04[i] = -999.;
			   muonTrk02[i] = -999.;
			   muonTrk03[i] = -999.;
			   muonTrk04[i] = -999.;
			   muonSign[i] = -999;

			   tauPt[i] = -999.;
			   tauEta[i] = -999.;
			   tauPhi[i] = -999.;
			   tauQ[i] = -999;
			   tauTag[i] = -999;
			   tauCal02[i] = -999.;
			   tauCal03[i] = -999.;
			   tauCal04[i] = -999.;
			   tauTrk02[i] = -999.;
			   tauTrk03[i] = -999.;
			   tauTrk04[i] = -999.;
			   tauSign[i] = -999;

			   jetPt[i] = -999.;
			   jetEta[i] = -999.;
			   jetPhi[i] = -999.;
			   jetQ[i] = -999;
			   jetTag[i] = -999;
			   jetCal02[i] = -999.;
			   jetCal03[i] = -999.;
			   jetCal04[i] = -999.;
			   jetTrk02[i] = -999.;
			   jetTrk03[i] = -999.;
			   jetTrk04[i] = -999.;
   	   }


 	    // Load selected branches with data from specified event
 	    treeReader->ReadEntry(entry);

 	    int nJets = branchJet->GetEntries();
 	    int nElectrons = branchElectron->GetEntries();
 	    int nMuons = branchMuon->GetEntries();
 	    int nPhotons = branchPhoton->GetEntries();
 	    int nMETs = branchMET->GetEntries();

 	    printf("event number %5d: %5d jets, %5d electrons, %5d muons, %5d photons, %5d nMETS\n",evt,nJets,nElectrons,nMuons,nPhotons,nMETs);

	   nElectron = nElectrons;
	   for(int i=0; i<nElectrons; i++)
	   {
	       Electron *electron = (Electron*) branchElectron->At(i);
		   electronPt[i] = electron->PT;
		   electronEta[i] = electron->Eta;
		   electronPhi[i] = electron->Phi;
		   electronQ[i] = electron->Charge;
		   printf("ele %5d: (pt,eta,phi)=(%7.3f,%7.3f,%7.3f)\n",i,electronPt[i],electronEta[i],electronPhi[i] = electron->Phi);
//		   electronTag[i] = electron; // what is electron tag??
//		   electronSign[i] = electron;
	   }

	   nPhoton = nPhotons;
	   for(int i=0; i<nPhotons; i++)
	   {
		   Photon *photon = (Photon*) branchPhoton->At(i);
		   photonPt[i] = photon->PT;
    	   photonEta[i] = photon->Eta;
    	   photonPhi[i] = photon->Phi;
	   }

	   nMuon = nMuons;
	   for(int i=1; i<nMuons; i++)
	   {
		   Muon *muon = (Muon*) branchMuon->At(i);
   		   muonPt[i] = muon->PT;
   		   muonEta[i] = muon->Eta;
   		   muonPhi[i] = muon->Phi;
   		   muonQ[i] = muon->Charge;
//   		   muonTag[i] = m_tempTag[muIndex[i]];
//    	   muonSign[i] = m_tempSign[muIndex[i]];
	   }


	   for(int i=1; i<nJets; i++)
	   {
		   Jet* jet = (Jet*) branchJet->At(i);
		   if(jet->TauTag)
		   {
			   nTau++;
			   tauPt[i] = jet->PT;
    		   tauEta[i] = jet->Eta;
    		   tauPhi[i] = jet->Phi;
    		   tauQ[i] = jet->Charge;
//    		   tauTag[i] = data->Jet_[i]
//    		   tauSign[i] = data->Jet_[i]
		   }else
		   {
			   nJet++;
       		   jetPt[i] = jet->PT;
			   jetEta[i] = jet->Eta;
			   jetPhi[i] = jet->Phi;
			   jetQ[i] = jet->Charge;
//			   jetTag[i] = data->Jet_Charge[i];
			}
	   }

	   for(int i=1; i<nMETs; i++)
	   {
		   MissingET* met = (MissingET*) branchJet->At(i);
		   metPt = met->ET;
		   metEta = met->Eta;
		   metPhi = met->Phi;
	   }
	   //fill the tree
	   t->Fill();
	}

//   t->Print();
   f.cd();
   t->Write("",TObject::kOverwrite);

   return;
}
