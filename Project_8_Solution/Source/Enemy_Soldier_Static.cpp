#include "Enemy_Soldier_Static.h"
#include "ModulePickUps.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL_Scancode.h"
#include "Application.h"
#include "ModuleInput.h"

Enemy_Soldier_Static::Enemy_Soldier_Static(int x, int y) : Enemy(x, y)
{
	
	idleDownL.PushBack({ 23, 41, 30, 48 });

	shootDownL.PushBack({ 23, 41, 30, 48 });
	shootDownL.PushBack({ 101, 41, 30, 49 });
	shootDownL.PushBack({ 23, 41, 30, 48 });
	shootDownL.loop = false;
	shootDownL.speed = 0.1f;
	//front.pingpong = true;

	idleDownR.PushBack({ 179, 41, 30, 48 });

	shootDownR.PushBack({ 179, 41, 30, 48 });
	shootDownR.PushBack({ 257, 41, 30, 49 });
	shootDownR.PushBack({ 179, 41, 30, 48 });
	shootDownR.loop = false;
	shootDownR.speed = 0.1f;
	
	idleSE1.PushBack({ 335, 41, 26, 49 });

	shootSE1.PushBack({ 335, 41, 26, 49 });
	shootSE1.PushBack({ 410, 41, 25, 50 });
	shootSE1.PushBack({ 335, 41, 26, 49 });
	shootSE1.loop = false;
	shootSE1.speed = 0.1f;

	idleSE2.PushBack({482, 40, 34, 49});

	shootSE2.PushBack({ 482, 40, 34, 49 });
	shootSE2.PushBack({ 565, 40, 33, 50 });
	shootSE2.PushBack({ 482, 40, 34, 49 });
	shootSE2.loop = false;
	shootSE2.speed = 0.1f;

	idleRight.PushBack({ 645, 40, 45, 49 });

	shootRight.PushBack({ 645, 40, 45, 49 });
	shootRight.PushBack({ 738, 40, 43, 49 });
	shootRight.PushBack({ 645, 40, 45, 49 });
	shootRight.loop = false;
	shootRight.speed = 0.1f;

	idleNE1.PushBack({ 829, 41, 40, 48 });

	shootNE1.PushBack({ 829, 41, 40, 48 });
	shootNE1.PushBack({ 917, 41, 38, 47 });
	shootNE1.PushBack({ 829, 41, 40, 48 });
	shootNE1.loop = false;
	shootNE1.speed = 0.1f;

	idleNE2.PushBack({ 1003, 41, 37, 48 });

	shootNE2.PushBack({ 1003, 41, 37, 48 });
	shootNE2.PushBack({ 1088, 41, 37, 47 });
	shootNE2.PushBack({ 1003, 41, 37, 48 });
	shootNE2.loop = false;
	shootNE2.speed = 0.1f;

	idleUpL.PushBack({ 1173, 41, 30, 48 });

	shootUpL.PushBack({ 1173, 41, 30, 48 });
	shootUpL.PushBack({ 1252, 41, 30, 47 });
	shootUpL.PushBack({ 1173, 41, 30, 48 });
	shootUpL.loop = false;
	shootUpL.speed = 0.1f;

	idleUpR.PushBack({ 24, 105, 30, 47 });

	shootUpR.PushBack({ 24, 105, 30, 47 });
	shootUpR.PushBack({ 103, 105, 30, 48 });
	shootUpR.PushBack({ 24, 105, 30, 47 });
	shootUpR.loop = false;
	shootUpR.speed = 0.1f;

	idleNW1.PushBack({ 181, 105, 38, 47 });

	shootNW1.PushBack({ 181, 105, 38, 47 });
	shootNW1.PushBack({ 266, 105, 37, 48 });
	shootNW1.PushBack({ 181, 105, 38, 47 });
	shootNW1.loop = false;
	shootNW1.speed = 0.1f;

	idleNW2.PushBack({ 351, 105, 38, 47 });

	shootNW2.PushBack({ 351, 105, 38, 47 });
	shootNW2.PushBack({ 439, 105, 40, 48 });
	shootNW2.PushBack({ 351, 105, 38, 47 });
	shootNW2.loop = false;
	shootNW2.speed = 0.1f;

	idleLeft.PushBack({ 525, 103, 43, 49 });

	shootLeft.PushBack({ 525, 103, 43, 49 });
	shootLeft.PushBack({ 618, 103, 45, 49 });
	shootLeft.PushBack({ 525, 103, 43, 49 });
	shootLeft.loop = false;
	shootLeft.speed = 0.1f;

	idleSW1.PushBack({ 709, 102, 33, 50 });

	shootSW1.PushBack({ 709, 102, 33, 50 });
	shootSW1.PushBack({ 792, 102, 34, 49 });
	shootSW1.PushBack({ 709, 102, 33, 50 });
	shootSW1.loop = false;
	shootSW1.speed = 0.1f;

	idleSW2.PushBack({ 872, 102, 25, 50 });

	shootSW2.PushBack({ 872, 102, 25, 50 });
	shootSW2.PushBack({ 947, 102, 26, 49 });
	shootSW2.PushBack({ 872, 102, 25, 50 });
	shootSW2.loop = false;
	shootSW2.speed = 0.1f;

	//enemy_airspawnL.PushBack({ 17, 260, 64, 69 });
	//enemy_airspawnL.PushBack({ 80, 261, 63, 67 });
	//enemy_airspawnL.PushBack({ 143, 263, 59, 62 });
	//enemy_airspawnL.PushBack({ 206, 264, 58, 61 });
	//enemy_airspawnL.PushBack({ 270, 264, 54, 60 });
	//enemy_airspawnL.PushBack({ 332, 265, 53, 58 });
	//enemy_airspawnL.PushBack({ 395, 266, 52, 57 });
	//enemy_airspawnL.PushBack({ 457, 267, 51, 55 });
	//enemy_airspawnL.PushBack({ 520, 267, 50, 54 });
	//enemy_airspawnL.PushBack({ 582, 268, 49, 53 });
	//enemy_airspawnL.PushBack({ 645, 268, 48, 52 });
	//enemy_airspawnL.PushBack({ 707, 269, 47, 50 });
	//enemy_airspawnL.PushBack({ 770, 270, 46, 49 });
	//enemy_airspawnL.PushBack({ 834, 271, 42, 47 });
	//enemy_airspawnL.loop = false;
	//enemy_airspawnL.speed = 0.3f;

	//getUpL.PushBack({ 961, 275, 36, 38 });
	//getUpL.loop = false;
	//getUpL.speed = 0.1f;

	//enemy_airspawnR.PushBack({ 940, 347, 64, 69 });
	//enemy_airspawnR.PushBack({ 879, 348, 63, 67 });
	//enemy_airspawnR.PushBack({ 819, 350, 59, 62 });
	//enemy_airspawnR.PushBack({ 757, 351, 58, 61 });
	//enemy_airspawnR.PushBack({ 697, 351, 54, 60 });
	//enemy_airspawnR.PushBack({ 636, 352, 53, 58 });
	//enemy_airspawnR.PushBack({ 574, 353, 52, 57 });
	//enemy_airspawnR.PushBack({ 513, 354, 51, 55 });
	//enemy_airspawnR.PushBack({ 451, 354, 50, 54 });
	//enemy_airspawnR.PushBack({ 390, 355, 49, 53 });
	//enemy_airspawnR.PushBack({ 328, 355, 48, 52 });
	//enemy_airspawnR.PushBack({ 267, 356, 47, 50 });
	//enemy_airspawnR.PushBack({ 145, 357, 46, 49 });
	//enemy_airspawnL.PushBack({ 84, 358, 42, 47 });
	////enemy_airspawnL.PushBack({ 834, 271, 42, 47 });
	//enemy_airspawnR.loop = false;
	//enemy_airspawnR.speed = 0.3f;

	//getUpR.PushBack({ 24, 362, 36, 38 });
	//getUpR.loop = false;
	//getUpR.speed = 0.1f;

	moveDown.PushBack({ 411, 417, 42, 56 });
	moveDown.PushBack({ 456, 417, 42, 56 });
	moveDown.PushBack({ 501, 417, 42, 56 });
	moveDown.PushBack({ 546, 417, 42, 56 });
	moveDown.PushBack({ 591, 417, 42, 56 });
	moveDown.PushBack({ 636, 417, 42, 56 });
	moveDown.PushBack({ 681, 417, 42, 56 });
	moveDown.PushBack({ 726, 417, 42, 56 });

	moveDown.loop = true;
	moveDown.speed = 0.2f;

	moveSE.PushBack({ 20, 417, 42, 56 });
	moveSE.PushBack({ 65, 417, 42, 56 });
	moveSE.PushBack({ 110, 417, 42, 56 });
	moveSE.PushBack({ 155, 417, 42, 56 });
	moveSE.PushBack({ 200, 417, 42, 56 });
	moveSE.PushBack({ 245, 417, 42, 56 });
	moveSE.PushBack({ 290, 417, 42, 56 });
	moveSE.PushBack({ 335, 417, 42, 56 });

	moveSE.loop = true;
	moveSE.speed = 0.2f;

	moveSW.PushBack({ 802, 417, 42, 56 });
	moveSW.PushBack({ 847, 417, 42, 56 });
	moveSW.PushBack({ 892, 417, 42, 56 });
	moveSW.PushBack({ 937, 417, 42, 56 });
	moveSW.PushBack({ 982, 417, 42, 56 });
	moveSW.PushBack({ 1027, 417, 42, 56 });
	moveSW.PushBack({ 1072, 417, 42, 56 });
	moveSW.PushBack({ 1117, 417, 42, 56 });

	moveSW.loop = true;
	moveSW.speed = 0.2f;

	moveRight.PushBack({ 20, 485, 42, 56 });
	moveRight.PushBack({ 65, 485, 42, 56 });
	moveRight.PushBack({ 110, 485, 42, 56 });
	moveRight.PushBack({ 155, 485, 42, 56 });
	moveRight.PushBack({ 200, 485, 42, 56 });
	moveRight.PushBack({ 245, 485, 42, 56 });
	moveRight.PushBack({ 290, 485, 42, 56 });
	moveRight.PushBack({ 335, 485, 42, 56 });

	moveRight.loop = true;
	moveRight.speed = 0.2f;

	moveLeft.PushBack({ 411, 485, 42, 56 });
	moveLeft.PushBack({ 456, 485, 42, 56 });
	moveLeft.PushBack({ 501, 485, 42, 56 });
	moveLeft.PushBack({ 546, 485, 42, 56 });
	moveLeft.PushBack({ 591, 485, 42, 56 });
	moveLeft.PushBack({ 636, 485, 42, 56 });
	moveLeft.PushBack({ 681, 485, 42, 56 });
	moveLeft.PushBack({ 726, 485, 42, 56 });

	moveLeft.loop = true;
	moveLeft.speed = 0.2f;

	moveNE.PushBack({ 802, 485, 42, 56 });
	moveNE.PushBack({ 847, 485, 42, 56 });
	moveNE.PushBack({ 892, 485, 42, 56 });
	moveNE.PushBack({ 937, 485, 42, 56 });
	moveNE.PushBack({ 982, 485, 42, 56 });
	moveNE.PushBack({ 1027, 485, 42, 56 });
	moveNE.PushBack({ 1072, 485, 42, 56 });
	moveNE.PushBack({ 1117, 485, 42, 56 });

	moveNE.loop = true;
	moveNE.speed = 0.2f;

	moveNW.PushBack({ 20, 555, 42, 56 });
	moveNW.PushBack({ 65, 555, 42, 56 });
	moveNW.PushBack({ 110, 555, 42, 56 });
	moveNW.PushBack({ 155, 555, 42, 56 });
	moveNW.PushBack({ 200, 555, 42, 56 });
	moveNW.PushBack({ 245, 555, 42, 56 });
	moveNW.PushBack({ 290, 555, 42, 56 });
	moveNW.PushBack({ 335, 555, 42, 56 });

	moveNW.loop = true;
	moveNW.speed = 0.2f;

	moveUp.PushBack({ 411, 555, 42, 56 });
	moveUp.PushBack({ 456, 555, 42, 56 });
	moveUp.PushBack({ 501, 555, 42, 56 });
	moveUp.PushBack({ 546, 555, 42, 56 });
	moveUp.PushBack({ 591, 555, 42, 56 });
	moveUp.PushBack({ 636, 555, 42, 56 });
	moveUp.PushBack({ 681, 555, 42, 56 });
	moveUp.PushBack({ 726, 555, 42, 56 });

	moveUp.loop = true;
	moveUp.speed = 0.2f;

	meleeSE.PushBack({ 1944, 124, 82, 49 });
	meleeSE.PushBack({ 1858, 126, 82, 48 });
	meleeSE.PushBack({ 1775, 127, 82, 50 });
	meleeSE.PushBack({ 1690, 128, 82, 52 });
	meleeSE.PushBack({ 1602, 122, 82, 46 });
	meleeSE.PushBack({ 1520, 124, 82, 47 });
	meleeSE.PushBack({ 1447, 126, 30, 47 });
	meleeSE.PushBack({ 1361, 125, 38, 49 });

	meleeSE.loop = false;
	meleeSE.speed = 0.2f;

	meleeSW.PushBack({ 1350, 53, 38, 49 });
	meleeSW.PushBack({ 1444, 55, 30, 47 });
	meleeSW.PushBack({ 1531, 56, 26, 47 });
	meleeSW.PushBack({ 1613, 57, 29, 46 });
	meleeSW.PushBack({ 1696, 51, 34, 52 });
	meleeSW.PushBack({ 1777, 53, 35, 50 });
	meleeSW.PushBack({ 1857, 55, 28, 48 });
	meleeSW.PushBack({ 1933, 54, 38, 49 });

	meleeSW.loop = false;
	meleeSW.speed = 0.2f;

	meleeDown.PushBack({ 1361, 196, 28, 48 });
	meleeDown.PushBack({ 1442, 198, 29, 46 });
	meleeDown.PushBack({ 1524, 194, 44, 50 });
	meleeDown.PushBack({ 1609, 191, 38, 53 });
	meleeDown.PushBack({ 1686, 200, 37, 44 });
	meleeDown.PushBack({ 1772, 198, 34, 46 });
	meleeDown.PushBack({ 1853, 198, 37, 46 });
	meleeDown.PushBack({ 1944, 196, 28, 48 });

	meleeDown.loop = false;
	meleeDown.speed = 0.2f;

	meleeRight.PushBack({ 1359, 269, 42, 49 });
	meleeRight.PushBack({ 1444, 270, 40, 48 });
	meleeRight.PushBack({ 1524, 268, 31, 49 });
	meleeRight.PushBack({ 1599, 268, 41, 50 });
	meleeRight.PushBack({ 1693, 271, 30, 47 });
	meleeRight.PushBack({ 1775, 271, 31, 47 });
	meleeRight.PushBack({ 1857, 271, 32, 47 });
	meleeRight.PushBack({ 1942, 269, 42, 49 });

	meleeRight.loop = false;
	meleeRight.speed = 0.2f;

	meleeLeft.PushBack({ 1931, 342, 42, 49 });
	meleeLeft.PushBack({ 1848, 343, 40, 48 });
	meleeLeft.PushBack({ 1777, 341, 31, 49 });
	meleeLeft.PushBack({ 1692, 341, 41, 50 });
	meleeLeft.PushBack({ 1609, 344, 30, 47 });
	meleeLeft.PushBack({ 1526, 344, 31, 47 });
	meleeLeft.PushBack({ 1443, 344, 32, 47 });
	meleeLeft.PushBack({ 1348, 342, 42, 49 });

	meleeLeft.loop = false;
	meleeLeft.speed = 0.2f;

	meleeNE.PushBack({ 1360, 418, 40, 48 });
	meleeNE.PushBack({ 1439, 418, 42, 48 });
	meleeNE.PushBack({ 1524, 419, 48, 46 });
	meleeNE.PushBack({ 1607, 418, 34, 48 });
	meleeNE.PushBack({ 1690, 418, 33, 48 });
	meleeNE.PushBack({ 1768, 420, 38, 45 });
	meleeNE.PushBack({ 1854, 420, 35, 46 });
	meleeNE.PushBack({ 1934, 420, 38, 46 });

	meleeNE.loop = false;
	meleeNE.speed = 0.2f;

	meleeNW.PushBack({ 1932, 494, 40, 48 });
	meleeNW.PushBack({ 1851+4, 493, 42, 48 });
	meleeNW.PushBack({ 1760+12, 495, 48, 46 });
	meleeNW.PushBack({ 1691, 494, 34, 48 });
	meleeNW.PushBack({ 1609, 494, 33, 48 });
	meleeNW.PushBack({ 1526, 496, 38, 45 });
	meleeNW.PushBack({ 1443, 496, 35, 46 });
	meleeNW.PushBack({ 1360, 496, 38, 46 });

	meleeNW.loop = false;
	meleeNW.speed = 0.2f;

	meleeUp.PushBack({ 1360, 566, 36, 48 });
	meleeUp.PushBack({ 1446, 568, 34, 46 });
	meleeUp.PushBack({ 1512+19, 566, 47-19, 48 });
	meleeUp.PushBack({ 1594+20, 566, 48-20, 48 });
	meleeUp.PushBack({ 1696, 569, 39, 45 });
	meleeUp.PushBack({ 1779, 569, 35, 45 });
	meleeUp.PushBack({ 1862, 569, 39, 45 });
	meleeUp.PushBack({ 1943, 566, 36, 48 });

	meleeUp.loop = false;
	meleeUp.speed = 0.2f;

	enemyShotFx = App->audio->LoadFx("Assets/Fx/enemy_single_shot.wav");
	enemyKnifeFx = App->audio->LoadFx("Assets/Fx/Knife.wav");

	/*isSpawning = true;*/

	if (spawnPos.x - App->player->position.x > 0){
		currentAnim = &idleDownR;
		collider = App->collisions->AddCollider({ 0, 0, 30, 40 }, Collider::Type::SOLDIER, (Module*)App->enemies);
	}
	
	else if (spawnPos.x - App->player->position.x < 0){
		currentAnim = &idleDownL;
		collider = App->collisions->AddCollider({ 0, 0, 30, 40 }, Collider::Type::SOLDIER, (Module*)App->enemies);
	}

	timer = 0.7f;
	position = spawnPos;
}

