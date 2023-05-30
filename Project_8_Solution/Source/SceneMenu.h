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
	int QuadPos_x;
	int QuadPos_y;

	int lastPos_x; // Position X variable reminder for the sound player in the character selection.
	int lastPos_y; // Position Y variable reminder for the sound player in the character selection.


	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* CurrentAnimaton1 = nullptr;
	Animation* CurrentAnimaton2 = nullptr;


	// A set of animations
	//Animation idleAnim;
	Animation menu;
	Animation QuadSelect;


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
	SDL_Texture* TimeText = nullptr;
	SDL_Texture* PlayerSelect = nullptr;
	SDL_Texture* QuadSelect1 = nullptr;



	//NAMES TEXT
	//BlueFont and BlueFontSmall
	int NameFont = -1;
	int NameFont2 = -1;
	int startFontt = -1;


	char MenuFont[65] = { "\0" };
	char MenuFont2[43] = { "\0" };
	char startFont[49] = { "\0" };



	SDL_Rect menuFontRect;
	SDL_Rect menuFontRect2;
	SDL_Rect startFontRect;
	SDL_Rect CharRect;


	uint selectFx = 0;
	bool soundPlayed = false;






};

#endif

#pragma once