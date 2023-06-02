    #ifndef __MODULE_OBSATCLE_H__
#define __MODULE_OBSATCLE_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"


struct SDL_Texture;

class ModuleObstacles : public Module
{
public:
	//Constructor
	ModuleObstacles(bool startEnabled);

	//Destructor
	~ModuleObstacles();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);


	iPoint position;
	bool boxIsDestroyed = false;

	Animation* currentHP = nullptr;
	Animation* currentBox = nullptr;
	Animation* currentDBox = nullptr;

	Animation box, boxDestroyed;


public:

	SDL_Texture* textureBox = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	bool removeCollider = false;

	int life = 1;

	Collider* collider = nullptr;


};

#endif
