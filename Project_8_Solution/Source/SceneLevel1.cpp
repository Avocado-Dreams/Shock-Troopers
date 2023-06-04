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
#include "ModuleFonts.h"
#include "ModuleParticles.h"
#include "ModuleHelicopter.h"
#include "ModuleFinalBoss.h"
#include "ModulePlayer.h"
#include "SceneLayer2.h"
#include "SceneGameOver.h"
#include <stdio.h>

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
	enemy6Spawned = false;
	enemy7Spawned = false;
	enemy8Spawned = false;
	enemy9Spawned = false;
	enemy10Spawned = false;
	enemy11Spawned = false;
	enemy12Spawned = false;
	enemy13Spawned = false;
	enemy14Spawned = false;
	enemy15Spawned = false;
	enemy16Spawned = false;
	enemy17Spawned = false;
	enemy18Spawned = false;
	enemy19Spawned = false;
	enemy20Spawned = false;
	enemy21Spawned = false;
	enemy22Spawned = false;
	enemy23Spawned = false;
	enemy24Spawned = false;
	enemy25Spawned = false;
	enemy26Spawned = false;
	enemy27Spawned = false;


	bool ret = true;

	textureSky = App->textures->Load("Assets/Sprites/Background/Cielo.png");
	bgTexture = App->textures->Load("Assets/Sprites/Background/Mapa.png");
	App->audio->PlayMusic("Assets/Music/RideOn.ogg", 1.0f);


	bool contador = false;
	bool contador2 = false;



	App->render->camera.x = 0;
	App->render->camera.y = 2715 * SCREEN_SIZE;

	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->sceneLayer2->Enable();
	App->pickUps->Enable();
	App->collisions->Enable();

	App->player->vida = 100;
	App->player->hit = 0;
	App->sceneLayer2->hp = 100;
	App->player->win = 0; 
	App->player->zone = 1; 
	App->finalBoss->bossDestroyed = false; 
	App->finalBoss->life = 150; 
	App->finalBoss->position.x = 2182;
	App->finalBoss->position.y = -162;
	App->finalBoss->state = 1;
	App->helicopter->helicopterDestroyed = false;
	App->helicopter->life = 100;
	App->helicopter->position.x = 967;
	App->helicopter->position.y = 1928;
	App->helicopter->state = 1;

	App->sceneOver->firstTime = true;


	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.y -= 3;
	if (App->player->position.y < 2850 && enemy1Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 170, 2800);
		enemy1Spawned = true;
	}
	if (App->player->position.y < 2850 && enemy2Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 200, 2780);
		enemy2Spawned = true;
	}
	if (App->player->position.y < 2850 && enemy3Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 50, 2800);
		enemy3Spawned = true;
	}
	if (App->player->position.y < 2850 && enemy4Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 80, 2780);
		enemy4Spawned = true;
	}
	if (App->player->position.y < 2450 && enemy5Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 170, 2400);
		enemy5Spawned = true;
	}
	if (App->player->position.y < 2450 && enemy6Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 200, 2380);
		enemy6Spawned = true;
	}
	if (App->player->position.y < 2450 && enemy7Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 50, 2400);
		enemy7Spawned = true;
	}
	if (App->player->position.y < 2450 && enemy8Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 80, 2380);
		enemy8Spawned = true;
	}
	if (App->player->position.y < 2315 && enemy9Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 95, 2265);
		enemy9Spawned = true;
	}
	if (App->player->position.y < 2315 && enemy10Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 105, 2225);
		enemy10Spawned = true;
	}
	if (App->player->position.y < 2315 && enemy11Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 195, 2220);
		enemy11Spawned = true;
	}
	if (App->player->position.y < 2315 && enemy12Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 205, 2180);
		enemy12Spawned = true;
	}
	if (App->player->position.y < 2875 && enemy13Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 260, 2675);
		enemy13Spawned = true;
	}
	if (App->player->position.y < 2875 && enemy14Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 300, 2675);
		enemy14Spawned = true;
	}
	if (App->player->position.y < 2875 && enemy15Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 65, 2690);
		enemy15Spawned = true;
	}
	if (App->player->position.y < 2875 && enemy16Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 100, 2690);
		enemy16Spawned = true;
	}
	if (App->player->position.y < 2835 && enemy17Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 165, 2635);
		enemy17Spawned = true;
	}
	if (App->player->position.y < 2545 && enemy18Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 100, 2345);
		enemy18Spawned = true;
	}
	if (App->player->position.y < 2500 && enemy19Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 110, 2300);
		enemy19Spawned = true;
	}
	if (App->player->position.y < 2545 && enemy20Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 220, 2345);
		enemy20Spawned = true;
	}
	if (App->player->position.y < 2500 && enemy21Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 210, 2300);
		enemy21Spawned = true;
	}
	if (App->player->position.y <2200 && enemy22Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::TANK, 150, 2000);
		enemy22Spawned = true;
	}
	if (App->player->position.y <2190 && enemy23Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 160, 1990);
		enemy23Spawned = true;
	}
	if (App->player->position.y < 2147 && enemy23Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 1338, 1947);
		enemy24Spawned = true;
	}
	if (App->player->position.y < 1855 && enemy25Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 2215, 1655);
		enemy25Spawned = true;
	}
	if (App->player->position.y < 959 && enemy26Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 2153, 759);
		enemy26Spawned = true;
	}
	if (App->player->position.y < 756 && enemy27Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 2269, 756);
		enemy27Spawned = true;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	
	if (App->player->zone == 3)
	{
		SDL_Rect sky{ 0, 0, 433, 142 };
		App->render->Blit(textureSky, 890, 1795, &sky);
	}
	if (App->player->zone == 3 && contador == false )
	{
		if (reloj == 0)
		{
			contador = true;
			App->enemies->AddEnemy(Enemy_Type::TANK, 150, 1740);
			App->enemies->AddEnemy(Enemy_Type::SOLDIER, 190, 1740);
			App->enemies->AddEnemy(Enemy_Type::SOLDIER, 110, 1740);
		}
		if (contador2 == false)
		{
			App->enemies->AddEnemy(Enemy_Type::SOLDIER, 120, 1740);
			App->enemies->AddEnemy(Enemy_Type::SOLDIER, 140, 1740);
			App->enemies->AddEnemy(Enemy_Type::SOLDIER, 180, 1740);
			App->enemies->AddEnemy(Enemy_Type::SOLDIER, 200, 1740);
			contador2 = true;
		}
		
		
		reloj--;
	}
	
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
	App->particles->Disable();
	App->helicopter->Disable();
	App->collisions->Disable();
	
	App->textures->Unload(textureSky);
	App->textures->Unload(bgTexture);
	App->textures->Unload(App->sceneLayer2->bgTexture2);
	App->textures->Unload(App->sceneLayer2->bgTexture3);
	App->textures->Unload(App->sceneLayer2->palms);
	App->textures->Unload(App->sceneLayer2->palms2);
	App->textures->Unload(App->sceneLayer2->P1);
	App->textures->Unload(App->sceneLayer2->PhotoFrame);
	App->textures->Unload(App->sceneLayer2->Time);
	App->textures->Unload(App->sceneLayer2->Weapon);
	App->textures->Unload(App->sceneLayer2->Grenade);
	App->textures->Unload(App->sceneLayer2->GoUp);
	App->textures->Unload(App->sceneLayer2->GoRight);
	App->textures->Unload(App->sceneLayer2->HBar);

	App->textures->Unload(App->player->texture);
	App->textures->Unload(App->player->textureD);
	App->textures->Unload(App->player->textureL);
	App->textures->Unload(App->player->textureState);
	App->textures->Unload(App->helicopter->textureH);
	App->textures->Unload(App->helicopter->textureSky);
	
	/*App->textures->Unload(App->player->textureD);
	App->textures->Unload(App->player->textureL);
	App->textures->Unload(App->player->textureState);
	App->textures->Unload(App->helicopter->textureH);
	App->textures->Unload(App->helicopter->textureSky);*/
	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}

void SceneLevel1::OnCollision()
{


}