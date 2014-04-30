#include "LFVPrivate/SimData.h"
#include "TFile.h"
#include "TTree.h"
#include "TLatex.h"
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
			"H2tt", "ttbar", "WWleptonic",  "Z2tt","H2tm","H2te"};
	Int_t   MCcolors[11]={ kMagenta+3, kMagenta,kBlue+1,kOrange+1,kOrange,
			kGreen, kRed, kYellow, kCyan, kBlack, kBlack};

//	TString MCSamples[9]={"ZZ","H2WWleptonic", "WlepZmue","WincZtautau",
//				"H2tt", "WWleptonic",  "Z2tt","H2tm","H2te"};
//	Int_t   MCcolors[11]={kMagenta,kBlue+1,kOrange+1,kOrange,
//				kGreen, kYellow, kCyan, kBlack, kBlack};

	TCanvas* c1 = new TCanvas("canvasLog"+cut,"canvasLog"+cut,600,600);
	c1->SetLogy();
//	TCanvas* c2 = new TCanvas("c_diff","c_diff",600,600);
	TCanvas* c3 = new TCanvas("c_ratio"+cut,"c_ratio"+cut,600,600);
	TCanvas* c4 = new TCanvas("canvasStack"+cut,"canvasStack"+cut,600,600);	c4->SetLogy();
	TCanvas* c5 = new TCanvas("canvasStack2"+cut,"canvasStack2"+cut,600,600); c5->SetLogy();
	TCanvas* c6 = new TCanvas("canvasEM_ME","canvasEM_ME",600,600); c6->SetLogy();

	TLegend* leg = new TLegend(0.5,0.7,0.7,0.9);
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(1);

	THStack* hs = new THStack("ME_EM","ME_EM");
	THStack* hsStackedME = new THStack("stacked_ME",";"
			"M_{Collinear} (GeV);Events / 4 GeV");
	THStack* hsStackedEM = new THStack("stacked_EM","e#mu Channel;"
			"M_{Collinear} (GeV);Events / 4 GeV");
	THStack* hsEM_ME = new THStack("stacked_EM_ME",";"
				"M_{Collinear} (GeV);Events / 4 GeV");

	TH1D* EM_sum = new TH1D("EM_sum","bla",250,0,500);
	TH1D* ME_sum = new TH1D("ME_sum","bla",250,0,500);

	TFile* fs = new TFile(path+"H2tm"+cut+".root");
	TH1D* signal_ME = (TH1D*)fs->Get("ME_Mcoll"); signal_ME->SetLineColor(kBlack);
	signal_ME->SetLineStyle(2);
	signal_ME->SetName("signal_ME_Mcoll");
	TH1D* signal_EM = (TH1D*)fs->Get("EM_Mcoll"); signal_EM->SetLineColor(kBlack);
	signal_EM->SetLineStyle(2);
	signal_EM->SetName("signal_EM_Mcoll");

	double signalME_c = ME_Br*10;
	double signalEM_c = EM_Br*10;

//	cout<<"Br*10 = "<<signalME_c<<endl;

	double c[11]={0.9346, 0.1584,0.008744,0.00996899,0.001882,
			0.003268,0.2204,0.120508,0.2,signalME_c*0.006832495,signalEM_c*0.06671551};

//	double c[9]={0.1584,0.008743268,0.009968992,0.0153296,
//				0.00327,0.2204,0.118279925,signalME_c*0.013502715,signalEM_c*0.013502715};

	//group BG
	//diboson
	TFile* f_ZZ = new TFile(path+"ZZ"+cut+".root");
	TFile* f_WZ1 = new TFile(path+"WlepZmue"+cut+".root");
	TFile* f_WZ2 = new TFile(path+"WincZtautau"+cut+".root");
	TFile* f_WW = new TFile(path+"WWleptonic"+cut+".root");

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

	TFile *diboson_out = new TFile(path+"Diboson"+cut+".root","RECREATE");
	Diboson_ME->Write();
	Diboson_EM->Write();
	diboson_out->Close();

	//Higgs SM
	TFile* f_H2WW = new TFile(path+"H2WWleptonic"+cut+".root");
	TFile* f_H2tt = new TFile(path+"H2tt"+cut+".root");
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

	TFile *SMHiggs_out = new TFile(path+"SMHiggs"+cut+".root","RECREATE");
	SMHiggs_ME->Write();
	SMHiggs_EM->Write();
	SMHiggs_out->Close();

	TString MCSamplesGrouped[5]={"wt",	"SMHiggs", "ttbar", "Diboson",  "Z2tt"};
//	TString MCSamplesGrouped[5]={"SMHiggs", "Diboson",  "Z2tt"};
	Int_t   MCcolorsGrouped[5]={ kMagenta+3,kGreen, kRed, kYellow, kCyan};
//	Int_t   MCcolorsGrouped[5]={kGreen, kYellow, kCyan};
	double cGrouped[5]={0.9346, 1,0.120508602,1,0.2};
