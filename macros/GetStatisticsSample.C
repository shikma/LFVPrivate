#include "LFVPrivate/SimData.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

void GetStatisticsSample(TString infile,TString outfile, int numEntries)
{
	const int kMaxTrack = 10;	// maximal number of particles in a single event. @@@
	
	
	int evt = -999;	// probably a flag
	
	
	// definitions for the braches in the tree. some are scalars (# of particles prob) and some are vectors (info. for each particle)
	int nPhoton = 0;
	float photonPt[kMaxTrack];
	float photonEta[kMaxTrack];
	float photonPhi[kMaxTrack];
	
	int nElectron = 0;
	float electronPt[kMaxTrack];
	float electronEta[kMaxTrack];
	float electronPhi[kMaxTrack];
	int electronQ[kMaxTrack];

	int nMuon = 0;
	float muonPt[kMaxTrack];
	float muonEta[kMaxTrack];
	float muonPhi[kMaxTrack];
	int muonQ[kMaxTrack];

	int nTau = 0;
	float tauPt[kMaxTrack];
	float tauEta[kMaxTrack];
	float tauPhi[kMaxTrack];
	int tauQ[kMaxTrack];
	
	int nJet = 0;
	float jetPt[kMaxTrack];
	float jetEta[kMaxTrack];
	float jetPhi[kMaxTrack];
	int jetQ[kMaxTrack];

	float metPt = -999.;
	float metEta = -999.;
	float metPhi = -999.;

	
	TFile f(outfile,"recreate");	// the file and tree
	TTree *t = new TTree("t","Reconst ntuple");
	
	
	// adding branches:
	// t->Branch(Branch name in the browser, pointer to the variable, variable name)
	
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

	t->Branch("nMuon",&nMuon,"nMuon/I");
	t->Branch("muonPt",muonPt,"muonPt[nMuon]/F");
	t->Branch("muonEta",muonEta,"muonEta[nMuon]/F");
	t->Branch("muonPhi",muonPhi,"muonPhi[nMuon]/F");
	t->Branch("muonQ",muonQ,"muonQ[nMuon]/I");

	t->Branch("nTau",&nTau,"nTau/I");
	t->Branch("tauPt",tauPt,"tauPt[nTau]/F");
	t->Branch("tauEta",tauEta,"tauEta[nTau]/F");
	t->Branch("tauPhi",tauPhi,"tauPhi[nTau]/F");
	t->Branch("tauQ",tauQ,"tauQ[nTau]/I");

	t->Branch("nJet",&nJet,"nJet/I");
	t->Branch("jetPt",jetPt,"jetPt[nJet]/F");
	t->Branch("jetEta",jetEta,"jetEta[nJet]/F");
	t->Branch("jetPhi",jetPhi,"jetPhi[nJet]/F");
	t->Branch("jetQ",jetQ,"jetQ[nJet]/I");

	t->Branch("metPt",&metPt,"metPt/F");
	t->Branch("metEta",&metEta,"metEta/F");
	t->Branch("metPhi",&metPhi,"metPhi/F");
	
	
	// This next part is taken from looper.
	
	TChain* chain = new TChain("t");
	chain->Add("../run/"+infile+"/t");
	TTree* tree = chain;
	
	SimData* data = new SimData(tree);

    if(data->fChain == 0) {
		cout << " fchain is empty" << endl;
	}
    Int_t nentries = Int_t(data->fChain->GetEntries());
    cout << " Reading data ..." << numEntries << " in physics tree" << endl;

    Int_t nTen = numEntries/10;
    Int_t nbytes = 0, nb = 0;

    double effMax = 0;

    for (Int_t jentry=0; jentry<numEntries; jentry++) {

		Int_t ientry = data->LoadTree(jentry);
		if (ientry < 0) break;
		
		nb = data->fChain->GetEntry(jentry);
		nbytes += nb;
		
		if (nTen!=0) if (jentry%nTen==0) cout << " " << 10*(jentry/nTen) << "%-" <<flush;

		
		evt = data->evt;

		nPhoton = data->nPhoton;
		nElectron = data->nElectron;
		nMuon = data->nMuon;
		nTau = data->nTau;
		nJet = data->nJet;

//		cout<<"nElectron = "<<nElectron<<endl;

		for (int i = 0; i < kMaxTrack; i++) {

			photonPt[i] = data->photonPt[i];
			photonEta[i] = data->photonEta[i];
			photonPhi[i] = data->photonPhi[i];
			
			electronPt[i] = data->electronPt[i];
			electronEta[i] = data->electronEta[i];
			electronPhi[i] = data->electronPhi[i];
			electronQ[i] = data->electronQ[i];
			
			muonPt[i] = data->muonPt[i];
			muonEta[i] = data->muonEta[i];
			muonPhi[i] = data->muonPhi[i];
			muonQ[i] = data->muonQ[i];

			tauPt[i] = data->tauPt[i];
			tauEta[i] = data->tauEta[i];
			tauPhi[i] = data->tauPhi[i];
			tauQ[i] = data->tauQ[i];

			jetPt[i] = data->jetPt[i];
			jetEta[i] = data->jetEta[i];
			jetPhi[i] = data->jetPhi[i];
			jetQ[i] = data->jetQ[i];

		}

		metPt = data->metPt;
		metEta = data->metEta;
		metPhi = data->metPhi;


		t->Fill();

	}


	f.cd();
	t->Write("",TObject::kOverwrite);
	
	delete data;
}
