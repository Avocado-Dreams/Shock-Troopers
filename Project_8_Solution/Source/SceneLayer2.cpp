#include "SceneLayer2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModulePickUps.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "ModuleHelicopter.h"
#include <stdio.h>
#include <iostream>
#include "SDL/include/SDL.h"

SceneLayer2::SceneLayer2(bool startEnabled) : Module(startEnabled)
{
	//Life 100
	life100.PushBack({ 185, 5, 8, 132 });
	life100.loop = false;
	life100.speed = 0.0f;
	//Life 90
	life90.PushBack({ 167, 5, 8, 132 });
	life90.loop = false;
	life90.speed = 0.0f;
	//Life 80
	life80.PushBack({ 149, 5, 8, 132 });
	life80.loop = false;
	life80.speed = 0.0f;
	//Life 70
	life70.PushBack({ 131, 5, 8, 132 });
	life70.loop = false;
	life70.speed = 0.0f;
	//Life 60
	life60.PushBack({ 113, 5, 8, 132 });
	life60.loop = false;
	life60.speed = 0.0f;
	//Life 50
	life50.PushBack({ 59, 5, 8, 132 });
	life50.loop = false;
	life50.speed = 0.0f;
	//Life 40
	life40.PushBack({ 95, 5, 8, 132 });
	life40.loop = false;
	life40.speed = 0.0f;
	//Life 30
	life30.PushBack({ 77, 5, 8, 132 });
	life30.loop = false;
	life30.speed = 0.0f;
	//Life 20
	life20.PushBack({ 41, 5, 8, 132 });
	life20.loop = false;
	life20.speed = 0.0f;
	//Life 10
	life10.PushBack({ 23, 5, 8, 132 });
	life10.loop = false;
	life10.speed = 0.0f;
	//Life 0
	life0.PushBack({ 5, 5, 8, 132 });
	life0.loop = false;
	life0.speed = 0.0f;

}

SceneLayer2::~SceneLayer2()
{

}

void SceneLayer2::updateHp()
{
	if (hp > 90)
	{
		currentHP = &life100;
	}
	if (hp > 80 && hp <= 90)
	{
		currentHP = &life90;
	}
	if (hp > 70 && hp <= 80)
	{
		currentHP = &life80;
	}
	 if (hp > 60 && hp <= 70)
	{
		currentHP = &life70;
	}
	 if (hp > 50 && hp <= 60)
	{
		currentHP = &life60;
	}
	 if (hp > 40 && hp <= 50)
	{
		currentHP = &life50;
	}
	 if (hp > 30 && hp <= 40)
	{
		currentHP = &life40;
	}
	 if (hp > 20 && hp <= 30)
	{
		currentHP = &life30;
	}
	 if (hp > 10 && hp <= 20)
	{
		currentHP = &life20;
	}
	 if (hp > 0 && hp <= 10)
	{
		currentHP = &life10;
	}
	 if (hp <= 0)
	{
		currentHP = &life0;
		destroyed = true;
	}
	//Carga sprite en base a la vida del jugador
	/*switch (hp) {
	case 100:
		currentHP = &life100;
		break;
	case 90:
		currentHP = &life90;
		break;
	case 80:
		currentHP = &life80;
		break;
	case 70:
		currentHP = &life70;
		break;
	case 60:
		currentHP = &life60;
		break;
	case 50:
		currentHP = &life50;
		break;
	case 40:
		currentHP = &life40;
		break;
	case 30:
		currentHP = &life30;;
		break;
	case 20:
		currentHP = &life20;
		break;
	case 10:
		currentHP = &life10;
		break;
	case 0:
		currentHP = &life0;
		destroyed = true;
		break;
	default:
		currentHP = &life100;
		break;
	}*/
}

// Load assets
bool SceneLayer2::Start()
{
	LOG("Loading UI assets");

	currentHP = &life100;
	Time1 = SDL_GetTicks();

	bool ret = true;
	palms = App->textures->Load("Assets/Sprites/Background/Palmeras.png");
	palms2 = App->textures->Load("Assets/Sprites/Background/Palmeras2.png");
	P1 = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	FacePhoto = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	PhotoFrame = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Time = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Weapon = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Grenade = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	GoUp = App->textures->Load("Assets/Sprites/UI/GoUp.png");
	GoRight = App->textures->Load("Assets/Sprites/UI/GoRight.png");

	char lookupTableTimer[] = { "0123456789" };
	timerFont = App->fonts->Load("Assets/Sprites/Fonts/numberTime.png", lookupTableTimer);
	timerRect = { 0, 0, 30, 8 };

	char lookupTable[] = { "0123456789:;(=)? abcdefghijklmnopqrstuvwxyz@!.-." };
	scoreFont = App->fonts->Load("Assets/Sprites/Fonts/OrangeFont.png", lookupTable, 3);

	char lookupTableStages[] = { "    ABCDEFGHIJKLMNOPQRSTUVWXYZ   1234567890?!;:-" };
	stageFont = App->fonts->Load("Assets/Sprites/Fonts/FontStage.png", lookupTableStages, 6);
	stageFontRect = { 0, 0, 128, 16 };

	HBar = App->textures->Load("Assets/Sprites/UI/HBar.png");
	hp = App->player->vida;

	return ret;
}

