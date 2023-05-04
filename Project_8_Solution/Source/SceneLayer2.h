#ifndef __SCENE_LAYER2_H__
#define __SCENE_LAYER2_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLayer2 : public Module
{
public:
	//Constructor
	SceneLayer2(bool startEnabled);

	//Destructor
	~SceneLayer2();

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

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* palms = nullptr;
	SDL_Texture* palms2 = nullptr;
	SDL_Texture* P1 = nullptr;
	SDL_Texture* P1Shadow = nullptr;
	SDL_Texture* FacePhoto = nullptr;
	SDL_Texture* Time = nullptr;
	SDL_Texture* Credits = nullptr;
	SDL_Texture* Weapon = nullptr;
	SDL_Texture* Grenade = nullptr;
};

#endif
