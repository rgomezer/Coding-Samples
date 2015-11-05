#ifndef VECT4D_SIMD_H
#define VECT4D_SIMD_H

#include <xmmintrin.h>
#include <smmintrin.h>  

class Matrix_SIMD;

class Vect4D_SIMD
{
public:

	Vect4D_SIMD()
		:x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	};

	Vect4D_SIMD(const __m128 &tmp)
		:m(tmp)
	{
	}

	Vect4D_SIMD(const float tx, const float ty, const float tz, const float tw)
		:x(tx), y(ty), z(tz), w(tw)
	{
	};

	~Vect4D_SIMD()
	{
	};

	void operator = ( const Vect4D_SIMD &tmp)
	{
		this->m = tmp.m;
	};

	void set(const float xVal, const float yVal, const float zVal, const float wVal)
	{
		this->m = _mm_setr_ps(xVal, yVal, zVal, wVal);
	};

	const Vect4D_SIMD operator + (const Vect4D_SIMD &tmp) const
	{
		return Vect4D_SIMD(_mm_add_ps(this->m, tmp.m));
	};

	void operator += (const Vect4D_SIMD &tmp)
	{
		this->m = _mm_add_ps(this->m, tmp.m);
	};

	const Vect4D_SIMD operator - (const Vect4D_SIMD &tmp) const
	{
		return Vect4D_SIMD(_mm_sub_ps(this->m, tmp.m));
	};

	void operator -= (const Vect4D_SIMD &tmp)
	{
		this->m = _mm_sub_ps(this->m, tmp.m);
	}

	const Vect4D_SIMD operator * (const Vect4D_SIMD &tmp) const
	{
		return Vect4D_SIMD(_mm_mul_ps(this->m, tmp.m));
	};

	void operator *= (const Vect4D_SIMD &tmp)
	{
		this->m = _mm_mul_ps(this->m, tmp.m);
	}

	const Vect4D_SIMD operator / (const Vect4D_SIMD &tmp) const
	{
		return Vect4D_SIMD(_mm_div_ps(this->m, tmp.m));
	};

	void operator /= (const Vect4D_SIMD &tmp)
	{
		this->m = _mm_div_ps(this->m, tmp.m);
	}

	float dot(const Vect4D_SIMD &tmp )
	{
		float store = 0.0f;

		//The simple and slow ass way of doing it
		//this->m = _mm_dp_ps(this->m, tmp.m, 0xf1);
		//_mm_store_ss(&store, this->m);

		//The hard but fast way of doing it
		/*__m128 tempVec = _mm_setr_ps(tmp.x, tmp.y, tmp.z, tmp.w);
		__m128 tempInVec = _mm_setr_ps(this->x, this->y, this->z, this->w);
		
		__m128 t1;
		__m128 t2;

		t1 = _mm_mul_ps(tempInVec, tempVec);
		t2 = _mm_add_ps(t1, t1);*/

		//Do dot product calculation here
		const __m128 tx = _mm_set1_ps(this->x);
		const __m128 ty = _mm_set1_ps(this->y);
		const __m128 tz = _mm_set1_ps(this->z);
		const __m128 tw = _mm_set1_ps(this->w);
		
		__m128 t1;
		__m128 t2;

		t1 = _mm_set1_ps(tmp.x);
		t2 = _mm_mul_ps(tx, t1);
		t1 = _mm_set1_ps(tmp.y);
		t2 = _mm_add_ps(_mm_mul_ps(ty, t1), t2);
		t1 = _mm_set1_ps(tmp.z);
		t2 = _mm_add_ps(_mm_mul_ps(tz, t1), t2);
		t1 = _mm_set1_ps(tmp.w);
		t2 = _mm_add_ps(_mm_mul_ps(tw, t1), t2);
		
		_mm_store_ss(&store, t2);

		return store;
	};

	Vect4D_SIMD Vect4D_SIMD::operator * (const Matrix_SIMD &m);

public:

	// Level 4 complains nameless struct/union ...
	#pragma warning( disable : 4201)

	// anonymous union
	union 
	{
		__m128	m;

		// anonymous struct
		struct 
			{
			float x;
			float y;
			float z;
			float w;
			};
	};
};

#endif



