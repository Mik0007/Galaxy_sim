#ifndef GRAVIT
#define GRAVIT
//Gravitazione.h

#include "Vector_algebra.h"
#include<iostream>
using namespace std;

const float GRAV_CONST = 6.67*pow(10,-11);
//(N*m^2)/kg^2 = (kg*m/s^2 *m^2)/kg^2 = m^3/(kg* s^2)

/*
332,132,231,233, (spigoli della faccio di y = +1)
312,112,213,211, (spigoli della faccio di y = -1)

323,123,213,233, (spigoli della faccio di z = +1)
321,121,231,211, (spigoli della faccio di z = -1)
*/

const bool vicini[26][26] = {//322,122,232,212,223,221, (facce)
							 //332,312,323,321, (spigoli della faccio di x = +1)
							 //132,112,123,121, (spigoli della faccio di x = -1)
							 //213,231,211,233  (spigoli con x = 0)
							 //333,331,313,133,113,131,311,111 (vertici) 
						//facce
						{0,0,0,0,0,0, 1,1,1,1, 0,0,0,0, 0,0,0,0, 1,1,1,0,0,0,1,0},
						{0,0,0,0,0,0, 0,0,0,0, 1,1,1,1, 0,0,0,0, 0,0,0,1,1,1,0,1},
						{0,0,0,0,0,0, 1,0,0,0, 1,0,0,0, 0,1,0,1, 1,1,0,1,0,1,0,0},
						{0,0,0,0,0,0, 0,1,0,0, 0,1,0,0, 1,0,1,0, 0,0,1,0,1,0,1,1},
						{0,0,0,0,0,0, 0,0,1,0, 0,0,1,0, 1,0,0,1, 1,0,1,1,1,0,0,0},
						{0,0,0,0,0,0, 0,0,0,1, 0,0,0,1, 0,1,1,0, 0,1,0,0,0,1,1,1},
						//spigoli della faccio di x = +1
						{1,0,1,0,0,0, 0,0,1,1, 0,0,0,0, 0,1,0,1, 1,1,0,0,0,0,0,0},
						{1,0,0,1,0,0, 0,0,1,1, 0,0,0,0, 1,0,1,0, 0,0,1,0,0,0,1,0},
						{1,0,0,0,1,0, 1,1,0,0, 0,0,0,0, 1,0,0,1, 1,0,1,0,0,0,0,0},
						{1,0,0,0,0,1, 1,1,0,0, 0,0,0,0, 0,1,1,0, 0,1,0,0,0,0,1,0},
						//spigoli della faccio di x = -1
						{0,1,1,0,0,0, 0,0,0,0, 0,0,1,1, 0,1,0,1, 0,0,0,1,0,1,0,0},
						{0,1,0,1,0,0, 0,0,0,0, 0,0,1,1, 1,0,1,0, 0,0,0,0,1,0,0,1},
						{0,1,0,0,1,0, 0,0,0,0, 1,1,0,0, 1,0,0,1, 0,0,0,1,1,0,0,0},
						{0,1,0,0,0,1, 0,0,0,0, 1,1,0,0, 0,1,1,0, 0,0,0,0,0,1,0,1},
						//spigoli con x = 0
						{0,0,0,1,1,0, 0,1,1,0, 0,1,1,0, 0,0,0,0, 0,0,1,0,1,0,0,0},
						{0,0,1,0,0,1, 1,0,0,1, 1,0,0,1, 0,0,0,0, 0,1,0,0,0,1,0,0},
						{0,0,0,1,0,1, 0,1,0,1, 0,1,0,1, 0,0,0,0, 0,0,0,0,0,0,1,1},
						{0,0,1,0,1,0, 1,0,1,0, 1,0,1,0, 0,0,0,0, 1,0,0,1,0,0,0,0},
						//vertici
						{1,0,1,0,1,0, 1,0,1,0, 0,0,0,0, 0,0,0,1, 0,0,0,0,0,0,0,0},
						{1,0,1,0,0,1, 1,0,0,1, 0,0,0,0, 0,1,0,0, 0,0,0,0,0,0,0,0},
						{1,0,0,1,1,0, 0,1,1,0, 0,0,0,0, 1,0,0,0, 0,0,0,0,0,0,0,0},
						{0,1,1,0,1,0, 0,0,0,0, 1,0,1,0, 0,0,0,1, 0,0,0,0,0,0,0,0},
						{0,1,0,1,1,0, 0,0,0,0, 0,1,1,0, 1,0,0,0, 0,0,0,0,0,0,0,0},
						{0,1,1,0,0,1, 0,0,0,0, 1,0,0,1, 0,1,0,0, 0,0,0,0,0,0,0,0},
						{1,0,0,1,0,1, 0,1,0,1, 0,0,0,0, 0,0,1,0, 0,0,0,0,0,0,0,0},
						{0,1,0,1,0,1, 0,0,0,0, 0,1,0,1, 0,0,1,0, 0,0,0,0,0,0,0,0}
						}; 

