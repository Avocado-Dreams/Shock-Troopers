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
#include "ModuleHelicopter.h"
#include "ModuleFinalBoss.h"
#include "ModulePlayer.h"
#include "SceneLayer2.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{
	//Background / sky
	sky = { 0, 0, 433, 142 };
}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	enemy1Spawned = false;
	enemy2Spawned = false;
	enemy3Spawned = false;
	enemy4Spawned = false;
	enemy5Spawned = false;

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Background/Mapa.png");
	textureSky = App->textures->Load("Assets/Sprites/Background/Cielo.png");
	App->audio->PlayMusic("Assets/Music/RideOn.ogg", 1.0f);

	////Bottomside collider
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);     //Eliminados porque eran del otro juego y destruyen el jugador cuando no deben

	////First two columns colliders
	//App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	// Enemies ---
	/*App->enemies->AddEnemy(Enemy_Type::Enemy_Tank, 250, 2400);
	App->enemies->AddEnemy(Enemy_Type::Enemy_Tank, 625, 80);
	App->enemies->AddEnemy(Enemy_Type::Enemy_Tank, 640, 80);
	App->enemies->AddEnemy(Enemy_Type::Enemy_Tank, 665, 80);

	App->enemies->AddEnemy(Enemy_Type::Enemy_Tank, 735, 120);
	App->enemies->AddEnemy(Enemy_Type::Enemy_Tank, 750, 120);
	App->enemies->AddEnemy(Enemy_Type::Enemy_Tank, 775, 120);
	App->enemies->AddEnemy(Enemy_Type::Enemy_Tank, 790, 120);
*/
	App->enemies->AddEnemy(Enemy_Type::TANK, 100, 2400);
	

	App->render->camera.x = 0;
	App->render->camera.y = 2715 * 3;

	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->sceneLayer2->Enable();
	App->pickUps->Enable();

	App->player->vida = 100;
	App->sceneLayer2->hp = 100;
	App->player->win = 0; 
	App->player->zone = 1; 
	App->finalBoss->bossDestroyed = false; 
	App->finalBoss->life = 100; 
	App->finalBoss->position.x = 2182;
	App->finalBoss->position.y = -162;
	App->finalBoss->state = 1;

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
	if (App->player->position.y < 2700 && enemy5Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::TANK, 100, 2400);
		enemy5Spawned = true;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(textureSky, 890, 1795, &sky);
	

	//box.Update();
	//SDL_Rect boxPosition = { 95, 50, 29, 38 };
	//App->render->Blit(textureBox, 95, 50, &currentBox->GetCurrentFrame(), 0);


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

void SceneLevel1::OnCollision()
{
	/*if (boxActive && App->player->collider->CheckCollision(boxCollider))
	{
		boxActive = false;
		currentBox = &boxDestroyed;
		currentBox->Reset();
		currentBox->speed = 0.3f;
	}*/

}