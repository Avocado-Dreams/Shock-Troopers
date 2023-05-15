#include "PickUps.h"
#include "ModulePickUps.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

PickUps::PickUps(int x, int y) : position(x, y)
{
	spawnPos = position;
}

PickUps::~PickUps()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* PickUps::GetCollider() const
{
	return collider;
}

void PickUps::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void PickUps::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

//void PickUps::OnCollision(Collider* collider)
//{
//
//		
//}