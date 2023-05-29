#include "Enemy_Tank.h"

#include "ModulePickUps.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

Enemy_Tank::Enemy_Tank(int x, int y) : Enemy(x, y)
{
	idleDown.PushBack({ 904, 705, 66, 44 });

	shootDown.PushBack({ 904, 705, 66, 44 });
	shootDown.PushBack({ 969, 705, 66, 44 });
	shootDown.PushBack({ 1034, 705, 66, 44 });
	shootDown.loop = false;
	shootDown.speed = 0.1f;

	idleSW1.PushBack({ 1099, 705, 66, 44 });

	shootSW1.PushBack({ 1099, 705, 66, 44 });
	shootSW1.PushBack({ 1164, 705, 66, 44 });
	shootSW1.PushBack({ 1229, 705, 66, 44 });
	shootSW1.loop = false;
	shootSW1.speed = 0.1f;

	idleSW2.PushBack({ 1294, 705, 66, 44 });

	shootSW2.PushBack({ 1294, 705, 66, 44 });
	shootSW2.PushBack({ 1359, 705, 66, 44 });
	shootSW2.PushBack({ 1424, 705, 66, 44 });
	shootSW2.loop = false;
	shootSW2.speed = 0.1f;

	idleSW3.PushBack({ 904, 748, 66, 44 });

	shootSW3.PushBack({ 904, 748, 66, 44 });
	shootSW3.PushBack({ 969, 748, 66, 44 });
	shootSW3.PushBack({ 1034, 748, 66, 44 });
	shootSW3.loop = false;
	shootSW3.speed = 0.1f;

	idleLeft.PushBack({ 1099, 748, 66, 44 });

	shootLeft.PushBack({ 1099, 748, 66, 44 });
	shootLeft.PushBack({ 1164, 748, 66, 44 });
	shootLeft.PushBack({ 1229, 748, 66, 44 });
	shootLeft.loop = false;
	shootLeft.speed = 0.1f;

	idleNW1.PushBack({ 1294, 748, 66, 44 });

	shootNW1.PushBack({ 1294, 748, 66, 44 });
	shootNW1.PushBack({ 1359, 748, 66, 44 });
	shootNW1.PushBack({ 1424, 748, 66, 44 });
	shootNW1.loop = false;
	shootNW1.speed = 0.1f;


	idleNW2.PushBack({ 904, 791, 66, 44 });

	shootNW2.PushBack({ 904, 791, 66, 44 });
	shootNW2.PushBack({ 969, 791, 66, 44 });
	shootNW2.PushBack({ 1034, 791, 66, 44 });
	shootNW2.loop = false;
	shootNW2.speed = 0.1f;


	idleNW3.PushBack({ 1099, 791, 66, 44 });

	shootNW3.PushBack({ 1099, 791, 66, 44 });
	shootNW3.PushBack({ 1164, 791, 66, 44 });
	shootNW3.PushBack({ 1229, 791, 66, 44 });
	shootNW3.loop = false;
	shootNW3.speed = 0.1f;

	idleUp.PushBack({ 1294, 791, 66, 44 });

	shootUp.PushBack({ 1294, 791, 66, 44 });
	shootUp.PushBack({ 1359, 791, 66, 44 });
	shootUp.PushBack({ 1424, 791, 66, 44 });
	shootUp.loop = false;
	shootUp.speed = 0.1f;

	idleNE1.PushBack({ 1099, 877, 66, 44 });

	shootNE1.PushBack({ 1099, 877, 66, 44 });
	shootNE1.PushBack({ 1164, 877, 66, 44 });
	shootNE1.PushBack({ 1229, 877, 66, 44 });
	shootNE1.loop = false;
	shootNE1.speed = 0.1f;

	idleNE2.PushBack({ 1294, 877, 66, 44 });

	shootNE2.PushBack({ 1294, 877, 66, 44 });
	shootNE2.PushBack({ 1359, 877, 66, 44 });
	shootNE2.PushBack({ 1424, 877, 66, 44 });
	shootNE2.loop = false;
	shootNE2.speed = 0.1f;

	idleNE3.PushBack({ 904, 877, 66, 44 });

	shootNE3.PushBack({ 904, 877, 66, 44 });
	shootNE3.PushBack({ 969, 877, 66, 44 });
	shootNE3.PushBack({ 1034, 877, 66, 44 });
	shootNE1.loop = false;
	shootNE1.speed = 0.1f;

	idleRight.PushBack({ 904, 920, 66, 44 });

	shootRight.PushBack({ 904, 920, 66, 44 });
	shootRight.PushBack({ 969, 920, 66, 44 });
	shootRight.PushBack({ 1034, 920, 66, 44 });
	shootRight.loop = false;
	shootRight.speed = 0.1f;

	idleSE1.PushBack({ 904, 834, 66, 44 });

	shootSE1.PushBack({ 904, 834, 66, 44 });
	shootSE1.PushBack({ 969, 834, 66, 44 });
	shootSE1.PushBack({ 1034, 834, 66, 44 });
	shootSE1.loop = false;
	shootSE1.speed = 0.1f;

	idleSE2.PushBack({ 1099, 834, 66, 44 });

	shootSE2.PushBack({ 1099, 834, 66, 44 });
	shootSE2.PushBack({ 1164, 834, 66, 44 });
	shootSE2.PushBack({ 1229, 834, 66, 44 });
	shootSE2.loop = false;
	shootSE2.speed = 0.1f;

	idleSE3.PushBack({ 1294, 834, 66, 44 });

	shootSE3.PushBack({ 1294, 834, 66, 44 });
	shootSE3.PushBack({ 1359, 834, 66, 44 });
	shootSE3.PushBack({ 1424, 834, 66, 44 });
	shootSE3.loop = false;
	shootSE3.speed = 0.1f;

	tankStop.PushBack({ 1294, 834, 66, 44 });

	tankMove.PushBack({ 1294, 834, 66, 44 });
	tankMove.PushBack({ 1359, 834, 66, 44 });
	tankMove.PushBack({ 1424, 834, 66, 44 });
	tankMove.loop = false;
	tankMove.speed = 0.1f;

	isSpawning = false;

	tankShotFx = App->audio->LoadFx("Assets/Fx/tankShot.wav");

	collider = App->collisions->AddCollider({ 0, 0, 34, 34 }, Collider::Type::TANK, (Module*)App->enemies);

	currentAnim = &idleDown;

	path.PushBack({ 0.0f, 0.0f }, 0, &idleDown);

	timer = 0.0f;
}

