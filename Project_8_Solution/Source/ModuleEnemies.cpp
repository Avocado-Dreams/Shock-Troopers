#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "ModulePickUps.h"

#include "PickUps.h"

#include "Enemy.h"
#include "Enemy_Tank.h"
#include "Enemy_Soldier_Static.h"
#include "Enemy_Box.h"
#include "Enemy_Soldier_Air.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/Sprites/Enemies/soldado_sprites.png");
	textureL = App->textures->Load("Assets/Sprites/Enemies/tanquesL.png");
	//textureBoss = App->textures->Load("Assets/Sprites/Enemies/FinalBoss.png");
	if (enemyDestroyedFx == 0) enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/damaged_enemy.wav");
	if (enemyShotFx == 0) enemyShotFx = App->audio->LoadFx("Assets/Fx/enemy_single_shot.wav");
	if (enemyKnifeFx == 0) enemyKnifeFx = App->audio->LoadFx("Assets/Fx/Knife.wav");
	if (damagedSoldier == 0) damagedSoldier = App->audio->LoadFx("Assets/Fx/damaged_enemy.wav");
	if (destroyedTank == 0) destroyedTank = App->audio->LoadFx("Assets/Fx/tankDestroyed.wav");
	if (enemyShotFx == 0) enemyShotFx = App->audio->LoadFx("Assets/Fx/enemy_single_shot.wav");
	if (enemyKnifeFx == 0) enemyKnifeFx = App->audio->LoadFx("Assets/Fx/Knife.wav");
	if (tankShotFx == 0) tankShotFx = App->audio->LoadFx("Assets/Fx/tankShot.wav");
	if (tankMovingFX == 0) tankMovingFX = App->audio->LoadFx("Assets/Fx/tankMoving.wav");

	return true;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case Enemy_Type::TANK:
					enemies[i] = new Enemy_Tank(info.x, info.y);
					break;
				case Enemy_Type::SOLDIER:
					enemies[i] = new Enemy_Soldier_Static(info.x, info.y);
					break;
				case Enemy_Type::CAJA:
					enemies[i] = new Enemy_Box(info.x, info.y);
					break;
				case Enemy_Type::AIR_SOLDIER:
					enemies[i] = new Enemy_Soldier_Air(info.x, info.y);
					break;
			}
			enemies[i]->texture = texture;
			//enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			if (c2->type == Collider::Type::PLAYER_SHOT&& enemies[i]->GetLife()<=0)
			{
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
			
		}
	}
}