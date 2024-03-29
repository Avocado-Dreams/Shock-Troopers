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
	enemy28Spawned = false;
	enemy29Spawned = false;
	enemy30Spawned = false;
	enemy31Spawned = false;
	enemy32Spawned = false;
	enemy33Spawned = false;
	enemy34Spawned = false;
	enemy35Spawned = false;
	enemy36Spawned = false;
	enemy37Spawned = false;
	enemy38Spawned = false;
	enemy39Spawned = false;
	enemy40Spawned = false;
	enemy41Spawned = false;
	enemy42Spawned = false;
	enemy43Spawned = false;
	enemy44Spawned = false;
	enemy45Spawned = false;
	enemy46Spawned = false;
	enemy47Spawned = false;
	enemy48Spawned = false;
	enemy49Spawned = false;
	enemy50Spawned = false;
	enemy51Spawned = false;
	enemy52Spawned = false;
	enemy53Spawned = false;
	enemy54Spawned = false;
	enemy55Spawned = false;
	enemy56Spawned = false;
	enemy57Spawned = false;
	enemy58Spawned = false;
	enemy59Spawned = false;
	enemy60Spawned = false;
	enemy61Spawned = false;
	enemy62Spawned = false;
	enemy63Spawned = false;
	enemy64Spawned = false;
	enemy65Spawned = false;
	enemy66Spawned = false;

	bool ret = true;

	textureSky = App->textures->Load("Assets/Sprites/Background/Cielo.png");
	bgTexture = App->textures->Load("Assets/Sprites/Background/Mapa.png");
	App->audio->PlayMusic("Assets/Music/RideOn.ogg", 1.0f);


	contador = false;
	contador2 = false;
	reloj = 120;

	App->render->camera.x = 0;
	App->render->camera.y = 2715 * SCREEN_SIZE;

	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->sceneLayer2->Enable();
	App->pickUps->Enable();
	App->collisions->Enable();
	App->particles->Enable();

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

	App->finalBoss->Disable();

	App->sceneOver->firstTime = true;


	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.y -= 3;
	if (App->player->position.y < 2830 && enemy1Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 160, 2805);
		enemy1Spawned = true;
	}
	if (App->player->position.y < 2830 && enemy2Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 190, 2770);
		enemy2Spawned = true;
	}
	if (App->player->position.y < 2830 && enemy3Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 60, 2805);
		enemy3Spawned = true;
	}
	if (App->player->position.y < 2830 && enemy4Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 90, 2770);
		enemy4Spawned = true;
	}
	if (App->player->position.y < 2710 && enemy5Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 80, 2600);
		enemy5Spawned = true;
	}
	if (App->player->position.y < 2710 && enemy6Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 110, 2635);
		enemy6Spawned = true;
	}
	if (App->player->position.y < 2710 && enemy7Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 180, 2635);
		enemy7Spawned = true;
	}
	if (App->player->position.y < 2710 && enemy8Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 190, 2600);
		enemy8Spawned = true;
	}
	if (App->player->position.y < 2415 && enemy9Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 70, 2340);
		enemy9Spawned = true;
	}

	if (App->player->position.y < 2435 && enemy12Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 230, 2270);
		enemy12Spawned = true;
	}
	if (App->player->position.y < 2455 && enemy13Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 80, 2220);
		enemy13Spawned = true;
	}
	if (App->player->position.y < 2455 && enemy14Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 700, 2180);
		enemy14Spawned = true;
	}
	if (App->player->position.x > 435 && enemy15Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 435, 1870);
		enemy15Spawned = true;
	}
	if (App->player->position.x > 435 && enemy16Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 470, 1870);
		enemy16Spawned = true;
	}
	if (App->player->position.x > 435 && enemy17Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 505, 1870);
		enemy17Spawned = true;
	}
	if (App->player->position.x > 435 && enemy18Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 540, 1870);
		enemy18Spawned = true;
	}
	if (App->player->position.y < 2840 && enemy19Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 185, 2720);
		enemy19Spawned = true;
	}
	if (App->player->position.y < 2930 && enemy20Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 220, 2710);
		enemy20Spawned = true;
	}
	if (App->player->position.y < 2910 && enemy21Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 255, 2690);
		enemy21Spawned = true;
	}
	if (App->player->position.y <2900 && enemy22Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 90, 2680);
		enemy22Spawned = true;
	}
	if (App->player->position.y < 2610 && enemy25Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 105, 2400);
		enemy25Spawned = true;
	}
	if (App->player->position.y < 2610 && enemy26Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 190, 2400);
		enemy26Spawned = true;
	}
	if (App->player->position.y < 2450 && enemy27Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 100, 2250);
		enemy27Spawned = true;
	}
	if (App->player->position.y < 2420 && enemy28Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 195, 2220);
		enemy28Spawned = true;
	}
	if (App->player->position.y < 2245 && enemy29Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 190, 2045);
		enemy29Spawned = true;
	}
	if (App->player->position.y < 2220 && enemy30Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 225, 2020);
		enemy30Spawned = true;
	}
	if (App->player->position.y < 2230 && enemy31Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 70, 2030);
		enemy31Spawned = true;
	}
	if (App->player->position.y < 2180 && enemy32Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 160, 1980);
		enemy32Spawned = true;
	}
	if (App->player->position.y < 2180 && enemy33Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 125, 1980);
		enemy33Spawned = true;
	}
	if (App->player->position.y < 2325 && enemy34Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::TANK, 95, 2125);
		enemy34Spawned = true;
	}
	if (App->player->position.y < 2325 && enemy35Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::TANK, 180, 2125);
		enemy35Spawned = true;
	}
	if (App->player->position.y < 2690 && enemy36Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 110, 2490);
		enemy36Spawned = true;
	}
	if (App->player->position.y < 2690 && enemy37Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 190, 2490);
		enemy37Spawned = true;
	}
	if (App->player->position.x > 565 && enemy38Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 765, 1940);
		enemy38Spawned = true;
	}
	if (App->player->position.x > 565 && enemy39Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 765, 1980);
		enemy39Spawned = true;
	}
	if (App->player->position.x > 1105 && enemy40Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 1305, 1960);
		enemy40Spawned = true;
	}
	if (App->player->position.y < 1860 && enemy41Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 2222, 1660);
		enemy41Spawned = true;
	}
	if (App->player->position.y < 970 && enemy42Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 2160, 770);
		enemy42Spawned = true;
	}
	if (App->player->position.y < 970 && enemy43Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::CAJA, 2270, 770);
		enemy43Spawned = true;
	}
	if (App->player->position.x > 1240 && enemy44Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 1440, 1970);
		enemy44Spawned = true;
	}
	if (App->player->position.x > 1240 && enemy24Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 1470, 1990);
		enemy24Spawned = true;
	} //24,23,10,11
	if (App->player->position.x > 1240 && enemy23Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 1470, 1930);
		enemy23Spawned = true;
	}
	if (App->player->position.x > 1240 && enemy24Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 1470, 1990);
		enemy24Spawned = true;
	}
	if (App->player->position.x > 1500 && enemy10Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 1580, 1880);
		enemy10Spawned = true;
	}
	if (App->player->position.x > 1500 && enemy24Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 1570, 2000);
		enemy11Spawned = true;
	}
	if (App->player->position.x > 1440 && enemy45Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::TANK, 1640, 1885);
		enemy45Spawned = true;
	}
	if (App->player->position.x > 1620 && enemy46Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::TANK, 1820, 1940);
		enemy46Spawned = true;
	}
	if (App->player->position.x > 1850 && enemy47Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 1900, 1900);
		enemy47Spawned = true;
	}
	if (App->player->position.x > 1850 && enemy48Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 1960, 1875);
		enemy48Spawned = true;
	}
	if (App->player->position.x > 1750 && enemy66Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 1950, 1960);
		enemy66Spawned = true;
	}
	if (App->player->position.x > 1880 && enemy49Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::TANK, 2080, 1960);
		enemy49Spawned = true;
	}
	if (App->player->position.x > 2000 && enemy50Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2200, 1960);
		enemy50Spawned = true;
	}
	if (App->player->position.x > 2100 && enemy51Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2260, 1960);
		enemy51Spawned = true;
	}
	if (App->player->position.x > 2100 && enemy52Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2300, 1910);
		enemy52Spawned = true;
	}
	if (App->player->position.x > 2100 && enemy53Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2340, 1910);
		enemy53Spawned = true;
	}
	if (App->player->position.x > 2100 && enemy54Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2380, 1910);
		enemy54Spawned = true;
	}
	if (App->player->position.y < 1930 && enemy55Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2230, 1730);
		enemy55Spawned = true;
	}
	if (App->player->position.y < 1930 && enemy56Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2300, 1660);
		enemy56Spawned = true;
	}
	if (App->player->position.y < 1930 && enemy57Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2150, 1660);
		enemy57Spawned = true;
	}
	if (App->player->position.y < 2680 && enemy58Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2310, 2580);
		enemy58Spawned = true;
	}
	if (App->player->position.y < 2680 && enemy59Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2135, 2580);
		enemy59Spawned = true;
	}
	if (App->player->position.y < 1375 && enemy60Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 2150, 1275);
		enemy60Spawned = true;
	}
	if (App->player->position.y < 1375 && enemy61Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::AIR_SOLDIER, 2150, 1200);
		enemy61Spawned = true;
	}
	if (App->player->position.y < 1315 && enemy62Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::TANK, 2290, 1115);
		enemy62Spawned = true;
	}
	if (App->player->position.y < 1200 && enemy63Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2180, 1040);
		enemy63Spawned = true;
	}
	if (App->player->position.y < 1200 && enemy64Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2250, 1040);
		enemy64Spawned = true;
	}
	if (App->player->position.y < 1200 && enemy65Spawned == false) {
		App->enemies->AddEnemy(Enemy_Type::SOLDIER, 2200, 995);
		enemy65Spawned = true;
	}
	if (App->player->zone == 3 && contador == false)
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
	App->finalBoss->Disable();
	
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
	App->textures->Unload(App->finalBoss->texture);

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