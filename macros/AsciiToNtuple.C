#include "TFile.h"
#include "TTree.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

void AsciiToNtuple()
{
	/*
	 *   # typ  eta  phi    pT tag  cal02  cal03  cal04  trk02  trk03  trk04

      1        0        0 1.0000
  1  0  0.25 6.18   10.7  0   0.00   0.00   0.00   0.00   0.00   0.00
  2 -2 -1.05 1.32   60.0  0   0.00   0.00   0.00   0.00   0.00   0.00
  3  2 -0.15 5.34   23.7  0   0.02   0.02   5.29   0.00   0.00   0.00
  4  4  1.54 3.26   26.7  0   0.00   0.00   0.00   0.00   0.00   0.00
  5  6  0.00 5.01   20.0  0   0.00   0.00   0.00   0.00   0.00   0.00

      2        0        0 1.0000
  1 -3 -0.62 1.80   41.6  0   0.00   0.00   0.00   0.00   0.00   1.00
  2  2 -0.01 5.55   70.5  0   0.00   0.00   2.09   0.00   0.00   0.00
  3  4 -0.62 1.84   40.8  3   0.00   0.00   0.00   0.00   0.00   0.00
  4  4 -1.29 3.13   20.2  0   0.00   0.00   0.00   0.00   0.00   0.00
  5  6  0.00 1.09   25.3  0   0.00   0.00   0.00   0.00   0.00   0.00
	 */
	/*
	 * 0 for photons, +/-1 for electrons, +/-2 for muons, +/-3 hadronic tau 4 for jets, and 6 for MET
	 */
   const int kMaxTrack = 20;

   int evt = -999;

   int nPhoton = 0;
   double photonPt[kMaxTrack];
   double photonEta[kMaxTrack];
   double photonPhi[kMaxTrack];

   int nElectron = 0;
   double electronPt[kMaxTrack];
   double electronEta[kMaxTrack];
   double electronPhi[kMaxTrack];
   int electronQ[kMaxTrack];
   int electronTag[kMaxTrack];
   double electronCal02[kMaxTrack];
   double electronCal03[kMaxTrack];
   double electronCal04[kMaxTrack];
   double electronTrk02[kMaxTrack];
   double electronTrk03[kMaxTrack];
   double electronTrk04[kMaxTrack];

   int nMuon = 0;
   double muonPt[kMaxTrack];
   double muonEta[kMaxTrack];
   double muonPhi[kMaxTrack];
   int muonQ[kMaxTrack];
   int muonTag[kMaxTrack];
   double muonCal02[kMaxTrack];
   double muonCal03[kMaxTrack];
   double muonCal04[kMaxTrack];
   double muonTrk02[kMaxTrack];
   double muonTrk03[kMaxTrack];
   double muonTrk04[kMaxTrack];

   int nTau = 0;
   double tauPt[kMaxTrack];
   double tauEta[kMaxTrack];
   double tauPhi[kMaxTrack];
   int tauQ[kMaxTrack];
   int tauTag[kMaxTrack];
   double tauCal02[kMaxTrack];
   double tauCal03[kMaxTrack];
   double tauCal04[kMaxTrack];
   double tauTrk02[kMaxTrack];
   double tauTrk03[kMaxTrack];
   double tauTrk04[kMaxTrack];

   int nJet = 0;
   double jetPt[kMaxTrack];
   double jetEta[kMaxTrack];
   double jetPhi[kMaxTrack];
   int jetQ[kMaxTrack];
   int jetTag[kMaxTrack];
   double jetCal02[kMaxTrack];
   double jetCal03[kMaxTrack];
   double jetCal04[kMaxTrack];
   double jetTrk02[kMaxTrack];
   double jetTrk03[kMaxTrack];
   double jetTrk04[kMaxTrack];

   double metPt = -999.;
   double metEta = -999.;
   double metPhi = -999.;


   TFile f("Yevgeny.root","recreate");
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
   t->Branch("metPt",&metPt,"metPt/I");
   t->Branch("metEta",&metEta,"metEta/I");
   t->Branch("metPhi",&metPhi,"metPhi/I");

   string line;
   ifstream infile ("../SimOutput/H2tm.cmnd.8.lhco");
   while (!infile.eof() )
   {
	   int number = -999;
	   int type = -999;
	   float eta = -999.;
	   float phi = -999.;
	   float pT = -999.;
	   int tag = -999;
	   float cal02 = -999.;
	   float cal03 = -999.;
	   float cal04 = -999.;
	   float trk02 = -999.;
	   float trk03 = -999.;
	   float trk04 = -999.;

       getline (infile,line);
       sscanf(line.c_str(),"%d %d %f %f %f %d %f %f %f %f %f %f",&number,&type,&eta,&phi,&pT,&tag,&cal02,&cal03,&cal04,&trk02,&trk03,&trk04);
       cout << line << " --> " << number << " " << trk04 << endl;

       //empty line
       if(number == -999 && trk04 == -999) continue;

       //new event
       if(number != -999 && trk04 == -999)
       {
    	   if(evt != -999)
    	   {
    		   //fill the tree
    		   t->Fill();
    	   }
		   //initialize the variables
		   nPhoton = 0;
		   nElectron = 0;
		   nMuon = 0;
		   nTau = 0;
		   nJet = 0;
		   metPt = -999;
		   metEta = -999;
		   metPhi = -999;
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
    	   evt = number;
       }

       //new particle/object
       if(number != -999 && trk04 != -999)
       {
    	   if(type == 0) //photon
    	   {
    		   nPhoton++;
    		   photonPt[nPhoton-1] = pT;
    		   photonEta[nPhoton-1] = eta;
    		   photonPhi[nPhoton-1] = phi;
    	   }else if(type == -1 || type == 1)
    	   {
    		   nElectron++;
    		   electronPt[nElectron-1] = pT;
    		   electronEta[nElectron-1] = eta;
    		   electronPhi[nElectron-1] = phi;
    		   electronQ[nElectron-1] = (type > 0 ? 1 : -1);
    		   electronTag[nElectron-1] = tag;
    		   electronCal02[nElectron-1] = cal02;
    		   electronCal03[nElectron-1] = cal03;
    		   electronCal04[nElectron-1] = cal04;
    		   electronCal02[nElectron-1] = cal02;
    		   electronCal03[nElectron-1] = cal03;
    		   electronCal04[nElectron-1] = cal04;
    	   }else if(type == -2 || type == 2)
    	   {
    		   nMuon++;
    		   muonPt[nMuon-1] = pT;
    		   muonEta[nMuon-1] = eta;
    		   muonPhi[nMuon-1] = phi;
    		   muonQ[nMuon-1] = (type > 0 ? 1 : -1);
    		   muonTag[nMuon-1] = tag;
    		   muonCal02[nMuon-1] = cal02;
    		   muonCal03[nMuon-1] = cal03;
    		   muonCal04[nMuon-1] = cal04;
    		   muonCal02[nMuon-1] = cal02;
    		   muonCal03[nMuon-1] = cal03;
    		   muonCal04[nMuon-1] = cal04;
    	   }else if(type == -3 || type == 3)
    	   {
    		   nTau++;
    		   tauPt[nTau-1] = pT;
    		   tauEta[nTau-1] = eta;
    		   tauPhi[nTau-1] = phi;
    		   tauQ[nTau-1] = (type > 0 ? 1 : -1);
    		   tauTag[nTau-1] = tag;
    		   tauCal02[nTau-1] = cal02;
    		   tauCal03[nTau-1] = cal03;
    		   tauCal04[nTau-1] = cal04;
    		   tauCal02[nTau-1] = cal02;
    		   tauCal03[nTau-1] = cal03;
    		   tauCal04[nTau-1] = cal04;
    	   }else if(type == -4 || type == 4)
    	   {
    		   nJet++;
    		   jetPt[nJet-1] = pT;
    		   jetEta[nJet-1] = eta;
    		   jetPhi[nJet-1] = phi;
    		   jetQ[nJet-1] = (type > 0 ? 1 : -1);
    		   jetTag[nJet-1] = tag;
    		   jetCal02[nJet-1] = cal02;
    		   jetCal03[nJet-1] = cal03;
    		   jetCal04[nJet-1] = cal04;
    		   jetCal02[nJet-1] = cal02;
    		   jetCal03[nJet-1] = cal03;
    		   jetCal04[nJet-1] = cal04;
    	   }else if(type == 6)
    	   {
    		   metPt = pT;
    		   metEta = eta;
    		   metPhi = phi;
    	   }
       }
   }

   t->Print();
   f.cd();
   t->Write();
   infile.close();

   return;
}