//	double cGrouped[3]={ 1,1,0.118279925};

	//BG
	for(int i=0; i<5; i++)
		{
			TFile* f = new TFile(path+MCSamplesGrouped[i]+cut+".root");
			TH1D* h_ME = (TH1D*)f->Get("ME_Mcoll");
			TH1D* h_EM = (TH1D*)f->Get("EM_Mcoll");
			TH1D* h_ME_l = (TH1D*)h_ME->Clone();
			TH1D* h_EM_l = (TH1D*)h_EM->Clone();
			h_ME->Scale(cGrouped[i]); h_EM->Scale(cGrouped[i]);
			h_ME_l->Scale(cGrouped[i]); h_EM_l->Scale(cGrouped[i]);
			h_ME->Rebin(2); h_EM->Rebin(2); h_ME_l->Rebin(2); h_EM_l->Rebin(2);
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
		TFile* f = new TFile(path+MCSamples[i]+cut+".root");
		TH1D* h_ME = (TH1D*)f->Get("ME_Mcoll");
		TH1D* h_EM = (TH1D*)f->Get("EM_Mcoll");
		h_ME->Scale(c[i]); h_EM->Scale(c[i]);
		h_ME->Rebin(2); h_EM->Rebin(2);
		h_ME->GetXaxis()->SetRangeUser(0,300); h_EM->GetXaxis()->SetRangeUser(0,300);
		h_ME->SetLineColor(MCcolors[i]); h_EM->SetLineColor(MCcolors[i]);
		h_ME->SetLineStyle(2);h_EM->SetLineStyle(2);
		EM_sum->Add(h_EM);
		ME_sum->Add(h_ME);
		TH1D* h_ratio = (TH1D*)h_ME->Clone("h_ratio");
		h_ratio->Divide(h_EM);
		h_ratio->GetXaxis()->SetRangeUser(0,300); h_ratio->GetYaxis()->SetRangeUser(0,20);
		hs->Add(h_ME); hs->Add(h_EM);
		c3->cd();
		h_ratio->Draw("sames");
	}

	TString MCSamplesGrouped2[5]={"Wt",	"SM Higgs", "t#bar{t}", "Diboson",  "Z#rightarrow#tau#tau"};
	//legend
	leg->AddEntry(signal_ME,"Signal","l");
	for(int j=4;j>=0;j--){
		TFile* f = new TFile(path+MCSamplesGrouped[j]+cut+".root");
		TH1D* h_ME = (TH1D*)f->Get("ME_Mcoll");
		h_ME->SetLineColor(MCcolorsGrouped[j]);
		h_ME->SetFillColor(MCcolorsGrouped[j]);
		leg->AddEntry(h_ME,MCSamplesGrouped2[j],"f");
	}

	ME_sum->GetXaxis()->SetRangeUser(0,300); EM_sum->GetXaxis()->SetRangeUser(0,300);
	ME_sum->SetLineColor(kBlue); ME_sum->SetFillColor(0);
	EM_sum->SetLineColor(kGreen+2); EM_sum->SetFillColor(0);
	ME_sum->SetOption("E1"); EM_sum->SetOption("E1");
	hsEM_ME->Add(ME_sum); hsEM_ME->Add(EM_sum);
	TLegend* leg2 = new TLegend(0.5,0.7,0.7,0.9);
	leg2->SetFillColor(kWhite); leg2->SetLineColor(0);
	leg2->AddEntry(ME_sum,"#mue sample","l");
	leg2->AddEntry(EM_sum,"e#mu sample","l");
	leg2->SetTextFont(42);
	TLatex* t = new TLatex(0.5,0.8,"#sqrt{s} = 8 TeV");
	t->SetTextSizePixels(18);
	c6->cd();
//	ME_sum->Draw("E1");
//	EM_sum->Draw("E1 sames");
//	hsEM_ME->GetXaxis()->SetRangeUser(0,300);
	hsEM_ME->Draw("nostack, e1");
	leg2->Draw();
	t->Draw();


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
//	hsStackedME->GetXaxis()->SetRangeUser(0,300);
	hsStackedME->Draw("hist");
//	signal_ME->Draw("sames");
	leg->SetLineColor(0);
	leg->Draw();

	c5->cd();
	signal_EM->Scale(c[9]);
	signal_EM->Rebin(2);
	hsStackedEM->Add(signal_EM);
//	hsStackedEM->GetXaxis()->SetRangeUser(0,300);
	hsStackedEM->Draw("hist");
	//	signal_EM->Draw("sames");
	leg->Draw();

	std::ostringstream strsME;
	strsME << ME_Br;
	std::string strBrME = strsME.str();

	std::ostringstream strsEM;
	strsEM << EM_Br;
	std::string strBrEM = strsEM.str();

	TFile *outputf = new TFile("MCStacked"+cut+"BR_ME"+strBrME+"BR_EM"+strBrEM+".root","RECREATE");

	hsStackedME->Write();
	hsStackedEM->Write();
	EM_sum->Write();
	ME_sum->Write();

	signal_ME->Write();

	c1->Write();
	c4->Write();
	c3->Write();
	c5->Write();
	c6->Write();

	outputf->Close();

}
