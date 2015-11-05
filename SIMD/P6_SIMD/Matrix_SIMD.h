#ifndef MATRIX_SIMD_H
#define MATRIX_SIMD_H

#include "Vect4D_SIMD.h"

#include <xmmintrin.h>
#include <smmintrin.h> 




class Matrix_SIMD
{
public:
	Matrix_SIMD()
	{
	}

	Matrix_SIMD( Vect4D_SIMD &tV0, Vect4D_SIMD &tV1, Vect4D_SIMD &tV2, Vect4D_SIMD &tV3)
	{
		v0.m = _mm_setr_ps(tV0.x, tV0.y, tV0.z, tV0.w);
		v1.m = _mm_setr_ps(tV1.x, tV1.y, tV1.z, tV1.w);
		v2.m = _mm_setr_ps(tV2.x, tV2.y, tV2.z, tV2.w);
		v3.m = _mm_setr_ps(tV3.x, tV3.y, tV3.z, tV3.w);
	}

	Matrix_SIMD operator * ( Matrix_SIMD & t);

	
public:

	union 
		{
		struct 
			{
			Vect4D_SIMD v0;
			Vect4D_SIMD v1;
			Vect4D_SIMD v2;
			Vect4D_SIMD v3;
			};

		struct 
			{
			float m0;
			float m1;
			float m2;
			float m3;
			float m4;
			float m5;
			float m6;	
			float m7;
			float m8;
			float m9;
			float m10;
			float m11;
			float m12;
			float m13;
			float m14;
			float m15;
			};
		};
};

#endif