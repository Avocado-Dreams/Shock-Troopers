#include "SceneMenu.h"

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


SceneMenu::SceneMenu(bool startEnabled) : Module(startEnabled)
{
	//menu animation intro
	menu.PushBack({ 0, 0, 304, 223 });
	menu.PushBack({ 311, 0, 304, 223 });
	menu.PushBack({ 629, 0, 304, 223 });
	menu.PushBack({ 941, 0, 304, 223 });
	menu.PushBack({ 1324, 0, 304, 223 });
	menu.speed = 0.1;
	menu.loop = false;




}

SceneMenu::~SceneMenu()
{

}

// Load assets
bool SceneMenu::Start()
{
	LOG("Loading menu assets");

	bool ret = true;
	startTime = SDL_GetTicks();
	showCharacters[0][0] = false;

	/*bgTexture = App->textures->Load("Assets/Sprites/startScreen.png");*/
	App->audio->PlayMusic("Assets/Music/STIntro.ogg", 1.0f); // MENú MUSIC?

	Texture1 = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	CurrentAnimaton1 = &menu;


	Jackal = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	Milky = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	Loki = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	SouthernCross = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	MarieBee = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	Rio = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	Haru = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	BigMama = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	LonelyWolf = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	QuadSelect = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");


	char lookupTable1[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz?!" };
	NameFont = App->fonts->Load("Assets/Sprites/Fonts/BlueFont.png", lookupTable1, 7);
	menuFontRect = { 0,0,207,9 };  //lletres maj big blue font

	char lookupTable2[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	NameFont2 = App->fonts->Load("Assets/Sprites/Fonts/BlueFont.png", lookupTable2, 8);
	menuFontRect2 = { 0,19,127,10 };  //small blue font CANVIAR 10 per 65!


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneMenu::Update()
{
	// MENU CONDITIONS 
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				if (j >= 4)
					showCharacters[i][j] = showCharacters[i][4];
				else
				{
					showCharacters[i][j + 1] = true;
				}
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				if (j <= 0)
				showCharacters[i][j] = showCharacters[i][0];
				else
				{
					showCharacters[i][j - 1] = true;
				}

			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				showCharacters[i][j] = (i == 0);

			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				showCharacters[i][j] = (i == 1);

			}
		}

	}


	// to change scenes
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	menu.Update();
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	SDL_Rect rectM = menu.GetCurrentFrame();
	App->render->Blit(Texture1, 0, 0, &rectM);


	//Calculate time transcurred
	Uint32 currentTime = SDL_GetTicks() - startTime;
	if (currentTime >= 2000) //(2 seconds!)
	{
		//Draw characters
		if (showCharacters[0][0]) {
			SDL_Rect IsJackal{ 0,249,91,62 };
			App->render->Blit(Jackal, 42, 47, &IsJackal, 0);
		}

		else if (showCharacters[0][1]) {
			SDL_Rect IsMilky{ 103, 250, 91, 62 };
			App->render->Blit(Milky, 41, 47, &IsMilky, 0);
			//sprintf_s(MenuFont2, 65, "%c", App->sceneMenu->menu);
			//App->fonts->BlitText(20, 160, NameFont2, "Milky"); 
		}

		else if (showCharacters[0][2]) {
			SDL_Rect IsLoki{ 219, 250, 91, 62 };
			App->render->Blit(Loki, 42, 47, &IsLoki, 0);
		}

		else if (showCharacters[0][3]) {
			SDL_Rect IsSouthernCross{ 327, 250,91,62 };
			App->render->Blit(SouthernCross, 42, 47, &IsSouthernCross, 0);
			//sprintf_s(MenuFont, 27, "%c", App->sceneMenu->menu);
			//App->fonts->BlitText(70, 120, NameFont, "SOUTHERN CROSS");
		}

		else if (showCharacters[1][0]) {
			SDL_Rect IsMarieBee{ 438, 250, 91, 62 };
			App->render->Blit(MarieBee, 42, 47, &IsMarieBee, 0);
		}

		else if (showCharacters[1][1]) {
			SDL_Rect IsRio{ 550, 250, 91, 62 };
			App->render->Blit(Rio, 42, 47, &IsRio, 0);
		}

		else if (showCharacters[1][2]) {
			SDL_Rect IsHaru{ 676, 250, 91, 62 };
			App->render->Blit(Haru, 42, 47, &IsHaru, 0);
		}

		else if (showCharacters[1][3]) {
			SDL_Rect IsBigMama{ 787, 250, 91, 62 };
			App->render->Blit(BigMama, 42, 47, &IsBigMama, 0);
		}

		//draw design items
		SDL_Rect rectLonelyWolf{ 1631, 3, 66,34 };
		App->render->Blit(LonelyWolf, 7, 24, &rectLonelyWolf);

		SDL_Rect rectQuadSelect{ 1706, 4, 32, 32 };
		App->render->Blit(QuadSelect, 136, 38, &rectQuadSelect);
	}




	return Update_Status::UPDATE_CONTINUE;
}








