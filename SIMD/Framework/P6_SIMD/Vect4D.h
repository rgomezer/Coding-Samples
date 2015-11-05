#ifndef VECT4D_H
#define VECT4D_H

class Matrix;

class Vect4D
{
public:

	Vect4D()
		:x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	Vect4D(const Vect4D &t)
		: x(t.x), y(t.y), z(t.z), w(t.w)
	{};

	Vect4D(const float tx, const float ty, const float tz, const float tw )
		:x(tx), y(ty), z(tz), w(tw)
	{
	}


	~Vect4D()
	{
	}

	void operator = ( const Vect4D &tmp)
	{
		this->x = tmp.x;
		this->y = tmp.y;
		this->z = tmp.z;
		this->w = tmp.w;
	}

	void set(const float xVal, const float yVal, const float zVal, const float wVal )
	{
		this->x = xVal;
		this->y = yVal;
		this->z = zVal;
		this->w = wVal;
	}

	const Vect4D operator + (const Vect4D &t) const
	{
		return Vect4D(x + t.x, y + t.y, z + t.z, w + t.w);
	}

	void operator += (const Vect4D &t)
	{
		x += t.x;
		y += t.y;
		z += t.z;
		w += t.w;
	}

	const Vect4D operator - (const Vect4D &t) const
	{
		return Vect4D(x - t.x, y - t.y, z - t.z, w - t.w);
	}

	void operator -= (const Vect4D &t)
	{
		x -= t.x;
		y -= t.y;
		z -= t.z;
		w -= t.w;
	}

	const Vect4D operator * (const Vect4D &t) const
	{
		return Vect4D(x * t.x, y * t.y, z * t.z, w * t.w);
	};

	const Vect4D operator * (const float s) const
	{
		return Vect4D(x * s, y * s, z * s, w * s);
	}

	void operator *= (const Vect4D &t)
	{
		x *= t.x;
		y *= t.y;
		z *= t.z;
		w *= t.w;
	}

	const Vect4D operator / (const Vect4D &t) const
	{
		return Vect4D(x / t.x, y / t.y, z / t.z, w / t.w);
	}

	void operator /= (const Vect4D &t)
	{
		x /= t.x;
		y /= t.y;
		z /= t.z;
		w /= t.w;
	}
	
	Vect4D operator * (const Matrix &m);

	const float dot(const Vect4D &t )
	{
		return (x * t.x + y * t.y + z * t.z + w * t.w); 
	}

public:
	float x;
	float y;
	float z;
	float w;

};

#endif