void Enemy_Soldier_Static::Update()
{
	/*if (currentAnim == &enemy_airspawnL && timer <= 0) {
		currentAnim = &getUpL;
		collider = App->collisions->AddCollider({ 0, 0, 30, 40 }, Collider::Type::SOLDIER, (Module*)App->enemies);
		timer = 0.5f;
	}
	else if (currentAnim == &getUpL && timer <= 0)
	{
		isSpawning = false;
		currentAnim = &idleDownL;
		timer = rand() % 3;
	}

	else if (currentAnim == &enemy_airspawnR && timer <= 0) {
		currentAnim = &getUpR;
		collider = App->collisions->AddCollider({ 0, 0, 30, 40 }, Collider::Type::SOLDIER, (Module*)App->enemies);
		timer = 0.5f;
	}
	else if (currentAnim == &getUpR && timer <= 0)
	{
		isSpawning = false;
		currentAnim = &idleDownR;
		timer = rand() % 3;

	}*/

	if (Enemy_Soldier_Static::find_player())
	{
		if (timer <= 0.0f && isShooting == false)
		{
			isMoving = false;
			isIdle = false;
			hasDecided = false;
			Attack();
		}
		if (Enemy_Soldier_Static::position.y >= 1740 && Enemy_Soldier_Static::position.y <= 1780)
		{
			isMoving = true;
			isIdle = false;
			isShooting = false;
		}
		else if (isShooting == false && hasDecided == false ) {
			if (rand() % 100 > 55 && distance > 40 ) {
				isIdle = false;
				isMoving = true;
			}
			hasDecided = true;
		}
		else if (isMoving == false && isShooting == false)
		{
			isIdle = true;
		}
	}

	if (isMoving)
	{
		Move();
	}
	if (isIdle) {
		Idle();
	}
	//currentAnim = path.GetCurrentAnimation();
	timer -= 1.0f / 60.0f;
	if (timer <= (tempTimer - 0.8))isShooting = false;
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	
	
		collider->SetPos(position.x, position.y);
	
	Enemy::Update();
}

