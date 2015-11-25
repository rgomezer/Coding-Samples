#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"
#include "Matrix.h"
#include "ParticleData.h"
#include <malloc.h>
#include <new.h>
#include <assert.h>

//forward declare
class Particle;

class Particle
{
public:
	friend class ParticleEmitter;
	
	Particle();	
	~Particle();
	//void Update(const float& time_elapsed);
	void CopyDataOnly(const ParticleData &p );

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

private:
	Particle *next;
	Particle *prev;
	ParticleData *data;
	void *buffer;

	Matrix tmp;
	Vect4D tmp_Row0;
	Vect4D tmp_Row1;
	Vect4D tmp_Row2;
	Vect4D tmp_Row3;
	
};


#endif //PARTICLE_H
