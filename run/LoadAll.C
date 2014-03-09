#include "TROOT.h"
#include "TSystem.h"

void LoadAll()
{

    gROOT->ProcessLine("#include <vector>");

    // Set the include path for all packages
    gSystem->AddIncludePath("-I/home/avitald/LFV/LFVPrivate");
    cout << gSystem->GetIncludePath() << endl;

    // Load package libraries
    gROOT->ProcessLine(".L ../cmt/LFVPrivate.C+");

    //Load additional macros
    gROOT->ProcessLine(".L ../macros/AsciiToNtuple.C+");
    gROOT->ProcessLine(".L ../macros/AddDetectorEffects.C+");
    gROOT->ProcessLine(".L ../macros/GetSample.C+");
    gROOT->ProcessLine(".L ../macros/Looper.C+");

}
