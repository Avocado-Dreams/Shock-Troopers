#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"

#define MAX_ACTIVE_PARTICLES 3500

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	Particle* AddParticle(const Particle& particle, float x, float y, float speedx, float speedy, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;


	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

public:
	//Template particle for an explosion
	Particle enemy_deathDown, enemy_deathSE, enemy_deathSW, enemy_deathLeft, enemy_deathRight, enemy_deathNE, enemy_deathNW, tank_explosion;
	//Template particle for a laser
	Particle laser,melee;
	Particle bossDown, bossRight, bossLeft, bossSudest, bossSudoest, bossSudR, bossSudoL, bossExplosion, normalBShot;
	Particle shotYAnim, shotGAnim, shotSFire, shotEFire, shotOFire, explosionAnim;
	Particle enemyShot,tankShot;
	Particle sUp, sDown, sLeft, sRight, sNorest, sNoroest, sSudest, sSudoest;
	Particle tankUp, tankDown, tankLeft, tankRight, tankNE1, tankNE2, tankNE3, tankSE1, tankSE2, tankSE3, tankSO1, tankSO2, tankSO3, tankNO1, tankNO2, tankNO3;
	Particle BlueDiamond, Life;
	Particle boxDestroyed;
};

#endif // !__MODULEPARTICLES_H__