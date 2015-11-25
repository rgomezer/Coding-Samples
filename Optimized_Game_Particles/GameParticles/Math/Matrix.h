#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"
#include "Vect4D.h"
#include <xmmintrin.h>
#include <smmintrin.h> 

// forward declare
class Vect4D;

// class
class Matrix
{
public:

	// local enumerations
	enum MatrixRowEnum
	{
		MATRIX_ROW_0,
		MATRIX_ROW_1,
		MATRIX_ROW_2,
		MATRIX_ROW_3
	};

	Matrix();	
	Matrix(const Matrix& t );

	Matrix(Vect4D &tV0, Vect4D &tV1, Vect4D &tV2, Vect4D &tV3)
	{
		v0.m = _mm_setr_ps(tV0.x, tV0.y, tV0.z, tV0.w);
		v1.m = _mm_setr_ps(tV1.x, tV1.y, tV1.z, tV1.w);
		v2.m = _mm_setr_ps(tV2.x, tV2.y, tV2.z, tV2.w);
		v3.m = _mm_setr_ps(tV3.x, tV3.y, tV3.z, tV3.w);
	}

	Matrix(const float tm0, const float tm1, const float tm2, const float tm3,
		   const float tm4, const float tm5, const float tm6, const float tm7, 
		   const float tm8, const float tm9, const float tm10, const float tm11, 
		   const float tm12, const float tm13, const float tm14, const float tm15);
	~Matrix();

	void set( const Vect4D &t );
	void get( Vect4D *vOut );

	void setIdentMatrix();
	void setTransMatrix(const Vect4D &t );
	void setScaleMatrix(const Vect4D &s );
	void setRotZMatrix( const float Z_Radians );

	//float &operator[]( INDEX_ENUM e);
	
	Matrix operator*( Matrix &t );
	Matrix operator*(const float s );

	float Determinant();
	
	Matrix GetAdjugate();
	Matrix& Matrix::operator/=(const float t);
	
	void Matrix::Inverse(Matrix &out );

	//Accessors galore!
	float getM0() const { return (m0); }
	float getM1() const { return (m1); }
	float getM2() const { return (m2); }
	float getM3() const { return (m3); }
	float getM4() const { return (m4); }
	float getM5() const { return (m5); }
	float getM6() const { return (m6); }
	float getM7() const { return (m7); }
	float getM8() const { return (m8); }
	float getM9() const { return (m9); }
	float getM10() const { return (m10); }
	float getM11() const { return (m11); }
	float getM12() const { return (m12); }
	float getM13() const { return (m13); }
	float getM14() const { return (m14); }
	float getM15() const{ return (m15); }

/*private:

	// ROW 0
	float m0;
	float m1;
	float m2;
	float m3;

	// ROW 1
	float m4;
	float m5;
	float m6;
	float m7;

	// ROW 2
	float m8;
	float m9;
	float m10;
	float m11;

	// ROW 3
	float m12;
	float m13;
	float m14;
	float m15;
	*/
#pragma warning( disable : 4201)
	union
	{
		struct 
		{
			Vect4D v0;
			Vect4D v1;
			Vect4D v2;
			Vect4D v3;
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

#endif  // Matrix.h

#if 0
//Entering parts unknown where witchraft and black magic occurs
struct MmultM
{
	const Matrix &v1;
	const Matrix &v2;

	MmultM(const Matrix &t1, const Matrix &t2)
		:v1(t1), v2(t2)
	{
	};

	operator Matrix()
	{

		return Matrix( (v1.getM0()*v2.getM0()) + (v1.getM1()*v2.getM4()) + (v1.getM2()*v2.getM8()) + (v1.getM3()*v2.getM12()),
					   (v1.getM0()*v2.getM1()) + (v1.getM1()*v2.getM5()) + (v1.getM2()*v2.getM9()) + (v1.getM3()*v2.getM13()),
					   (v1.getM0()*v2.getM2()) + (v1.getM1()*v2.getM6()) + (v1.getM2()*v2.getM10()) + (v1.getM3()*v2.getM14()),
					   (v1.getM0()*v2.getM3()) + (v1.getM1()*v2.getM7()) + (v1.getM2()*v2.getM11()) + (v1.getM3()*v2.getM15()),
					
					   (v1.getM4()*v2.getM0()) + (v1.getM5()*v2.getM4()) + (v1.getM6()*v2.getM8()) + (v1.getM7()*v2.getM12()),
					   (v1.getM4()*v2.getM1()) + (v1.getM5()*v2.getM5()) + (v1.getM6()*v2.getM9()) + (v1.getM7()*v2.getM13()),
					   (v1.getM4()*v2.getM2()) + (v1.getM5()*v2.getM6()) + (v1.getM6()*v2.getM10()) + (v1.getM7()*v2.getM14()),
					   (v1.getM4()*v2.getM3()) + (v1.getM5()*v2.getM7()) + (v1.getM6()*v2.getM11()) + (v1.getM7()*v2.getM15()),
					
					   (v1.getM8()*v2.getM0()) + (v1.getM9()*v2.getM4()) + (v1.getM10()*v2.getM8()) + (v1.getM11()*v2.getM12()),
					   (v1.getM8()*v2.getM1()) + (v1.getM9()*v2.getM5()) + (v1.getM10()*v2.getM9()) + (v1.getM11()*v2.getM13()),
					   (v1.getM8()*v2.getM2()) + (v1.getM9()*v2.getM6()) + (v1.getM10()*v2.getM10()) + (v1.getM11()*v2.getM14()),
					   (v1.getM8()*v2.getM3()) + (v1.getM9()*v2.getM7()) + (v1.getM10()*v2.getM11()) + (v1.getM11()*v2.getM15()),
					
					   (v1.getM12()*v2.getM0()) + (v1.getM13()*v2.getM4()) + (v1.getM14()*v2.getM8()) + (v1.getM15()*v2.getM12()),
					   (v1.getM12()*v2.getM1()) + (v1.getM13()*v2.getM5()) + (v1.getM14()*v2.getM9()) + (v1.getM15()*v2.getM13()),
					   (v1.getM12()*v2.getM2()) + (v1.getM13()*v2.getM6()) + (v1.getM14()*v2.getM10()) + (v1.getM15()*v2.getM14()),
					   (v1.getM12()*v2.getM3()) + (v1.getM13()*v2.getM7()) + (v1.getM14()*v2.getM11()) + (v1.getM15()*v2.getM15()) );
	}
};

inline MmultM operator* (const Matrix &a1, const Matrix &a2)
{
	return MmultM(a1, a2);
}


struct MmultMmultM
{
	const Matrix &v1;
	const Matrix &v2;
	const Matrix &v3;

