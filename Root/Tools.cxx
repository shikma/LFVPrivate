/*
 * Tools.cxx
 *
 *  Created on: Jan 9, 2014
 *      Author: avitald
 */

#include "../LFVPrivate/Tools.h"
Tools::Tools(vector<float> v_pt):
m_v_pt(v_pt)
{
	// TODO Auto-generated constructor stub


}
//Tools::Tools(SimData* data):
//m_data(data)
//{
//	// TODO Auto-generated constructor stub
//
//
//}


bool Tools::SortPt(int a, int b)
{
	return m_v_pt[a]>m_v_pt[b];
}
Tools::~Tools() {
	// TODO Auto-generated destructor stub
}
