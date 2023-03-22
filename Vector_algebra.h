#ifndef VEC_ALG
#define VEC_ALG

#include<cmath>
using namespace std;

class vec {
	public:
		static float* molt_scal(float t, float* vec, int size = 3)//t*vec
		{
			float* v = new float[3];
			for (int i = 0; i < size; i++)
				v[i] = t*vec[i]; 
			return v;
		}
		
		static float* linear_sum(float t, float* vec, float* vec0, int size = 3)//vec0 + t*vec
		{
			float* v = new float[3];
			for (int i = 0; i < size; i++)
				v[i] = t*vec[i] + vec0[i]; 
			return v;
		}
		
		static float squared(float* vec, int size = 3)//vec^2
		{
			float mod2 = 0;
			for (int i = 0; i < size; i++)
				mod2 += vec[i]*vec[i];
			return mod2;
		}
		
		static float* sum(float* vec1, float* vec2, int size = 3)//vec1 + vec2
		{
			float* v = new float[3];
			for (int i = 0; i < size; i++)
				v[i] = vec1[i] + vec2[i]; 
			return v;
		}
		
		static float* sum(float* vec1, float* vec2, float* vec3, int size = 3)//vec1 + vec2
		{
			float* v = new float[3];
			for (int i = 0; i < size; i++)
				v[i] = vec1[i] + vec2[i] + vec3[i]; 
			return v;
		}
		
		static float* d(float* vec1, float* vec2, int size = 3)//distanza tra vettori
		{
			float* v = new float[3];
			for (int i = 0; i < size; i++)
				v[i] = vec1[i] - vec2[i]; 
			return v;
		}
		
		static void azzera(float* vec, int size = 3)
		{
			for (int i = 0; i < size; i++)
				vec[i] =  0;
		}
		
		static void copy(float* vec, float* vec0, int size = 3)
		{
			for (int i = 0; i < size; i++)
				vec[i] = vec0[i];
		}
		
		static float angle(float* vec1, float* vec2, int size = 3)
		{
			float P = 0;
			for (int i = 0; i < size; i++)
				P += vec1[i]*vec2[i];
			P /= sqrt( squared(vec1) );
			P /= sqrt( squared(vec2) );
			return acos(P);
		}
		
		static float cos2_angle(float* vec1, float* vec2, int size = 3)
		{
			//per capire vedi f precedente
			float P = 0;
			for (int i = 0; i < size; i++)
				P += vec1[i]*vec2[i];
			P = P*P;
			P /= squared(vec1);
			P /= squared(vec2);
			return P;
		}
		
		static void rotate(float* vec, float angle)//2D
		{
			float x = vec[0];
			float y = vec[1];
			float c = cos(angle);
			float s = sin(angle);
			
			vec[0] = x * c - y * s;
			vec[1] = x * s + y * c;
		}
		
//		static void rotate(float* vec, float theta, float phi)//3D
//		{
//			float x = vec[0];
//			float y = vec[1];
//			float z = vec[2]:
//				
//			float ct = cos(theta);
//			float st = sin(theta);
//			float cp = cos(phi);
//			float sp = sin(phi);

//			da finire

//			vec[0] = x * c - y * s;
//			vec[1] = x * s + y * c;
//		}
		
	private:
		vec(){}
};

#endif
