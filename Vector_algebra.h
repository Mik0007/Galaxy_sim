#ifndef VEC_ALG
#define VEC_ALG

#include<cmath>
using namespace std;

class vec {
	public:
		static void molt_scal(float* res, float t, float* vec, int size = 3)//t*vec
		{
			for (int i = 0; i < size; i++)
				res[i] = t*vec[i]; 
		}
		
		static void linear_sum(float* res, float t, float* vec, float* vec0, int size = 3)//vec0 + t*vec
		{
			for (int i = 0; i < size; i++)
				res[i] = t*vec[i] + vec0[i];
		}
		
		static float squared(float* vec, int size = 3)//vec^2
		{
			float mod2 = 0;
			for (int i = 0; i < size; i++)
				mod2 += vec[i]*vec[i];
			return mod2;
		}
		
		static void sum(float* res, float* vec1, float* vec2, int size = 3)//vec1 + vec2
		{
			for (int i = 0; i < size; i++)
				res[i] = vec1[i] + vec2[i];
		}
		
		static void sum(float* res, float* vec1, float* vec2, float* vec3, int size = 3)//vec1 + vec2
		{
			for (int i = 0; i < size; i++)
				res[i] = vec1[i] + vec2[i] + vec3[i]; 
		}
		
		static void d(float* res, float* vec1, float* vec2, int size = 3)//distanza tra vettori
		{
			for (int i = 0; i < size; i++)
				res[i] = vec1[i] - vec2[i];
		}
		
		static void azzera(float* vec, int size = 3)
		{
			for (int i = 0; i < size; i++)
				vec[i] =  0;
		}
		
		static void copy(float* res, float* vec0, int size = 3)
		{
			for (int i = 0; i < size; i++)
				res[i] = vec0[i];
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
		
	private:
		vec(){}
};

#endif
