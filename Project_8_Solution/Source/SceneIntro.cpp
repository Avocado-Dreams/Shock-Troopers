#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include "SceneMenu.h"
#include <stdio.h>

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	//characters intro
	title.PushBack({ 0, 0, 304, 223 });
	title.PushBack({ 313, 0, 304, 223 });
	title.PushBack({ 627, 0, 304, 223 });
	title.PushBack({ 944, 0, 304, 223 });
	title.PushBack({ 1260, 0, 304, 223 });
	title.PushBack({ 1579, 0, 304, 223 });
	title.PushBack({ 1894, 0, 304, 223 });
	title.PushBack({ 0, 264, 304, 223 });
	title.PushBack({ 315, 265, 304, 223 });
	title.PushBack({ 625, 266, 304, 223 });

	//title intro animation
	title.PushBack({ 0, 500, 304, 223 });
	title.PushBack({ 311, 500, 304, 223 });
	title.PushBack({ 622, 500, 304, 223 });
	title.PushBack({ 934, 500, 304, 223 });
	title.PushBack({ 1246, 500, 304, 223 });
	title.PushBack({ 1558, 500, 304, 223 });
	title.PushBack({ 1867, 500, 304, 223 });
	title.PushBack({ 2176, 500, 304, 223 });
	title.PushBack({ 0, 733, 304, 223 });
	title.PushBack({ 311, 733, 304, 223 });
	title.PushBack({ 623, 733, 304, 223 });
	title.PushBack({ 935, 734, 304, 223 });
	title.PushBack({ 1248, 734, 304, 223 });
	title.PushBack({ 1559, 734, 304, 223 });
	title.PushBack({ 1869, 734, 304, 223 });
	title.PushBack({ 2176, 734, 304, 223 });
	title.PushBack({ 0, 965, 304, 223 });
	title.PushBack({ 311, 965, 304, 223 });
	title.PushBack({ 623, 965, 304, 223 });
	title.PushBack({ 935, 966, 304, 223 });
	title.PushBack({ 1248, 967, 304, 223 }); //S 
	title.PushBack({ 1559, 967, 304, 223 }); //h 
	title.PushBack({ 1868, 968, 304, 223 }); //o 
	title.PushBack({ 2176, 968, 304, 223 }); //c 
	title.PushBack({ 0, 1198, 304, 223 }); //k
	title.PushBack({ 311, 1199, 304, 223 }); //T
	title.PushBack({ 624, 1200, 304, 223 }); //r
	title.PushBack({ 936, 1201, 304, 223 }); //o
	title.PushBack({ 1249, 1202, 304, 223 }); //o
	title.PushBack({ 1559, 1202, 304, 223 }); //p
	title.PushBack({ 1868, 1201, 304, 223 }); //e
	title.PushBack({ 2176, 1202, 304, 223 }); //r
	title.PushBack({ 0, 1432, 304, 223 }); //s
	title.PushBack({ 312, 1432, 304, 223 });
	title.PushBack({ 624, 1432, 304, 223 });
	title.PushBack({ 936, 1432, 304, 223 });
	title.PushBack({ 1249, 1434, 304, 223 });
	title.PushBack({ 1560, 1434, 304, 223 });
	title.PushBack({ 1871, 1433, 304, 223 });

	title.speed = 0.2;
	title.loop = false;




}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;


	/*bgTexture = App->textures->Load("Assets/Sprites/startScreen.png");*/
	//bgTexture = App->textures->Load("Assets/Sprites/intro_sprites/shocktro004.png");
	App->audio->PlayMusic("Assets/Music/STIntro.ogg", 1.0f);

	introTexture = App->textures->Load("Assets/Sprites/intro_sprites/epicintro.png");
	CurrentIntro = &title;
	char lookupTable1[] = { "0123456789:;(=)? ABCDEFGHIJKLMNOPQRSTUVWXYZc!,-." };
	startFontt = App->fonts->Load("Assets/Sprites/Fonts/OrangeFont.png", lookupTable1, 3);
	startFontRect = { 0,0,128,8 }; 
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneMenu, 90); 
	}

	if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN) //saltar-se la intro  ir al juego
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	title.Update();
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	SDL_Rect rect = title.GetCurrentFrame();
	App->render->Blit(introTexture, 0, 0, &rect);


	sprintf_s(startFont, 32, "%c", App->sceneIntro->title);
	App->fonts->BlitText(20, 190, startFontt, "PRESS THE SPACE BUTTON TO START"); 
	return Update_Status::UPDATE_CONTINUE;
}

