#include "SceneRouteSelect.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "SceneIntro.h"
#include "ModuleFadeToBlack.h"
#include <stdio.h>
#include <SDL/include/SDL_timer.h>


SceneRouteSelect::SceneRouteSelect(bool startEnabled) : Module(startEnabled)
{
	// animation intro
	jungleRoute.PushBack({ 0, 0, 304, 223 });
	jungleRoute.PushBack({ 310, 0, 304, 223 });
	jungleRoute.PushBack({ 622, 0, 304, 223 });
	jungleRoute.PushBack({ 932, 0, 304, 223 });
	jungleRoute.PushBack({ 1245, 0, 304, 223 });
	jungleRoute.PushBack({ 1555, 0, 304, 223 });
	jungleRoute.PushBack({ 1866, 0, 304, 223 });
	jungleRoute.PushBack({ 2176, 0, 304, 223 });

	jungleRoute.PushBack({ 0, 239, 304, 223 });
	jungleRoute.PushBack({ 311,240, 304, 223 });
	jungleRoute.PushBack({ 623, 241, 304, 223 });
	jungleRoute.PushBack({ 934, 242, 304, 223 });
	jungleRoute.PushBack({ 1247, 242, 304, 223 });
	jungleRoute.PushBack({ 1556, 243, 304, 223 });
	jungleRoute.PushBack({ 1866, 243, 304, 223 });
	jungleRoute.PushBack({ 2176, 243, 304, 223 });
	
	jungleRoute.PushBack({ 0, 482, 304, 223 });
	jungleRoute.PushBack({ 312,482, 304, 223 });
	jungleRoute.PushBack({ 625, 482, 304, 223 });//19
	jungleRoute.PushBack({ 936, 966, 304, 223 });//20
	jungleRoute.PushBack({ 1247, 965, 304, 223 });//21
	jungleRoute.PushBack({ 1558, 965, 304, 223 });//22
	jungleRoute.PushBack({ 938, 481, 304, 223 });//22
	jungleRoute.PushBack({ 1250, 480, 304, 223 });
	jungleRoute.PushBack({ 1868, 480, 304, 223 }); //25
	jungleRoute.PushBack({ 1558, 480, 304, 223 });//24

	jungleRoute.PushBack({ 0, 962, 304, 223 });//26
	jungleRoute.PushBack({ 313, 966, 304, 223 });//27

	jungleRoute.PushBack({ 625, 966, 304, 223 });//28
	jungleRoute.PushBack({ 2175, 482, 304, 223 });//29

	
	
	jungleRoute.PushBack({ 1, 719, 304, 223 }); //30
	jungleRoute.PushBack({ 313,718, 304, 223 }); //31
	jungleRoute.PushBack({ 2176, 718, 304, 223 });//32
	jungleRoute.PushBack({ 626, 717, 304, 223 }); //33
	
	jungleRoute.PushBack({ 2181, 963, 304, 223 });//34
	jungleRoute.PushBack({ 939, 717, 304, 223 }); //35

	jungleRoute.PushBack({ 1251, 716, 304, 223 });//36
	jungleRoute.PushBack({ 1564, 716, 304, 223 });//37
	jungleRoute.PushBack({ 1869, 715, 304, 223 });//38

	jungleRoute.speed = 0.2;
	jungleRoute.loop = false;


}

SceneRouteSelect::~SceneRouteSelect()
{

}

// Load assets
bool SceneRouteSelect::Start()
{
	LOG("Loading menu assets");

	bool ret = true;
	startTime = SDL_GetTicks();

	App->audio->PlayMusic("Assets/Music/MusicMenuSelect.ogg", 1.0f); 

	Route1 = App->textures->Load("Assets/Sprites/intro_sprites/ruta jungle.png");
	CurrentAnimaton1 = &jungleRoute;


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneRouteSelect::Update()
{
	jungleRoute.Update();
	

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneRouteSelect::PostUpdate()
{
	// Draw everything --------------------------------------
	//App->render->Blit(bgTexture, 0, 0, NULL);
	SDL_Rect rectJR = jungleRoute.GetCurrentFrame();
	App->render->Blit(Route1, 0, 0, &rectJR);
	
	Uint32 currentTime = SDL_GetTicks() - startTime;
	if (currentTime >= 2700) //(3 seconds aprox)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);

	}


	return Update_Status::UPDATE_CONTINUE;
}




