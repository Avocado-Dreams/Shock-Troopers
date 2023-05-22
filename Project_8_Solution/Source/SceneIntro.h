#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:
	//Constructor
	SceneIntro(bool startEnabled);

	//Destructor
	~SceneIntro();

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
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* introTexture = nullptr;
	SDL_Texture* introTexture2 = nullptr;

	//start message
	int startFontt = -1;
	char startFont[32] = { "\0" };

	SDL_Rect startFontRect;
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* CurrentIntro = nullptr;


	// A set of animations
	//Animation idleAnim;
	Animation title;



};

#endif

