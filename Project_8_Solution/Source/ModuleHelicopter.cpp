#include "ModuleHelicopter.h"

#include "Application.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_timer.h"
#include "SDL_image/include/SDL_image.h"


ModuleHelicopter::ModuleHelicopter(bool startEnabled) : Module(startEnabled)
{
	//Background / sky
	sky = { 0, 0, 433, 142 };

	//DESTROYED ANIMATION
	destroyedAnim.PushBack({ 83, 5, 112, 98 });
	destroyedAnim.PushBack({ 203, 5, 112, 98 });
	destroyedAnim.PushBack({ 323, 5, 112, 98 });
	destroyedAnim.loop = true;
	destroyedAnim.speed = 0.3f;

	//FLICKER ANIMATION
	flickerAnim.PushBack({ 9, 214, 112, 98 });

	//FLY ANIMATION
	flyAnim.PushBack({ 83, 5, 112, 98 });


	timer = 1.0f;
}

ModuleHelicopter::~ModuleHelicopter()
{

}

bool ModuleHelicopter::Start()
{
	LOG("Loading helicopter textures");
	textureH = App->textures->Load("Assets/Sprites/Enemies/Helicoptero.png");
	textureSky = App->textures->Load("Assets/Sprites/Background/Cielo.png");

	if (helicopterDestroyedFx == 0) helicopterDestroyedFx = App->audio->LoadFx("Assets/Fx/Helicopter breaking.wav");
	if (helicopterShotFx == 0) helicopterShotFx = App->audio->LoadFx("Assets/Fx/Helicopter shots.wav");
	if (helicopterMovingFx == 0) helicopterMovingFx = App->audio->LoadFx("Assets/Fx/Helicopter arrival.wav");

	currentFAnim = &flyAnim;
	currentShotAnim = &shotYAnim;
	currentDestroyedAnim = &destroyedAnim;

	bool ret = true;
	startTime = SDL_GetTicks();
	
	life = 100;

	position.x = 967;
	position.y = 1928;

	//// TODO 4: Retrieve the player when playing a second time
	//destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 112, 98 }, Collider::Type::HELICOPTER, this);
	
	return ret;
}
Update_Status ModuleHelicopter::Update()
{
	Uint32 currentTime = SDL_GetTicks() - startTime;
	
	if (!helicopterDestroyed) {
		if (loop % 60 == 0) 
			App->audio->PlayFx(helicopterMovingFx);
		if (state == 1)
		{
			currentFAnim = &flyAnim;
			if (position.y > 1788) { position.y--;}
		}
		
		if (loop % 2 == 0 && life > 50) {

			if (App->player->position.x - 39 < position.x) position.x -= App->player->speed;
			if (App->player->position.x - 39 > position.x) position.x += App->player->speed;

		}

		/*	Idle();*/
		if (ModuleHelicopter::find_player())
		{
			if (timer <= 0.0f && isShooting == false && position.y == 1788) Attack();
			/*	else if (timer > 0.0f && isShooting == false)Idle();*/
		}


		collider->SetPos(position.x, position.y);
		currentFAnim->Update();
		currentShotAnim->Update();

		timer -= 1.0f / 60.0f;
		if (timer <= 4.2) isShooting = false;

		if (helicopterShot > 0 && life != 0)
		{
			if (helicopterShot % 2 == 0)
			{
				currentFAnim = &flickerAnim;
			}
			helicopterShot--;
		}
		loop++;
	}
	else
	{
		if (position.y < 1928) 
		{ 
			position.y++; 
		}
		/*if (position.y >= 1927) {
			helicopterMovingFx = NULL;
		}*/
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleHelicopter::find_player()
{
	dx = position.x - (App->player->position.x);
	dy = position.y - (App->player->position.y);
	distance = sqrt((dx * dx) + (dy * dy));
	if (distance < 550) return true;
	else return false;
}

void ModuleHelicopter::Idle()
{

}

void ModuleHelicopter::Attack()
{
	App->particles->AddParticle(App->particles->shotSFire, position.x + 43, position.y + 97, NULL, NULL, Collider::Type::HELICOPTER_SHOT);
	App->particles->AddParticle(App->particles->shotYAnim, position.x + 56, position.y + 97, NULL, 1, Collider::Type::HELICOPTER_SHOT);
	LOG("Attack Heli %f", timer)

	isShooting = true;
	App->audio->PlayFx(helicopterShotFx);
	timer = SHOOT_INTERVAL;
}

Update_Status ModuleHelicopter::PostUpdate()
{
	App->render->Blit(textureSky, 890, 1795, &sky);

	if (currentFAnim != nullptr) {
		App->render->Blit(textureH, position.x, position.y, &(currentFAnim->GetCurrentFrame()));
	}

	if (App->player->zone == 3)
	{
		SDL_Rect sky { 0, 0, 433, 142 };
		App->render->Blit(textureSky, 890, 1795, &sky);
	}

	return Update_Status::UPDATE_CONTINUE;
}
bool ModuleHelicopter::CleanUp()
{
	App->helicopter->Disable();
	return true;
}

void ModuleHelicopter::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == Collider::Type::PLAYER_SHOT)
	{
		helicopterShot = 2;
		LOG("Helicopter being shot")
			life--;
		if (life == 0) { helicopterDestroyed = true; }
	}

	if (helicopterDestroyed)
	{
		App->particles->AddParticle(App->particles->explosionAnim, position.x, position.y, NULL, NULL, Collider::Type::EXPLOSION);
		App->particles->explosionAnim.anim.Reset();
		App->audio->PlayFx(helicopterDestroyedFx);
		currentDestroyedAnim = &destroyedAnim;
		SDL_Rect rectHelicopter = destroyedAnim.GetCurrentFrame();
		App->render->Blit(Destroyed, 136, 70, &rectHelicopter);
		
	}

}