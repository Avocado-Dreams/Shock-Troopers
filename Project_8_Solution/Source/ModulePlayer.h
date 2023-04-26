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

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	//init map zones
	int zone = 1; //1 = zone A; 2 = zone AB; 3 = zone B; 4 = zone BC; 5 = zone C; 6 = zone D; 7 = zone E

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	int bulletdir = 0;
	int movedir = 0;
	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	//timer callback
	//SDL_TimerCallback callbackBC(Uint32 interval, void* name);
	//SDL_TimerCallback callbackAB(Uint32 interval, void* name);
};

#endif //!__MODULE_PLAYER_H__