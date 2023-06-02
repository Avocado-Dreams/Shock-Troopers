#include "ModuleObstacles.h"

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

ModuleObstacles::ModuleObstacles(bool startEnabled) : Module(startEnabled)
{
	//Inactive box
	box.PushBack({ 85, 50, 29, 38 });

	//Destroy box
	boxDestroyed.PushBack({ 95, 50, 29, 38 });
	boxDestroyed.PushBack({ 135, 44, 43, 44 });
	boxDestroyed.PushBack({ 188, 38, 54, 51 });
	boxDestroyed.PushBack({ 255, 37, 64, 52 });
	boxDestroyed.PushBack({ 329, 38, 63, 53 });
	boxDestroyed.PushBack({ 403, 41, 63, 50 });
	boxDestroyed.PushBack({ 476, 49, 64, 39 });
	boxDestroyed.PushBack({ 550, 54, 64, 34 });
	boxDestroyed.PushBack({ 625, 59, 63, 31 });
	boxDestroyed.loop = false;
	boxDestroyed.speed = 0.3f;

}

ModuleObstacles::~ModuleObstacles()
{

}

// Load assets
bool ModuleObstacles::Start()
{
	LOG("Loading UI assets");

	textureBox = App->textures->Load("Assets/Sprites/Others/Box.png");
	currentBox = &box;
	currentDBox = &boxDestroyed;

	collider = App->collisions->AddCollider({ 90, 2837, 29, 38 }, Collider::Type::BOX, this);

	bool ret = true;

	return ret;
}

Update_Status ModuleObstacles::Update()
{
	


	boxDestroyed.Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ModuleObstacles::PostUpdate()
{
	// Draw everything --------------------------------------

	if (!boxIsDestroyed)
	{
		SDL_Rect boxPosition = { 96, 50, 29, 38 };
		App->render->Blit(textureBox, 90, 2837, &boxPosition);
	}

	
	

	return Update_Status::UPDATE_CONTINUE;
}


bool ModuleObstacles::CleanUp()
{
	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}

void ModuleObstacles::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::BOX)
	{
		LOG("Box being shot")
		life = 0;
		if (life <= 0)
		{
			SDL_Rect rectBox1 = boxDestroyed.GetCurrentFrame();
			App->render->Blit(textureBox, 90, 2837, &rectBox1);
			boxIsDestroyed = true;

		}
	}


}