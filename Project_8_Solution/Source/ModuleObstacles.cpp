#include "ModuleObstacles.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModulePickUps.h"
#include "ModuleFonts.h"
#include <stdio.h>
#include <iostream>
#include "SDL/include/SDL.h"

ModuleObstacles::ModuleObstacles(int x, int y) : Enemy(x, y)
{
	//Inactive box
	box.PushBack({ 20, 678, 31, 40 });
	box.loop = false;
	
	LOG("Loading UI assets");

	currentAnim = &box;
	collider = App->collisions->AddCollider({ 0, 0, 31, 40 }, Collider::Type::BOX, (Module*)App->enemies);
	Enemy::Update();
}

void ModuleObstacles::Update()
{
	randomValue = rand() % 101;
	Enemy::Update();
}


void ModuleObstacles::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
	{

		App->particles->AddParticle(App->particles->boxDestroyed, position.x, position.y, NULL, NULL, Collider::Type::NONE, NULL);
		LOG("Box being shot");

		int prob_diamond = 35;
		int prob_life = 17;

		if (randomValue < prob_diamond && hasDropped == false) {
			App->pickUps->AddPickUps(PickUps_Type::BLUEDIAMOND, position.x + 12, position.y + 4);
			hasDropped = true;
		}
		if (randomValue > 100 - prob_life && hasDropped == false) {
			App->pickUps->AddPickUps(PickUps_Type::LIFE, position.x + 12, position.y + 4);
			hasDropped = true;
		}
	}
	
}