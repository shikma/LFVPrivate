/*
 * Tools.h
 *
 *  Created on: Jan 9, 2014
 *      Author: avitald
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <vector>
//#include "LFVPrivate/SimData.h"

using namespace std;

class Tools {
public:
	Tools(vector<float> v_pt);
//	Tools(SimData* data);
	virtual ~Tools();
	bool SortPt(int a, int b);
	bool operator() (int a, int b){return m_v_pt[a]>m_v_pt[b];}
	void Setv_pt(vector<float> v){m_v_pt=v;}
private:
//	SimData* m_data;
	vector<float> m_v_pt;
};

#endif /* TOOLS_H_ */
