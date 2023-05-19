#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;

	damagedSoldier = App->audio->LoadFx("Assets/Fx/damaged_enemy.wav");
	destroyedTank = App->audio->LoadFx("Assets/Fx/Tank destruction.wav");
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	randomValue = rand() % 100;
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy::OnCollision(Collider* collider){}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

