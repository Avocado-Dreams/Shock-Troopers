#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

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

	void OnCollision();

	bool contador;
	bool contador2;
	int reloj;

	bool enemy1Spawned;
	bool enemy2Spawned;
	bool enemy3Spawned;
	bool enemy4Spawned;
	bool enemy5Spawned;
	bool enemy6Spawned;
	bool enemy7Spawned;
	bool enemy8Spawned;
	bool enemy9Spawned;
	bool enemy10Spawned;
	bool enemy11Spawned;
	bool enemy12Spawned;
	bool enemy13Spawned;
	bool enemy14Spawned;
	bool enemy15Spawned;
	bool enemy16Spawned;
	bool enemy17Spawned;
	bool enemy18Spawned;
	bool enemy19Spawned;
	bool enemy20Spawned;
	bool enemy21Spawned;
	bool enemy22Spawned;
	bool enemy23Spawned;
	bool enemy24Spawned;
	bool enemy25Spawned;
	bool enemy26Spawned;
	bool enemy27Spawned;
	bool enemy28Spawned;
	bool enemy29Spawned;
	bool enemy30Spawned;
	bool enemy31Spawned;
	bool enemy32Spawned;
	bool enemy33Spawned;
	bool enemy34Spawned;
	bool enemy35Spawned;
	bool enemy36Spawned;
	bool enemy37Spawned;
	bool enemy38Spawned;
	bool enemy39Spawned;
	bool enemy40Spawned;
	bool enemy41Spawned;
	bool enemy42Spawned;
	bool enemy43Spawned;
	bool enemy44Spawned;
	bool enemy45Spawned;
	bool enemy46Spawned;
	bool enemy47Spawned;
	bool enemy48Spawned;
	bool enemy49Spawned;
	bool enemy50Spawned;
	bool enemy51Spawned;
	bool enemy52Spawned;
	bool enemy53Spawned;
	bool enemy54Spawned;
	bool enemy55Spawned;
	bool enemy56Spawned;
	bool enemy57Spawned;
	bool enemy58Spawned;
	bool enemy59Spawned;
	bool enemy60Spawned;
	bool enemy61Spawned;
	bool enemy62Spawned;
	bool enemy63Spawned;
	bool enemy64Spawned;
	bool enemy65Spawned;
	bool enemy66Spawned;

	SDL_Texture* textureSky = nullptr;
	SDL_Rect sky;



public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

};

#endif