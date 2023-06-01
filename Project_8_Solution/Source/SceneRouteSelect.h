#ifndef __SCENE_ROUTE_H__
#define __SCENE_ROUTE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneRouteSelect : public Module
{
public:
	//Constructor
	SceneRouteSelect(bool startEnabled);

	//Destructor
	~SceneRouteSelect();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:

	//to save starting time
	Uint32 startTime = 0;


	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* CurrentAnimaton1 = nullptr;
	

	// A set of animations
	//Animation idleAnim;
	Animation jungleRoute;


	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* Route1 = nullptr;
	



};

#endif

