
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

#include "LFVPrivate/Tools.h"


void AsciiToNtuple(TString inputfile,TString outputfile)
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


   TFile f(outputfile,"recreate");
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

   string line;
   ifstream infile (inputfile);

   while (!infile.eof())
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

       sscanf(line.c_str(),"%d %d %f %f %f %d %f %f %f %f %f %f",&number,&type,&eta,&phi,&pT,
    		   &tag,&cal02,&cal03,&cal04,&trk02,&trk03,&trk04);
//       cout << line << " --> " << number << " " << trk04 << endl;

       //empty line
       if(number == -999 && trk04 == -999) continue;

       //new event
       if(number != -999 && trk04 == -999)
       {

    	   if(evt != -999)
    	   {
    		   //SORT variables by pT
    		   //sort photons
    	   	   vector<int> photonIndex;
    	   	   vector<float> photon_Pt;
    	   	   for (int i = 0 ; i < nPhoton ; i++) {
    	   		   photonIndex.push_back(i);
    	   		   photon_Pt.push_back(photonPt[i]);
    	   	   }
    	   	   Tools tool(photon_Pt);
    	   	   sort(photonIndex.begin(), photonIndex.end(),tool);

    	   	   float p_tempPt[nPhoton];
    	   	   float p_tempEta[nPhoton];
    	   	   float p_tempPhi[nPhoton];

    	   	   for (int i = 0 ; i < nPhoton ; i++) {
    	   		   p_tempPt[i] = photonPt[i];
    	   		   p_tempEta[i] = photonEta[i];
    	   		   p_tempPhi[i] = photonPhi[i];
    	   	   }
    	   	   for (int i = 0 ; i < nPhoton ; i++){
    	   		   photonPt[i] = p_tempPt[photonIndex[i]];
    	   		   photonEta[i] = p_tempEta[photonIndex[i]];
    	   		   photonPhi[i] = p_tempPhi[photonIndex[i]];
    	   	   }

    	   	   //sort electrons
    	   	   vector<int> eleIndex;
    	   	   vector<float> ele_Pt;
    	   	   for (int i = 0 ; i < nElectron ; i++) {
    	   		   eleIndex.push_back(i);
    	   		   ele_Pt.push_back(electronPt[i]);
    	   	   }
    	   	   tool.Setv_pt(ele_Pt);
    	   	   sort(eleIndex.begin(), eleIndex.end(),tool);

    	   	   float e_tempPt[nElectron];
    	   	   float e_tempEta[nElectron];
    	   	   float e_tempPhi[nElectron];
    	   	   float e_tempQ[nElectron];
    	   	   float e_tempTag[nElectron];
    	   	   float e_tempCal02[nElectron];
    	   	   float e_tempCal03[nElectron];
    	   	   float e_tempCal04[nElectron];
    	   	   float e_tempTrk02[nElectron];
    	   	   float e_tempTrk03[nElectron];
    	   	   float e_tempTrk04[nElectron];
    	   	   float e_tempSign[nElectron];


        	   for (int i = 0 ; i < nElectron ; i++) {
        		   e_tempPt[i] = electronPt[i];
        		   e_tempEta[i] = electronEta[i];
        		   e_tempPhi[i] = electronPhi[i];
        		   e_tempQ[i] = electronQ[i];
        		   e_tempTag[i] = electronTag[i];
        		   e_tempCal02[i] = electronCal02[i];
        		   e_tempCal03[i] = electronCal03[i];
        		   e_tempCal04[i] = electronCal04[i];
        		   e_tempTrk02[i] = electronTrk02[i];
        		   e_tempTrk03[i] = electronTrk03[i];
        		   e_tempTrk04[i] = electronTrk04[i];
        		   e_tempSign[i] = electronSign[i];

        	   }
        	   for (int i = 0 ; i < nElectron ; i++){
        		   electronPt[i] = e_tempPt[eleIndex[i]];
        		   electronEta[i] = e_tempEta[eleIndex[i]];
        		   electronPhi[i] = e_tempPhi[eleIndex[i]];
        		   electronQ[i] = e_tempQ[eleIndex[i]];
        		   electronTag[i] = e_tempTag[eleIndex[i]];
        		   electronCal02[i] = e_tempCal02[eleIndex[i]];
        		   electronCal03[i] = e_tempCal03[eleIndex[i]];
        		   electronCal04[i] = e_tempCal04[eleIndex[i]];
        		   electronTrk02[i] = e_tempTrk02[eleIndex[i]];
        		   electronTrk03[i] = e_tempTrk03[eleIndex[i]];
        		   electronTrk04[i] = e_tempTrk04[eleIndex[i]];
        		   electronSign[i] = e_tempSign[eleIndex[i]];
        	   }

        	   //sort muons
        	   vector<int> muIndex;
        	   vector<float> mu_Pt;
        	   for (int i = 0 ; i < nMuon ; i++) {
        		   muIndex.push_back(i);
        		   mu_Pt.push_back(muonPt[i]);
        	   }
        	   tool.Setv_pt(mu_Pt);
        	   sort(muIndex.begin(), muIndex.end(),tool);

        	   float m_tempPt[nMuon];
        	   float m_tempEta[nMuon];
        	   float m_tempPhi[nMuon];
        	   float m_tempQ[nMuon];
        	   float m_tempTag[nMuon];
        	   float m_tempCal02[nMuon];
        	   float m_tempCal03[nMuon];
        	   float m_tempCal04[nMuon];
        	   float m_tempTrk02[nMuon];
        	   float m_tempTrk03[nMuon];
        	   float m_tempTrk04[nMuon];
        	   float m_tempSign[nMuon];


        	   for (int i = 0 ; i < nMuon ; i++) {
        		   m_tempPt[i] = muonPt[i];
        		   m_tempEta[i] = muonEta[i];
        		   m_tempPhi[i] = muonPhi[i];
        		   m_tempQ[i] = muonQ[i];
        		   m_tempTag[i] = muonTag[i];
        		   m_tempCal02[i] = muonCal02[i];
        		   m_tempCal03[i] = muonCal03[i];
        		   m_tempCal04[i] = muonCal04[i];
        		   m_tempTrk02[i] = muonTrk02[i];
        		   m_tempTrk03[i] = muonTrk03[i];
        		   m_tempTrk04[i] = muonTrk04[i];
        		   m_tempSign[i] = muonSign[i];

        	   }
        	   for (int i = 0 ; i < nMuon ; i++){
        		   muonPt[i] = m_tempPt[muIndex[i]];
        		   muonEta[i] = m_tempEta[muIndex[i]];
        		   muonPhi[i] = m_tempPhi[muIndex[i]];
        		   muonQ[i] = m_tempQ[muIndex[i]];
        		   muonTag[i] = m_tempTag[muIndex[i]];
        		   muonCal02[i] = m_tempCal02[muIndex[i]];
        		   muonCal03[i] = m_tempCal03[muIndex[i]];
        		   muonCal04[i] = m_tempCal04[muIndex[i]];
        		   muonTrk02[i] = m_tempTrk02[muIndex[i]];
        		   muonTrk03[i] = m_tempTrk03[muIndex[i]];
        		   muonTrk04[i] = m_tempTrk04[muIndex[i]];
        		   muonSign[i] = m_tempSign[muIndex[i]];
        	   }

        	   //sort taus
        	   vector<int> tauIndex;
        	   vector<float> tau_Pt;
        	   for (int i = 0 ; i < nTau ; i++) {
        		   tauIndex.push_back(i);
        		   tau_Pt.push_back(tauPt[i]);
        	   }
        	   tool.Setv_pt(tau_Pt);
        	   sort(tauIndex.begin(), tauIndex.end(),tool);

        	   float t_tempPt[nTau];
        	   float t_tempEta[nTau];
        	   float t_tempPhi[nTau];
        	   float t_tempQ[nTau];
        	   float t_tempTag[nTau];
        	   float t_tempCal02[nTau];
        	   float t_tempCal03[nTau];
        	   float t_tempCal04[nTau];
        	   float t_tempTrk02[nTau];
        	   float t_tempTrk03[nTau];
        	   float t_tempTrk04[nTau];
        	   float t_tempSign[nTau];


        	   for (int i = 0 ; i < nTau ; i++) {
        		   t_tempPt[i] = tauPt[i];
        		   t_tempEta[i] = tauEta[i];
        		   t_tempPhi[i] = tauPhi[i];
        		   t_tempQ[i] = tauQ[i];
        		   t_tempTag[i] = tauTag[i];
        		   t_tempCal02[i] = tauCal02[i];
        		   t_tempCal03[i] = tauCal03[i];
        		   t_tempCal04[i] = tauCal04[i];
        		   t_tempTrk02[i] = tauTrk02[i];
        		   t_tempTrk03[i] = tauTrk03[i];
        		   t_tempTrk04[i] = tauTrk04[i];
        		   t_tempSign[i] = tauSign[i];

        	   }
        	   for (int i = 0 ; i < nTau ; i++){
        		   tauPt[i] = t_tempPt[tauIndex[i]];
        		   tauEta[i] = t_tempEta[tauIndex[i]];
        		   tauPhi[i] = t_tempPhi[tauIndex[i]];
        		   tauQ[i] = t_tempQ[tauIndex[i]];
        		   tauTag[i] = t_tempTag[tauIndex[i]];
        		   tauCal02[i] = t_tempCal02[tauIndex[i]];
        		   tauCal03[i] = t_tempCal03[tauIndex[i]];
        		   tauCal04[i] = t_tempCal04[tauIndex[i]];
        		   tauTrk02[i] = t_tempTrk02[tauIndex[i]];
        		   tauTrk03[i] = t_tempTrk03[tauIndex[i]];
        		   tauTrk04[i] = t_tempTrk04[tauIndex[i]];
        		   tauSign[i] = t_tempSign[tauIndex[i]];
        	   }

        	   //sort jets
        	   vector<int> jetIndex;
        	   vector<float> jet_Pt;
        	   for (int i = 0 ; i < nJet ; i++) {
        		   jetIndex.push_back(i);
        		   jet_Pt.push_back(jetPt[i]);
        	   }
        	   tool.Setv_pt(jet_Pt);
        	   sort(jetIndex.begin(), jetIndex.end(),tool);

        	   float j_tempPt[nJet];
        	   float j_tempEta[nJet];
        	   float j_tempPhi[nJet];
        	   float j_tempQ[nJet];
        	   float j_tempTag[nJet];
        	   float j_tempCal02[nJet];
        	   float j_tempCal03[nJet];
        	   float j_tempCal04[nJet];
        	   float j_tempTrk02[nJet];
        	   float j_tempTrk03[nJet];
        	   float j_tempTrk04[nJet];


        	   for (int i = 0 ; i < nJet ; i++) {
        		   j_tempPt[i] = jetPt[i];
        		   j_tempEta[i] = jetEta[i];
        		   j_tempPhi[i] = jetPhi[i];
        		   j_tempQ[i] = jetQ[i];
        		   j_tempTag[i] = jetTag[i];
        		   j_tempCal02[i] = jetCal02[i];
        		   j_tempCal03[i] = jetCal03[i];
        		   j_tempCal04[i] = jetCal04[i];
        		   j_tempTrk02[i] = jetTrk02[i];
        		   j_tempTrk03[i] = jetTrk03[i];
        		   j_tempTrk04[i] = jetTrk04[i];

        	   }
        	   for (int i = 0 ; i < nJet ; i++){
        		   jetPt[i] = j_tempPt[jetIndex[i]];
        		   jetEta[i] = j_tempEta[jetIndex[i]];
        		   jetPhi[i] = j_tempPhi[jetIndex[i]];
        		   jetQ[i] = j_tempQ[jetIndex[i]];
        		   jetTag[i] = j_tempTag[jetIndex[i]];
        		   jetCal02[i] = j_tempCal02[jetIndex[i]];
        		   jetCal03[i] = j_tempCal03[jetIndex[i]];
        		   jetCal04[i] = j_tempCal04[jetIndex[i]];
        		   jetTrk02[i] = j_tempTrk02[jetIndex[i]];
        		   jetTrk03[i] = j_tempTrk03[jetIndex[i]];
        		   jetTrk04[i] = j_tempTrk04[jetIndex[i]];
        	   }

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
    		   electronSign[nElectron-1] = copysign(1,type);
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
    		   muonSign[nMuon-1] = copysign(1,type);
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
    		   tauSign[nTau-1] = copysign(1,type);
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



       }//end new particle/object
//       if(evt>100) break;
   }


   t->Print();
   f.cd();
   t->Write("",TObject::kOverwrite);
   infile.close();

   return;
}
