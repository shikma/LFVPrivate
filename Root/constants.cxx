#include "LFVPrivate/constants.h"

#include "TRandom.h"
#include "TH1.h"

TRandom RAND;

void InitExterns()
{
	RAND.SetSeed(12);
}
