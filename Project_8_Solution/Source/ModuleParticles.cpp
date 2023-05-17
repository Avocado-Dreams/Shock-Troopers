#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/Enemies/particulas.png");
	//enemy_death particle
	enemy_death.anim.PushBack({23, 201, 27, 37});
	enemy_death.anim.PushBack({ 74, 180, 37, 55 });
	enemy_death.anim.PushBack({ 128, 182, 37, 52 });
	enemy_death.anim.PushBack({ 176, 185, 43, 39 });
	enemy_death.anim.PushBack({ 231, 194, 37, 37 });
	enemy_death.anim.PushBack({ 282, 195, 43, 39 });
	enemy_death.anim.PushBack({ 339, 194, 39, 40 });
	enemy_death.anim.loop = false;
	enemy_death.anim.speed = 0.1f;
	enemy_death.lifetime = 100;
	//App->textures->Unload(texture);

	tank_explosion.anim.PushBack({ 23, 201, 27, 37 });
	tank_explosion.anim.PushBack({ 74, 180, 37, 55 });
	tank_explosion.anim.PushBack({ 128, 182, 37, 52 });
	tank_explosion.anim.PushBack({ 176, 185, 43, 39 });
	tank_explosion.anim.PushBack({ 231, 194, 37, 37 });
	tank_explosion.anim.PushBack({ 282, 195, 43, 39 });
	tank_explosion.anim.PushBack({ 339, 194, 39, 40 });
	tank_explosion.anim.loop = false;
	tank_explosion.anim.speed = 0.1f;
	tank_explosion.lifetime = 100;

	//BURST
	//shoot up
	sUp.anim.PushBack({ 0, 0, 11, 17 });
	sUp.anim.PushBack({ 22, 0, 11, 17 }); 
	sUp.speed.y = -11;
	sUp.lifetime = 180;
	sUp.anim.speed = 0.5f;
	//shoot down
	sDown.anim.PushBack({ 10, 0, 11, 17 });
	sDown.anim.PushBack({ 32, 0, 11, 17 });
	sDown.speed.y = 11;
	sDown.lifetime = 180;
	sDown.anim.speed = 0.5f;
	//shoot right
	sRight.anim.PushBack({ 189, 0, 13, 17 });
	sRight.anim.PushBack({ 223, 0, 13, 17 });
	sRight.speed.x = 11;
	sRight.lifetime = 180;
	sRight.anim.speed = 0.5f;
	//shoot left
	sLeft.anim.PushBack({ 172, 0, 13, 17 });
	sLeft.anim.PushBack({ 206, 0, 13, 17 });
	sLeft.speed.x = -11;
	sLeft.lifetime = 180;
	sLeft.anim.speed = 0.5f;
	//shoot norest
	sNorest.anim.PushBack({ 44, 0, 13, 17 });
	sNorest.anim.PushBack({ 108, 0, 13, 17 });
	sNorest.speed.y = -7;
	sNorest.speed.x = 7;
	sNorest.lifetime = 180;
	sNorest.anim.speed = 0.5f;
	//shoot noroest
	sNoroest.anim.PushBack({ 60, 0, 13, 17 });
	sNoroest.anim.PushBack({ 124, 0, 13, 17 });
	sNoroest.speed.y = -7;
	sNoroest.speed.x = -7;
	sNoroest.lifetime = 180;
	sNoroest.anim.speed = 0.5f;
	//shoot sudest
	sSudest.anim.PushBack({ 75, 0, 13, 17 });
	sSudest.anim.PushBack({ 139, 0, 13, 17 });
	sSudest.speed.y = 7;
	sSudest.speed.x = 7;
	sSudest.lifetime = 180;
	sSudest.anim.speed = 0.5f;
	//shoot sudoest
	sSudoest.anim.PushBack({ 92, 0, 13, 17 });
	sSudoest.anim.PushBack({ 155, 0, 13, 17 });
	sSudoest.speed.y = 7;
	sSudoest.speed.x = -7;
	sSudoest.lifetime = 180;
	sSudoest.anim.speed = 0.5f;

	enemyShot.anim.PushBack({ 18, 32, 8, 9 });
	enemyShot.anim.PushBack({ 5, 32, 8, 9 });
	enemyShot.anim.PushBack({ 30, 32, 8, 9 });
	//enemyShot.speed.x = 0;
	//enemyShot.speed.y = 1;
	enemyShot.lifetime = 180;
	enemyShot.anim.speed = 0.2f;

	BlueDiamond.anim.PushBack({ 215,318,28,16 });
	BlueDiamond.anim.PushBack({ 243,318,28,16 });
	BlueDiamond.anim.PushBack({ 271,318,28,16 });
	BlueDiamond.anim.speed = 0.2f;
	BlueDiamond.lifetime = 50;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, float speedx, float speedy,Collider::Type colliderType, uint delay)
{
	Particle* p = new Particle(particle);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;
			if(speedx != NULL) p->speed.x = speedx;
			if(speedy != NULL) p->speed.y = speedy;
			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
	return p;
}