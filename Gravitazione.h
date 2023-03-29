#ifndef GRAVIT
#define GRAVIT
//Gravitazione.h

#include "Vector_algebra.h"
#include<iostream>
#include<cmath>
using namespace std;

const float GRAV_CONST = 6.67*pow(10,-11);
//(N*m^2)/kg^2 = (kg*m/s^2 *m^2)/kg^2 = m^3/(kg* s^2)

float CostR, Angle; 
float* ZERO = new float[3];

float mod(float A, float B)
{
	while(A < 0) A += B;
	while(A > B) A -= B;
	return A;
}

class body3D
{
	private:
		float mass;
		
		float* pos = new float[3];
		float* vel = new float[3];
		float* acc = new float[3];
		
		float* time;
		
		float radius2, theta, theta_sup, theta_inf, radius2_inf, radius2_sup; //raggio^2
		
	public:
		body3D() 
		{		
			vec::azzera(acc);
			vec::azzera(vel);
			vec::azzera(pos);
		}
		
		void set_param(float Mass, float* Position, float* Velocity, float* Time)
		{
			mass = Mass;
			vec::copy(pos, Position);
			vec::copy(vel, Velocity);
			time = Time;
		}
		
		body3D(float Mass, float* Position, float* Velocity, float* Time)
		{
			vec::azzera(acc);
			set_param(Mass, Position, Velocity, Time);
		}	
		
		void update()
		{			
			//Suppongo che l'acc sia costante nel piccolo 
			//intervallo di tempo che considero
			// pos = t^2 * acc /2 + t * vel + pos
			vec::linear_sum(this->vel, *time, this->acc, this->vel);
			
			float* A = new float[3];
			float* B = new float[3];
			vec::molt_scal(A, (*time)*(*time)/2 , this->acc);
			vec::molt_scal(B, (*time) , this->vel);
			
			vec::sum(this->pos, A, B, this->pos);
			
			vec::azzera(this->acc);
			delete[] A;
			delete[] B;
		}
		
		void evaluate_force(body3D* b, bool optimise = false)
		{
			if (optimise == true)
			{
				/* CASO BUCO NERO / STELLA MASSICCIA CENTRALE*/
				if(    b->getradius2() < this->radius2_inf //Raggio
					|| b->getradius2() > this->radius2_sup
					|| b->gettheta()   < this->theta_inf
					|| b->gettheta()   > this->theta_sup             )
					{
	//					cout << 1;
						return;
					} 
			}			
			
			//m1 = this->mass
			//m1*a = F = G(m1*m2)/r^2
			//a = G*m2/r^2
			//vec(a) = ( G*m2/(r^2)^(3/2) ) * vec(r) = k * vec(r)
			
			float* dist = new float[3];
			vec::d(dist, b->getpos(), this->pos);
			float d2 = vec::squared( dist );
			float k = ( GRAV_CONST * b->getmass() ) / ( d2 );
			
			float* acc1 = new float[3];
			float* force = new float[3];
			vec::molt_scal(acc1, (k / sqrt(d2)) , dist);
			vec::sum(this->acc, acc1, this->acc);
			
			vec::molt_scal(force, this->mass, acc1 );
			b->setforce( force );
			delete[] acc1;
			delete[] force;
			delete[] dist;
		}
		
		void setforce(float* force)
		{
			vec::linear_sum(this->acc, (-1/this->mass), force, this->acc );
		}
		
		void update_polar_coord()
		{
			float* dist = new float[3];
			vec::d(dist, ZERO, this->pos);
			this->radius2 = vec::squared( dist );
			delete[] dist;
			
			this->radius2_sup = this->radius2 * ( 1+ CostR );
			this->radius2_inf = this->radius2 * ( 1- CostR );
			
			this->theta = atan( this->pos[1] / this->pos[0] );
			
			if ( this->pos[0] <= 0 ) this->theta += 3.141592;
//			else if ( this->pos[1] < 0 ) this->theta += 2* 3.141592;
			
			this->theta_sup = mod( (this->theta + Angle), (2*3.141592) );
			this->theta_inf = mod( (this->theta - Angle), (2*3.141592) );
		}
		
		void set_Cost(float Mcorpo, float Mstella)
		{
			CostR = 3000 * Mcorpo / Mstella;
			Angle = atan( sqrt( CostR ) );
			vec::azzera(ZERO);
		}
		
		float getmass()
		{
			return mass;
		}
		
		float getradius2()
		{
			return radius2;
		}
		
		float gettheta()
		{
			return theta;
		}
		
		float* getpos()
		{
			float* pos2 = new float[3];
			vec::copy(pos2, pos);
			return pos2;
		}
		
		float* getvel()
		{
			float* pos2 = new float[3];
			vec::copy(pos2, vel);
			return pos2;
		}
};

#endif
