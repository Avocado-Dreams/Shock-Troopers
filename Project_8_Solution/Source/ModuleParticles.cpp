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
	enemy_deathDown.anim.PushBack({23, 201, 27, 37});
	enemy_deathDown.anim.PushBack({ 74, 180, 37, 55 });
	enemy_deathDown.anim.PushBack({ 128, 182, 37, 52 });
	enemy_deathDown.anim.PushBack({ 176, 185, 43, 39 });
	enemy_deathDown.anim.PushBack({ 231, 194, 37, 37 });
	enemy_deathDown.anim.PushBack({ 282, 195, 43, 39 });
	enemy_deathDown.anim.PushBack({ 339, 194, 39, 40 });
	enemy_deathDown.anim.loop = false;
	enemy_deathDown.anim.speed = 0.1f;
	enemy_deathDown.lifetime = 100;
	//App->textures->Unload(texture);

	enemy_deathSE.anim.PushBack({ 341, 63, 55, 55 });
	enemy_deathSE.anim.PushBack({ 285, 63, 55, 55 });
	enemy_deathSE.anim.PushBack({ 229, 63, 55, 55 });
	enemy_deathSE.anim.PushBack({ 173, 63, 55, 55 });
	enemy_deathSE.anim.PushBack({ 117, 63, 55, 55 });
	enemy_deathSE.anim.PushBack({ 61, 63, 55, 55 });
	enemy_deathSE.anim.PushBack({ 5, 63, 55, 55 });

	enemy_deathSE.anim.loop = false;
	enemy_deathSE.anim.speed = 0.1f;
	enemy_deathSE.lifetime = 100;

	enemy_deathNE.anim.PushBack({ 341, 119, 55, 55 });
	enemy_deathNE.anim.PushBack({ 285, 119, 55, 55 });
	enemy_deathNE.anim.PushBack({ 229, 119, 55, 55 });
	enemy_deathNE.anim.PushBack({ 173, 119, 55, 55 });
	enemy_deathNE.anim.PushBack({ 117, 119, 55, 55 });
	enemy_deathNE.anim.PushBack({ 61, 119, 55, 55 });
	enemy_deathNE.anim.PushBack({ 5, 119, 55, 55 });

	enemy_deathNE.anim.loop = false;
	enemy_deathNE.anim.speed = 0.1f;
	enemy_deathNE.lifetime = 100;

	enemy_deathLeft.anim.PushBack({ 341, 244, 55, 55 });
	enemy_deathLeft.anim.PushBack({ 285, 244, 55, 55 });
	enemy_deathLeft.anim.PushBack({ 229, 244, 55, 55 });
	enemy_deathLeft.anim.PushBack({ 173, 244, 55, 55 });
	enemy_deathLeft.anim.PushBack({ 117, 244, 55, 55 });
	enemy_deathLeft.anim.PushBack({ 61, 244, 55, 55 });
	enemy_deathLeft.anim.PushBack({ 5, 244, 55, 55 });

	enemy_deathLeft.anim.loop = false;
	enemy_deathLeft.anim.speed = 0.1f;
	enemy_deathLeft.lifetime = 100;

	enemy_deathSW.anim.PushBack({ 579, 57, 55, 55 });
	enemy_deathSW.anim.PushBack({ 635, 57, 55, 55 });
	enemy_deathSW.anim.PushBack({ 691, 57, 55, 55 });
	enemy_deathSW.anim.PushBack({ 747, 57, 55, 55 });
	enemy_deathSW.anim.PushBack({ 803, 57, 55, 55 });
	enemy_deathSW.anim.PushBack({ 859, 57, 55, 55 });
	enemy_deathSW.anim.PushBack({ 915, 57, 55, 55 });

	enemy_deathSW.anim.loop = false;
	enemy_deathSW.anim.speed = 0.1f;
	enemy_deathSW.lifetime = 100;

	enemy_deathNW.anim.PushBack({ 579, 113, 55, 55 });
	enemy_deathNW.anim.PushBack({ 635, 113, 55, 55 });
	enemy_deathNW.anim.PushBack({ 691, 113, 55, 55 });
	enemy_deathNW.anim.PushBack({ 747, 113, 55, 55 });
	enemy_deathNW.anim.PushBack({ 803, 113, 55, 55 });
	enemy_deathNW.anim.PushBack({ 859, 113, 55, 55 });
	enemy_deathNW.anim.PushBack({ 915, 113, 55, 55 });

	enemy_deathNW.anim.loop = false;
	enemy_deathNW.anim.speed = 0.1f;
	enemy_deathNW.lifetime = 100;

	enemy_deathRight.anim.PushBack({ 579, 238, 55, 55 });
	enemy_deathRight.anim.PushBack({ 635, 238, 55, 55 });
	enemy_deathRight.anim.PushBack({ 691, 238, 55, 55 });
	enemy_deathRight.anim.PushBack({ 747, 238, 55, 55 });
	enemy_deathRight.anim.PushBack({ 803, 238, 55, 55 });
	enemy_deathRight.anim.PushBack({ 859, 238, 55, 55 });
	enemy_deathRight.anim.PushBack({ 915, 238, 55, 55 });

	enemy_deathRight.anim.loop = false;
	enemy_deathRight.anim.speed = 0.1f;
	enemy_deathRight.lifetime = 100;

	//BOX DESTROYED
	boxDestroyed.anim.PushBack({ 9, 949, 45, 44 });
	boxDestroyed.anim.PushBack({ 62, 943, 56, 53 });
	boxDestroyed.anim.PushBack({ 129, 942, 65, 54 });
	boxDestroyed.anim.PushBack({ 203, 943, 65, 55 });
	boxDestroyed.anim.PushBack({ 277, 946, 65, 52 });
	boxDestroyed.anim.PushBack({ 350, 954, 66, 40 });
	boxDestroyed.anim.PushBack({ 424, 959, 66, 36 });
	boxDestroyed.anim.PushBack({ 499, 964, 65, 33 });
	boxDestroyed.anim.loop = false;
	boxDestroyed.anim.speed = 0.2f;

	//TANK
	tank_explosion.anim.PushBack({ 11, 722, 32, 32 });
	tank_explosion.anim.PushBack({ 44, 722, 32, 32 });
	tank_explosion.anim.PushBack({ 77, 722, 32, 32 });
	tank_explosion.anim.PushBack({ 110, 722, 32, 32 });
	tank_explosion.anim.PushBack({ 11, 755, 32, 32 });
	tank_explosion.anim.PushBack({ 44, 755, 32, 32 });
	tank_explosion.anim.PushBack({ 77, 755, 32, 32 });
	tank_explosion.anim.PushBack({ 110, 755, 32, 32 });
	tank_explosion.anim.loop = false;
	tank_explosion.anim.speed = 0.1f;
	tank_explosion.lifetime = 100;

	tankUp.anim.PushBack({ 448,18,15,25 });
	tankUp.anim.PushBack({ 475,18,16,25 });
	tankUp.anim.PushBack({ 508,18,15,25 });
	tankUp.anim.PushBack({ 535,18,16,24 });

	tankDown.anim.PushBack({ 448,66,15,25 });
	tankDown.anim.PushBack({ 475,66,16,25 });
	tankDown.anim.PushBack({ 508,66,15,25 });
	tankDown.anim.PushBack({ 535,66,16,24 });

	tankLeft.anim.PushBack({ 448,96,25,16 });
	tankLeft.anim.PushBack({ 475,96,25,16 });
	tankLeft.anim.PushBack({ 501,96,26,16 });
	tankLeft.anim.PushBack({ 528,96,24,16 });

	tankRight.anim.PushBack({ 448,51,25,15 });
	tankRight.anim.PushBack({ 475,51,25,15 });
	tankRight.anim.PushBack({ 501,51,26,15 });
	tankRight.anim.PushBack({ 531,51,24,15 });

	tankNE1.anim.PushBack({ 448,371,16,25 });
	tankNE1.anim.PushBack({ 474,371,16,24 });
	tankNE1.anim.PushBack({ 501,371,16,25 });
	tankNE1.anim.PushBack({ 528,371,17,24 });

	tankNE2.anim.PushBack({ 448,398,18,23 });
	tankNE2.anim.PushBack({ 473,398,18,22 });
	tankNE2.anim.PushBack({ 498,398,19,22 });
	tankNE2.anim.PushBack({ 523,398,19,22 });

	tankNE3.anim.PushBack({ 448,349,24,18 });
	tankNE3.anim.PushBack({ 472,349,23,17 });
	tankNE3.anim.PushBack({ 497,349,24,17 });
	tankNE3.anim.PushBack({ 525,349,22,18 });

	tankSE1.anim.PushBack({ 448,274,24,17 });
	tankSE1.anim.PushBack({ 476,274,23,17 });
	tankSE1.anim.PushBack({ 505,274,24,17 });
	tankSE1.anim.PushBack({ 532,274,23,17 });

	tankSE2.anim.PushBack({ 448,295,21,21 });
	tankSE2.anim.PushBack({ 478,295,20,21 });
	tankSE2.anim.PushBack({ 507,295,21,21 });
	tankSE2.anim.PushBack({ 536,295,19,20 });

	tankSE3.anim.PushBack({ 448,320,17,25 });
	tankSE3.anim.PushBack({ 476,320,16,24 });
	tankSE3.anim.PushBack({ 501,320,17,25 });
	tankSE3.anim.PushBack({ 528,321,16,23 });

	tankSO1.anim.PushBack({ 448,114,16,25 });
	tankSO1.anim.PushBack({ 475,114,16,24 });
	tankSO1.anim.PushBack({ 507,114,16,25 });
	tankSO1.anim.PushBack({ 535,113,16,24 });

	tankSO2.anim.PushBack({ 448,140,18,24 });
	tankSO2.anim.PushBack({ 474,140,17,23 });
	tankSO2.anim.PushBack({ 503,140,18,24 });
	tankSO2.anim.PushBack({ 532,140,17,22 });

	tankSO3.anim.PushBack({ 448,171,22,20 });
	tankSO3.anim.PushBack({ 474,171,21,19 });
	tankSO3.anim.PushBack({ 502,171,22,20 });
	tankSO3.anim.PushBack({ 529,172,20,19 });

	tankNO1.anim.PushBack({ 448,196,22,19 });
	tankNO1.anim.PushBack({ 474,196,22,19 });
	tankNO1.anim.PushBack({ 502,197,23,19 });
	tankNO1.anim.PushBack({ 528,197,22,18 });

	tankNO2.anim.PushBack({ 448,221,20,21 });
	tankNO2.anim.PushBack({ 474,220,20,21 });
	tankNO2.anim.PushBack({ 503,221,20,21 });
	tankNO2.anim.PushBack({ 530,221,19,20 });

	tankNO3.anim.PushBack({ 448,245,15,25 });
	tankNO3.anim.PushBack({ 476,246,16,24 });
	tankNO3.anim.PushBack({ 507,245,16,25 });
	tankNO3.anim.PushBack({ 531,246,16,23 });
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

	normalBShot.anim.PushBack({ 18, 32, 8, 9 });
	normalBShot.anim.PushBack({ 5, 32, 8, 9 });
	normalBShot.anim.PushBack({ 30, 32, 8, 9 });
	normalBShot.lifetime = 380;
	normalBShot.anim.speed = 0.2f;

	BlueDiamond.anim.PushBack({ 215,318,28,16 });
	BlueDiamond.anim.PushBack({ 243,318,28,16 });
	BlueDiamond.anim.PushBack({ 271,318,28,16 });
	BlueDiamond.anim.speed = 0.2f;
	BlueDiamond.lifetime = 50;

	Life.anim.PushBack({ 275, 399, 34, 17 });
	Life.anim.PushBack({ 309, 399, 34, 17 });
	Life.anim.PushBack({ 343, 399, 34, 17 });
	Life.anim.speed = 0.2f;
	Life.lifetime = 50;

	//BOSS SHOOTING
	//shoot down
	bossDown.anim.PushBack({ 10, 491, 32, 49 });
	bossDown.anim.PushBack({ 10, 559, 32, 49 });
	bossDown.speed.y = 2;
	bossDown.lifetime = 180;
	bossDown.anim.speed = 0.8f;
	//shoot right
	bossRight.anim.PushBack({ 370, 491, 48, 48 });
	bossRight.anim.PushBack({ 344, 559, 48, 48 });
	bossRight.speed.x = 1;
	bossRight.lifetime = 180;
	bossRight.anim.speed = 0.8f;
	//shoot left
	bossLeft.anim.PushBack({ 313, 491, 48, 48 });
	bossLeft.anim.PushBack({ 285, 559, 48, 48 });
	bossLeft.speed.x = -2;
	bossLeft.lifetime = 180;
	bossLeft.anim.speed = 0.8f;
	//shoot sudest
	bossSudest.anim.PushBack({ 204, 491, 44, 48 });
	bossSudest.anim.PushBack({ 230, 551, 46, 50 });
	bossSudest.speed.y = 1;
	bossSudest.speed.x = 1;
	bossSudest.lifetime = 180;
	bossSudest.anim.speed = 0.8f;
	//shoot sudoest
	bossSudoest.anim.PushBack({ 95, 491, 43, 48 });
	bossSudoest.anim.PushBack({ 95, 553, 36, 48 });
	bossSudoest.speed.y = 1;
	bossSudoest.speed.x = -1;
	bossSudoest.lifetime = 180;
	bossSudoest.anim.speed = 0.8f;

	//Boss explosion
	bossExplosion.anim.PushBack({ 10, 795, 95, 102 });
	bossExplosion.anim.PushBack({ 119, 795, 95, 102 });
	bossExplosion.anim.PushBack({ 241, 795, 95, 102 });
	bossExplosion.anim.PushBack({ 376, 795, 95, 102 });
	bossExplosion.anim.PushBack({ 19, 640, 133, 137 });
	bossExplosion.anim.PushBack({ 187, 640, 133, 137 });
	bossExplosion.anim.PushBack({ 330, 640, 133, 137 });
	bossExplosion.anim.loop = false; 
	bossExplosion.anim.speed = 0.2f;

	//HELICOPTER SHOOTING
	//NORMAL SHOT YELLOW
	shotYAnim.anim.PushBack({ 49, 28, 4, 4 });
	shotYAnim.lifetime = 180;

	//NORMAL SHOT GREY
	shotGAnim.anim.PushBack({ 65, 28, 4, 4 });
	shotGAnim.lifetime = 180;

	//SHOT FIRE DOWN
	shotSFire.anim.PushBack({ 80, 27, 9, 13 });
	shotSFire.anim.PushBack({ 186, 27, 17, 17 });
	shotSFire.anim.PushBack({ 278, 27, 30, 31 });
	shotSFire.anim.loop = false;
	shotSFire.anim.speed = 0.3f;

	//SHOT FIRE SUDEST
	shotEFire.anim.PushBack({ 117, 27, 12, 15 });
	shotEFire.anim.PushBack({ 162, 27, 15, 17 });
	shotEFire.anim.PushBack({ 211, 26, 26, 28 });
	shotEFire.anim.loop = false;
	shotEFire.anim.speed = 0.3f;

	//SHOT FIRE SUDOEST
	shotOFire.anim.PushBack({ 99, 27, 10, 15 });
	shotOFire.anim.PushBack({ 138, 27, 14, 17 });
	shotOFire.anim.PushBack({ 246, 26, 26, 28 });
	shotOFire.anim.loop = false;
	shotOFire.anim.speed = 0.3f;

	//EXPLOSION HELICOPTER
	explosionAnim.anim.PushBack({ 17, 638, 137, 141 });
	explosionAnim.anim.PushBack({ 168, 638, 137, 141 });
	explosionAnim.anim.PushBack({ 309, 638, 137, 141 });
	explosionAnim.anim.PushBack({ 0, 804, 103, 106 });
	explosionAnim.anim.PushBack({ 113, 804, 103, 106 });
	explosionAnim.anim.PushBack({ 236, 802, 103, 106 });
	explosionAnim.anim.PushBack({ 358, 794, 103, 106 });
	explosionAnim.anim.loop = false;
	explosionAnim.anim.speed = 0.2f;

	

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