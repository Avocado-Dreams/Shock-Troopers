#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneMenu : public Module
{
public:
	//Constructor
	SceneMenu(bool startEnabled);

	//Destructor
	~SceneMenu();

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

	// to show characters
	bool showCharacters[2][4];
	/*
	bool showJackal = true;
	bool showMilky = false;
	bool showLoki = false;
	bool showSouthernCross = false;
	bool showMarieBee = false;
	bool showRio = false;
	bool showHaru = false;
	bool showBigMama = false; */

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* CurrentAnimaton1 = nullptr;


	// A set of animations
	//Animation idleAnim;
	Animation menu;


	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* Texture1 = nullptr;
	SDL_Texture* Jackal = nullptr;
	SDL_Texture* Milky = nullptr;
	SDL_Texture* Loki = nullptr;
	SDL_Texture* SouthernCross = nullptr;
	SDL_Texture* MarieBee = nullptr;
	SDL_Texture* Rio = nullptr;
	SDL_Texture* Haru = nullptr;
	SDL_Texture* BigMama = nullptr;
	SDL_Texture* LonelyWolf = nullptr;
	SDL_Texture* QuadSelect = nullptr;


	//NAMES TEXT
	int NameFont = -1;
	char MenuFont[26] = { "\0" };

	int NameFont2 = -1;
	char MenuFont2[52] = { "\0" };

	SDL_Rect menuFontRect;
	SDL_Rect menuFontRect2;
	SDL_Rect CharRect;







};

#endif

#pragma once