bool Enemy_Soldier_Static::find_player()
{
	playerX = App->player->position.x;
	playerY = App->player->position.y;
	dx = position.x - playerX;
	dy = position.y - playerY;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < 150) return true;
	else return false;
	//angle = atan2(dy, dx);
	//shotX = dx*0.02f;
	//shotY = dy*0.02f;
}

double  Enemy_Soldier_Static::calculateAngle()
{
	dx = position.x - playerX;
	dy = position.y - playerY;
	angle = atan2(dy, dx) * 180.0 / M_PI;
	return angle;
}

void Enemy_Soldier_Static::Move()
{
	loop++;
	if (loop % 2 == 0) {

		if (Enemy_Soldier_Static::calculateAngle() >= -110 && Enemy_Soldier_Static::calculateAngle() < -70) {
			currentAnim = &moveDown;
			position.y++;
		}
		else if (Enemy_Soldier_Static::calculateAngle() >= -160 && Enemy_Soldier_Static::calculateAngle() < -110) {
			currentAnim = &moveSE;
			position.y++;
			position.x++;
		}
		else if ((Enemy_Soldier_Static::calculateAngle() >= -180 && Enemy_Soldier_Static::calculateAngle() < -160) || (Enemy_Soldier_Static::calculateAngle() >= 160 && Enemy_Soldier_Static::calculateAngle() <= 180)) {
			currentAnim = &moveRight;
			position.x++;
		}
		else if (Enemy_Soldier_Static::calculateAngle() <= 160 && Enemy_Soldier_Static::calculateAngle() > 110) {
			currentAnim = &moveNE;
			position.y--;
			position.x++;
		}
		else if (Enemy_Soldier_Static::calculateAngle() <= 110 && Enemy_Soldier_Static::calculateAngle() > 70) {
			currentAnim = &moveUp;
			position.y--;
		}
		else if (Enemy_Soldier_Static::calculateAngle() <= 70 && Enemy_Soldier_Static::calculateAngle() > 20) {
			currentAnim = &moveNW;
			position.y--;
			position.x--;
		}
		else if ((Enemy_Soldier_Static::calculateAngle() <= 20 && Enemy_Soldier_Static::calculateAngle() >= 0) || (Enemy_Soldier_Static::calculateAngle() >= -20 && Enemy_Soldier_Static::calculateAngle() < -1)) {
			currentAnim = &moveLeft;
			position.x--;
		}
		else if (Enemy_Soldier_Static::calculateAngle() >= -70 && Enemy_Soldier_Static::calculateAngle() < -20) {
			currentAnim = &moveSW;
			position.y++;
			position.x--;
		}
	}
}
void Enemy_Soldier_Static::Idle()
{
	if (Enemy_Soldier_Static::calculateAngle() >= -90 && Enemy_Soldier_Static::calculateAngle() < -80) currentAnim = &idleDownL;
	else if (Enemy_Soldier_Static::calculateAngle() >= -100 && Enemy_Soldier_Static::calculateAngle() < -90) currentAnim = &idleDownR;
	else if (Enemy_Soldier_Static::calculateAngle() >= -135 && Enemy_Soldier_Static::calculateAngle() < -100) currentAnim = &idleSE1;
	else if (Enemy_Soldier_Static::calculateAngle() >= -170 && Enemy_Soldier_Static::calculateAngle() < -135) currentAnim = &idleSE2;
	else if ((Enemy_Soldier_Static::calculateAngle() >= -179 && Enemy_Soldier_Static::calculateAngle() < -170) || (Enemy_Soldier_Static::calculateAngle() >= 170 && Enemy_Soldier_Static::calculateAngle() < 180)) currentAnim = &idleRight;
	else if (Enemy_Soldier_Static::calculateAngle() <= 170 && Enemy_Soldier_Static::calculateAngle() > 135) currentAnim = &idleNE1;
	else if (Enemy_Soldier_Static::calculateAngle() <= 135 && Enemy_Soldier_Static::calculateAngle() > 100) currentAnim = &idleNE2;
	else if (Enemy_Soldier_Static::calculateAngle() <= 100 && Enemy_Soldier_Static::calculateAngle() > 90) currentAnim = &idleUpL;

	else if (Enemy_Soldier_Static::calculateAngle() <= 90 && Enemy_Soldier_Static::calculateAngle() > 80) currentAnim = &idleUpR;
	else if (Enemy_Soldier_Static::calculateAngle() <= 80 && Enemy_Soldier_Static::calculateAngle() > 45) currentAnim = &idleNW1;
	else if (Enemy_Soldier_Static::calculateAngle() <= 45 && Enemy_Soldier_Static::calculateAngle() > 10) currentAnim = &idleNW2;
	else if ((Enemy_Soldier_Static::calculateAngle() <= 10 && Enemy_Soldier_Static::calculateAngle() > 0) || (Enemy_Soldier_Static::calculateAngle() >= -10 && Enemy_Soldier_Static::calculateAngle() < -1)) currentAnim = &idleLeft;
	else if (Enemy_Soldier_Static::calculateAngle() >= -45 && Enemy_Soldier_Static::calculateAngle() < -10) currentAnim = &idleSW1;
	else if (Enemy_Soldier_Static::calculateAngle() >= -80 && Enemy_Soldier_Static::calculateAngle() < -45) currentAnim = &idleSW2;
}

