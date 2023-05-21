#include "PickUps_BLUEDIAMOND.h"

#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

PickUps_BLUEDIAMOND::PickUps_BLUEDIAMOND(int x, int y) : PickUps(x, y)
{
	blueDiamond.PushBack({ 85, 68, 16, 16 });
	blueDiamond.PushBack({ 101, 67, 16, 17 });
	blueDiamond.PushBack({ 117, 66, 16, 18 });
	blueDiamond.PushBack({ 133, 67, 16, 17 });
	blueDiamond.PushBack({ 149, 68, 15, 16 });
	blueDiamond.PushBack({ 165, 67, 16, 17 });
	blueDiamond.PushBack({ 181, 66, 16, 18 });
	blueDiamond.PushBack({ 197, 67, 16, 17 });
	
	blueDiamond.speed = 0.1f;
	//back.pingpong = true;

	path.PushBack({ -0.0f, 0.0f }, 0, &blueDiamond);
	/*path.PushBack({0.3f, 0.0f}, 0, &back);*/
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::BLUEDIAMOND, (Module*)App->pickUps);

	getPickUps = App->audio->LoadFx("Assets/Fx/Scoring diamond.wav");

}

void PickUps_BLUEDIAMOND::Update()
{
	path.Update();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	PickUps::Update();
}

void PickUps::OnCollision(Collider* collider)
{
	App->player->score += 30000;
	App->particles->AddParticle(App->particles->BlueDiamond, position.x, position.y, NULL, NULL, Collider::Type::NONE, 14);
	App->audio->PlayFx(getPickUps);
}