void Enemy_Tank::Update()
{
	if (isSpawning == false && Enemy_Tank::find_player())
	{
		if (timer <= 0.0f && isShooting == false)
		{
			Attack();
		}
		else if (timer > 0.0f && isShooting == false)Idle();
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

bool Enemy_Tank::find_player()
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

double  Enemy_Tank::calculateAngle()
{
	dx = position.x - playerX;
	dy = position.y - playerY;
	angle = atan2(dy, dx) * 180.0 / M_PI;
	return angle;
}

void Enemy_Tank::Idle()
{
	if (Enemy_Tank::calculateAngle() >= -100 && Enemy_Tank::calculateAngle() < -80) currentAnim = &idleDown;
	else if (Enemy_Tank::calculateAngle() >= -120 && Enemy_Tank::calculateAngle() < -100) currentAnim = &idleSE3;
	else if (Enemy_Tank::calculateAngle() >= -145 && Enemy_Tank::calculateAngle() < -120) currentAnim = &idleSE2;
	else if (Enemy_Tank::calculateAngle() >= -170 && Enemy_Tank::calculateAngle() < -145) currentAnim = &idleSE1;
	else if ((Enemy_Tank::calculateAngle() >= -179 && Enemy_Tank::calculateAngle() < -170) || (Enemy_Tank::calculateAngle() >= 170 && Enemy_Tank::calculateAngle() < 180)) currentAnim = &idleRight;
	else if (Enemy_Tank::calculateAngle() <= 170 && Enemy_Tank::calculateAngle() > 150) currentAnim = &idleNE3;
	else if (Enemy_Tank::calculateAngle() <= 150 && Enemy_Tank::calculateAngle() > 125) currentAnim = &idleNE2;
	else if (Enemy_Tank::calculateAngle() <= 125 && Enemy_Tank::calculateAngle() > 100) currentAnim = &idleNE1;

	else if (Enemy_Tank::calculateAngle() <= 100 && Enemy_Tank::calculateAngle() > 80) currentAnim = &idleUp;
	else if (Enemy_Tank::calculateAngle() <= 80 && Enemy_Tank::calculateAngle() > 60) currentAnim = &idleNW3;
	else if (Enemy_Tank::calculateAngle() <= 60 && Enemy_Tank::calculateAngle() > 35) currentAnim = &idleNW2;
	else if (Enemy_Tank::calculateAngle() <= 35 && Enemy_Tank::calculateAngle() > 10) currentAnim = &idleNW1;
	else if ((Enemy_Tank::calculateAngle() <= 10 && Enemy_Tank::calculateAngle() >= 0) || (Enemy_Tank::calculateAngle() >= -10 && Enemy_Tank::calculateAngle() < -1 )) currentAnim = &idleLeft;
	else if (Enemy_Tank::calculateAngle() >= -30 && Enemy_Tank::calculateAngle() < -10) currentAnim = &idleSW3;
	else if (Enemy_Tank::calculateAngle() >= -55 && Enemy_Tank::calculateAngle() < -30) currentAnim = &idleSW2;
	else if (Enemy_Tank::calculateAngle() >= -80 && Enemy_Tank::calculateAngle() < -55) currentAnim = &idleSW1;
}

void Enemy_Tank::Attack()
{
	//find_player();


	//if(distance > 100)
	//{
	//	position.x += cos(angle) * 3;
	//	position.y += sin(angle) * 3;
	//}

	if (Enemy_Tank::calculateAngle() >= -100 && Enemy_Tank::calculateAngle() < -80) {
		shootDown.Reset();
		currentAnim = &shootDown;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 9, position.y + 30, NULL, 1, Collider::Type::TANK_SHOT);
	}
	else if (Enemy_Tank::calculateAngle() >= -120 && Enemy_Tank::calculateAngle() < -100) {
		shootSE3.Reset();
		currentAnim = &shootSE3;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y + 31, NULL, 1, Collider::Type::TANK_SHOT);
	}
	else if (Enemy_Tank::calculateAngle() >= -145 && Enemy_Tank::calculateAngle() < -120) {
		shootSE2.Reset();
		currentAnim = &shootSE2;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 19, position.y + 28, 1, 1, Collider::Type::TANK_SHOT);
	}
	else if (Enemy_Tank::calculateAngle() >= -170 && Enemy_Tank::calculateAngle() < -145) {
		shootSE1.Reset();
		currentAnim = &shootSE1;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 26, position.y + 26, 2, 1, Collider::Type::TANK_SHOT);
	}
	else if ((Enemy_Tank::calculateAngle() >= -179 && Enemy_Tank::calculateAngle() < -170) || (Enemy_Tank::calculateAngle() >= 170 && Enemy_Tank::calculateAngle() < 180)) {
		shootRight.Reset();
		currentAnim = &shootRight;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 41, position.y + 16, 1, 0, Collider::Type::TANK_SHOT);
	}
	else if (Enemy_Tank::calculateAngle() <= 170 && Enemy_Tank::calculateAngle() > 150) {
		shootNE3.Reset();
		currentAnim = &shootNE3;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 34, position.y + 5, 2, -1, Collider::Type::TANK_SHOT);
	}

	else if (Enemy_Tank::calculateAngle() <= 150 && Enemy_Tank::calculateAngle() > 125) {
		shootNE2.Reset();
		currentAnim = &shootNE2;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 28, position.y + 4, 1, -1, Collider::Type::TANK_SHOT);
	}

	else if (Enemy_Tank::calculateAngle() <= 125 && Enemy_Tank::calculateAngle() > 100) {
		shootNE1.Reset();
		currentAnim = &shootNE1;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, NULL, -1, Collider::Type::TANK_SHOT);
	}

	else if (Enemy_Tank::calculateAngle() <= 100 && Enemy_Tank::calculateAngle() > 80) {
		shootUp.Reset();
		currentAnim = &shootUp;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 16, position.y - 5, NULL, -1, Collider::Type::TANK_SHOT);
	}

	else if (Enemy_Tank::calculateAngle() <= 80 && Enemy_Tank::calculateAngle() > 60) {
		shootNW1.Reset();
		currentAnim = &shootNW1;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 6, position.y + 4, -1, -1, Collider::Type::TANK_SHOT);
	}

	else if (Enemy_Tank::calculateAngle() <= 60 && Enemy_Tank::calculateAngle() > 35) {
		shootNW2.Reset();
		currentAnim = &shootNW2;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 3, position.y + 6, -2, -1, Collider::Type::TANK_SHOT);
	}

	else if (Enemy_Tank::calculateAngle() <= 35 && Enemy_Tank::calculateAngle() > 10) {
		shootNW3.Reset();
		currentAnim = &shootNW3;
		App->particles->AddParticle(App->particles->enemyShot, position.x + 3, position.y + 6, -2, -1, Collider::Type::TANK_SHOT);
	}

	else if ((Enemy_Tank::calculateAngle() <= 10 && Enemy_Tank::calculateAngle() >= 0) || (Enemy_Tank::calculateAngle() >= -10 && Enemy_Tank::calculateAngle() < -1)) {
		shootLeft.Reset();
		currentAnim = &shootLeft;
		App->particles->AddParticle(App->particles->enemyShot, position.x - 5, position.y + 17, -2, NULL, Collider::Type::TANK_SHOT);
	}

	else if (Enemy_Tank::calculateAngle() <= -10 && Enemy_Tank::calculateAngle() > -30) {
		shootSW3.Reset();
		currentAnim = &shootSW3;
		App->particles->AddParticle(App->particles->enemyShot, position.x - 5, position.y + 32, -2, 1, Collider::Type::TANK_SHOT);
	}

	else if (Enemy_Tank::calculateAngle() <= -30 && Enemy_Tank::calculateAngle() > -55) {
		shootSW2.Reset();
		currentAnim = &shootSW2;
		App->particles->AddParticle(App->particles->enemyShot, position.x - 8, position.y + 32, -1, 1, Collider::Type::TANK_SHOT);
	}

	else if (Enemy_Tank::calculateAngle() <= -55 && Enemy_Tank::calculateAngle() > -80) {
		shootSW1.Reset();
		currentAnim = &shootSW1;
		App->particles->AddParticle(App->particles->enemyShot, position.x - 8, position.y + 32, -1, 1, Collider::Type::TANK_SHOT);
	}

	isShooting = true;
	App->audio->PlayFx(tankShotFx);
	timer = SHOOT_INTERVAL;
}

