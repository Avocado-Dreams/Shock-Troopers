#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	//Animation
	void UpdateAnim();

	//Zones
	void UpdateZoneA();
	void UpdateZoneAB();
	void UpdateZoneB();
	void UpdateZoneBC();
	void UpdateZoneC();
	void UpdateZoneD();
	void UpdateZoneE();

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// burst counter
	int shot;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	//init map zones
	int zone = 1; //1 = zone A; 2 = zone AB; 3 = zone B; 4 = zone BC; 5 = zone C; 6 = zone D; 7 = zone E

	int vida = 3;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* textureL = nullptr;
	SDL_Texture* textureState = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;
	Animation* currentLAnimation = nullptr;
	Animation* currentStateAnimation = nullptr;

	// A set of animations
	//Animation idleAnim;
	Animation upAnim, downAnim, rightAnim, leftAnim, norestAnim, noroestAnim, sudestAnim, sudoestAnim;
	Animation upLAnim, downLAnim, rightLAnim, leftLAnim, norestLAnim, noroestLAnim, sudestLAnim, sudoestLAnim;
	Animation upWAnim, downWAnim, rightWAnim, leftWAnim, norestWAnim, noroestWAnim, sudestWAnim, sudoestWAnim;
	Animation upSAnim, downSAnim, rightSAnim, leftSAnim, norestSAnim, noroestSAnim, sudestSAnim, sudoestSAnim;
	Animation upDAnim, downDAnim, rightDAnim, leftDAnim, norestDAnim, noroestDAnim, sudestDAnim, sudoestDAnim;
	Animation upHAnim, downHAnim, rightHAnim, leftHAnim, norestHAnim, noroestHAnim, sudestHAnim, sudoestHAnim;
	Animation winAnim; 

	Animation idleAnim;
	int bulletdir = 0;
	int movedir = 0;
	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	int win = 0;
	int death = 0;
	int hit = 0;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;
	uint deathFx = 0;
	uint winFx = 0;
	uint hitFx = 0;

	//timer callback
	//SDL_TimerCallback callbackBC(Uint32 interval, void* name);
	//SDL_TimerCallback callbackAB(Uint32 interval, void* name);
};

#endif //!__MODULE_PLAYER_H__