#include "Vect4D_SIMD.h"
#include "Matrix.h"


Vect4D_SIMD::Vect4D_SIMD()
	:x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
}

Vect4D_SIMD::Vect4D_SIMD(const Vect4D_SIMD &tmp)
	: x(tmp.x), y(tmp.y), z(tmp.z), w(tmp.w)
{
}

Vect4D_SIMD::Vect4D_SIMD(const __m128 &tmp)
	: m(tmp)
{
}

Vect4D_SIMD::~Vect4D_SIMD()
{
	//does nothing
}