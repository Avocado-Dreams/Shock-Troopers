#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

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

	idleUp.PushBack({ 1173, 41, 30, 48 });

	shootUp.PushBack({ 1173, 41, 30, 48 });
	shootUp.PushBack({ 1252, 41, 30, 47 });
	shootUp.PushBack({ 1173, 41, 30, 48 });
	shootUp.loop = false;
	shootUp.speed = 0.1f;

	path.PushBack({0.0f, 0.0f}, 0, &idleDownL);
	currentAnim = &idleDownR;

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
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
	if (distance < 100) return true;
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
	else if (Enemy_Mech::calculateAngle() <= 100 && Enemy_Mech::calculateAngle() > 80) currentAnim = &idleUp;
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
		isShooting = true;
		App->particles->AddParticle(App->particles->enemyShotDownL, position.x + 9, position.y + 30, NULL, NULL, Collider::Type::ENEMY_SHOT);
	}
	else if (Enemy_Mech::calculateAngle() >= -100 && Enemy_Mech::calculateAngle() < -90) {
		shootDownR.Reset();
		currentAnim = &shootDownR;
		isShooting = true;
		App->particles->AddParticle(App->particles->enemyShotDownR, position.x + 16, position.y + 31, NULL, NULL, Collider::Type::ENEMY_SHOT);
	}
	else if (Enemy_Mech::calculateAngle() >= -135 && Enemy_Mech::calculateAngle() < -100) {
		shootSE1.Reset();
		currentAnim = &shootSE1;
		isShooting = true;
		App->particles->AddParticle(App->particles->enemyShotSE1, position.x + 19, position.y + 28, 1, 1, Collider::Type::ENEMY_SHOT);
	}
	else if (Enemy_Mech::calculateAngle() >= -170 && Enemy_Mech::calculateAngle() < -135) {
		shootSE2.Reset();
		currentAnim = &shootSE2;
		isShooting = true;
		App->particles->AddParticle(App->particles->enemyShotSE2, position.x + 26, position.y + 26, 2, 1, Collider::Type::ENEMY_SHOT);
	}
	else if ((Enemy_Mech::calculateAngle() >= -179 && Enemy_Mech::calculateAngle() < -170) || (Enemy_Mech::calculateAngle() >= 170 && Enemy_Mech::calculateAngle() < 180)){
		shootRight.Reset();
		currentAnim = &shootRight;
		isShooting = true;
		App->particles->AddParticle(App->particles->enemyShotRight, position.x + 41, position.y + 16, NULL, NULL, Collider::Type::ENEMY_SHOT);
	}
	else if (Enemy_Mech::calculateAngle() <= 170 && Enemy_Mech::calculateAngle() > 135) {
		shootNE1.Reset();
		currentAnim = &shootNE1;
		isShooting = true;
		App->particles->AddParticle(App->particles->enemyShotNE1, position.x + 34, position.y + 5, 2, -1, Collider::Type::ENEMY_SHOT);
	}

	else if (Enemy_Mech::calculateAngle() <= 135 && Enemy_Mech::calculateAngle() > 100) {
		shootNE2.Reset();
		currentAnim = &shootNE2;
		isShooting = true;
		App->particles->AddParticle(App->particles->enemyShotNE2, position.x + 28, position.y + 4, 1, -1, Collider::Type::ENEMY_SHOT);
	}

	else if (Enemy_Mech::calculateAngle() <= 100 && Enemy_Mech::calculateAngle() > 80) {
		shootUp.Reset();
		currentAnim = &shootUp;
		isShooting = true;
		App->particles->AddParticle(App->particles->enemyShotUp, position.x + 16, position.y -5, NULL, NULL, Collider::Type::ENEMY_SHOT);
	}
	timer = SHOOT_INTERVAL;
}