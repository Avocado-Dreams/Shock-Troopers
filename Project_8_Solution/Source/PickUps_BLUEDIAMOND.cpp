#include "PickUps_BLUEDIAMOND.h"

#include "Application.h"
#include "ModuleCollisions.h"

PickUps_BLUEDIAMOND::PickUps_BLUEDIAMOND(int x, int y) : PickUps(x, y)
{
	fly.PushBack({ 5,72,21,22 });
	currentAnim = &fly;

	path.PushBack({ -1.0f, 0.0f }, 100);
	path.PushBack({ 1.0f, 0.0f }, 80);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::PICKUPS, (Module*)App->enemies);
}

void PickUps_BLUEDIAMOND::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	PickUps::Update();
}