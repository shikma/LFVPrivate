#include "LFVPrivate/SimData.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include <iostream>

using namespace std;

void Looper(bool useEM)
{
	TChain* chain = new TChain("t","");
	chain->Add("../run/Z_noSmearing.root/t");
	TTree* tree = chain;

	SimData* data = new SimData(tree);

    if(data->fChain == 0) {
        cout << " fchain is empty" << endl;
    }
    Int_t nentries = Int_t(data->fChain->GetEntries());
    cout << " Reading data ..." << nentries << " in physics tree" << endl;

    Int_t nTen = nentries/10;
    Int_t nbytes = 0, nb = 0;

    TH1D* elPt = new TH1D("elPt","elPt",60,0,300);
    TH1D* muPt = new TH1D("muPt","muPt",60,0,300);

    TH1D* eleta = new TH1D("elEta","elEta",60,-3,3);
    TH1D* mueta = new TH1D("muEta","muEta",60,-3,3);


    for (Int_t jentry=0; jentry<nentries; jentry++)
	{
		Int_t ientry = data->LoadTree(jentry);
		if (ientry < 0) {   break;        }

		nb = data->fChain->GetEntry(jentry);
		nbytes += nb;

		if (nTen!=0) if (jentry%nTen==0) { cout << " " << 10*(jentry/nTen) << "%-" <<flush;                }

//	 	printf("evt %d: nPhoton %d, nElectron %d, nMuon %d, nTau %d, nJet %d \n",
//	 			data->evt,data->nPhoton,data->nElectron,data->nMuon,data->nTau,data->nJet);

	 	int n_e = data->nElectron;
	 	int n_m = data->nMuon;

	  	if (useEM &&(n_e!=1 || n_m!=1)){continue; 	}

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
	 				elPt->Fill(data->electronPt[i]);
	 				eleta->Fill(data->electronEta[i]);
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
	 				muPt->Fill(data->muonPt[i]);
	 				mueta->Fill(data->muonEta[i]);
//	 				cout<<"muon# "<<i+1<<" out of "<< n_m<<" pt "<<data->muonPt[i]<<endl;
	 			}

	 		}
	 	}

	}

    elPt->SetLineColor(kGreen+2);
    elPt->Draw();
    muPt->Draw("sames");

    eleta->SetLineColor(kGreen+2);

//    eleta->DrawNormalized();
//    mueta->DrawNormalized("sames");

    delete data;
}
