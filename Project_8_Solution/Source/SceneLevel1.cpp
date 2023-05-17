#include "SceneLevel1.h"
#include "Enemy.h"
#include "Enemy_Soldier_Static.h"
#include "ModulePickUps.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "SceneLayer2.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Background/Mapa.png");
	sky = App->textures->Load("Assets/Sprites/Background/Cielo.png");
	App->audio->PlayMusic("Assets/Music/RideOn.ogg", 1.0f);

	////Bottomside collider
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);     //Eliminados porque eran del otro juego y destruyen el jugador cuando no deben

	////First two columns colliders
	//App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	// Enemies ---
	/*App->enemies->AddEnemy(Enemy_Type::REDBIRD, 250, 2400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 625, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 640, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 665, 80);

	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 735, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 750, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 775, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 790, 120);

	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 300, 2400);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 850, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 870, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 890, 100);*/

	
	
	

	App->render->camera.x = 0;
	App->render->camera.y = 2715 * 3;

	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->sceneLayer2->Enable();
	App->pickUps->Enable();



	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.y -= 3;
	if (App->player->position.y < 2700 && enemy1Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 200, 2600);
		enemy1Spawned = true;
	}
	if (App->player->position.y < 2700 && enemy2Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 170, 2580);
		enemy2Spawned = true;
	}
	if (App->player->position.y < 2700 && enemy3Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 80, 2600);
		enemy3Spawned = true;
	}
	if (App->player->position.y < 2700 && enemy4Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 50, 2580);
		enemy4Spawned = true;
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	SDL_Rect cielo{ 0, 0, 433, 142 };
	App->render->Blit(sky, 890, 1795, &cielo);
	
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// TODO 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	App->sceneLayer2->Disable();
	App->pickUps->Disable();

	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}