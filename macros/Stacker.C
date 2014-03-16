#include "LFVPrivate/SimData.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include <math.h>
#include <sstream>

using namespace std;

void Stacker(TString path,TString cut,double ME_Br,double EM_Br)
{
	TString MCSamples[11]={"wt", "ZZ","H2WWleptonic", "WlepZmue","WincZtautau",
			"H2tt", "ttbar", "WWleptonic",  "Z2tt_highmass","H2tm","H2te_tau2mu"};
	Int_t   MCcolors[11]={ kMagenta+3, kMagenta,kBlue+1,kOrange+1,kOrange,
			kGreen, kRed, kYellow, kCyan, kBlack, kBlack};

	TCanvas* c1 = new TCanvas("canvasLog"+cut,"canvasLog"+cut,600,600);
	c1->SetLogy();
//	TCanvas* c2 = new TCanvas("c_diff","c_diff",600,600);
	TCanvas* c3 = new TCanvas("c_ratio"+cut,"c_ratio"+cut,600,600);
	TCanvas* c4 = new TCanvas("canvasStack"+cut,"canvasStack"+cut,600,600);	c4->SetLogy();
	TCanvas* c5 = new TCanvas("canvasStack2"+cut,"canvasStack2"+cut,600,600); c5->SetLogy();

	TLegend* leg = new TLegend(0.5,0.7,0.7,0.9);
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(1);

	THStack* hs = new THStack("ME_EM","ME_EM");
	THStack* hsStackedME = new THStack("stacked_ME","#bf{#mu}e Channel;"
			"M_{collinear};Events /4 GeV");
	THStack* hsStackedEM = new THStack("stacked_EM","e#mu Channel;"
			"M_{collinear};Events /4 GeV");

	TH1D* EM_sum = new TH1D("EM_sum","EM_sum",250,0,500);
	TH1D* ME_sum = new TH1D("ME_sum","ME_sum",250,0,500);

	TFile* fs = new TFile(path+"H2tm_"+cut+".root");
	TH1D* signal_ME = (TH1D*)fs->Get("ME_Mcoll"); signal_ME->SetLineColor(kBlack);
	signal_ME->SetLineStyle(7);
	signal_ME->SetName("signal_ME_Mcoll");
	TH1D* signal_EM = (TH1D*)fs->Get("EM_Mcoll"); signal_EM->SetLineColor(kBlack);
	signal_EM->SetLineStyle(7);
	signal_EM->SetName("signal_EM_Mcoll");

	double signalME_c = ME_Br*10;
	double signalEM_c = EM_Br*10;

//	cout<<"Br*10 = "<<signalME_c<<endl;

	double c[11]={0.47, 0.1584,0.008743268,0.009968992,0.0153296,
			0.00327,0.120508602,0.2204,0.118279925,signalME_c*0.013502715,signalEM_c*0.00666742};

	//group BG
	//diboson
	TFile* f_ZZ = new TFile(path+"ZZ_"+cut+".root");
	TFile* f_WZ1 = new TFile(path+"WlepZmue_"+cut+".root");
	TFile* f_WZ2 = new TFile(path+"WincZtautau_"+cut+".root");
	TFile* f_WW = new TFile(path+"WWleptonic_"+cut+".root");

	TH1D* h_ME_ZZ = (TH1D*)f_ZZ->Get("ME_Mcoll");h_ME_ZZ->Scale(c[1]);
	TH1D* h_EM_ZZ = (TH1D*)f_ZZ->Get("EM_Mcoll");h_EM_ZZ->Scale(c[1]);
	TH1D* h_ME_WZ1 = (TH1D*)f_WZ1->Get("ME_Mcoll");h_ME_WZ1->Scale(c[3]);
	TH1D* h_EM_WZ1 = (TH1D*)f_WZ1->Get("EM_Mcoll");h_EM_WZ1->Scale(c[3]);
	TH1D* h_ME_WZ2 = (TH1D*)f_WZ2->Get("ME_Mcoll");h_ME_WZ2->Scale(c[4]);
	TH1D* h_EM_WZ2 = (TH1D*)f_WZ2->Get("EM_Mcoll");h_EM_WZ2->Scale(c[4]);
	TH1D* h_ME_WW = (TH1D*)f_WW->Get("ME_Mcoll");h_ME_WW->Scale(c[7]);
	TH1D* h_EM_WW = (TH1D*)f_WW->Get("EM_Mcoll");h_EM_WW->Scale(c[7]);

	TH1D* Diboson_ME = new TH1D("Diboson_ME","Diboson_ME",250,0,500);
	Diboson_ME = (TH1D*)h_ME_ZZ->Clone("ME_Mcoll");
	Diboson_ME->Add(h_ME_WZ1);Diboson_ME->Add(h_ME_WZ2);Diboson_ME->Add(h_ME_WW);
	TH1D* Diboson_EM = new TH1D("Diboson_EM","Diboson_EM",250,0,500);
	Diboson_EM = (TH1D*)h_ME_ZZ->Clone("EM_Mcoll");
	Diboson_EM->Add(h_EM_WZ1);Diboson_EM->Add(h_EM_WZ2);Diboson_EM->Add(h_EM_WW);

	TFile *diboson_out = new TFile(path+"Diboson_"+cut+".root","RECREATE");
	Diboson_ME->Write();
	Diboson_EM->Write();
	diboson_out->Close();

	//Higgs SM
	TFile* f_H2WW = new TFile(path+"H2WWleptonic_"+cut+".root");
	TFile* f_H2tt = new TFile(path+"H2tt_"+cut+".root");
	TH1D* h_ME_H2WW = (TH1D*)f_H2WW->Get("ME_Mcoll");h_ME_H2WW->Scale(c[2]);
	TH1D* h_EM_H2WW = (TH1D*)f_H2WW->Get("EM_Mcoll");h_EM_H2WW->Scale(c[2]);
	TH1D* h_ME_H2tt = (TH1D*)f_H2tt->Get("ME_Mcoll");h_ME_H2tt->Scale(c[5]);
	TH1D* h_EM_H2tt = (TH1D*)f_H2tt->Get("EM_Mcoll");h_EM_H2tt->Scale(c[5]);

	TH1D* SMHiggs_ME = new TH1D("SMHiggs_ME","SMHiggs_ME",250,0,500);
	SMHiggs_ME = (TH1D*)h_ME_H2WW->Clone("ME_Mcoll");
	SMHiggs_ME->Add(h_ME_H2tt);
	TH1D* SMHiggs_EM = new TH1D("SMHiggs_EM","SMHiggs_EM",250,0,500);
	SMHiggs_EM = (TH1D*)h_EM_H2WW->Clone("EM_Mcoll");
	SMHiggs_EM->Add(h_EM_H2tt);

	TFile *SMHiggs_out = new TFile(path+"SMHiggs_"+cut+".root","RECREATE");
	SMHiggs_ME->Write();
	SMHiggs_EM->Write();
	SMHiggs_out->Close();

	TString MCSamplesGrouped[5]={"wt",	"SMHiggs", "ttbar", "Diboson",  "Z2tt_highmass"};
	Int_t   MCcolorsGrouped[5]={ kMagenta+3,kGreen, kRed, kYellow, kCyan};
	double cGrouped[5]={0.47, 1,0.120508602,1,0.118279925};

	//BG
	for(int i=0; i<5; i++)
		{
			TFile* f = new TFile(path+MCSamplesGrouped[i]+"_"+cut+".root");
			TH1D* h_ME = (TH1D*)f->Get("ME_Mcoll");
			TH1D* h_EM = (TH1D*)f->Get("EM_Mcoll");
			TH1D* h_ME_l = (TH1D*)h_ME->Clone();
			TH1D* h_EM_l = (TH1D*)h_EM->Clone();
			h_ME->Scale(cGrouped[i]); h_EM->Scale(cGrouped[i]);
			h_ME_l->Scale(cGrouped[i]); h_EM_l->Scale(cGrouped[i]);
			h_ME->Rebin(2); h_EM->Rebin(2);
			h_ME->SetLineColor(MCcolorsGrouped[i]); h_EM->SetLineColor(MCcolorsGrouped[i]);
			h_ME_l->SetLineColor(MCcolorsGrouped[i]); h_EM_l->SetLineColor(MCcolorsGrouped[i]);
			h_ME->SetFillColor(MCcolorsGrouped[i]); h_EM->SetFillColor(MCcolorsGrouped[i]);
//			h_EM->SetLineStyle(7); h_EM_l->SetLineStyle(7);

			if (i==0){
				EM_sum = (TH1D*)h_EM->Clone("EM_sum");
				ME_sum = (TH1D*)h_ME->Clone("ME_sum");
			}
			else{
				EM_sum->Add(h_EM);
				ME_sum->Add(h_ME);
			}
			TH1D* h_ratio = (TH1D*)h_ME->Clone("h_ratio");
			h_ratio->Divide(h_EM);
			h_ratio->GetXaxis()->SetRangeUser(0,300); h_ratio->GetYaxis()->SetRangeUser(0,20);
			hs->Add(h_ME_l); hs->Add(h_EM_l);
			hsStackedME->Add(h_ME);
			hsStackedEM->Add(h_EM);

			c3->cd();
			h_ratio->Draw("sames");

		}
	//add Signals
	for(int i=9;i<11;i++){
		TFile* f = new TFile(path+MCSamples[i]+"_"+cut+".root");
		TH1D* h_ME = (TH1D*)f->Get("ME_Mcoll");
		TH1D* h_EM = (TH1D*)f->Get("EM_Mcoll");
		h_ME->Scale(c[i]); h_EM->Scale(c[i]);
		h_ME->Rebin(2); h_EM->Rebin(2);
		h_ME->SetLineColor(MCcolors[i]); h_EM->SetLineColor(MCcolors[i]);
		h_ME->SetLineStyle(7);h_EM->SetLineStyle(7);
		EM_sum->Add(h_EM);
		ME_sum->Add(h_ME);
		TH1D* h_ratio = (TH1D*)h_ME->Clone("h_ratio");
		h_ratio->Divide(h_EM);
		h_ratio->GetXaxis()->SetRangeUser(0,300); h_ratio->GetYaxis()->SetRangeUser(0,20);
		hs->Add(h_ME); hs->Add(h_EM);
		c3->cd();
		h_ratio->Draw("sames");
	}

	//legend
	leg->AddEntry(signal_ME,"Signal","f");
	for(int j=4;j>=0;j--){
		TFile* f = new TFile(path+MCSamplesGrouped[j]+"_"+cut+".root");
		TH1D* h_ME = (TH1D*)f->Get("ME_Mcoll");
		h_ME->SetLineColor(MCcolorsGrouped[j]);
		leg->AddEntry(h_ME,MCSamplesGrouped[j],"f");
	}


	c3->cd();
	c3->SetTitle("ratio"+cut);
	leg->Draw();

	c1->cd();
	hs->Draw("nostack");
	leg->Draw();
	c4->cd();
	signal_ME->Scale(c[9]);
	signal_ME->Rebin(2);
	hsStackedME->Add(signal_ME);
	hsStackedME->Draw("hist");
//	signal_ME->Draw("sames");
	leg->Draw();

	c5->cd();
	signal_EM->Scale(c[9]);
	signal_EM->Rebin(2);
	hsStackedEM->Add(signal_EM);
	hsStackedEM->Draw("hist");
	//	signal_EM->Draw("sames");
	leg->Draw();

	std::ostringstream strsME;
	strsME << ME_Br;
	std::string strBrME = strsME.str();

	std::ostringstream strsEM;
	strsEM << EM_Br;
	std::string strBrEM = strsEM.str();

	TFile *outputf = new TFile("MCStacked_"+cut+"BR_ME"+strBrME+"BR_EM"+strBrEM+".root","RECREATE");

	hsStackedME->Write();
	hsStackedEM->Write();
	EM_sum->Write();
	ME_sum->Write();

	signal_ME->Write();

	c1->Write();
	c4->Write();
	c3->Write();
	c5->Write();

	outputf->Close();

}
