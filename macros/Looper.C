#include "LFVPrivate/SimData.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>

using namespace std;

void Looper()
{
	TChain* chain = new TChain("t","");
	chain->Add("../run/Yevgeny.root/t");
	TTree* tree = chain;

	SimData* data = new SimData(tree);

    if(data->fChain == 0) {
        cout << " fchain is empty" << endl;
    }
    Int_t nentries = Int_t(data->fChain->GetEntries());
    cout << " Reading data ..." << nentries << " in physics tree" << endl;

    Int_t nTen = nentries/10;
    Int_t nbytes = 0, nb = 0;

    for (Int_t jentry=0; jentry<nentries; jentry++)
	{
		Int_t ientry = data->LoadTree(jentry);
		if (ientry < 0) {   break;        }

		nb = data->fChain->GetEntry(jentry);
		nbytes += nb;

		if (nTen!=0) if (jentry%nTen==0) { cout << " " << 10*(jentry/nTen) << "%-" <<flush;                }

	 	printf("evt %d: nPhoton %d, nElectron %d, nMuon %d, nTau %d, nJet %d \n",data->evt,data->nPhoton,data->nElectron,data->nMuon,data->nTau,data->nJet);
	}

    delete data;
}
