//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec 12 00:36:24 2013 by ROOT version 5.34/09
// from TTree t/Reconst ntuple
// found on file: Yevgeny.root
//////////////////////////////////////////////////////////

#ifndef SimData_h
#define SimData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class SimData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           evt;
   Int_t           nPhoton;
   Float_t         photonPt[10];   //[nPhoton]
   Float_t         photonEta[10];   //[nPhoton]
   Float_t         photonPhi[10];   //[nPhoton]
   Int_t           nElectron;
   Float_t         electronPt[10];   //[nElectron]
   Float_t         electronEta[10];   //[nElectron]
   Float_t         electronPhi[10];   //[nElectron]
   Int_t           electronQ[10];   //[nElectron]
   Int_t           electronTag[10];   //[nElectron]
   Float_t         electronCal02[10];   //[nElectron]
   Float_t         electronCal03[10];   //[nElectron]
   Float_t         electronCal04[10];   //[nElectron]
   Float_t         electronTrk02[10];   //[nElectron]
   Float_t         electronTrk03[10];   //[nElectron]
   Float_t         electronTrk04[10];   //[nElectron]
   Float_t		   electronSign[10];
   Int_t           nMuon;
   Float_t         muonPt[10];   //[nMuon]
   Float_t         muonEta[10];   //[nMuon]
   Float_t         muonPhi[10];   //[nMuon]
   Int_t           muonQ[10];   //[nMuon]
   Int_t           muonTag[10];   //[nMuon]
   Float_t         muonCal02[10];   //[nMuon]
   Float_t         muonCal03[10];   //[nMuon]
   Float_t         muonCal04[10];   //[nMuon]
   Float_t         muonTrk02[10];   //[nMuon]
   Float_t         muonTrk03[10];   //[nMuon]
   Float_t         muonTrk04[10];   //[nMuon]
   Float_t		   muonSign[10];
   Int_t           nTau;
   Float_t         tauPt[10];   //[nTau]
   Float_t         tauEta[10];   //[nTau]
   Float_t         tauPhi[10];   //[nTau]
   Int_t           tauQ[10];   //[nTau]
   Int_t           tauTag[10];   //[nTau]
   Float_t         tauCal02[10];   //[nTau]
   Float_t         tauCal03[10];   //[nTau]
   Float_t         tauCal04[10];   //[nTau]
   Float_t         tauTrk02[10];   //[nTau]
   Float_t         tauTrk03[10];   //[nTau]
   Float_t         tauTrk04[10];   //[nTau]
   Float_t		   tauSign[10];
   Int_t           nJet;
   Float_t         jetPt[10];   //[nJet]
   Float_t         jetEta[10];   //[nJet]
   Float_t         jetPhi[10];   //[nJet]
   Int_t           jetQ[10];   //[nJet]
   Int_t           jetTag[10];   //[nJet]
   Float_t         jetCal02[10];   //[nJet]
   Float_t         jetCal03[10];   //[nJet]
   Float_t         jetCal04[10];   //[nJet]
   Float_t         jetTrk02[10];   //[nJet]
   Float_t         jetTrk03[10];   //[nJet]
   Float_t         jetTrk04[10];   //[nJet]
   Float_t         metPt;
   Float_t         metEta;
   Float_t         metPhi;

   Float_t         sf_el_reco_eff[10];
   Float_t         sf_mu_reco_eff[10];

   // List of branches
   TBranch        *b_evt;   //!
   TBranch        *b_nPhoton;   //!
   TBranch        *b_photonPt;   //!
   TBranch        *b_photonEta;   //!
   TBranch        *b_photonPhi;   //!
   TBranch        *b_nElectron;   //!
   TBranch        *b_electronPt;   //!
   TBranch        *b_electronEta;   //!
   TBranch        *b_electronPhi;   //!
   TBranch        *b_electronQ;   //!
   TBranch        *b_electronTag;   //!
   TBranch        *b_electronCal02;   //!
   TBranch        *b_electronCal03;   //!
   TBranch        *b_electronCal04;   //!
   TBranch        *b_electronTrk02;   //!
   TBranch        *b_electronTrk03;   //!
   TBranch        *b_electronTrk04;   //!
   TBranch        *b_electronSign;
   TBranch        *b_nMuon;   //!
   TBranch        *b_muonPt;   //!
   TBranch        *b_muonEta;   //!
   TBranch        *b_muonPhi;   //!
   TBranch        *b_muonQ;   //!
   TBranch        *b_muonTag;   //!
   TBranch        *b_muonCal02;   //!
   TBranch        *b_muonCal03;   //!
   TBranch        *b_muonCal04;   //!
   TBranch        *b_muonTrk02;   //!
   TBranch        *b_muonTrk03;   //!
   TBranch        *b_muonTrk04;   //!
   TBranch        *b_muonSign;
   TBranch        *b_nTau;   //!
   TBranch        *b_tauPt;   //!
   TBranch        *b_tauEta;   //!
   TBranch        *b_tauPhi;   //!
   TBranch        *b_tauQ;   //!
   TBranch        *b_tauTag;   //!
   TBranch        *b_tauCal02;   //!
   TBranch        *b_tauCal03;   //!
   TBranch        *b_tauCal04;   //!
   TBranch        *b_tauTrk02;   //!
   TBranch        *b_tauTrk03;   //!
   TBranch        *b_tauTrk04;   //!
   TBranch        *b_tauSign;
   TBranch        *b_nJet;   //!
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_jetPhi;   //!
   TBranch        *b_jetQ;   //!
   TBranch        *b_jetTag;   //!
   TBranch        *b_jetCal02;   //!
   TBranch        *b_jetCal03;   //!
   TBranch        *b_jetCal04;   //!
   TBranch        *b_jetTrk02;   //!
   TBranch        *b_jetTrk03;   //!
   TBranch        *b_jetTrk04;   //!
   TBranch        *b_metPt;   //!
   TBranch        *b_metEta;   //!
   TBranch        *b_metPhi;   //!
   TBranch        *b_sf_el_reco_eff; //!
   TBranch        *b_sf_mu_reco_eff; //!

   SimData(TTree *tree=0);
   virtual ~SimData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SimData_cxx
