    #ifndef __MODULE_OBSATCLE_H__
#define __MODULE_OBSATCLE_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Enemy.h"

struct SDL_Texture;

class ModuleObstacles : public Enemy
{
public:
	//Constructor
	ModuleObstacles(int x, int y);

	//Destructor
	

	// Called when the module is activated
	// Loads the necessary textures for the map background
	/*bool Start() override;*/

	// Called at the middle of the application loop
	// Updates the scene's background animations
	void Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	/*Update_Status PostUpdate() override;*/

	// Disables the player and the enemies
	bool CleanUp();

	void OnCollision(Collider* collider) override;


	/*iPoint position;*/
	bool boxIsDestroyed = false;

	Animation* currentHP = nullptr;
	Animation* currentBox = nullptr;
	Animation* currentDBox = nullptr;

	Animation box;


public:

	SDL_Texture* textureBox = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	bool removeCollider = false;

	int life = 1;

	/*Collider* collider = nullptr;*/


};

#endif
