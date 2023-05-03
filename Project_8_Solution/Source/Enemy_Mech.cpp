#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	idleDown.PushBack({ 23, 41, 30, 48 });
	currentAnim = &idleDown;
	//front.pingpong = true;

	path.PushBack({0.0f, 0.0f}, 0, &idleDown);

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Mech::Update()
{
	Attack();
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	//currentAnim = path.GetCurrentAnimation();
	timer -= 1.0f / 60.0f;
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Mech::find_player()
{
	playerX = App->player->position.x;
	playerY = App->player->position.y;
	dx = position.x - playerX;
	dy = position.y - playerY;
	distance = sqrt(dx * dx + dy * dy);
	angle = atan2(dy, dx);
	shotX = dx*0.02f;
	shotY = dy*0.02f;
}

void Enemy_Mech::Attack()
{
	find_player();
	

	//if(distance > 100)
	//{
	//	position.x += cos(angle) * 3;
	//	position.y += sin(angle) * 3;
	//}
	
	if (distance <= 70 && timer <= 0.0f)
	{
		shootDown.PushBack({ 23, 41, 30, 48 });
		shootDown.PushBack({ 101, 41, 30, 49 });
		shootDown.speed = 0.1f;
		currentAnim = &shootDown;
		App->particles->AddParticle(App->particles->enemyShot, position.x - 10, position.y, -shotX, -shotY, Collider::Type::ENEMY_SHOT);
		timer = SHOOT_INTERVAL;

	}
}
