#include "Particle.h"
#include "Matrix.h"
#include "ParticleData.h"

Particle::Particle()
{
	// construtor
	//buffer = _aligned_malloc(sizeof(ParticleData), 16);
	//data = new (buffer) ParticleData();
	data = new ParticleData();
	data->life = 0.0f;
	data->position.set( 0.0f, 0.0f,  0.0f );
	data->velocity.set( 0.0f, 0.0f,  0.0f );
	data->scale.set( 1.0f, 1.0f, 1.0f );
	data->rotation = 0.0f;
	data->rotation_velocity = 0.5f;

}

Particle::~Particle()
{
	// nothing to do
	delete this->data;
	//_aligned_free(buffer);
}

void Particle::CopyDataOnly(const ParticleData &p )
{
	// copy the data only
	// data way of copying data is more efficient that element by element

	// No it is not because you are passing in a pointer dumbsh*t 
	// Use a goddamn reference &p
	// -RMG
	data->position = p.position;
	data->velocity = p.velocity;
	data->scale    = p.scale;
	data->rotation = p.rotation;
	data->rotation_velocity = p.rotation_velocity;
	data->life     = p.life;
}

/*void Particle::Update(const float& time_elapsed)
{
	// Rotate the matrices
	/*tmp_Row0 = data->curr_Row0;
	data->prev_Row0 = tmp_Row0;
	
	tmp_Row1 = data->curr_Row1;
	data->prev_Row1 = tmp_Row1;
	
	tmp_Row2 = data->curr_Row2;
	data->prev_Row2 = tmp_Row2;

	tmp_Row3 = data->curr_Row3;
	data->prev_Row3 = tmp_Row3;

	tmp.set( data->diff_Row0);
	tmp.set( data->diff_Row1);
	tmp.set( data->diff_Row2);
	tmp.set( data->diff_Row3);

	float scale = tmp.Determinant();

	// serious math below - magic secret sauce
	data->life += time_elapsed;
	//position = position + (velocity * time_elapsed);
	data->position += data->velocity * time_elapsed;
	Vect4D z_axis(0.0f, -0.25f, 1.0f);
	Vect4D v(3.0f, 4.0f, 0.0f);
	data->position.Cross( z_axis, v);
	v.norm(v);
	//position = position + v * 0.05f * life;
	data->position += (v * (0.05f * data->life));
	
	/*if( scale > 1.0f )
	{
		scale = 1.0f/scale;
	};

	//rotation = rotation + scale + rotation_velocity * time_elapsed *2.01f;
	data->rotation += ( (data->rotation_velocity * (time_elapsed *2.01f)));
}*/
// End of file


