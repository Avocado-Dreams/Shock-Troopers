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
	box.loop = false;

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

	//collider = App->collisions->AddCollider({ 0, 0, 29, 38 }, Collider::Type::BOX, this);

}

ModuleObstacles::~ModuleObstacles()
{

}

// Load assets
bool ModuleObstacles::Start()
{
	LOG("Loading UI assets");

	currentBox = &box;
	currentDBox = &boxDestroyed;

	textureBox = App->textures->Load("Assets/Sprites/Others/Box.png");

	bool ret = true;


	return ret;
}

Update_Status ModuleObstacles::Update()
{

	box.Update();
	boxDestroyed.Update();
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ModuleObstacles::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect boxPosition = { 95, 50, 29, 38 };
	App->render->Blit(textureBox, 80, 2880, &boxPosition);




	return Update_Status::UPDATE_CONTINUE;
}


bool ModuleObstacles::CleanUp()
{
	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}

void ModuleObstacles::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == Collider::Type::PLAYER)
	{
		if (!boxIsDestroyed)
		{
			// Evitar que el personaje se mueva hacia arriba si está por encima de la caja
			if (position.y < c2->rect.y + c2->rect.h)
			{
				position.y = c2->rect.y + c2->rect.h;
			}
			// Evitar que el personaje se mueva hacia abajo si está por debajo de la caja
			if (position.y + 43 > c2->rect.y)
			{
				position.y = c2->rect.y - 43; //43 = player height
			}
			// Evitar que el personaje se mueva hacia la izquierda si está a la izquierda de la caja
			if (position.x < c2->rect.x + c2->rect.w)
			{
				position.x = c2->rect.x + c2->rect.w;
			}
			// Evitar que el personaje se mueva hacia la derecha si está a la derecha de la caja
			if (position.x + 33 > c2->rect.x) //33 = player width
			{
				position.x = c2->rect.x - 33;
			}
		}
		else
		{


		}
	}

}