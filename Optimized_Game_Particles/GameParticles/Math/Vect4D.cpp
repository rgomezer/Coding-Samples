#include <math.h>
#include <assert.h>

#include "Vect4D.h"


Vect4D::Vect4D()
	:x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
}

Vect4D::Vect4D( const float tx, const float ty, const float tz, const float tw )
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect4D::Vect4D(const __m128 &tmp)
	: m(tmp)
{
}

Vect4D::Vect4D( const Vect4D &tmp)
	:x(tmp.x), y(tmp.y), z(tmp.z), w(tmp.w)
{
}

Vect4D::~Vect4D()
{
	// nothing to delete
}

/* Inverse square root function is based on the one used
*  by id software
*  https://en.wikipedia.org/wiki/Fast_inverse_square_root
*/
/*const float inverseSquareRoot(const float input)
{
	float temp;
	long i;
	float x2;
	const float threehalfs = 1.5F; // 3/2

	x2 = input * 0.5F;
	temp = input;

	// Black Magic happens here
	i = *(long *)&temp;
	i = 0x5f3759df - (i >> 1);
	temp = *(float *)&i;
	temp = temp * (threehalfs - (x2 * temp * temp));   // 1st iteration

	return temp;
}*/

void Vect4D::norm(Vect4D& out)
{
	//float mag = 1.0f/sqrtf( this->x * this->x + this->y * this->y + this->z * this->z );
	float mag = 0.0f;
	
	//Do dot product calculation here
	const __m128 tx = _mm_set1_ps(this->x);
	const __m128 ty = _mm_set1_ps(this->y);
	const __m128 tz = _mm_set1_ps(this->z);

	__m128 t2;
	__m128 t1;

	t2 = _mm_mul_ps(tx, tx);
	t2 = _mm_add_ps(_mm_mul_ps(ty, ty), t2);
	t2 = _mm_add_ps(_mm_mul_ps(tz, tz), t2);
	
	t1 = _mm_rsqrt_ps(t2);
	
	_mm_store_ss(&mag, t1);
	
	if( 0.0001f < mag )
	{
		__m128 tmp = _mm_set1_ps(mag);
		out.m = _mm_mul_ps(this->m, tmp);
		out.w = 1.0f;
	}
}

Vect4D Vect4D::operator + ( const Vect4D &tmp ) const
{
	//return Vect4D(this->x + tmp.x, this->y + tmp.y, this->z + tmp.z);
	return Vect4D(_mm_add_ps(this->m, tmp.m));
}

Vect4D Vect4D::operator - ( const Vect4D &tmp ) const
{
	//return Vect4D(this->x - tmp.x, this->y - tmp.y, this->z - tmp.z);
	return Vect4D(_mm_sub_ps(this->m, tmp.m));
}

Vect4D Vect4D::operator *(const float scale) const
{
	//return Vect4D(this->x * scale, this->y * scale, this->z * scale);
	__m128 tmp = _mm_set1_ps(scale);
	return Vect4D(_mm_mul_ps(this->m, tmp));
}

Vect4D Vect4D::operator *=(const float scale) const
{
	//return Vect4D(this->x * scale, this->y * scale, this->z * scale);
	__m128 tmp = _mm_set1_ps(scale);
	return Vect4D(_mm_mul_ps(this->m, tmp));
}

void Vect4D::operator = (const Vect4D &tmp)
{
	/*this->x = tmp.x;
	this->y = tmp.y;
	this->z = tmp.z;*/
	this->m = tmp.m;
}

void Vect4D::operator = (const float scale)
{
	/*this->x = scale;
	this->y = scale;
	this->z = scale;*/
	this->m = _mm_set1_ps(scale);
}

void Vect4D::operator += (const Vect4D &tmp )
{
	/*this->x += tmp.x;
	this->y += tmp.y;
	this->z += tmp.z;*/
	this->m = _mm_add_ps(this->m, tmp.m);
}


#if 1
float& Vect4D::operator[]( VECT_ENUM e )
{
	switch(e)
	{
	case 0:
			return x;
			break;
	case 1:
			return y;
			break;
	case 2: 
			return z;
			break;
	case 3:
			return w;
			break;
	default:
			assert(0);
			return x;
	}
}
#endif

void Vect4D::Cross( const Vect4D& vin, Vect4D& vout)
{
	vout.x = (y*vin.z - z*vin.y);
	vout.y = (z*vin.x - x*vin.z);
	vout.z = (x*vin.y - y*vin.x);
	vout.w = 1.0f;
}

void Vect4D::set(const float tx, const float ty, const float tz, const float tw)
{
	/*this->x = tx;
	this->y = ty;
	this->z = tz;
	this->w = tw;*/
	this->m = _mm_setr_ps(tx, ty, tz, tw);
}

float Vect4D::getX() const
{
	return this->x;
}

float Vect4D::getY() const
{ 
	return this->y;
}

float Vect4D::getZ() const
{
	return this->z;
}

float Vect4D::getW() const
{
	return this->w;
}

// End of file