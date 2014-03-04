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

void Looper(TString infile,TString outfile, bool useEM, bool useCuts)
{
	//CUT VALUES
	float L0_PT_CUT = 30;
	float L1_PT_CUT = 10;
	float dPhi_l0l1_CUT = 0;
	float dPhi_l1Met_CUT = 5;


	TChain* chain = new TChain("t","");
	chain->Add("../run/"+infile+"/t");
	TTree* tree = chain;

	SimData* data = new SimData(tree);

    if(data->fChain == 0) {
        cout << " fchain is empty" << endl;
    }
    Int_t nentries = Int_t(data->fChain->GetEntries());
    cout << " Reading data ..." << nentries << " in physics tree" << endl;

    Int_t nTen = nentries/10;
    Int_t nbytes = 0, nb = 0;

    //Histo definitions

    TH1D* h_elPt = new TH1D("elPt","elPt",150,0,300);
    TH1D* h_muPt = new TH1D("muPt","muPt",150,0,300);
    TH1D* h_elPt_2 = new TH1D("elPt2","elPt2",150,0,300);
    TH1D* h_muPt_2 = new TH1D("muPt2","muPt2",150,0,300);
    TH1D* h_deltaPt = new TH1D("ElPt - MuPt","ElPt - MuPt",200,-100,100);
    TH2D* h_deltaPt_vs_ElPt = new TH2D("deltaPt vs. ElPt","deltaPt vs ElPt",75,0,150,200,-100,100);
    TH1D* h_ME_l0_Pt = new TH1D("ME_l0_Pt","ME_l0_Pt",150,0,300);
    TH1D* h_EM_l0_Pt = new TH1D("EM_l0_Pt","EM_l0_Pt",150,0,300);
    TH1D* h_ME_l1_Pt = new TH1D("ME_l1_Pt","ME_l1_Pt",150,0,300);
    TH1D* h_EM_l1_Pt = new TH1D("EM_l1_Pt","EM_l1_Pt",150,0,300);
    TH1D* h_ME_dPhi_l0_l1 = new TH1D("ME_dPhi_l0_l1","ME_dPhi_l0_l1",50,0,5);
    TH1D* h_EM_dPhi_l0_l1 = new TH1D("EM_dPhi_l0_l1","EM_dPhi_l0_l1",50,0,5);
    TH1D* h_ME_dPhi_l1_MET = new TH1D("ME_dPhi_l1_MET","ME_dPhi_l1_MET",50,0,5);
    TH1D* h_EM_dPhi_l1_MET = new TH1D("EM_dPhi_l1_MET","EM_dPhi_l1_MET",50,0,5);
    TH1D* h_EM_dEta_l0_l1 = new TH1D("EM_delta_Eta","EM_delta_Eta",50,0,5);
    TH1D* h_ME_dEta_l0_l1 = new TH1D("ME_delta_Eta","ME_delta_Eta",50,0,5);
    TH1D* h_EM_Mcoll = new TH1D("EM_Mcoll","EM_Mcoll",250,0,500);
    TH1D* h_ME_Mcoll = new TH1D("ME_Mcoll","ME_Mcoll",250,0,500);
    TH1D* h_eleta = new TH1D("elEta","elEta",60,-3,3);
    TH1D* h_mueta = new TH1D("muEta","muEta",60,-3,3);

    TH1D* h_delta = new TH1D("elPt-muPt","elPt-muPt",150,0,300);



    //output
    TFile* file = new TFile(outfile+".root","RECREATE");


    //cut flow counters
    int n_readIn = 0;
    int n_pass2DifferentFlavor = 0;
    int n_passOppositeSign = 0;
    int n_passL0Pt = 0;
    int n_passL1Pt = 0;
    int n_passJetVeto = 0;
    int n_passdPhiL0L1 = 0;
    int n_passdPhiL1Met = 0;



    for (Int_t jentry=0; jentry<nentries; jentry++)
	{
		Int_t ientry = data->LoadTree(jentry);
		if (ientry < 0) {   break;        }

		nb = data->fChain->GetEntry(jentry);
		nbytes += nb;

		n_readIn++;
		if (nTen!=0) if (jentry%nTen==0) { cout << " " << 10*(jentry/nTen) << "%-" <<flush;                }

//	 	printf("evt %d: nPhoton %d, nElectron %d, nMuon %d, nTau %d, nJet %d \n",
//	 			data->evt,data->nPhoton,data->nElectron,data->nMuon,data->nTau,data->nJet);

	 	int n_e = data->nElectron;
	 	int n_m = data->nMuon;

//	 	for (int i=0; i<n_m; i++){
//	 		if (abs(data->muonEta[i])>2.1){n_m--; }
//	 	}

	  	if (useEM) {
	  		if (n_e!=1 || n_m!=1){continue; 	}
	  		n_pass2DifferentFlavor++;

	  		//Isolation
//	  		if ((data->electronCal04[0] > 4.0)||
//	 					(data->electronCal04[0] > 0.1*data->electronPt[0])||
//	 					(data->electronTrk04[0] > 0.1*data->electronPt[0]))
//	  		{continue;}
//	  		if ((data->muonCal04[0] > 4.0)||
//	  				(data->muonCal04[0] > 0.1*data->muonPt[0])||
//	  				(data->muonTrk04[0] > 0.1*data->muonPt[0]))
//	  		{continue;}


	  		//create TLorentzVectors
	  		float ElPhi = data->electronPhi[0];
	  		float ElPt = data->electronPt[0];
	  		TLorentzVector vEle;
	  		vEle.SetPxPyPzE(ElPt*cos(ElPhi),ElPt*sin(ElPhi),0,ElPt);
	  		float MuPhi = data->muonPhi[0];
	  		float MuPt = data->muonPt[0];
	  		TLorentzVector vMu;
	  		vMu.SetPxPyPzE(MuPt*cos(MuPhi),MuPt*sin(MuPhi),0,MuPt);
	  		float MetPhi = data->metPhi;
	  		float MetPt = data->metPt;
	  		TLorentzVector vMet;
	  		vMet.SetPxPyPzE(MetPt*cos(MetPhi),MetPt*sin(MetPhi),0,MetPt);
	  		double dPhiElMu = abs(vEle.DeltaPhi(vMu));

	  		if (useCuts){
	  			//Opposite Sign
	  			if (data->electronSign[0]==data->muonSign[0]){continue; }
	  			n_passOppositeSign++;
	  			//L1 Pt
	  			if ((ElPt >= MuPt)&&(MuPt < L1_PT_CUT)){continue; }
	  			if ((ElPt < MuPt)&&(ElPt < L1_PT_CUT)){continue; }
	  			n_passL1Pt++;
	  			//L0 Pt
	  			if ((ElPt >= MuPt)&&(ElPt < L0_PT_CUT)){continue; }
	  			if ((ElPt < MuPt)&&(MuPt < L0_PT_CUT)){continue; }
	  			n_passL0Pt++;

	  			//jet veto
	  			bool jveto = 0;
	  			for (int j=0; j<data->nJet && !jveto ; j++){
	  				if ((data->jetPt[j] > 30)&&(abs(data->jetEta[j])<2.5)){jveto = 1; }
	  			}
	  			if (jveto){continue; }
	  			n_passJetVeto++;

	  			//DeltaPhi(l0,l1)
	  			if (dPhiElMu<dPhi_l0l1_CUT){continue; }
	  			n_passdPhiL0L1++;

	  			//DeltaPhi(l1,Met)
	  			if ((ElPt >= MuPt)&&(abs(vMu.DeltaPhi(vMet))>dPhi_l1Met_CUT)){continue; }
	  			if ((ElPt < MuPt)&&(abs(vEle.DeltaPhi(vMet))>dPhi_l1Met_CUT)){continue; }
	  			n_passdPhiL1Met++;
	  		}



			h_elPt_2->Fill(ElPt);
	  		h_muPt_2->Fill(MuPt);
	  		h_deltaPt->Fill(ElPt-MuPt);
	  		h_deltaPt_vs_ElPt->Fill(ElPt,ElPt-MuPt);

	  		if (ElPt >= MuPt){
	  			double dEtaElMu = abs(data->electronEta[0]-data->muonEta[0]);
	  			double Mcoll = sqrt(2.0*ElPt*(MuPt+MetPt)*(cosh(dEtaElMu) - cos(dPhiElMu)));
//	  			if (Mcoll>100 || Mcoll<20){continue;}
	  			h_EM_l0_Pt->Fill(ElPt);
	  			h_EM_l1_Pt->Fill(MuPt);
	  			h_EM_dPhi_l0_l1->Fill(dPhiElMu);
	  			h_EM_dPhi_l1_MET->Fill(abs(vMu.DeltaPhi(vMet)));

	  			h_EM_dEta_l0_l1->Fill(dEtaElMu);

	  			h_EM_Mcoll->Fill(Mcoll);

	  		}
	  		else{
	  			double dEtaElMu = abs(data->electronEta[0]-data->muonEta[0]);
	  			double Mcoll = sqrt(2.0*MuPt*(ElPt+MetPt)*(cosh(dEtaElMu) - cos(dPhiElMu)));
//	  			if (Mcoll>100 || Mcoll<20){continue;}
	  			h_ME_l1_Pt->Fill(ElPt);
	  			h_ME_l0_Pt->Fill(MuPt);
	  			h_ME_dPhi_l0_l1->Fill(dPhiElMu);
	  			h_ME_dPhi_l1_MET->Fill(abs(vEle.DeltaPhi(vMet)));

	  			h_ME_dEta_l0_l1->Fill(dEtaElMu);

	  			h_ME_Mcoll->Fill(Mcoll);

	  		}

	  	}

	 	if (n_e>0)
	 	{
	 		for (int i=0;i<n_e;i++)
	 		{
	 			//isolation
	 			if (1)//(//(data->electronCal03[i] < 4.0)||
	 					//(data->electronCal03[i] < 0.2*data->electronPt[i])||
	 					//(data->electronTrk02[i] < 0.2*data->electronPt[i]))
	 					//data->electronCal04[i] < 0.1*data->electronPt[i])
	 			{
	 				h_elPt->Fill(data->electronPt[i]);
	 				h_eleta->Fill(data->electronEta[i]);
	 				if(data->electronPt[i] < 0)
	 				{
//	 					cout<<"electron# "<<i+1<<" out of "<< n_e<<" pt "<<data->electronPt[i]<<endl;
	 				}
	 			}
	 		}
	 	}
	 	if (n_m>0)
	 	{
	 		for (int i=0;i<n_m;i++)
	 		{
	 			//isolation
	 			if (1)//(//(data->muonCal03[i] < 4.0)||
	 					//(data->muonCal03[i] < 0.2*data->muonPt[i])||
	 					//(data->muonTrk02[i] < 0.2*data->muonPt[i]))
	 					//data->muonCal04[i] < 0.1*data->muonPt[i])
	 			{
	 				h_muPt->Fill(data->muonPt[i]);
	 				h_mueta->Fill(data->muonEta[i]);
//	 				cout<<"muon# "<<i+1<<" out of "<< n_m<<" pt "<<data->muonPt[i]<<endl;
	 			}
	 		}
	 	}
	}

    if (useEM){
    	//Draw Histos
    	TCanvas *c1 = new TCanvas(infile+" leading Lepton Pt",infile+" leading Lepton Pt",600,400);	c1->cd();
    	h_EM_l0_Pt->SetLineColor(kGreen+2); h_EM_l0_Pt->SetLineWidth(2); h_EM_l0_Pt->Draw("E1");
    	h_ME_l0_Pt->SetLineWidth(2); h_ME_l0_Pt->Draw("sames E1");
       	TCanvas *c2 = new TCanvas(infile+" subleading Lepton Pt",infile+" subleading Lepton Pt",600,400); c2->cd();
       	h_EM_l1_Pt->SetLineColor(kGreen+2); h_EM_l1_Pt->SetLineWidth(2); h_EM_l1_Pt->Draw("E1");
       	h_ME_l1_Pt->SetLineWidth(2); h_ME_l1_Pt->Draw("sames E1");
    	TCanvas *c3 = new TCanvas(infile+" Electron Muon Pt",infile+" Electron Muon Pt",600,400); c3->cd();
    	h_elPt_2->SetLineColor(kGreen+2); h_elPt_2->SetLineWidth(2); h_elPt_2->Draw("E1");
    	h_muPt_2->SetLineWidth(2); h_muPt_2->Draw("sames E1");
    	TCanvas *c4 = new TCanvas(infile+" DeltaPhi(el,mu)",infile+" DeltaPhi(el,mu)",600,400); c4->cd();
    	h_EM_dPhi_l0_l1->SetLineColor(kGreen+2); h_EM_dPhi_l0_l1->SetLineWidth(2); h_EM_dPhi_l0_l1->Draw("E1");
    	h_ME_dPhi_l0_l1->SetLineWidth(2); h_ME_dPhi_l0_l1->Draw("sames E1");
    	TCanvas *c5 = new TCanvas(infile+" DeltaPhi(l1,met)",infile+" DeltaPhi(l1,met)",600,400); c5->cd();
    	h_EM_dPhi_l1_MET->SetLineColor(kGreen+2); h_EM_dPhi_l1_MET->SetLineWidth(2); h_EM_dPhi_l1_MET->Draw("E1");
    	h_ME_dPhi_l1_MET->SetLineWidth(2); h_ME_dPhi_l1_MET->Draw("sames E1");
    	TCanvas *c6 = new TCanvas("c6","c6",600,400); c6->cd();
    	TH1D* h_elPtMinusMuPt = (TH1D*)h_elPt_2->Clone("elPtMinusMuPt");
    	TH1D* h_ptSum = (TH1D*)h_elPt_2->Clone("sum");
    	h_ptSum->Add(h_muPt_2,1);
    	h_elPtMinusMuPt->Add(h_muPt_2,-1);
    	h_delta->Divide(h_elPtMinusMuPt,h_ptSum,1,2);
    	h_delta->Draw("E1");
    	TCanvas *c7 = new TCanvas(infile+" DeltaEta(l0,l1)",infile+" DeltaEta(l0,l1)",600,400); c7->cd();
    	h_ME_dEta_l0_l1->SetLineWidth(2); h_ME_dEta_l0_l1->Draw("E1");
    	h_EM_dEta_l0_l1->SetLineColor(kGreen+2); h_EM_dEta_l0_l1->SetLineWidth(2); h_EM_dEta_l0_l1->Draw("sames E1");
    	TCanvas *c8 = new TCanvas(infile+" Mcoll",infile+" Mcoll",600,400); c8->cd();
    	h_EM_Mcoll->SetLineWidth(2); h_EM_Mcoll->SetLineColor(kGreen+2); h_EM_Mcoll->Draw("E1");
    	h_ME_Mcoll->SetLineWidth(2); h_ME_Mcoll->Draw("sames E1");
    	TCanvas *c9 = new TCanvas(infile+" deltaPt",infile+" deltaPt",600,400); c9->cd();
    	h_deltaPt->SetLineWidth(2); h_deltaPt->SetLineColor(kGreen+2); h_deltaPt->Draw("E1");
    	TCanvas *c10 = new TCanvas(infile+" deltaPt vs. ElPt",infile+" deltaPt vs. ElPt",600,400); c10->cd();
    	h_deltaPt_vs_ElPt->Draw("colz");


    	//Save histos
    	h_EM_l0_Pt->Write();
    	h_ME_l0_Pt->Write();
    	h_EM_l1_Pt->Write();
    	h_ME_l1_Pt->Write();
    	h_EM_dPhi_l0_l1->Write();
    	h_ME_dPhi_l0_l1->Write();
    	h_EM_dPhi_l1_MET->Write();
    	h_ME_dPhi_l1_MET->Write();
    	h_EM_dEta_l0_l1->Write();
    	h_ME_dEta_l0_l1->Write();
    	h_EM_Mcoll->Write();
    	h_ME_Mcoll->Write();
    	h_elPt_2->Write();
    	h_muPt_2->Write();
    	h_deltaPt->Write();
    	h_deltaPt_vs_ElPt->Write();

    }



    if (useCuts){
    	cout<<endl;
		cout<<"# read in: "<<n_readIn<<endl;
		cout<<"# passed exactly 2 DF: "<<n_pass2DifferentFlavor<<endl;
		cout<<"# passed Opposite Sign: "<<n_passOppositeSign<<endl;
		cout<<"# passed l1 Pt cut: "<<n_passL1Pt<<endl;
		cout<<"# passed l0 Pt cut: "<<n_passL0Pt<<endl;
		cout<<"# passed jet veto: "<<n_passJetVeto<<endl;
		cout<<"# passed deltaPhi(l0,l1) cut: "<<n_passdPhiL0L1<<endl;
		cout<<"# passed deltaPhi(l1,Met) cut: "<<n_passdPhiL1Met<<endl;

    }

    file->Close();

    ofstream output;
    output.open(outfile+".txt");
    output<<"# read in: "<<n_readIn<<endl;
    output<<"# passed exactly 2 DF: "<<n_pass2DifferentFlavor<<endl;
    output<<"# passed Opposite Sign: "<<n_passOppositeSign<<endl;
    output<<"# passed l1 Pt cut: "<<n_passL1Pt<<endl;
    output<<"# passed l0 Pt cut: "<<n_passL0Pt<<endl;
    output<<"# passed jet veto: "<<n_passJetVeto<<endl;
    output<<"# passed deltaPhi(l0,l1) cut: "<<n_passdPhiL0L1<<endl;
    output<<"# passed deltaPhi(l1,Met) cut: "<<n_passdPhiL1Met<<endl;

    output.close();

    delete data;
}
