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

	QuadSelect.PushBack({ 0,0, 32, 32 });
	QuadSelect.PushBack({ 33,0, 32, 32 });
	QuadSelect.PushBack({ 66,0, 32, 32 });
	QuadSelect.PushBack({ 99,0, 32, 32 });
	QuadSelect.PushBack({ 132,0, 32, 32 });
	QuadSelect.PushBack({ 165,0, 32, 32 });
	QuadSelect.PushBack({ 198,0, 32, 32 });
	QuadSelect.PushBack({ 231,0, 32, 32 });
	QuadSelect.PushBack({ 264,0, 32, 32 });
	QuadSelect.speed = 0.15;
	QuadSelect.loop = true;



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

	QuadPos_x = 137;
	QuadPos_y = 39;

	App->audio->PlayMusic("Assets/Music/MusicMenuSelect.ogg", 1.0f); 
	selectFx = App->audio->LoadFx("Assets/Fx/Change selection.wav"); //això posar-ho en el Update!!
	acceptSelectFx = App->audio->LoadFx("Assets/Fx/Accept selection.wav");

	Texture1 = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	CurrentAnimaton1 = &menu;

	QuadSelect1 = App->textures->Load("Assets/Sprites/UI/Spritesheet of all the UI elements/QuadSelect.png");
	CurrentAnimaton2 = &QuadSelect;


	Jackal = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	Milky = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	Loki = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	SouthernCross = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	MarieBee = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	Rio = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	Haru = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	BigMama = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	LonelyWolf = App->textures->Load("Assets/Sprites/intro_sprites/menu.png");
	TimeText = App->textures->Load("Assets/Sprites/UI/Spritesheet of all the UI elements/PlayerSelectText.png");
	PlayerSelect = App->textures->Load("Assets/Sprites/UI/Spritesheet of all the UI elements/PlayerSelectText.png");



	char lookupTable1[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz?!" };
	NameFont = App->fonts->Load("Assets/Sprites/Fonts/BlueFont.png", lookupTable1, 4);
	menuFontRect = { 0, 0, 128, 9 };  //lletres maj big blue font

	char lookupTable2[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ      " };
	NameFont2 = App->fonts->Load("Assets/Sprites/Fonts/BlueFontSmall.png", lookupTable2, 4);
	menuFontRect2 = { 0, 0, 64, 8 };  //small blue font 


	char lookupTable3[] = { "0123456789:;(=)? ABCDEFGHIJKLMNOPQRSTUVWXYZc!,-." };
	startFontt = App->fonts->Load("Assets/Sprites/Fonts/OrangeFont.png", lookupTable3, 3);
	startFontRect = { 0,0,128,8 };



	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneMenu::Update()
{
	// MENU CONDITIONS 
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
	{
		if (QuadPos_x < 233) {
			QuadPos_x += 32;
		}
		else {
			QuadPos_x = 233;
		}


	}

	else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
	{
		if (QuadPos_x > 137) {
			QuadPos_x -= 32;
		}
		else {
			QuadPos_x = 137;
		}

	}

	else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN)
	{
		if (QuadPos_y > 40) {
			QuadPos_y -= 32;
		}
		else {
			QuadPos_y = 39;

		}
	}

	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
	{
		if (QuadPos_y < 70) {
			QuadPos_y += 32;
		}
		else {
			QuadPos_y = 71;

		}
	}

	menu.Update();
	QuadSelect.Update();

	return Update_Status::UPDATE_CONTINUE;
	
}

Update_Status SceneMenu::PostUpdate()
{
		// Draw everything --------------------------------------
		SDL_Rect rectM = menu.GetCurrentFrame();
		App->render->Blit(Texture1, 0, 0, &rectM);

		//Calculate time transcurred
		Uint32 currentTime = SDL_GetTicks() - startTime;

		if (lastPos_x == QuadPos_x && lastPos_y == QuadPos_y) {
			soundPlayed = true;
		}
		else {
			soundPlayed = false;
		}
	
		if (currentTime >= 2000) //(2 seconds!)
		{
			//Draw characters

			if ((QuadPos_x == 137) && (QuadPos_y == 39)) {
				SDL_Rect IsJackal{ 0,249,91,62 };
				App->render->Blit(Jackal, 42, 47, &IsJackal, 0);

				sprintf_s(MenuFont, 65, "%c", App->sceneMenu->menu);
				App->fonts->BlitText(30, 100, NameFont, "JACKAL");

				SDL_Rect rectQuadSelect = QuadSelect.GetCurrentFrame();
				App->render->Blit(QuadSelect1, 136, 38, &rectQuadSelect);

				if (!soundPlayed)
				{
					App->audio->PlayFx(selectFx);
					soundPlayed = true;
				}

			}

			else if ((QuadPos_x == 169) && (QuadPos_y == 39)) {

				SDL_Rect IsMilky{ 103, 250, 91, 62 };
				App->render->Blit(Milky, 40, 47, &IsMilky, 0);

				sprintf_s(MenuFont, 65, "%c", App->sceneMenu->menu);
				App->fonts->BlitText(30, 100, NameFont, "MILKY");

				SDL_Rect rectQuadSelect = QuadSelect.GetCurrentFrame();
				App->render->Blit(QuadSelect1, 168, 38, &rectQuadSelect);

				if (!soundPlayed)
				{
					App->audio->PlayFx(selectFx);
					soundPlayed = true;
				}
				
				if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
				{
					App->audio->PlayFx(acceptSelectFx);
					App->fade->FadeToBlack(this, (Module*)App->sceneRoute, 90);
				}

			}

			else if ((QuadPos_x == 201) && (QuadPos_y == 39)) {
				SDL_Rect IsLoki{ 219, 250, 91, 62 };
				App->render->Blit(Loki, 41, 47, &IsLoki, 0);

				sprintf_s(MenuFont, 65, "%c", App->sceneMenu->menu);
				App->fonts->BlitText(30, 100, NameFont, "LOKI");

				SDL_Rect rectQuadSelect = QuadSelect.GetCurrentFrame();
				App->render->Blit(QuadSelect1, 200, 38, &rectQuadSelect);

				if (!soundPlayed)
				{
					App->audio->PlayFx(selectFx);
					soundPlayed = true;
				}
				
			}

			else if ((QuadPos_x == 233) && (QuadPos_y == 39)) {
				SDL_Rect IsSouthernCross{ 327, 250,91,62 };
				App->render->Blit(SouthernCross, 42, 47, &IsSouthernCross, 0);

				sprintf_s(MenuFont2, 42, "%c", App->sceneMenu->menu);
				App->fonts->BlitText(30, 100, NameFont2, "SOUTHERN");

				sprintf_s(MenuFont2, 42, "%c", App->sceneMenu->menu);
				App->fonts->BlitText(30, 110, NameFont2, "CROSS");

				SDL_Rect rectQuadSelect = QuadSelect.GetCurrentFrame();
				App->render->Blit(QuadSelect1, 232, 38, &rectQuadSelect); 

				if (!soundPlayed)
				{
					App->audio->PlayFx(selectFx);
					soundPlayed = true;
				}
				
			}

			else if ((QuadPos_x == 137) && (QuadPos_y == 71)) {
				SDL_Rect IsMarieBee{ 438, 250, 91, 62 };
				App->render->Blit(MarieBee, 42, 47, &IsMarieBee, 0);

				sprintf_s(MenuFont2, 42, "%c", App->sceneMenu->menu);
				App->fonts->BlitText(30, 100, NameFont2, "MARIE");
				sprintf_s(MenuFont2, 42, "%c", App->sceneMenu->menu);
				App->fonts->BlitText(30, 110, NameFont2, "BEE");

				SDL_Rect rectQuadSelect = QuadSelect.GetCurrentFrame();
				App->render->Blit(QuadSelect1, 136, 70, &rectQuadSelect); 

				if (!soundPlayed)
				{
					App->audio->PlayFx(selectFx);
					soundPlayed = true;
				}
				
			}

			else if ((QuadPos_x == 169) && (QuadPos_y == 71)) {
				SDL_Rect IsRio{ 550, 250, 91, 62 };
				App->render->Blit(Rio, 42, 47, &IsRio, 0);

				sprintf_s(MenuFont, 65, "%c", App->sceneMenu->menu);
				App->fonts->BlitText(30, 100, NameFont, "RIO");

				SDL_Rect rectQuadSelect = QuadSelect.GetCurrentFrame();
				App->render->Blit(QuadSelect1, 168, 70, &rectQuadSelect);

				if (!soundPlayed)
				{
					App->audio->PlayFx(selectFx);
					soundPlayed = true;
				}
				
			}

			else if ((QuadPos_x == 201) && (QuadPos_y == 71)) {
				SDL_Rect IsHaru{ 676, 250, 91, 62 };
				App->render->Blit(Haru, 42, 47, &IsHaru, 0);

				sprintf_s(MenuFont, 65, "%c", App->sceneMenu->menu);
				App->fonts->BlitText(30, 100, NameFont, "HARU");

				SDL_Rect rectQuadSelect = QuadSelect.GetCurrentFrame();
				App->render->Blit(QuadSelect1, 200, 70, &rectQuadSelect);

				if (!soundPlayed)
				{
					App->audio->PlayFx(selectFx);
					soundPlayed = true;
				}
				
			}

			else if ((QuadPos_x == 233) && (QuadPos_y == 71)) {
				SDL_Rect IsBigMama{ 787, 250, 91, 62 };
				App->render->Blit(BigMama, 42, 47, &IsBigMama, 0);

				sprintf_s(MenuFont2, 42, "%c", App->sceneMenu->MenuFont2);
				App->fonts->BlitText(30, 100, NameFont2, "BIG"); 
				sprintf_s(MenuFont2, 42, "%c", App->sceneMenu->MenuFont2);
				App->fonts->BlitText(30, 110, NameFont2, "MAMA");

				SDL_Rect rectQuadSelect = QuadSelect.GetCurrentFrame();
				App->render->Blit(QuadSelect1, 232, 70, &rectQuadSelect);
				
				if (!soundPlayed)
				{
					App->audio->PlayFx(selectFx);
					soundPlayed = true;
				}

			}

			soundPlayed = false;
			//draw design items
			SDL_Rect rectLonelyWolf{ 1631, 3, 66,34 };
			App->render->Blit(LonelyWolf, 7, 25, &rectLonelyWolf);

			SDL_Rect rectTimeText{ 152, 112, 63, 16 };
			App->render->Blit(TimeText, 152, 112, &rectTimeText);
			//TEMPORITZADOR?

			lastPos_x = QuadPos_x;
			lastPos_y = QuadPos_y;
		}

		SDL_Rect rectPlayerSelect{ 48, 7, 208, 17 };
		App->render->Blit(PlayerSelect, 48, 6, &rectPlayerSelect);

		sprintf_s(startFont, 32, "%c", App->sceneMenu->menu);
		App->fonts->BlitText(15, 194, startFontt, "HINT: SELECT MILKY TO PLAY");




		return Update_Status::UPDATE_CONTINUE;
}




