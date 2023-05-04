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

	// Explosion particle
	//explosion.anim.PushBack({274, 296, 33, 30});
	//explosion.anim.PushBack({313, 296, 33, 30});
	//explosion.anim.PushBack({346, 296, 33, 30});
	//explosion.anim.PushBack({382, 296, 33, 30});
	//explosion.anim.PushBack({419, 296, 33, 30});
	//explosion.anim.PushBack({457, 296, 33, 30});
	//explosion.anim.loop = false;
	//explosion.anim.speed = 0.3f;

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

	enemyShotDownL.anim.PushBack({ 18, 32, 8, 9 });
	enemyShotDownL.anim.PushBack({ 5, 32, 8, 9 });
	enemyShotDownL.anim.PushBack({ 30, 32, 8, 9 });
	enemyShotDownL.speed.x = 0;
	enemyShotDownL.speed.y = 1;
	enemyShotDownL.lifetime = 180;
	enemyShotDownL.anim.speed = 0.2f;

	enemyShotDownR.anim.PushBack({ 18, 32, 8, 9 });
	enemyShotDownR.anim.PushBack({ 5, 32, 8, 9 });
	enemyShotDownR.anim.PushBack({ 30, 32, 8, 9 });
	enemyShotDownR.speed.x = 0;
	enemyShotDownR.speed.y = 1;
	enemyShotDownR.lifetime = 180;
	enemyShotDownR.anim.speed = 0.2f;

	enemyShotSE1.anim.PushBack({ 18, 32, 8, 9 });
	enemyShotSE1.anim.PushBack({ 5, 32, 8, 9 });
	enemyShotSE1.anim.PushBack({ 30, 32, 8, 9 });
	//enemyShotSE1.speed.x = 0.5;
	//enemyShotSE1.speed.y = 0.5;
	enemyShotSE1.lifetime = 180;
	enemyShotSE1.anim.speed = 0.2f;

	enemyShotSE2.anim.PushBack({ 18, 32, 8, 9 });
	enemyShotSE2.anim.PushBack({ 5, 32, 8, 9 });
	enemyShotSE2.anim.PushBack({ 30, 32, 8, 9 });
	//enemyShotSE2.speed.x = 0.75f;
	//enemyShotSE2.speed.y = 0.25f;
	enemyShotSE2.lifetime = 180;
	enemyShotSE2.anim.speed = 0.2f;

	enemyShotRight.anim.PushBack({ 18, 32, 8, 9 });
	enemyShotRight.anim.PushBack({ 5, 32, 8, 9 });
	enemyShotRight.anim.PushBack({ 30, 32, 8, 9 });
	enemyShotRight.speed.x = 1;
	enemyShotRight.speed.y = 0;
	enemyShotRight.lifetime = 180;
	enemyShotRight.anim.speed = 0.2f;

	enemyShotNE1.anim.PushBack({ 18, 32, 8, 9 });
	enemyShotNE1.anim.PushBack({ 5, 32, 8, 9 });
	enemyShotNE1.anim.PushBack({ 30, 32, 8, 9 });
	//enemyShotNE1.speed.x = 0.5;
	//enemyShotNE1.speed.y = -0.5;
	enemyShotNE1.lifetime = 180;
	enemyShotNE1.anim.speed = 0.2f;

	enemyShotNE2.anim.PushBack({ 18, 32, 8, 9 });
	enemyShotNE2.anim.PushBack({ 5, 32, 8, 9 });
	enemyShotNE2.anim.PushBack({ 30, 32, 8, 9 });
	//enemyShotNE2.speed.x = 0.25;
	//enemyShotNE2.speed.y = -0.75;
	enemyShotNE2.lifetime = 180;
	enemyShotNE2.anim.speed = 0.2f;

	enemyShotUp.anim.PushBack({ 18, 32, 8, 9 });
	enemyShotUp.anim.PushBack({ 5, 32, 8, 9 });
	enemyShotUp.anim.PushBack({ 30, 32, 8, 9 });
	enemyShotUp.speed.x = 0;
	enemyShotUp.speed.y = -1;
	enemyShotUp.lifetime = 180;
	enemyShotUp.anim.speed = 0.2f;

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