Update_Status SceneLayer2::Update()
{
	//LOG("%d", App->player->vida);
	hp = App->player->vida;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLayer2::PostUpdate()
{
	Uint32 currentTime = SDL_GetTicks() - Time1; //time transcurred

	// Draw everything --------------------------------------

	SDL_Rect palmeras{ 40, 0, 374, 1164 };
	App->render->Blit(palms, 0, 2226, &palmeras);

	SDL_Rect palmeras2{ 0, 0, 371, 569 };
	App->render->Blit(palms2, 2050, 1114, &palmeras2);

	SDL_Rect Player1 = { 10, 8, 21, 8 };
	App->render->Blit(P1, 10, 6, &Player1, 0);

	SDL_Rect MilkyPhoto = { 8, 16, 16, 16 };
	App->render->Blit(FacePhoto, 7, 15, &MilkyPhoto, 0);

	SDL_Rect Timer = { 137, 8, 30, 8 };
	App->render->Blit(Time, 136, 7, &Timer, 0);

	SDL_Rect IconWeapon = { 48, 199, 33, 18 };
	App->render->Blit(Weapon, 48, 198, &IconWeapon, 0);

	SDL_Rect IconGrenade = { 9, 201, 33, 16 };
	App->render->Blit(Grenade, 9, 199, &IconGrenade, 0);

	FramePlayer();
	FrameGO(); //GO!!

	//Time

	//if (timerpass < 180)
	//{
	//	App->render->Blit(bgTexture2, 0, 0);
	//}
	//if (timerpass > 180)
	//{
	//	App->render->Blit(bgTexture3, 0, 0);
	//}

	sprintf_s(scoreText, 10, "%08d", App->player->score);
	App->fonts->BlitText(38, 5, scoreFont, scoreText);

	sprintf_s(timerText, 10, "%2d", App->player->timer);
	App->fonts->BlitText(143, 17, timerFont, timerText);


	if (currentTime <= 2000) //(2 seconds!)
	{
		sprintf_s(LevelFont, 49, "%c", App->sceneLayer2->bgTexture3);
		App->fonts->BlitText(100, 80, stageFont, "STAGE 1");
		App->fonts->BlitText(110, 100, stageFont, "START");
	}

	//Health Bar
	updateHp();
	SDL_Rect hpBarPosition = { 8, 60, 8, 132 };
	App->render->Blit(HBar, hpBarPosition.x, hpBarPosition.y, &(currentHP->GetCurrentFrame()), 0);



	return Update_Status::UPDATE_CONTINUE;
}

void SceneLayer2::FramePlayer()
{
	const int FRAMES = 2;

	if (NameColor && timer < FRAMES) timer++;
	else if (NameColor && timer >= FRAMES)
	{
		NameColor = false;
		timer = 0;
	}
	else if (!NameColor && timer < FRAMES) {

		SDL_Rect WhiteFrame = { 8, 34, 16, 16 };
		App->render->Blit(PhotoFrame, 7, 15, &WhiteFrame, 0);
		timer++;

	}
	else if (!NameColor && timer >= FRAMES) {
		timer = 0;
		NameColor = true;
	}
}

void SceneLayer2::FrameGO()
{
	const int FRAMES = 8;

	if (NameColor2 && timer2 < FRAMES) timer2++;
	else if (NameColor2 && timer2 >= FRAMES)
	{
		NameColor2 = false;
		timer2 = 0;
	}
	else if (!NameColor2 && timer2 < FRAMES) { //GO!! conditions

		if (App->player->position.y < 2790 && App->player->position.y > 2690) {
			SDL_Rect rectGoUp = { 0, 0, 47, 38 };
			App->render->Blit(GoUp, 125, 32, &rectGoUp, 0);
		}

		if (App->player->position.x > 220 && App->player->position.y < 2025 && App->player->position.x < 320) {
			SDL_Rect rectGoRight = { 0, 0, 47, 40 };
			App->render->Blit(GoRight, 240, 100, &rectGoRight, 0);
		}

		if (App->player->position.x > 1020 && App->player->position.x < 1170 && App->helicopter->helicopterDestroyed == true) {
			SDL_Rect rectRight2 = { 0, 0, 47, 40 };
			App->render->Blit(GoRight, 240, 100, &rectRight2, 0);
		}

		if (App->player->position.x > 2214 && App->player->position.y < 1920 && App->player->position.y > 1810) {
			SDL_Rect rectGoUp2 = { 0, 0, 47, 38 };
			App->render->Blit(GoUp, 125, 32, &rectGoUp2, 0);
		}

		timer2++;

	}
	else if (!NameColor2 && timer2 >= FRAMES) {
		timer2 = 0;
		NameColor2 = true;
	}
}

bool SceneLayer2::CleanUp()
{
	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}
