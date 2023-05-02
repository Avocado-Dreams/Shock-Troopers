#include "ModulePickUps.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "PickUps.h"
#include "PickUps_BLUEDIAMOND.h"

#define SPAWN_MARGIN 50

ModulePickUps::ModulePickUps(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_PICKUPS; ++i)
		pickUps[i] = nullptr;
}

ModulePickUps::~ModulePickUps()
{

}

bool ModulePickUps::Start()
{
	texture = App->textures->Load("Assets/Sprites/Others/PickUps.png");
	getPickUps = App->audio->LoadFx("Assets/Fx/laser.wav");

	return true;
}

Update_Status ModulePickUps::Update()
{
	HandlePickUpsSpawn();

	for (uint i = 0; i < MAX_PICKUPS; ++i)
	{
		if (pickUps[i] != nullptr)
			pickUps[i]->Update();
	}

	HandlePickUpsDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePickUps::PostUpdate()
{
	for (uint i = 0; i < MAX_PICKUPS; ++i)
	{
		if (pickUps[i] != nullptr)
			pickUps[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePickUps::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_PICKUPS; ++i)
	{
		if (pickUps[i] != nullptr)
		{
			delete pickUps[i];
			pickUps[i] = nullptr;
		}
	}

	return true;
}

bool ModulePickUps::AddPickUps(PickUps_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_PICKUPS; ++i)
	{
		if (spawnQueue[i].type == PickUps_Type::NO_TYPE)
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

void ModulePickUps::HandlePickUpsSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_PICKUPS; ++i)
	{
		if (spawnQueue[i].type != PickUps_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnPickUps(spawnQueue[i]);
				spawnQueue[i].type = PickUps_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModulePickUps::HandlePickUpsDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_PICKUPS; ++i)
	{
		if (pickUps[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (pickUps[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", pickUps[i]->position.x * SCREEN_SIZE);

				delete pickUps[i];
				pickUps[i] = nullptr;
			}
		}
	}
}

void ModulePickUps::SpawnPickUps(const PickUpsSpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_PICKUPS; ++i)
	{
		if (pickUps[i] == nullptr)
		{
			switch (info.type)
			{
			case PickUps_Type::BLUEDIAMOND:
				pickUps[i] = new PickUps_BLUEDIAMOND(info.x, info.y);
				break;
			}
			pickUps[i]->texture = texture;
			pickUps[i]->getPickUps = getPickUps;
			break;
		}
	}
}

void ModulePickUps::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_PICKUPS; ++i)
	{
		if (pickUps[i] != nullptr && pickUps[i]->GetCollider() == c1)
		{
			pickUps[i]->OnCollision(c2); //Notify the enemy of a collision

			delete pickUps[i];
			pickUps[i] = nullptr;
			break;
		}
	}
}