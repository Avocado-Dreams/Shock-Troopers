#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModulePickUps.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "SceneGameOver.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::SOLDIER] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::BLUEDIAMOND] = false;
	matrix[Collider::Type::WALL][Collider::Type::TANK] = false;
	matrix[Collider::Type::WALL][Collider::Type::TANK_SHOT] = false;
	matrix[Collider::Type::WALL][Collider::Type::LIFE] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::SOLDIER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BLUEDIAMOND] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::HELICOPTER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::FINALBOSS] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TANK] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::TANK_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::LIFE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::EXPLOSION] = false;

	matrix[Collider::Type::SOLDIER][Collider::Type::WALL] = true;
	matrix[Collider::Type::SOLDIER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SOLDIER][Collider::Type::SOLDIER] = true;
	matrix[Collider::Type::SOLDIER][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::SOLDIER][Collider::Type::HELICOPTER_SHOT] = false;
	matrix[Collider::Type::SOLDIER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::SOLDIER][Collider::Type::BLUEDIAMOND] = false;
	matrix[Collider::Type::SOLDIER][Collider::Type::TANK] = false;
	matrix[Collider::Type::SOLDIER][Collider::Type::TANK_SHOT] = false;
	matrix[Collider::Type::SOLDIER][Collider::Type::LIFE] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::SOLDIER] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::HELICOPTER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BLUEDIAMOND] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::TANK] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::TANK_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::LIFE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BOSS_SHOT] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::SOLDIER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BLUEDIAMOND] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::TANK] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::TANK_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::LIFE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::HELICOPTER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::FINALBOSS] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BOSS_SHOT] = false;

	matrix[Collider::Type::BOSS_SHOT][Collider::Type::FINALBOSS] = false;
	matrix[Collider::Type::BOSS_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOSS_SHOT][Collider::Type::LIFE] = false;
	matrix[Collider::Type::BOSS_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::BOSS_SHOT][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::HELICOPTER_SHOT][Collider::Type::HELICOPTER] = false;
	matrix[Collider::Type::HELICOPTER_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::HELICOPTER_SHOT][Collider::Type::LIFE] = false;
	matrix[Collider::Type::HELICOPTER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::HELICOPTER_SHOT][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::TANK_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::TANK_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TANK_SHOT][Collider::Type::SOLDIER] = false;
	matrix[Collider::Type::TANK_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::TANK_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::TANK_SHOT][Collider::Type::BLUEDIAMOND] = false;
	matrix[Collider::Type::TANK_SHOT][Collider::Type::TANK] = false;
	matrix[Collider::Type::TANK_SHOT][Collider::Type::TANK_SHOT] = false;
	matrix[Collider::Type::TANK_SHOT][Collider::Type::LIFE] = false;

	matrix[Collider::Type::BLUEDIAMOND][Collider::Type::WALL] = false;
	matrix[Collider::Type::BLUEDIAMOND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BLUEDIAMOND][Collider::Type::SOLDIER] = false;
	matrix[Collider::Type::BLUEDIAMOND][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::BLUEDIAMOND][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::BLUEDIAMOND][Collider::Type::BLUEDIAMOND] = false;
	matrix[Collider::Type::BLUEDIAMOND][Collider::Type::LIFE] = false;

	matrix[Collider::Type::FINALBOSS][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FINALBOSS][Collider::Type::BOSS_SHOT] = false;
	matrix[Collider::Type::FINALBOSS][Collider::Type::EXPLOSION] = false;

	matrix[Collider::Type::HELICOPTER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::HELICOPTER][Collider::Type::HELICOPTER_SHOT] = false;
	matrix[Collider::Type::HELICOPTER][Collider::Type::EXPLOSION] = false;

	matrix[Collider::Type::BOX][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BOX][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BOX][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::BLUEDIAMOND][Collider::Type::TANK] = false;
	matrix[Collider::Type::BLUEDIAMOND][Collider::Type::TANK_SHOT] = false;

	matrix[Collider::Type::TANK][Collider::Type::WALL] = true;
	matrix[Collider::Type::TANK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TANK][Collider::Type::SOLDIER] = false;
	matrix[Collider::Type::TANK][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::TANK][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::TANK][Collider::Type::BLUEDIAMOND] = false;
	matrix[Collider::Type::TANK][Collider::Type::TANK] = false;
	matrix[Collider::Type::TANK][Collider::Type::TANK_SHOT] = false;
	matrix[Collider::Type::TANK][Collider::Type::LIFE] = false;

	matrix[Collider::Type::LIFE][Collider::Type::WALL] = false;
	matrix[Collider::Type::LIFE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LIFE][Collider::Type::SOLDIER] = false;
	matrix[Collider::Type::LIFE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::LIFE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::LIFE][Collider::Type::BLUEDIAMOND] = false;
	matrix[Collider::Type::LIFE][Collider::Type::TANK] = false;
	matrix[Collider::Type::LIFE][Collider::Type::TANK_SHOT] = false;
	matrix[Collider::Type::LIFE][Collider::Type::LIFE] = false;

	matrix[Collider::Type::EXPLOSION][Collider::Type::HELICOPTER] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::FINALBOSS] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::PLAYER_SHOT] = false;

	matrix[Collider::Type::MELEE][Collider::Type::MELEE] = false;
	matrix[Collider::Type::MELEE][Collider::Type::SOLDIER] = false;
	matrix[Collider::Type::MELEE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::MELEE][Collider::Type::BLUEDIAMOND] = false;
	matrix[Collider::Type::MELEE][Collider::Type::LIFE] = false;
	matrix[Collider::Type::MELEE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::MELEE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::MELEE][Collider::Type::WALL] = false;
	matrix[Collider::Type::MELEE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::MELEE][Collider::Type::TANK] = false;
	matrix[Collider::Type::MELEE][Collider::Type::TANK_SHOT] = false;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->Intersects(c2->rect))
			{
				if(matrix[c1->type][c2->type] && c1->listener) 
					c1->listener->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->listener) 
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debug = !debug;

	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		GodMode = !GodMode;

	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneOver, 60);
    
	}
	if (App->input->keys[SDL_SCANCODE_O] == KEY_DOWN && contador <= MAX_COLLIDERS)
	{
		App->pickUps->AddPickUps(PickUps_Type::LIFE, App->player->position.x , App->player->position.y -30);
		contador++;
	}
	if (App->input->keys[SDL_SCANCODE_P] == KEY_DOWN && contador <= MAX_COLLIDERS)
	{
		App->pickUps->AddPickUps(PickUps_Type::BLUEDIAMOND, App->player->position.x, App->player->position.y - 30);
		contador++;
	}
	if (App->input->keys[SDL_SCANCODE_L] == KEY_DOWN && contador <= MAX_COLLIDERS)
	{
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, App->player->position.x + 10 , App->player->position.y-40);
		contador++;
	}
	if (App->input->keys[SDL_SCANCODE_I] == KEY_DOWN && contador <= MAX_COLLIDERS)
	{
	App->enemies->AddEnemy(Enemy_Type::TANK, App->player->position.x - 10, App->player->position.y - 40);
	contador++;
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	if (GodMode)
		God_Mode();
	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::SOLDIER: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::TANK: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::BLUEDIAMOND: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::FINALBOSS: // pink
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
			case Collider::Type::BOSS_SHOT: // turquoise
			App->render->DrawQuad(colliders[i]->rect, 48, 213, 200, alpha);
			break;
			case Collider::Type::EXPLOSION: // dark blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 139, alpha);
			break;
			case Collider::Type::HELICOPTER: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 153, alpha);
			break;
			case Collider::Type::HELICOPTER_SHOT: // salmon
			App->render->DrawQuad(colliders[i]->rect, 255, 153, 102, alpha);
			break;
		}
	}
}

void ModuleCollisions::God_Mode()
{
	if (GodMode)
	{
		matrix[Collider::Type::PLAYER][Collider::Type::WALL] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::SOLDIER] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::TANK] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::TANK_SHOT] = false;
	}
	else {
		matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
		matrix[Collider::Type::PLAYER][Collider::Type::SOLDIER] = true;
		matrix[Collider::Type::PLAYER][Collider::Type::TANK] = true;
		matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
		matrix[Collider::Type::PLAYER][Collider::Type::TANK_SHOT] = true;
	}
	
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}
