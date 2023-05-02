#include "PickUps_BLUEDIAMOND.h"

#include "Application.h"
#include "ModuleCollisions.h"

PickUps_BLUEDIAMOND::PickUps_BLUEDIAMOND(int x, int y) : PickUps(x, y)
{
	blueDiamond.PushBack({ 85, 68, 31, 29 });
	/*front.PushBack({4, 141, 31, 29});
	front.PushBack({38, 108, 31, 29});*/
	blueDiamond.speed = 0.1f;
	//front.pingpong = true;

	blueDiamond.PushBack({ 170, 108, 31, 29 });
	/*back.PushBack({170, 141, 31, 29});
	back.PushBack({137, 108, 31, 29});*/
	blueDiamond.speed = 0.1f;
	//back.pingpong = true;

	path.PushBack({ -0.0f, 0.0f }, 0, &blueDiamond);
	/*path.PushBack({0.3f, 0.0f}, 0, &back);*/

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::PICKUPS, (Module*)App->pickUps);
}

void PickUps_BLUEDIAMOND::Update()
{
	path.Update();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	PickUps::Update();
}