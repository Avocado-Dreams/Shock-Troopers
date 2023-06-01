#ifndef __SCENE_LAYER2_H__
#define __SCENE_LAYER2_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"


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

	void FramePlayer();
	void FrameGO();

	void updateHp();

	Animation* currentHP = nullptr;
	Animation* currentBox = nullptr;
	Animation* currentDBox = nullptr;

	Animation life100, life90, life80, life70, life60, life50, life40, life30, life20, life10, life0;
	Animation box, boxDestroyed;

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* palms = nullptr;
	SDL_Texture* palms2 = nullptr;
	SDL_Texture* P1 = nullptr;
	SDL_Texture* FacePhoto = nullptr;
	SDL_Texture* PhotoFrame = nullptr;
	SDL_Texture* Time = nullptr;
	SDL_Texture* Weapon = nullptr;
	SDL_Texture* Grenade = nullptr;

	SDL_Texture* GoUp = nullptr;
	SDL_Texture* GoRight = nullptr;

	int timer = 0;
	bool NameColor = true;

	int timer2 = 0;
	bool NameColor2 = true;

	//Timer
	int timerpass;
	Uint32 Time1 = 0; //necessary for "stage 1 start"

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture2 = nullptr;
	SDL_Texture* bgTexture3 = nullptr;

	int timerFont = -1;
	int timerCounter = 0;
	char timerText[10] = { "\0" };
	SDL_Rect timerRect;

	//stage text
	int stageFont = -1;
	char LevelFont[49] = { "\0" };
	SDL_Rect stageFontRect;

	//Score
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	SDL_Texture* texture = nullptr;

	//Health bar

	int hp;
	SDL_Texture* textureHp = nullptr;
	SDL_Texture* HBar = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

protected:

	Collider* boxCollider = nullptr;

};

#endif