	MmultMmultM(const MmultM &t1, const Matrix &t2)
		:v1(t1.v1), v2(t1.v2), v3(t2)
	{
	};

	operator Matrix()
	{

		return Matrix( (v1.getM0()*v2.getM0()) + (v1.getM1()*v2.getM4()) + (v1.getM2()*v2.getM8()) + (v1.getM3()*v2.getM12()),
			(v1.getM0()*v2.getM1()) + (v1.getM1()*v2.getM5()) + (v1.getM2()*v2.getM9()) + (v1.getM3()*v2.getM13()),
			(v1.getM0()*v2.getM2()) + (v1.getM1()*v2.getM6()) + (v1.getM2()*v2.getM10()) + (v1.getM3()*v2.getM14()),
			(v1.getM0()*v2.getM3()) + (v1.getM1()*v2.getM7()) + (v1.getM2()*v2.getM11()) + (v1.getM3()*v2.getM15()),

			(v1.getM4()*v2.getM0()) + (v1.getM5()*v2.getM4()) + (v1.getM6()*v2.getM8()) + (v1.getM7()*v2.getM12()),
			(v1.getM4()*v2.getM1()) + (v1.getM5()*v2.getM5()) + (v1.getM6()*v2.getM9()) + (v1.getM7()*v2.getM13()),
			(v1.getM4()*v2.getM2()) + (v1.getM5()*v2.getM6()) + (v1.getM6()*v2.getM10()) + (v1.getM7()*v2.getM14()),
			(v1.getM4()*v2.getM3()) + (v1.getM5()*v2.getM7()) + (v1.getM6()*v2.getM11()) + (v1.getM7()*v2.getM15()),

			(v1.getM8()*v2.getM0()) + (v1.getM9()*v2.getM4()) + (v1.getM10()*v2.getM8()) + (v1.getM11()*v2.getM12()),
			(v1.getM8()*v2.getM1()) + (v1.getM9()*v2.getM5()) + (v1.getM10()*v2.getM9()) + (v1.getM11()*v2.getM13()),
			(v1.getM8()*v2.getM2()) + (v1.getM9()*v2.getM6()) + (v1.getM10()*v2.getM10()) + (v1.getM11()*v2.getM14()),
			(v1.getM8()*v2.getM3()) + (v1.getM9()*v2.getM7()) + (v1.getM10()*v2.getM11()) + (v1.getM11()*v2.getM15()),

			(v1.getM12()*v2.getM0()) + (v1.getM13()*v2.getM4()) + (v1.getM14()*v2.getM8()) + (v1.getM15()*v2.getM12()),
			(v1.getM12()*v2.getM1()) + (v1.getM13()*v2.getM5()) + (v1.getM14()*v2.getM9()) + (v1.getM15()*v2.getM13()),
			(v1.getM12()*v2.getM2()) + (v1.getM13()*v2.getM6()) + (v1.getM14()*v2.getM10()) + (v1.getM15()*v2.getM14()),
			(v1.getM12()*v2.getM3()) + (v1.getM13()*v2.getM7()) + (v1.getM14()*v2.getM11()) + (v1.getM15()*v2.getM15()) );
	}
};

inline MmultMmultM operator* (const MmultM &a1, const Matrix &a2)
{
	return MmultMmultM(a1, a2);
}

struct MmultMmultMmultM
{
	const Matrix &v1;
	const Matrix &v2;
	const Matrix &v3;
	const Matrix &v4;

	MmultMmultMmultM(const MmultMmultM &t1, const Matrix &t2)
		:v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t2)
	{
	};

	operator Matrix()
	{

		return Matrix(v1.getX() + v2.getX() + v3.getX() + v4.getX(),
			v1.getY() + v2.getY() + v3.getY() + v4.getY());
	}
};

inline MmultMmultMmultM operator* (const MmultMmultM &a1, const Matrix &a2)
{
	return MmultMmultMmultM(a1, a2);
}

struct MmultMmultMmultMmultM
{
	const Matrix &v1;
	const Matrix &v2;
	const Matrix &v3;
	const Matrix &v4;
	const Matrix &v5;

public:

	MmultMmultMmultMmultM(const MmultMmultMmultM &t1, const Matrix &t2)
		:v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t1.v4), v5(t2)
	{
	};

	operator Matrix()
	{

		return Matrix(v1.getX() + v2.getX() + v3.getX() + v4.getX() + v5.getX(),
			v1.getY() + v2.getY() + v3.getY() + v4.getY() + v5.getY());
	}
};

inline MmultMmultMmultMmultM operator* (const MmultMmultMmultM &a1, const Matrix &a2)
{
	return MmultMmultMmultMmultM(a1, a2);
}
#endif
