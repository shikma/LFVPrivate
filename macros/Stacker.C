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

void Stacker(TString path,TString cut,double Br)
{
	TString MCSamples[10]={"wt", "ZZ","H2WWleptonic", "WlepZmue","WincZtautau",  "H2tt", "WWleptonic", "ttbar",  "Z2tt","H2tm"};
	Int_t   MCcolors[10]={ kMagenta+3, kMagenta,kBlue+1,kOrange+1,kOrange,  kGreen,  kYellow,  kRed, kCyan, kBlack};

	TCanvas* c1 = new TCanvas("canvasLog"+cut,"canvasLog"+cut,600,600);
	c1->SetLogy();
//	TCanvas* c2 = new TCanvas("c_diff","c_diff",600,600);
	TCanvas* c3 = new TCanvas("c_ratio"+cut,"c_ratio"+cut,600,600);
	TCanvas* c4 = new TCanvas("canvasStack"+cut,"canvasStack"+cut,600,600);
	c4->SetLogy();

	TLegend* leg = new TLegend(0.1,0.7,0.48,0.9);
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(1);

	THStack* hs = new THStack("ME_EM","ME_EM");
	THStack* hs2 = new THStack("stacked_ME","stacked_ME");
	THStack* hs3 = new THStack("stacked_EM","stacked_EM");

	TH1D* EM_sum = new TH1D("EM_sum","EM_sum",250,0,500);
	TH1D* ME_sum = new TH1D("ME_sum","ME_sum",250,0,500);

	TFile* fs = new TFile(path+"H2tm_"+cut+".root");
	TH1D* signal_ME = (TH1D*)fs->Get("ME_Mcoll");
	signal_ME->SetName("signal_ME_Mcoll");

	double signal_c = Br*10;
	cout<<"Br*10 = "<<signal_c<<endl;

	double c[10]={0.47, 0.1584,0.008743268,0.009968992,0.0153296,0.00327,0.120508602,0.2204,0.118279925,signal_c*0.013502715};
	//assuming BR(h->tm)=0.1

	for(int i=0; i<10; i++)
		{
			TFile* f = new TFile(path+MCSamples[i]+"_"+cut+".root");
			TH1D* h_ME = (TH1D*)f->Get("ME_Mcoll");
			TH1D* h_EM = (TH1D*)f->Get("EM_Mcoll");
			h_ME->Scale(c[i]); h_EM->Scale(c[i]);
			h_ME->Rebin(5); h_EM->Rebin(5);
			h_ME->SetLineColor(MCcolors[i]); h_EM->SetLineColor(MCcolors[i]);
			h_EM->SetLineStyle(7);
//			h_ME->GetXaxis()->SetRangeUser(0,300); h_EM->GetXaxis()->SetRangeUser(0,300);
//			TH1D* h_diff = (TH1D*)h_ME->Clone("h_diff");
//			h_diff->Add(h_EM,-1.);
//			TH1D* h_sum = (TH1D*)h_ME->Clone("h_sum");
//			h_sum->Add(h_EM,1.);
//			h_diff->Divide(h_sum);
			if (i==0){
				EM_sum = (TH1D*)h_EM->Clone("EM_sum");
				ME_sum = (TH1D*)h_ME->Clone("ME_sum");
			}
			else{
				EM_sum->Add(h_EM);
				ME_sum->Add(h_ME);
			}
//			cout<<"n enetries = "<<EM_sum->GetEntries()<<" ME = "<<ME_sum->GetEntries()<<endl;
			TH1D* h_ratio = (TH1D*)h_ME->Clone("h_ratio");
			h_ratio->Divide(h_EM);
			h_ratio->GetXaxis()->SetRangeUser(0,300); h_ratio->GetYaxis()->SetRangeUser(0,20);
//			c2->cd();
//			h_diff->Draw("sames");
			hs->Add(h_ME); hs->Add(h_EM);
			hs2->Add(h_ME);
			hs3->Add(h_EM);
			leg->AddEntry(h_ME,MCSamples[i],"f");
			c3->cd();
			h_ratio->Draw("sames");

		}
//	hs->GetXaxis()->SetRange(0,300);
//	hs2->GetXaxis()->SetRange(0,300);
	c3->cd();
	c3->SetTitle("ratio"+cut);
	leg->Draw();
//	c2->cd();
//	leg->Draw();
	c1->cd();
	hs->Draw("nostack");
	leg->Draw();
	c4->cd();
	hs2->Draw("hist");
	leg->Draw();

	std::ostringstream strs;
	strs << Br;
	std::string strBr = strs.str();
	cout<<strBr<<endl;

	TFile *outputf = new TFile("MCStacked_"+cut+"BR"+strBr+".root","RECREATE");

	hs2->Write();
	hs3->Write();
	EM_sum->Write();
	ME_sum->Write();
	signal_ME->Scale(c[9]);
	signal_ME->Write();

	c1->Write();
	c4->Write();
	c3->Write();

	outputf->Close();

}