void Enemy_Soldier_Static::Attack()
{
	//find_player();


	//if(distance > 100)
	//{
	//	position.x += cos(angle) * 3;
	//	position.y += sin(angle) * 3;
	//}

	if (distance < 40)
	{
		App->audio->PlayFx(enemyKnifeFx);
		if (Enemy_Soldier_Static::calculateAngle() >= -110 && Enemy_Soldier_Static::calculateAngle() < -70) {
			meleeDown.Reset();
			currentAnim = &meleeDown;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 13, position.y + 30, NULL, 1, Collider::Type::ENEMY_SHOT);

		}
		else if (Enemy_Soldier_Static::calculateAngle() >= -160 && Enemy_Soldier_Static::calculateAngle() < -110) {
			meleeSE.Reset();
			currentAnim = &meleeSE;

			App->particles->AddParticle(App->particles->enemyShot, position.x + 23, position.y + 27, 2, 1, Collider::Type::ENEMY_SHOT);
		}
		else if ((Enemy_Soldier_Static::calculateAngle() >= -180 && Enemy_Soldier_Static::calculateAngle() < -160) || (Enemy_Soldier_Static::calculateAngle() >= 160 && Enemy_Soldier_Static::calculateAngle() <= 180)) {
			meleeRight.Reset();
			currentAnim = &meleeRight;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 41, position.y + 16, 1, 0, Collider::Type::ENEMY_SHOT);
		}
		else if (Enemy_Soldier_Static::calculateAngle() <= 160 && Enemy_Soldier_Static::calculateAngle() > 110) {
			meleeNE.Reset();
			currentAnim = &meleeNE;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 31, position.y + 4, 1, -1, Collider::Type::ENEMY_SHOT);
		}
		else if (Enemy_Soldier_Static::calculateAngle() <= 110 && Enemy_Soldier_Static::calculateAngle() > 70) {
			meleeUp.Reset();
			currentAnim = &meleeUp;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, NULL, -1, Collider::Type::ENEMY_SHOT);
		}
		else if (Enemy_Soldier_Static::calculateAngle() <= 70 && Enemy_Soldier_Static::calculateAngle() > 20) {
			meleeNW.Reset();
			currentAnim = &meleeNW;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 4, position.y + 5, -2, -1, Collider::Type::ENEMY_SHOT);
		}
		else if ((Enemy_Soldier_Static::calculateAngle() <= 20 && Enemy_Soldier_Static::calculateAngle() >= 0) || (Enemy_Soldier_Static::calculateAngle() >= -20 && Enemy_Soldier_Static::calculateAngle() < -1)) {
			meleeLeft.Reset();
			currentAnim = &meleeLeft;
			App->particles->AddParticle(App->particles->enemyShot, position.x - 5, position.y + 17, -2, NULL, Collider::Type::ENEMY_SHOT);
		}
		else if (Enemy_Soldier_Static::calculateAngle() >= -70 && Enemy_Soldier_Static::calculateAngle() < -20) {
			meleeSW.Reset();
			currentAnim = &meleeSW;
			App->particles->AddParticle(App->particles->enemyShot, position.x - 6, position.y + 32, -1, 1, Collider::Type::ENEMY_SHOT);
		}
	}
	else
	{
		if (Enemy_Soldier_Static::calculateAngle() >= -90 && Enemy_Soldier_Static::calculateAngle() < -80) {
			shootDownL.Reset();
			currentAnim = &shootDownL;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 9, position.y + 30, NULL, 1, Collider::Type::ENEMY_SHOT);
		}
		else if (Enemy_Soldier_Static::calculateAngle() >= -100 && Enemy_Soldier_Static::calculateAngle() < -90) {
			shootDownR.Reset();
			currentAnim = &shootDownR;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y + 31, NULL, 1, Collider::Type::ENEMY_SHOT);
		}
		else if (Enemy_Soldier_Static::calculateAngle() >= -135 && Enemy_Soldier_Static::calculateAngle() < -100) {
			shootSE1.Reset();
			currentAnim = &shootSE1;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 19, position.y + 28, 1, 1, Collider::Type::ENEMY_SHOT);
		}
		else if (Enemy_Soldier_Static::calculateAngle() >= -170 && Enemy_Soldier_Static::calculateAngle() < -135) {
			shootSE2.Reset();
			currentAnim = &shootSE2;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 26, position.y + 26, 2, 1, Collider::Type::ENEMY_SHOT);
		}
		else if ((Enemy_Soldier_Static::calculateAngle() >= -180 && Enemy_Soldier_Static::calculateAngle() < -170) || (Enemy_Soldier_Static::calculateAngle() >= 170 && Enemy_Soldier_Static::calculateAngle() <= 180)) {
			shootRight.Reset();
			currentAnim = &shootRight;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 41, position.y + 16, 1, 0, Collider::Type::ENEMY_SHOT);
		}
		else if (Enemy_Soldier_Static::calculateAngle() <= 170 && Enemy_Soldier_Static::calculateAngle() > 135) {
			shootNE1.Reset();
			currentAnim = &shootNE1;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 34, position.y + 5, 2, -1, Collider::Type::ENEMY_SHOT);
		}

		else if (Enemy_Soldier_Static::calculateAngle() <= 135 && Enemy_Soldier_Static::calculateAngle() > 100) {
			shootNE2.Reset();
			currentAnim = &shootNE2;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 28, position.y + 4, 1, -1, Collider::Type::ENEMY_SHOT);
		}

		else if (Enemy_Soldier_Static::calculateAngle() <= 100 && Enemy_Soldier_Static::calculateAngle() > 90) {
			shootUpL.Reset();
			currentAnim = &shootUpL;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, NULL, -1, Collider::Type::ENEMY_SHOT);
		}

		else if (Enemy_Soldier_Static::calculateAngle() <= 90 && Enemy_Soldier_Static::calculateAngle() > 80) {
			shootUpR.Reset();
			currentAnim = &shootUpR;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, NULL, -1, Collider::Type::ENEMY_SHOT);
		}

		else if (Enemy_Soldier_Static::calculateAngle() <= 80 && Enemy_Soldier_Static::calculateAngle() > 45) {
			shootNW1.Reset();
			currentAnim = &shootNW1;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 6, position.y + 4, -1, -1, Collider::Type::ENEMY_SHOT);
		}

		else if (Enemy_Soldier_Static::calculateAngle() <= 45 && Enemy_Soldier_Static::calculateAngle() > 10) {
			shootNW2.Reset();
			currentAnim = &shootNW2;
			App->particles->AddParticle(App->particles->enemyShot, position.x + 3, position.y + 6, -2, -1, Collider::Type::ENEMY_SHOT);
		}

		else if ((Enemy_Soldier_Static::calculateAngle() <= 10 && Enemy_Soldier_Static::calculateAngle() > 0) || (Enemy_Soldier_Static::calculateAngle() >= -10 && Enemy_Soldier_Static::calculateAngle() < -1)) {
			shootLeft.Reset();
			currentAnim = &shootLeft;
			App->particles->AddParticle(App->particles->enemyShot, position.x - 5, position.y + 17, -2, NULL, Collider::Type::ENEMY_SHOT);
		}

		else if (Enemy_Soldier_Static::calculateAngle() <= -10 && Enemy_Soldier_Static::calculateAngle() > -45) {
			shootSW1.Reset();
			currentAnim = &shootSW1;
			App->particles->AddParticle(App->particles->enemyShot, position.x - 5, position.y + 32, -2, 1, Collider::Type::ENEMY_SHOT);
		}

		else if (Enemy_Soldier_Static::calculateAngle() <= -45 && Enemy_Soldier_Static::calculateAngle() > -90) {
			shootSW2.Reset();
			currentAnim = &shootSW2;
			App->particles->AddParticle(App->particles->enemyShot, position.x - 8, position.y + 32, -1, 1, Collider::Type::ENEMY_SHOT);
		}
		App->audio->PlayFx(enemyShotFx);
	}


	isShooting = true;
	timer = SHOOT_INTERVAL - (randomValue = rand() % 2);
	tempTimer = timer;
}

