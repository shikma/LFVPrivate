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
	TCanvas* c4 = new TCanvas("canvasStack"+cut,"canvasStack"+cut,600,600);
	c4->SetLogy();

	TLegend* leg = new TLegend(0.5,0.7,0.7,0.9);
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(1);

	THStack* hs = new THStack("ME_EM","ME_EM");
	THStack* hsStackedME = new THStack("stacked_ME","stacked_ME");
	THStack* hsStackedEM = new THStack("stacked_EM","stacked_EM");

	TH1D* EM_sum = new TH1D("EM_sum","EM_sum",250,0,500);
	TH1D* ME_sum = new TH1D("ME_sum","ME_sum",250,0,500);

	TFile* fs = new TFile(path+"H2tm_"+cut+".root");
	TH1D* signal_ME = (TH1D*)fs->Get("ME_Mcoll"); signal_ME->SetLineColor(kBlack);
	signal_ME->SetLineStyle(7);
	signal_ME->SetName("signal_ME_Mcoll");

	double signalME_c = ME_Br*10;
	double signalEM_c = EM_Br*10;

//	cout<<"Br*10 = "<<signalME_c<<endl;

	double c[11]={0.47, 0.1584,0.008743268,0.009968992,0.0153296,
			0.00327,0.120508602,0.2204,0.118279925,signalME_c*0.013502715,signalEM_c*0.00666742};

	//BG
	for(int i=0; i<9; i++)
		{
			TFile* f = new TFile(path+MCSamples[i]+"_"+cut+".root");
			TH1D* h_ME = (TH1D*)f->Get("ME_Mcoll");
			TH1D* h_EM = (TH1D*)f->Get("EM_Mcoll");
			h_ME->Scale(c[i]); h_EM->Scale(c[i]);
			h_ME->Rebin(5); h_EM->Rebin(5);
			h_ME->SetLineColor(MCcolors[i]); h_EM->SetLineColor(MCcolors[i]);
			h_ME->SetFillColor(MCcolors[i]); h_EM->SetFillColor(MCcolors[i]);
			h_EM->SetLineStyle(7);

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
			hs->Add(h_ME); hs->Add(h_EM);
			hsStackedME->Add(h_ME);
			hsStackedEM->Add(h_EM);

			c3->cd();
			h_ratio->Draw("sames");

		}
	//add Signals
	for(int i=10;i<=11;i++){
		TFile* f = new TFile(path+MCSamples[i]+"_"+cut+".root");
		TH1D* h_ME = (TH1D*)f->Get("ME_Mcoll");
		TH1D* h_EM = (TH1D*)f->Get("EM_Mcoll");
		h_ME->Scale(c[i]); h_EM->Scale(c[i]);
		h_ME->Rebin(5); h_EM->Rebin(5);
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
	for(int j=11;j>0;j--){
		TFile* f = new TFile(path+MCSamples[j]+"_"+cut+".root");
		TH1D* h_ME = (TH1D*)f->Get("ME_Mcoll");
		h_ME->SetLineColor(MCcolors[j]);
		h_ME->SetLineStyle(7);
		leg->AddEntry(h_ME,MCSamples[j],"f");
	}


	c3->cd();
	c3->SetTitle("ratio"+cut);
	leg->Draw();

	c1->cd();
	hs->Draw("nostack");
	leg->Draw();
	c4->cd();
	hsStackedME->Draw("hist");
	signal_ME->Draw("sames");
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
	signal_ME->Scale(c[9]);
	signal_ME->Write();

	c1->Write();
	c4->Write();
	c3->Write();

	outputf->Close();

}
