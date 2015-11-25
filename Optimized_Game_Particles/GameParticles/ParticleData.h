#include "Particle.h"
#include <malloc.h>
#include <assert.h>
#include <new.h>

#ifndef PARTICLEDATA_H
#define PARTICLEDATA_H

//forward declare
class Particle;

struct ParticleData
{
public:
	Particle *p;
	Vect4D	position;
	float	life;
	Vect4D	velocity;
	Vect4D	scale;
	float	rotation;
	float	rotation_velocity;
	
	void* operator new (size_t size)
	{
		void * p = _aligned_malloc(size, 16);

		if (p == 0)
		{
			assert(p);
		}

		return p;
	}

	void operator delete (void *p)
	{
		_aligned_free(p);
	}
};

//extern ParticleData *data;

#endif