void Enemy_Soldier_Static::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT) {
		if (Enemy_Soldier_Static::calculateAngle() >= -100 && Enemy_Soldier_Static::calculateAngle() < -80) {
			App->particles->AddParticle(App->particles->enemy_deathDown, position.x, position.y, NULL, NULL, Collider::Type::NONE, NULL);
		}
		else if (Enemy_Soldier_Static::calculateAngle() >= -170 && Enemy_Soldier_Static::calculateAngle() < -100) {
			App->particles->AddParticle(App->particles->enemy_deathSE, position.x, position.y, NULL, NULL, Collider::Type::NONE, NULL);
		}
		else if ((Enemy_Soldier_Static::calculateAngle() >= -179 && Enemy_Soldier_Static::calculateAngle() < -170) || (Enemy_Soldier_Static::calculateAngle() >= 170 && Enemy_Soldier_Static::calculateAngle() < 180)) {
			App->particles->AddParticle(App->particles->enemy_deathRight, position.x, position.y, NULL, NULL, Collider::Type::NONE, NULL);
		}
		else if (Enemy_Soldier_Static::calculateAngle() <= 170 && Enemy_Soldier_Static::calculateAngle() > 100) {
			App->particles->AddParticle(App->particles->enemy_deathNE, position.x, position.y, NULL, NULL, Collider::Type::NONE, NULL);
		}
		else if (Enemy_Soldier_Static::calculateAngle() <= 100 && Enemy_Soldier_Static::calculateAngle() > 80) {
			App->particles->AddParticle(App->particles->enemy_deathDown, position.x, position.y, NULL, NULL, Collider::Type::NONE, NULL);
		}
		else if (Enemy_Soldier_Static::calculateAngle() <= 80 && Enemy_Soldier_Static::calculateAngle() > 10) {
			App->particles->AddParticle(App->particles->enemy_deathNW, position.x, position.y, NULL, NULL, Collider::Type::NONE, NULL);
		}
		else if ((Enemy_Soldier_Static::calculateAngle() <= 10 && Enemy_Soldier_Static::calculateAngle() >= 0) || (Enemy_Soldier_Static::calculateAngle() >= -10 && Enemy_Soldier_Static::calculateAngle() < -1)) {
			App->particles->AddParticle(App->particles->enemy_deathLeft, position.x, position.y, NULL, NULL, Collider::Type::NONE, NULL);
		}
		else if (Enemy_Soldier_Static::calculateAngle() >= -80 && Enemy_Soldier_Static::calculateAngle() < -10) {
			App->particles->AddParticle(App->particles->enemy_deathSW, position.x, position.y, NULL, NULL, Collider::Type::NONE, NULL);
		}

		App->player->score += 3000;
		App->audio->PlayFx(damagedSoldier);

		// Probabilidad de aparición de los BLUEDIAMONDS 
		int prob_diamond = 35;
		int prob_life = 17;
		// Comprobar si el número aleatorio esta dentro de la probabilidad de aparicion
		if (randomValue < prob_diamond && hasDropped == false) {
			App->pickUps->AddPickUps(PickUps_Type::BLUEDIAMOND, position.x + 12, position.y + 4);
			hasDropped = true;
		}
		if (randomValue > 100 - prob_life && hasDropped == false) {
			App->pickUps->AddPickUps(PickUps_Type::LIFE, position.x + 12, position.y + 4);
			hasDropped = true;
		}
	}

	else if (collider->type == Collider::Type::PLAYER) {
		isMoving = false;
	}

	/* Choque entre soldados
	else if (collider->type == Collider::Type::SOLDIER) {
		if (currentAnim == &moveUp) { position.y += 1; }
		if (currentAnim == &moveDown) { position.y -= 1; }
		if (currentAnim == &moveRight) { position.x -= 1; }
		if (currentAnim == &moveLeft) { position.x += 1; }
		if (currentAnim == &moveNE) { position.y += 1; position.x -= 1; }
		if (currentAnim == &moveNW) { position.y += 1; position.x += 1; }
		if (currentAnim == &moveSE) { position.y -= 1; position.x -= 1; }
		if (currentAnim == &moveSW) { position.y -= 1; position.x += 1; }

	}*/
}