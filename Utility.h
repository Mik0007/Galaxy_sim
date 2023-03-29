#ifndef UTIL
#define UTIL
//Utility.h

#include "Gravitazione.h"
using namespace std;


double evaluate_k_energy(body3D* Galaxy, int totbodies)//kinetik energy
{
	float en = 0;
	for (int i = 0; i < totbodies; i++)
	{
		en += Galaxy[i].getmass() * vec::squared(Galaxy[i].getvel()) / 2;
	}
	return en;
}

double evaluate_p_energy(body3D* Galaxy, int totbodies)//potential energy
{
	float en = 0;
	float* dist = new float[3];
	for (int i = 0; i < totbodies; i++)
	{    		
		for (int j = i+1; j < totbodies; j++)
		{	
			vec::d(dist, Galaxy[i].getpos(), Galaxy[j].getpos());
			en += - 2* 6.67*pow(10,-11) * Galaxy[i].getmass() * Galaxy[j].getmass() / sqrt( vec::squared(dist));
		}
	}
	return en;
}


#endif