void Enemy_Tank::OnCollision(Collider* collider)
{

	App->particles->AddParticle(App->particles->tank_explosion, position.x, position.y, NULL, NULL, Collider::Type::NONE, NULL);
	App->audio->PlayFx(destroyedTank);
	App->particles->AddParticle(App->particles->tank_explosion, position.x+9, position.y+9, NULL, NULL, Collider::Type::NONE, 4);
	App->audio->PlayFx(destroyedTank);
	App->particles->AddParticle(App->particles->tank_explosion, position.x+18, position.y+6, NULL, NULL, Collider::Type::NONE, 8);
	App->audio->PlayFx(destroyedTank);
	App->particles->AddParticle(App->particles->tank_explosion, position.x-9, position.y+18, NULL, NULL, Collider::Type::NONE, 12);
	App->audio->PlayFx(destroyedTank);
	App->particles->AddParticle(App->particles->tank_explosion, position.x+27, position.y+12, NULL, NULL, Collider::Type::NONE, 16);
	App->audio->PlayFx(destroyedTank);
	
	// Probabilidad de aparición de los BLUEDIAMONDS 
	int prob_diamond = 30;
	int prob_life = 50;
	// Comprobar si el número aleatorio esta dentro de la probabilidad de aparicion
	if (randomValue < prob_diamond && hasDropped == false) {
		App->pickUps->AddPickUps(PickUps_Type::BLUEDIAMOND, position.x + 12, position.y + 4);
		hasDropped = true;
	}
	if (randomValue < prob_life && hasDropped == false) {
		App->pickUps->AddPickUps(PickUps_Type::LIFE, position.x + 12, position.y + 4);
		hasDropped = true;
	}

}
