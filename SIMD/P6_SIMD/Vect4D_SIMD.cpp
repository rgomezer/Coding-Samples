#include "Vect4D_SIMD.h"
#include "Matrix_SIMD.h"

#include <xmmintrin.h>
#include <smmintrin.h> 

Vect4D_SIMD Vect4D_SIMD::operator * (const Matrix_SIMD &M) 
{		
	/*
		C.x = x * m.m0 + y*m.m4 + z*m.m8 + w * m.m12;
		C.y = x * m.m1 + y*m.m5 + z*m.m9 + w * m.m13;
		C.z = x * m.m2 + y*m.m6 + z*m.m10 + w * m.m14;
		C.w = x * m.m3 + y*m.m7 + z*m.m11 + w * m.m15;
	*/
	
	Vect4D_SIMD t;
	Vect4D_SIMD out;
	
	t.m = _mm_set1_ps(this->x);
	out.m = _mm_mul_ps(t.m, M.v0.m);

	t.m = _mm_set1_ps(this->y);
	out.m = _mm_add_ps(_mm_mul_ps(t.m, M.v1.m), out.m);

	t.m = _mm_set1_ps(this->z);
	out.m = _mm_add_ps(_mm_mul_ps(t.m, M.v2.m), out.m);

	t.m = _mm_set1_ps(this->w);
	out.m = _mm_add_ps(_mm_mul_ps(t.m, M.v3.m), out.m);

	return out;
};