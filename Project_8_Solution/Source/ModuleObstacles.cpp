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


	collider = App->collisions->AddCollider({ 0, 0, 29, 38 }, Collider::Type::BOX, this);

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
	if (c1->type == Collider::Type::BOX && c2->type == Collider::Type::PLAYER_SHOT)
	{
		LOG("Box being shot")
		life--;
		if (life == 0) 
		{ 
			SDL_Rect rectBox1 = boxDestroyed.GetCurrentFrame();
			App->render->Blit(Box1, 90, 2802, &rectBox1);
		
		}
	}


}