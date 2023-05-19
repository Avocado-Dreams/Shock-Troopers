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
#include <stdio.h>
#include <iostream>
#include "SDL/include/SDL.h"

SceneLayer2::SceneLayer2(bool startEnabled) : Module(startEnabled)
{

}

SceneLayer2::~SceneLayer2()
{

}

void SceneLayer2 ::updateHp()
{
	//Carga sprite en base a la vida del jugador
	switch (hp) {
	case 100:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida100%.png");
		break;
	case 90:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida90%.png");
		break;
	case 80:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida80%.png");
		break;
	case 70:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida70%.png");
		break;
	case 60:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida60%.png");
		break;
	case 50:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida50%.png");
		break;
	case 40:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida40%.png");
		break;
	case 30:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida30%.png");
		break;
	case 20:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida20%.png");
		break;
	case 10:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida10%.png");
		break;
	case 0:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida0%.png");
		destroyed = true;
		break;
	default:
		textureHp = App->textures->Load("Assets/Sprites/UI/Vida100%.png");
		break;
	}
}

// Load assets
bool SceneLayer2::Start()
{
	LOG("Loading UI assets");

	bool ret = true;
	palms = App->textures->Load("Assets/Sprites/Background/Palmeras.png");
	palms2 = App->textures->Load("Assets/Sprites/Background/Palmeras2.png");
	P1 = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	FacePhoto = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	PhotoFrame = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Time = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Credits = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Weapon = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Grenade = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");

	char lookupTableTimer[] = { "0123456789" };
	timerFont = App->fonts->Load("Assets/Sprites/Fonts/numberTime.png", lookupTableTimer);
	timerRect = { 0, 0, 30, 8 };
	char lookupTable[] = { "0123456789:;(=)? abcdefghijklmnopqrstuvwxyz@!.-." };
	scoreFont = App->fonts->Load("Assets/Sprites/Fonts/OrangeFont.png", lookupTable, 3);
	updateHp();

	return ret;
}

Update_Status SceneLayer2::Update()
{

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLayer2::PostUpdate()
{
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

	SDL_Rect NameCredits = { 207, 216, 58, 8 };
	App->render->Blit(Credits, 200, 205, &NameCredits, 0);

	SDL_Rect IconWeapon = { 48, 199, 33, 18 };
	App->render->Blit(Weapon, 48, 198, &IconWeapon, 0);

	SDL_Rect IconGrenade = { 9, 201, 33, 16 };
	App->render->Blit(Grenade, 9, 199, &IconGrenade, 0);

	FramePlayer();

	//Time

	if (timerpass < 180)
	{
		App->render->Blit(bgTexture2, 0, 0);
	}
	if (timerpass > 180)
	{
		App->render->Blit(bgTexture3, 0, 0);
	}

	sprintf_s(scoreText, 10, "%08d", App->player->score);
	App->fonts->BlitText(38, 5, scoreFont, scoreText);

	sprintf_s(timerText, 10, "%2d", App->player->timer);
	App->fonts->BlitText(143, 17, timerFont, timerText);


	//Health Bar
	SDL_Rect HBar = { 0, 0, 8, 132 };
	App->render->Blit(textureHp, 8, 60, &HBar, 0);

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

bool SceneLayer2::CleanUp()
{
	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}