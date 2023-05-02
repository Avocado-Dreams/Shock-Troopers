#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	front.PushBack({5, 108, 31, 29});
	/*front.PushBack({4, 141, 31, 29});
	front.PushBack({38, 108, 31, 29});*/
	front.speed = 0.1f;
	//front.pingpong = true;

	back.PushBack({170, 108, 31, 29});
	/*back.PushBack({170, 141, 31, 29});
	back.PushBack({137, 108, 31, 29});*/
	back.speed = 0.1f;
	//back.pingpong = true;

	path.PushBack({-0.0f, 0.0f}, 0, &front);
	/*path.PushBack({0.3f, 0.0f}, 0, &back);*/

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Mech::Update()
{
	
	if (App->player->position.y <= 2800)
	{
		find_player();
		if (distance <= 150 && timer <= 0.0f)
		{
			App->particles->AddParticle(App->particles->enemyShot, position.x + 20, position.y, -shotX, -shotY, Collider::Type::ENEMY_SHOT);
			timer = SHOOT_INTERVAL;
		}

		if (distance > 100)
		{
			// Si el jugador está lo suficientemente lejos, mueve el enemigo hacia su posición
			position.x -= cos(angle) * 3;
			position.y -= sin(angle) * 3;
		}

		path.Update();
		currentAnim = path.GetCurrentAnimation();
		// Call to the base class. It must be called at the end
		// It will update the collider depending on the position
		Enemy::Update();
	}
	
	
	//Attack();
	//path.Update();
	//position = spawnPos + path.GetRelativePosition();
	//currentAnim = path.GetCurrentAnimation();
	//timer -= 1.0f / 60.0f;
	//// Call to the base class. It must be called at the end
	//// It will update the collider depending on the position
	//Enemy::Update();
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

//void Enemy_Mech::Attack()
//{
//	find_player();
//	
//
//	//if(distance > 100)
//	//{
//	//	position.x += cos(angle) * 3;
//	//	position.y += sin(angle) * 3;
//	//}
//	
//	if (distance <= 150 && timer <= 0.0f)
//	{
//		App->particles->AddParticle(App->particles->enemyShot, position.x + 20, position.y, -shotX, -shotY, Collider::Type::ENEMY_SHOT);
//		timer = SHOOT_INTERVAL;
//	}
//}
