#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
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


	path.PushBack({0.0f, 0.0f}, 0, &idleDownL);
	currentAnim = &idleDownR;

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);

	enemyShotFx = App->audio->LoadFx("Assets/Fx/enemy_single_shot.wav");
}

void Enemy_Mech::Update()
{
	if (Enemy_Mech::find_player())
	{
		if (timer <= 0.0f && isShooting == false)
		{
			Attack();
		}
		else if (timer>0.0f && isShooting ==false)Idle();
	}
	
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	//currentAnim = path.GetCurrentAnimation();
	timer -= 1.0f / 60.0f;
	if (timer <= 4.2)isShooting = false;
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

bool Enemy_Mech::find_player()
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

double  Enemy_Mech::calculateAngle()
{
	dx = position.x - playerX;
	dy = position.y - playerY;
	angle = atan2(dy, dx) * 180.0 / M_PI;
	return angle;
}

void Enemy_Mech::Idle()
{
	if (Enemy_Mech::calculateAngle() >= -90 && Enemy_Mech::calculateAngle() < -80) currentAnim = &idleDownL;
	else if (Enemy_Mech::calculateAngle() >= -100 && Enemy_Mech::calculateAngle() < -90) currentAnim = &idleDownR;
	else if (Enemy_Mech::calculateAngle() >= -135 && Enemy_Mech::calculateAngle() < -100) currentAnim = &idleSE1;
	else if (Enemy_Mech::calculateAngle() >= -170 && Enemy_Mech::calculateAngle() < -135) currentAnim = &idleSE2;
	else if ((Enemy_Mech::calculateAngle() >= -179 && Enemy_Mech::calculateAngle() < -170) || (Enemy_Mech::calculateAngle() >= 170 && Enemy_Mech::calculateAngle() < 180)) currentAnim = &idleRight;
	else if (Enemy_Mech::calculateAngle() <= 170 && Enemy_Mech::calculateAngle() > 135) currentAnim = &idleNE1;
	else if (Enemy_Mech::calculateAngle() <= 135 && Enemy_Mech::calculateAngle() > 100) currentAnim = &idleNE2;
	else if (Enemy_Mech::calculateAngle() <= 100 && Enemy_Mech::calculateAngle() > 90) currentAnim = &idleUpL;
	
	else if (Enemy_Mech::calculateAngle() <= 90 && Enemy_Mech::calculateAngle() > 80) currentAnim = &idleUpR;
	else if (Enemy_Mech::calculateAngle() <= 80 && Enemy_Mech::calculateAngle() > 45) currentAnim = &idleNW1;
	else if (Enemy_Mech::calculateAngle() <= 45 && Enemy_Mech::calculateAngle() > 10) currentAnim = &idleNW2;
	else if ((Enemy_Mech::calculateAngle() <= 10 && Enemy_Mech::calculateAngle() > 0) || (Enemy_Mech::calculateAngle() >= -10 && Enemy_Mech::calculateAngle() < -1)) currentAnim = &idleLeft;
	else if (Enemy_Mech::calculateAngle() >= -45 && Enemy_Mech::calculateAngle() < -10) currentAnim = &idleSW1;
	else if (Enemy_Mech::calculateAngle() >= -80 && Enemy_Mech::calculateAngle() < -45) currentAnim = &idleSW2;
}

void Enemy_Mech::Attack()
{
	//find_player();


	//if(distance > 100)
	//{
	//	position.x += cos(angle) * 3;
	//	position.y += sin(angle) * 3;
	//}

	if (Enemy_Mech::calculateAngle() >= -90 && Enemy_Mech::calculateAngle() < -80) {
		shootDownL.Reset();
		currentAnim = &shootDownL;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 9, position.y + 30, NULL, 1, Collider::Type::ENEMY_SHOT);
	}
	else if (Enemy_Mech::calculateAngle() >= -100 && Enemy_Mech::calculateAngle() < -90) {
		shootDownR.Reset();
		currentAnim = &shootDownR;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y + 31, NULL, 1, Collider::Type::ENEMY_SHOT);
	}
	else if (Enemy_Mech::calculateAngle() >= -135 && Enemy_Mech::calculateAngle() < -100) {
		shootSE1.Reset();
		currentAnim = &shootSE1;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 19, position.y + 28, 1, 1, Collider::Type::ENEMY_SHOT);
	}
	else if (Enemy_Mech::calculateAngle() >= -170 && Enemy_Mech::calculateAngle() < -135) {
		shootSE2.Reset();
		currentAnim = &shootSE2;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 26, position.y + 26, 2, 1, Collider::Type::ENEMY_SHOT);
	}
	else if ((Enemy_Mech::calculateAngle() >= -179 && Enemy_Mech::calculateAngle() < -170) || (Enemy_Mech::calculateAngle() >= 170 && Enemy_Mech::calculateAngle() < 180)){
		shootRight.Reset();
		currentAnim = &shootRight;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 41, position.y + 16, 1, 0, Collider::Type::ENEMY_SHOT);
	}
	else if (Enemy_Mech::calculateAngle() <= 170 && Enemy_Mech::calculateAngle() > 135) {
		shootNE1.Reset();
		currentAnim = &shootNE1;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 34, position.y + 5, 2, -1, Collider::Type::ENEMY_SHOT);
	}

	else if (Enemy_Mech::calculateAngle() <= 135 && Enemy_Mech::calculateAngle() > 100) {
		shootNE2.Reset();
		currentAnim = &shootNE2;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 28, position.y + 4, 1, -1, Collider::Type::ENEMY_SHOT);
	}

	else if (Enemy_Mech::calculateAngle() <= 100 && Enemy_Mech::calculateAngle() > 90) {
		shootUpL.Reset();
		currentAnim = &shootUpL;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y -5, NULL, -1, Collider::Type::ENEMY_SHOT);
	}

	else if (Enemy_Mech::calculateAngle() <= 90 && Enemy_Mech::calculateAngle() > 80) {
		shootUpR.Reset();
		currentAnim = &shootUpR;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, NULL, -1, Collider::Type::ENEMY_SHOT);
	}

	else if (Enemy_Mech::calculateAngle() <= 80 && Enemy_Mech::calculateAngle() > 45) {
		shootNW1.Reset();
		currentAnim = &shootNW1;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, -1, -1, Collider::Type::ENEMY_SHOT);
	}

	else if (Enemy_Mech::calculateAngle() <= 45 && Enemy_Mech::calculateAngle() > 10) {
		shootNW2.Reset();
		currentAnim = &shootNW2;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, -2, -1, Collider::Type::ENEMY_SHOT);
	}

	else if ((Enemy_Mech::calculateAngle() <= 10 && Enemy_Mech::calculateAngle() > 0) || (Enemy_Mech::calculateAngle() >= -10 && Enemy_Mech::calculateAngle() < -1)) {
		shootLeft.Reset();
		currentAnim = &shootLeft;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, -2, NULL, Collider::Type::ENEMY_SHOT);
	}

	else if (Enemy_Mech::calculateAngle() <= -10 && Enemy_Mech::calculateAngle() > -45) {
		shootSW1.Reset();
		currentAnim = &shootSW1;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, -2, 1, Collider::Type::ENEMY_SHOT);
	}

	else if (Enemy_Mech::calculateAngle() <= -45 && Enemy_Mech::calculateAngle() > -90) {
		shootSW2.Reset();
		currentAnim = &shootSW2;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, -1, 1, Collider::Type::ENEMY_SHOT);
	}
	isShooting = true;
	App->audio->PlayFx(enemyShotFx);
	timer = SHOOT_INTERVAL;
}