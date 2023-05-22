#include "Application.h"
#include "SDL/include/SDL.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneTeam.h"
#include "SceneIntro.h"
#include "SceneMenu.h"
#include "SceneLevel1.h"
#include "SceneLayer2.h"
#include "SceneGameOver.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleFinalBoss.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModulePickUps.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow(true);
	modules[1] =	input =			new ModuleInput(true);
	modules[2] =	textures =		new ModuleTextures(true);
	modules[3] =	audio =			new ModuleAudio(true);

	modules[4] =    sceneTeam =     new SceneTeam(true);
	modules[5] =	sceneIntro =	new SceneIntro(false);
	modules[6] =	 sceneMenu =	new SceneMenu(false);
	modules[7] =	sceneLevel_1 =	new SceneLevel1(false);	//Gameplay scene starts disabled
	modules[8] =	player =		new ModulePlayer(false);	//Player starts disabled
	modules[9] =	enemies =		new ModuleEnemies(false);	//Enemies starts disabled
	modules[10] =	finalBoss =		new ModuleFinalBoss(false);
	modules[11] =	particles =		new ModuleParticles(true);//Boss starts disabled
	modules[12] =   sceneLayer2 =   new SceneLayer2(false);
	modules[13] =   sceneOver =     new SceneGameOver(false);

	modules[14] =	collisions =	new ModuleCollisions(true);
	modules[15] =	fade =			new ModuleFadeToBlack(true);
	modules[16] =   fonts =         new ModuleFonts(true);
	modules[17] =	pickUps =		new ModulePickUps(true);
	modules[18] =	render =		new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}


bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	SDL_Delay(16.66);

	return ret;

}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
