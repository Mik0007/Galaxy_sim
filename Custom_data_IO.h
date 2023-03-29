#ifndef CUST_DATA_IO
#define CUST_DATA_IO
//Custom_data_IO.h

#include <random>
#include <fstream>
#include <iostream>
#include "Gravitazione.h"
using namespace std;

void rand_normal_distribution(body3D* Galaxy, int totbodies, 
							  float massatot, float massa, float* Time)
{
	default_random_engine R;
	normal_distribution<float> randxy(0, 1*pow(10, 12));
	normal_distribution<float> randz(0, 1*pow(10, 10));
	normal_distribution<float> randtheta(0, 3.1415/12);
	
	float min_radius = 3*pow(10, 11);
	float max_radius = 2*pow(10, 12);
	
	float* pos = new float[3];
	float* vel = new float[3];
	
	for (int i = 1; i < totbodies; i++)
    {
    	setpos:
    	
    	pos[0] = randxy(R);
		pos[1] = randxy(R);
		pos[2] = randz(R);

		/*Mercury:
	    	Msun = 2*pow(10, 30) kg
	    	d = 57.9*pow(10, 9) m
    	
	    Trovo vel per orbita circolare:
	    	acc_centripeta = G*Msun/d^2 = 0.039 m/s^2
	    	vel = sqrt( G*Msun / d ) = 47 999 m/s
	    */
    	
		float d = sqrt( vec::squared( pos ) );
		if (min_radius > d || max_radius < d) goto setpos;
		
		float k = sqrt( 6.67*pow(10,-11) * massatot / d ) /d;
		
    	vel[0] = pos[1];
    	vel[1] = -pos[0];
    	vel[2] = 0;
    	vec::molt_scal(vel, k, vel);
    	vec::rotate(vel, randtheta(R));
    	
    	Galaxy[i].set_param(massa, pos, vel, Time);
	}
}

struct vec3D{
	float x, y, z;
};

void binary_export(string filename, body3D* Galaxy, int totbodies, bool vel = false)
{
	ofstream pen;
	pen.open( filename, ios::out | ios::binary );
	float* pos = new float[3];
	vec3D v;
	
	for (int i = 1; i < totbodies; i++)
	{
		if(vel == 1)
			pos = Galaxy[i].getvel();
		else
			pos = Galaxy[i].getpos();
			
		v.x = pos[0];
		v.y = pos[1];
		v.z = pos[2];
		
		pen.write((char*)(&v), sizeof(vec3D));
	}
	
	pen.close();
//	delete[] pos;
}

void binary_import(string filename, body3D* Galaxy, int totbodies, 
				   float massatot, float massa, float* Time, bool vel_bool = false)
{
	ifstream eye;
	eye.open( filename, ios::out | ios::binary );
	if (!eye)
	{
		cout << 333;
		return;
	}
	
	ifstream eye_vel;
	if (vel_bool == 1)
	{
		eye_vel.open( "Data/Binary_Data/vel_finali.dat", ios::out | ios::binary );
		if (!eye)
		{
			cout << 333;
			return;
		}
	}
	
	default_random_engine R;
	normal_distribution<float> randtheta(0, 3.1415/10);
	
	float* pos = new float[3];
	float* vel = new float[3];
	
	vec3D p, v;
	
	for (int i = 1; i < totbodies; i++)
	{
		eye.read( (char*) &p, sizeof(vec3D) );

		pos[0] = p.x;
		pos[1] = p.y;
		pos[2] = p.z;
		
		if (vel_bool == 1)
		{
			eye_vel.read( (char*) &v, sizeof(vec3D) );

			vel[0] = v.x;
			vel[1] = v.y;
			vel[2] = v.z;
		}
		else
		{
			//calcolo la velocità
			float d = sqrt( vec::squared( pos ) );
			float k = sqrt( 6.67*pow(10,-11) * massatot / d ) /d;
			
	    	vel[0] = pos[1];
	    	vel[1] = -pos[0];
	    	vel[2] = 0;
	    	vec::molt_scal(vel, k, vel);
	    	vec::rotate(vel, randtheta(R));
		}
    	
    	Galaxy[i].set_param(massa, pos, vel, Time);
	}
	
	eye.close();
}

vec3D* binary_import2(string filename, int totbodies)
{
	vec3D* v = new vec3D[totbodies];
	
	ifstream eye;
	eye.open( filename, ios::out | ios::binary );
	if (!eye)
	{
		cout << 333;
		return v;
	}
	
	for (int i = 0; i < totbodies; i++)
	{
		eye.read( (char*) &(v[i]), sizeof(vec3D) );
	}
	
	eye.close();
	
	return v;
}


class filewriter
{
	private:
		ofstream pen;
	
	public:
		filewriter(string filename, bool append = false)
		{
			if (append)
				pen.open( filename, ios::out | ios::binary | ios::app);
			else
				pen.open( filename, ios::out | ios::binary );
		}
		
		void en_write(double p_en, double k_en)
		{
			pen.write((char*)(&p_en), sizeof(double));
			pen.write((char*)(&k_en), sizeof(double));
		}
		
		
		void close()
		{
			pen.close();
		}
};



#endif
