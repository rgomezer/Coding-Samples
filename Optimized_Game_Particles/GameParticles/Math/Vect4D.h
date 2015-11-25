// Vect4D.h
//
// This is a 4 dimensional Vect4D class
#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"
#include <xmmintrin.h>
#include <smmintrin.h> 
#include <assert.h>

// Foward Declarations
class Matrix;

// class
class Vect4D
{
public:
	friend class Matrix;

	Vect4D();	
	Vect4D( const float tx, const float ty, const float tz, const float tw = 1.0f );
	Vect4D(const Vect4D &tmp);
	Vect4D(const __m128 &tmp);
	~Vect4D();

	void norm(Vect4D &out );
	void set( const float tx, const float ty, const float tz, const float tw = 1.0f);
	
	Vect4D operator + ( const Vect4D &tmp ) const;
	Vect4D operator - ( const Vect4D &tmp ) const;
	Vect4D operator * ( const float scale ) const;
	Vect4D operator *= (const float scale) const;
	void operator = (const Vect4D &tmp );
	void operator = (const float scale);
	void operator += (const Vect4D &tmp );

	void operator -= (const Vect4D &tmp )
	{
		this->x -= tmp.x;
		this->y -= tmp.y;
		this->z -= tmp.z;
		this->w -= tmp.w;
	}
	void operator *= (const Vect4D &tmp)
	{
		this->x *= tmp.x;
		this->y *= tmp.y;
		this->z *= tmp.z;
		this->w *= tmp.w;
	}

	void Cross(const Vect4D &vin, Vect4D &vout);

	float &operator[]( VECT_ENUM e);

	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;

/*private:
	float x;
	float y;
	float z;
	float w;
	*/

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
#endif  //Vect4D.h

//Entering parts unknown where witchraft and black magic occurs
//Use at your own risk
#if 0
struct VmultS
{
	const Vect4D &v1;
	const float s1;

	VmultS(const Vect4D &t1, const float tf1)
		:v1(t1), s1(tf1)
	{
	}

	operator Vect4D()
	{
		__m128 tmp = _mm_set1_ps(s1);
		return Vect4D(_mm_mul_ps(v1.m, tmp));
		//return Vect4D()
	}
	
};

inline VmultS operator* (const Vect4D &a1, const float &af1)
{
	return VmultS(a1, af1);
}

struct VmultSmultS
{
	const Vect4D &v1;
	const float &s1;
	const float &s2;

	VmultSmultS(const VmultS &t1, const float tf2)
		:v1(t1.v1), s1(t1.s1), s2(tf2)
	{
	}

	operator Vect4D()
	{
		__m128 tmp = _mm_set1_ps(s2);
		return Vect4D(_mm_mul_ps(v1.m, tmp));
		//return Vect4D()
	}
};

inline VmultSmultS operator* (const VmultS &a1 , const float &af1)
{
	return VmultSmultS(a1, af1);
}
#endif

