#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	front.PushBack({5, 108, 31, 29});
	front.PushBack({4, 141, 31, 29});
	front.PushBack({38, 108, 31, 29});
	front.speed = 0.1f;
	//front.pingpong = true;

	back.PushBack({170, 108, 31, 29});
	back.PushBack({170, 141, 31, 29});
	back.PushBack({137, 108, 31, 29});
	back.speed = 0.1f;
	//back.pingpong = true;

	path.PushBack({-0.3f, 0.0f}, 150, &front);
	path.PushBack({0.3f, 0.0f}, 150, &back);

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Mech::Update()
{
	Attack();
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();
	timer -= 1.0f / 60.0f;
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Mech::Attack()
{
	
	double playerX = App->player->position.x;
	double playerY = App->player->position.y;
	double dx = position.x - playerX;
	double dy = position.y - playerY;
	int distance = sqrt(dx * dx + dy * dy);
	float angle = atan2(dy, dx);

	if(distance > 100)
	{
		position.x += cos(angle) * 0.3f;
		position.y += sin(angle) * 0.3f;
	}

	else if (distance <= 100 && timer <= 0.0f)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::ENEMY_SHOT);
		timer = SHOOT_INTERVAL;
	}
}
