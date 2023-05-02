#include "ModulePickUps.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"

bool ModulePickUps::Start()
{
	texture = App->textures->Load("Assets/Sprites/enemies.png");
	getPickUps = App->audio->LoadFx("Assets/Fx/laser.wav");

	return true;
}