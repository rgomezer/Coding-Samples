#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Math\Matrix.h"
#include "Math\Vect4D.h"
#include "Particle.h"
#include "ParticleData.h"
#include <assert.h>
#include <list>

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	
	void SpawnParticle();
	void update();
	void draw();

	void addParticleToList(Particle *p );
	
	void removeParticleFromList(const Particle *p );

	void Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc);

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
	//void *buffer;
	Particle *newParticle;
	Particle *p;
	Vect4D	start_position;
	Vect4D	start_velocity;
	
	float	max_life;
	int		max_particles;
	float	spawn_frequency;
	float	last_spawn;
	float	last_loop;
	int		last_active_particle;

	// added for speed efficiency
	//int bufferCount;
	Vect4D	vel_variance;
	Vect4D	pos_variance;
	float	scale_variance;
	Particle *headParticle;

	// get the camera matrix from OpenGL
	// need to get the position
	Matrix cameraMatrix;

	//Temporary matrix
	Matrix tmp;
	Matrix transCamera;
	Matrix rotParticle;
	Matrix transParticle;
	Matrix pivotParticle;
	Vect4D pivotVect;
	Matrix scaleMatrix;
	Vect4D camPosVect;
	Vect4D z_axis;
	Vect4D v;
};

#endif // PARTICLEEMITTER_H