class body3D
{
	private:
		float mass;
		
		float* pos = new float[3];
		float* vel = new float[3];
		float* acc = new float[3];
		
		float* time;
		
		short int ang_section = 0;
		//1xx = (x=-1), 2xx = (x=0), 3xx = (x=1),
		//x1x = (y=-1), x2x = (y=0), x3x = (y=1),
		//xx1 = (z=-1), xx2 = (z=0), xx3 = (x=1)
		short int ang_n = 0; //numero 0-25 della colonna/riga 
		
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
			
			evaluate_ang_section();
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
			this->vel = vec::linear_sum(*time, this->acc, this->vel);
			
			float* A;
			float* B;
			A = vec::molt_scal( (*time)*(*time)/2 , this->acc);
			B = vec::molt_scal( (*time) , this->vel);
			
			this->pos = vec::sum(A, B, this->pos);
			evaluate_ang_section();
			
			vec::azzera(this->acc);
			delete[] A;
			delete[] B;
		}
		
		void evaluate_force(body3D b, bool optimise = false)
		{
			if (optimise == true)
				if ( check_ang_section(b.getang()) == 0)
					return;
//			cout << 1;

			//m1 = this->mass
			//m1*a = F = G(m1*m2)/r^2
			//a = G*m2/r^2
			//vec(a) = ( G*m2/(r^2)^(3/2) ) * vec(r) = k * vec(r)
			
			float* dist = vec::d(b.getpos(), this->pos);
			float d2 = vec::squared( dist );
			float k = ( GRAV_CONST * b.getmass() ) / ( d2 );
			
			if (optimise == true)
			{
				/* CASO BUCO NERO / STELLA MASSICCIA CENTRALE*/
				if( (k*k) < ( 0.1 * vec::squared(this->acc)))
				{
//					cout << 1;
					return;
				} 
			}

			float* acc1 = vec::molt_scal( (k / sqrt(d2)) , dist);
			this->acc = vec::sum(acc1, this->acc);
			
			b.setforce( vec::molt_scal( this->mass, acc1 ) );
			delete[] acc1;
		}
		
		bool check_ang_section(int ang2)
		{
			//1xx = (x=-1), 2xx = (x=0), 3xx = (x=1),
			//x1x = (y=-1), x2x = (y=0), x3x = (y=1),
			//xx1 = (z=-1), xx2 = (z=0), xx3 = (z=1)
			
			return vicini[this->ang_n][ang2];
		}
		
		void evaluate_ang_section()
		{
			//1xx = (x=-1), 2xx = (x=0), 3xx = (x=1),
			//x1x = (y=-1), x2x = (y=0), x3x = (y=1),
			//xx1 = (z=-1), xx2 = (z=0), xx3 = (z=1)
			this->ang_section = 0;
			
			float value = this->pos[1] / this->pos[0];
			if(this->pos[0] > 0)
			{
				if ( value > 2.41421) // y/x > tan(3*pi/8)
				{
					//x = 0, y = 1
					this->ang_section += 230;
				}
				else if ( value > 0.41421) // y/x > tan(pi/8)
				{
					//x = 1, y= 1
					this->ang_section += 330;
				}
				else if ( value > -0.41421)
				{
					//x = 1, y= 0
					this->ang_section += 320;
				}
				else if ( value > -2.41421)
				{
					//x = 1, y= -1
					this->ang_section += 310;
				}
				else
				{
					//x = 0, y= -1
					this->ang_section += 210;
				}
			}
			else
			{
				if ( value > 2.41421) // y/x > tan(3*pi/8)
				{
					//x = 0, y = -1
					this->ang_section += 210;
				}
				else if ( value > 0.41421) // y/x > tan(pi/8)
				{
					//x = -1, y = -1
					this->ang_section += 110;
				}
				else if ( value > -0.41421)
				{
					//x = -1, y = 0
					this->ang_section += 120;
				}
				else if ( value > -2.41421)
				{
					//x = -1, y = 1
					this->ang_section += 130;
				}
				else
				{
					//x = 0, y = 1
					this->ang_section += 230;
				}
			}
			
			value = this->pos[2] / this->pos[0];
			if(this->pos[0] > 0)
			{
//				if ( value > 2.41421) // z/x > tan(3*pi/8)
//				{
//					//x = 0, z = 1
//					this->ang_section += 3;
//				}
				if ( value > 0.41421) // z/x > tan(pi/8)
				{
					//x = 1, z = 1
					this->ang_section += 3;
				}
				else if ( value > -0.41421)
				{
					//x = 1, z = 0
					this->ang_section += 2;
				}
//				else if ( value > -2.41421)
//				{
//					//x = 1, z = -1
//					this->ang_section += 1;
//				}
				else
				{
					//x = 0, z = -1
					this->ang_section += 1;
				}
			}
			else
			{
//				if ( value > 2.41421) // z/x > tan(3*pi/8)
//				{
//					//x = 0, z = -1
//					this->ang_section += 1;
//				}
				if ( value > 0.41421) // z/x > tan(pi/8)
				{
					//x = -1, z = -1
					this->ang_section += 1;
				}
				else if ( value > -0.41421)
				{
					//x = -1, z = 0
					this->ang_section += 2;
				}
//				else if ( value > -2.41421)
//				{
//					//x = -1, z = 1
//					this->ang_section += 3;
//				}
				else
				{
					//x = 0, z = 1
					this->ang_section += 3;
				}
			}
			
			//assegno ang_n ad ogni ang_section
			{
			//322,122,232,212,223,221, (facce)
			if (this->ang_section == 322) this->ang_n = 0;
			else if (this->ang_section == 122) this->ang_n = 1;
			else if (this->ang_section == 232) this->ang_n = 2;
			else if (this->ang_section == 212) this->ang_n = 3;
			else if (this->ang_section == 223) this->ang_n = 4;
			else if (this->ang_section == 221) this->ang_n = 5;
			
			//332,312,323,321, (spigoli della faccio di x = +1)
			else if (this->ang_section == 332) this->ang_n = 6;
			else if (this->ang_section == 312) this->ang_n = 7;
			else if (this->ang_section == 323) this->ang_n = 8;
			else if (this->ang_section == 321) this->ang_n = 9;
			
			//132,112,123,121, (spigoli della faccio di x = -1)
			else if (this->ang_section == 132) this->ang_n = 10;
			else if (this->ang_section == 112) this->ang_n = 11;
			else if (this->ang_section == 123) this->ang_n = 12;
			else if (this->ang_section == 121) this->ang_n = 13;
			
			//213,231,211,233  (spigoli con x = 0)
			else if (this->ang_section == 213) this->ang_n = 14;
			else if (this->ang_section == 231) this->ang_n = 15;
			else if (this->ang_section == 211) this->ang_n = 16;
			else if (this->ang_section == 233) this->ang_n = 17;
			
			//333,331,313,133,113,131,311,111 (vertici)
			else if (this->ang_section == 333) this->ang_n = 18;
			else if (this->ang_section == 331) this->ang_n = 19;
			else if (this->ang_section == 313) this->ang_n = 20;
			else if (this->ang_section == 133) this->ang_n = 21;
			else if (this->ang_section == 113) this->ang_n = 22;
			else if (this->ang_section == 131) this->ang_n = 23;
			else if (this->ang_section == 311) this->ang_n = 24;
			else if (this->ang_section == 111) this->ang_n = 25;
			}
		}
		
		void setforce(float* force)
		{
			this->acc = vec::linear_sum( (-1/this->mass), force, this->acc );
			delete[] force;
		}
		
		float getmass()
		{
			return mass;
		}
		
		int getang()
		{
			return ang_n;
		}
		
		int getang_section()
		{
			return ang_section;
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
