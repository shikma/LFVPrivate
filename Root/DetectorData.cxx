#include "TString.h"
#include "LFVPrivate/DetectorData.h"
#include "TMath.h"

namespace DetectorData {

float EfficiencyForParticle(TString particle,float Pt, float eta, float phi)
{
	if (abs(Pt+eta+phi) >= 0) { // This is here just so that I won't get a warning about unused parameters.
		if (!particle.CompareTo("electron")){
			if (eta > 1.35 && eta < 2.47)
				return 1-0.346314 * TMath::Power(1.03137,-4.28008 * Pt); // from the loose data Shikma sent on March 10th, 2014.
			return 0.9;
		}
		if (!particle.CompareTo("muon")){
			if (eta > 1.35 && eta < 2.47)
				return 1 - 0.631769 * TMath::Power(1.03271, -5.62599 * Pt); // from the same loose data.
			return 0.7;
		}
	}
	return 1; 	
}

float DeviationForParameter(TString parameterName, float parameterValue)
{
	if (parameterName == "electronPt")
		return 2;
	if (parameterName == "muonPt")
		return 5;
	if (parameterName == "metPt")
		return 0.2 * parameterValue;
	
	return 0; // Avital and Aielet said that smearing only for Pt.

	//infile = parameterName + "_data.csv";
	// @@@ find out how the smearing data appears in the ATLAS ref., put it in files for each parameter.
	// Locate the needed value of the parameter and take the corresponding variance.
	// Then root it to find the standard deviation.

}
}