SimData::SimData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Yevgeny.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Yevgeny.root");
      }
      f->GetObject("t",tree);

   }
   Init(tree);
}

SimData::~SimData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SimData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SimData::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SimData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("nPhoton", &nPhoton, &b_nPhoton);
   fChain->SetBranchAddress("photonPt", photonPt, &b_photonPt);
   fChain->SetBranchAddress("photonEta", photonEta, &b_photonEta);
   fChain->SetBranchAddress("photonPhi", photonPhi, &b_photonPhi);
   fChain->SetBranchAddress("nElectron", &nElectron, &b_nElectron);
   fChain->SetBranchAddress("electronPt", electronPt, &b_electronPt);
   fChain->SetBranchAddress("electronEta", electronEta, &b_electronEta);
   fChain->SetBranchAddress("electronPhi", electronPhi, &b_electronPhi);
   fChain->SetBranchAddress("electronQ", electronQ, &b_electronQ);
   fChain->SetBranchAddress("electronTag", electronTag, &b_electronTag);
   fChain->SetBranchAddress("electronCal02", electronCal02, &b_electronCal02);
   fChain->SetBranchAddress("electronCal03", electronCal03, &b_electronCal03);
   fChain->SetBranchAddress("electronCal04", electronCal04, &b_electronCal04);
   fChain->SetBranchAddress("electronTrk02", electronTrk02, &b_electronTrk02);
   fChain->SetBranchAddress("electronTrk03", electronTrk03, &b_electronTrk03);
   fChain->SetBranchAddress("electronTrk04", electronTrk04, &b_electronTrk04);
   fChain->SetBranchAddress("electronSign", electronSign, &b_electronSign);
   fChain->SetBranchAddress("nMuon", &nMuon, &b_nMuon);
   fChain->SetBranchAddress("muonPt", muonPt, &b_muonPt);
   fChain->SetBranchAddress("muonEta", muonEta, &b_muonEta);
   fChain->SetBranchAddress("muonPhi", muonPhi, &b_muonPhi);
   fChain->SetBranchAddress("muonQ", muonQ, &b_muonQ);
   fChain->SetBranchAddress("muonTag", muonTag, &b_muonTag);
   fChain->SetBranchAddress("muonCal02", muonCal02, &b_muonCal02);
   fChain->SetBranchAddress("muonCal03", muonCal03, &b_muonCal03);
   fChain->SetBranchAddress("muonCal04", muonCal04, &b_muonCal04);
   fChain->SetBranchAddress("muonTrk02", muonTrk02, &b_muonTrk02);
   fChain->SetBranchAddress("muonTrk03", muonTrk03, &b_muonTrk03);
   fChain->SetBranchAddress("muonTrk04", muonTrk04, &b_muonTrk04);
   fChain->SetBranchAddress("muonSign", muonSign, &b_muonSign);
   fChain->SetBranchAddress("nTau", &nTau, &b_nTau);
   fChain->SetBranchAddress("tauPt", tauPt, &b_tauPt);
   fChain->SetBranchAddress("tauEta", tauEta, &b_tauEta);
   fChain->SetBranchAddress("tauPhi", tauPhi, &b_tauPhi);
   fChain->SetBranchAddress("tauQ", tauQ, &b_tauQ);
   fChain->SetBranchAddress("tauTag", tauTag, &b_tauTag);
   fChain->SetBranchAddress("tauCal02", tauCal02, &b_tauCal02);
   fChain->SetBranchAddress("tauCal03", tauCal03, &b_tauCal03);
   fChain->SetBranchAddress("tauCal04", tauCal04, &b_tauCal04);
   fChain->SetBranchAddress("tauTrk02", tauTrk02, &b_tauTrk02);
   fChain->SetBranchAddress("tauTrk03", tauTrk03, &b_tauTrk03);
   fChain->SetBranchAddress("tauTrk04", tauTrk04, &b_tauTrk04);
   fChain->SetBranchAddress("tauSign", tauSign, &b_tauSign);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("jetPt", jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEta", jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("jetQ", jetQ, &b_jetQ);
   fChain->SetBranchAddress("jetTag", jetTag, &b_jetTag);
   fChain->SetBranchAddress("jetCal02", jetCal02, &b_jetCal02);
   fChain->SetBranchAddress("jetCal03", jetCal03, &b_jetCal03);
   fChain->SetBranchAddress("jetCal04", jetCal04, &b_jetCal04);
   fChain->SetBranchAddress("jetTrk02", jetTrk02, &b_jetTrk02);
   fChain->SetBranchAddress("jetTrk03", jetTrk03, &b_jetTrk03);
   fChain->SetBranchAddress("jetTrk04", jetTrk04, &b_jetTrk04);
   fChain->SetBranchAddress("metPt", &metPt, &b_metPt);
   fChain->SetBranchAddress("metEta", &metEta, &b_metEta);
   fChain->SetBranchAddress("metPhi", &metPhi, &b_metPhi);
   fChain->SetBranchAddress("metPhi", &metPhi, &b_metPhi);
   fChain->SetBranchAddress("sf_el_reco_eff", sf_el_reco_eff, &b_sf_el_reco_eff);
   fChain->SetBranchAddress("sf_mu_reco_eff", sf_mu_reco_eff, &b_sf_mu_reco_eff);
   
   Notify();
}

Bool_t SimData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SimData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SimData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SimData_cxx
