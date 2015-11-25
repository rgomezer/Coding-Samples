#include "DO_NOT_MODIFY\Timer\Timer.h"
#include "DO_NOT_MODIFY\Timer\GlobalTimer.h"
#include "DO_NOT_MODIFY\OpenGL\OpenGLInterface.h"

#include <assert.h>

#include "ParticleEmitter.h"
#include "Settings.h"

static const unsigned char squareColors[] = 
{
	255,  255,  000,  255,
	000,  255,  255,  255,
	000,  000,  000,  000,
	255,  000,  255,  255,
}; 

static const float squareVertices[] = 
{
	-0.015f,  -0.015f, 0.0f,
	 0.015f,  -0.015f, 0.0f,
	-0.015f,   0.015f, 0.0f,
	 0.015f,   0.015f, 0.0f,
};

///////////////////////STUFF HAPPENS HERE/////////////////////////////////////////////////////

ParticleEmitter::ParticleEmitter()
	: start_position(0.0f, 0.0f, 0.0f),
	start_velocity(0.0f, 1.0f, 0.0f),
	max_life(MAX_LIFE),
	max_particles(NUM_PARTICLES),
	spawn_frequency(0.0000001f),
	last_spawn(globalTimer::getTimerInSec()),
	last_loop(globalTimer::getTimerInSec()),
	last_active_particle(-1),
	vel_variance(1.0f, 4.0f, 0.4f),
	pos_variance(1.0f, 1.0f, 1.0f),
	pivotVect(1.0f, 0.0f, 50.0f, 1.0f),
	scale_variance(2.5f),
	z_axis(0.0f, -0.25f, 1.0f),
	v(3.0f, 4.0f, 0.0f),
	headParticle(0)
{
	// nothing to do
	
}

ParticleEmitter::~ParticleEmitter()
{
	this->headParticle = 0;
	delete this->newParticle;
}

void ParticleEmitter::removeParticleFromList(const Particle *p )
{
	// make sure we are not screwed with a null pointer
	assert(p);

	if( p->prev == 0 && p->next == 0  )
	{ // only one on the list
		this->headParticle = 0;
	}
	else if( p->prev == 0 && p->next != 0  )
	{ // first on the list
		p->next->prev = 0;
		this->headParticle = p->next;
	}
	else if( p->prev!= 0 && p->next == 0 )
	{ // last on the list 
		p->prev->next = 0;
	}
	else//( p->next != 0  && p->prev !=0 )
	{ // middle of the list
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	
	// bye bye
	delete p;
}

void ParticleEmitter::update()
{
	// get current time
	float current_time = globalTimer::getTimerInSec();

	// spawn particles
	float time_elapsed = current_time - last_spawn;
	
	// update
	while( spawn_frequency < time_elapsed )
	{
		// spawn a particle
		this->SpawnParticle();
		// adjust time
		time_elapsed -= spawn_frequency;
		// last time
		last_spawn = current_time;
	}
	
	// total elapsed
	time_elapsed = current_time - last_loop;

	Particle *p = this->headParticle;
	
	// walk the particles
	while( p!= 0 )
	{
		// serious math below - magic secret sauce
		p->data->life += time_elapsed;
		p->data->position += p->data->velocity * time_elapsed;
		p->data->position.Cross(z_axis, v);
		v.norm(v);
		p->data->position += (v * (0.05f * p->data->life));
		p->data->rotation += ((p->data->rotation_velocity * (time_elapsed *2.01f)));

		// if it's live is greater that the max_life 
		// and there is some on the list
		// remove node
		if((p->data->life > max_life) && (last_active_particle > 0))
		{
			// particle to remove
			Particle *s = p;

			// need to squirrel it away.
			p=p->next;

			// remove last node
			this->removeParticleFromList( s );

			// update the number of particles
			last_active_particle--;
		}
		else
		{
			// increment to next point
			p = p->next;
		}
	}

	last_loop = current_time;
}

void ParticleEmitter::Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc)
{
	// Add some randomness...

	// Ses it's ugly - I didn't write this so don't bitch at me
	// Sometimes code like this is inside real commerical code ( so now you know how it feels )
	
	// x - variance
	float var = static_cast<float>(rand() % 1000) * 0.001f;
	float sign = static_cast<float>(rand() % 2);
	float *t_pos = reinterpret_cast<float*>(&pos);
	float t_var = pos_variance.getX();
	if(sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += t_var * var;

	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var = pos_variance.getY();
	if(sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += t_var * var;

	// z - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var = pos_variance.getZ();
	if(sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += t_var * var;
	
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	
	// x  - add velocity
	t_pos = &vel[x];
	t_var = vel_variance.getX();
	if(sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += t_var * var;
	
	// y - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var = vel_variance.getY();
	if(sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += t_var * var;
	
	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var = vel_variance.getZ();
	if(sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += t_var * var;

	// correct the sign
	var = 2.0f * static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	
	if(sign == 0)
	{
		var *= -1.0;
	}
	sc = sc * var;
}

void ParticleEmitter::SpawnParticle()
{
	// create another particle if there are ones free
	if( last_active_particle < max_particles-1 )
	{
		// create new particle
		newParticle = new Particle();

		// apply the variance
		this->Execute(newParticle->data->position, newParticle->data->velocity, newParticle->data->scale);

		// increment count
		last_active_particle++;

		// add to list
		this->addParticleToList( newParticle );

	}
}
	   
void ParticleEmitter::addParticleToList(Particle *p )
{
	assert(p);
	if( this->headParticle == 0 )
	{ // first on list
		this->headParticle = p;
		this->headParticle->next = 0;
		this->headParticle->prev= 0;
	}
	else 
	{ // add to front of list
		headParticle->prev = p;
		p->next = headParticle;
		p->prev = 0;
		headParticle = p;
	}

}

void ParticleEmitter::draw()
{
	// get the camera matrix from OpenGL
	glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<float*>(&cameraMatrix));
	
	// get the position from this matrix
	cameraMatrix.get(&camPosVect);

	// camera position
	transCamera.setTransMatrix(camPosVect);

	//walk through list of particles
	Particle *p = this->headParticle;

	// OpenGL goo... don't worrry about this
	glVertexPointer(3, GL_FLOAT, 0, squareVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
	glEnableClientState(GL_COLOR_ARRAY);

	while( p != 0)
	{
		// particle position
		transParticle.setTransMatrix( p->data->position );
		
		// rotation matrix
		rotParticle.setRotZMatrix( p->data->rotation );

		// pivot Point
		pivotVect *= (20.0f * (p->data->life));

		pivotParticle.setTransMatrix( pivotVect );

		// scale Matrix
		scaleMatrix.setScaleMatrix( p->data->scale );

		// total transformation of particle
		tmp = ((((scaleMatrix * transCamera) * transParticle) * rotParticle) * scaleMatrix);
		//tmp = (transCamera * transParticle) * rotParticle * scaleMatrix;

		// set the transformation matrix
		glLoadMatrixf(reinterpret_cast<float*>(&(tmp)));

		// draw the trangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); 

		//get the next particle on the list
		p = p->next;

		// clears or flushes some internal setting, used in debug, but is need for performance reasons
		// magic...  really it's magic.
		//I call bs -Rodolfo
		GLenum glError = glGetError();
		glError;
	}
}
// End of file