#ifndef __MODULE_FINALBOSS_H__
#define __MODULE_FINALBOSS_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

class Enemy;
struct SDL_Texture;

class ModuleFinalBoss : public Module
{
public:
	// Constructor
	ModuleFinalBoss(bool startEnabled);

	// Destructor
	~ModuleFinalBoss();

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
	Animation* currentBAnim = nullptr;
	Animation* currentBSAnim = nullptr; 

	//set of animations
	Animation idleAnim, upAnim, downAnim, flickerAnim, damagedAnim, destroyedAnim;
	Animation downBSAnim, leftBSAnim, rightBSAnim, sudoestBSAnim, sudestBSAnim, sudoRBSAnim, sudoLBSAnim, sudRBSAnim, sudLBSAnim;

	int distance;
	int numShots = 0;
	int MAXSHOTS = 5;
	bool moveToPlayer = false;
	bool isShooting = false;
	
	void Idle();
	bool find_player();

	float timer;
	float SHOOT_INTERVAL = 5;
	bool isSpawning;
	float scale;

	/*const int shootInterval = 5;
	int shootTimer = shootInterval;*/
	double dx;
	double dy;
	float angle;

	void Attack();

	double ModuleFinalBoss::calculateAngle(); 

public:
	// Position of the boss in the map
	iPoint position;

	// burst counter
	//int shot;

	// speed loop
	int loop = 0;

	//state of the boss
	int state = 1;

	// The speed in which we move the boss (pixels per frame)
	int speed = 1;

	//timer
	int time = 0;

	//count 
	int count = 0;

	//boss life
	int life = 100; 

	//red opacity when damaged
	Uint8 BTint = 255;
	int BTintInc = 0;

	//boss being shot 
	int bossShot = 0;

	bool bossDestroyed = false; 
	// The finale boss collider
	Collider* collider = nullptr;

private:


	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an enemy
	uint tankDestroyedFx = 0;
	uint tankShotFx = 0;
	uint tankMovingFx = 0;
};

#endif // __MODULE_ENEMIES_H__