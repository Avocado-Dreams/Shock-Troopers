#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 21

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneTeam;
class SceneIntro;
class SceneMenu;
class SceneRouteSelect;
class SceneLevel1;
class SceneLayer2;
class SceneGameOver;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleHelicopter;
class ModuleFinalBoss;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class ModulePickUps;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;
	ModulePlayer* player = nullptr;
	SceneTeam* sceneTeam = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneMenu* sceneMenu = nullptr;
	SceneRouteSelect* sceneRoute = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	SceneLayer2* sceneLayer2 = nullptr;
	SceneGameOver* sceneOver = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;
	ModulePickUps* pickUps = nullptr;
	ModuleHelicopter* helicopter = nullptr;
	ModuleFinalBoss* finalBoss = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;
	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__