#ifndef __MODULE_HELICOPTER_H__
#define __MODULE_HELICOPTER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

class Enemy;
struct SDL_Texture;

class ModuleHelicopter : public Module
{
public:
	// Constructor
	ModuleHelicopter(bool startEnabled);

	// Destructor
	~ModuleHelicopter();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	//pointer to current boss animation
	Animation* currentFAnim = nullptr;
	Animation* currentShotAnim = nullptr;
	Animation* currentDestroyedAnim = nullptr;

	SDL_Texture* textureSky = nullptr;
	SDL_Rect sky;

	//set of animations
	Animation flyAnim, flickerAnim, destroyedAnim, explosionAnim;
	Animation shotYAnim, shotGAnim, shotSFire, shotEFire, shotOFire;


	int distance;
	/*int numShots = 0;
	int MAXSHOTS = 5;
	bool moveToPlayer = false;*/
	bool isShooting = false;

	void Idle();
	bool find_player();

	float timer;
	float SHOOT_INTERVAL = 5;
	bool isSpawning;
	float scale;

	void Attack();
	/*const int shootInterval = 5;
	int shootTimer = shootInterval;*/
	double dx;
	double dy;
	float angle;

	int directionX = 0;

	double ModuleHelicopter::calculateAngle();

public:

	Uint32 startTime = 0;

	// Position of the helicopter in the map
	iPoint position;

	// burst counter
	//int shot;

	// speed loop
	int loop = 0;

	//state of the boss
	int state = 1;

	// The speed in which we move the helicopter (pixels per frame)
	int speed = 1;

	//timer
	int time = 0;

	//count 
	int count = 0;

	//helicopter life
	int life = 100;

	int gunPosX = 0;
	int gunPosY = 0;

	//red opacity when damaged
	Uint8 BTint = 255;
	int BTintInc = 0;

	//helicopter being shot 
	int helicopterShot = 0;

	SDL_Texture* Destroyed = nullptr;

	bool helicopterDestroyed = false;
	// The helicopter collider
	Collider* collider = nullptr;

private:

	// The enemies sprite sheet
	SDL_Texture* textureH = nullptr;

	// The audio fx for destroying an enemy
	uint helicopterDestroyedFx = 0;
	uint helicopterShotFx = 0;
	uint helicopterMovingFx = 0;
};

#endif // __MODULE_HELICOPTER_H__