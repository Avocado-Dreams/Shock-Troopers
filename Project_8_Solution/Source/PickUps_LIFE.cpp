#include "PickUps_LIFE.h"

#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

PickUps_LIFE::PickUps_LIFE(int x, int y) : PickUps(x, y)
{
	Life.PushBack({ 23, 150, 20, 15 });
	Life.PushBack({ 45, 150, 20, 15 });
	Life.PushBack({ 67, 148, 20, 17 });
	Life.PushBack({ 89, 148, 20, 17 });
	Life.PushBack({ 111, 148, 20, 17 });
	Life.PushBack({ 133, 148, 20, 17 });
	Life.PushBack({ 155, 148, 20, 17 });
	Life.PushBack({ 177, 148, 32, 17 });
	Life.PushBack({ 211, 148, 30, 17 });
	Life.PushBack({ 243, 148, 30, 17 });

	Life.speed = 0.1f;
	//back.pingpong = true;

	path.PushBack({ -0.0f, 0.0f }, 0, &Life);
	/*path.PushBack({0.3f, 0.0f}, 0, &back);*/
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::LIFE, (Module*)App->pickUps);

	getPickUps = App->audio->LoadFx("Assets/Fx/Scoring diamond.wav");

}

void PickUps_LIFE::Update()
{
	path.Update();
	currentAnim = path.GetCurrentAnimation();

	
		

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	PickUps::Update();
}

void PickUps_LIFE::OnCollision(Collider* collider)
{
	App->player->vida += 64;
	App->particles->AddParticle(App->particles->Life, position.x, position.y, NULL, NULL, Collider::Type::NONE, 14);
	App->audio->PlayFx(getPickUps);
}