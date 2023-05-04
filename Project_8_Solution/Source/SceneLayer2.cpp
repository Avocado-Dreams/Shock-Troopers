#include "SceneLayer2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModulePickUps.h"

SceneLayer2::SceneLayer2(bool startEnabled) : Module(startEnabled)
{

}

SceneLayer2::~SceneLayer2()
{

}

// Load assets
bool SceneLayer2::Start()
{
	LOG("Loading UI assets");

	bool ret = true;
	palms = App->textures->Load("Assets/Sprites/Background/Palmeras.png");
	palms2 = App->textures->Load("Assets/Sprites/Background/Palmeras2.png");
	P1 = App->textures->Load("Assets/Sprites/Fonts/fontsUI.png");
	P1Shadow = App->textures->Load("Assets/Sprites/Fonts/fontsUI.png");
	FacePhoto = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Time = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Credits = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Weapon = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");
	Grenade = App->textures->Load("Assets/Sprites/UI/FacePhoto.png");

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

	SDL_Rect Shadow1 = { 18, 345, 17, 9 };
	App->render->Blit(P1Shadow, 8, 5, &Shadow1, 0);

	SDL_Rect Player1 = { 0, 345, 17, 9 };
	App->render->Blit(P1, 5, 5, &Player1, 0);

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

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLayer2::CleanUp()
{
	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}