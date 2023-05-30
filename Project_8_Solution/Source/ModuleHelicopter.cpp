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

	//NORMAL SHOT YELLOW
	shotYAnim.PushBack({ 135, 227, 4, 4 });

	//NORMAL SHOT GREY
	shotGAnim.PushBack({ 151, 227, 4, 4 });

	//SHOT FIRE DOWN
	shotSFire.PushBack({ 167, 226, 7, 12 });
	shotSFire.PushBack({ 273, 227, 15, 15 });
	shotSFire.PushBack({ 367, 227, 25, 29 });
	shotSFire.loop = false;
	shotSFire.speed = 0.3f;

	//SHOT FIRE SUDEST
	shotEFire.PushBack({ 204, 227, 10, 13 });
	shotEFire.PushBack({ 249, 227, 13, 15 });
	shotEFire.PushBack({ 299, 226, 23, 26 });
	shotEFire.loop = false;
	shotEFire.speed = 0.3f;

	//SHOT FIRE SUDOEST
	shotOFire.PushBack({ 185, 227, 9, 13 });
	shotOFire.PushBack({ 225, 227, 13, 15 });
	shotOFire.PushBack({ 333, 226, 23, 26 });
	shotOFire.loop = false;
	shotOFire.speed = 0.3f;

	//EXPLOSION HELICOPTER
	explosionAnim.PushBack({9, 511, 121, 144});
	explosionAnim.PushBack({ 136, 457, 129, 87 });
	explosionAnim.PushBack({ 245, 338, 98, 121 });
	explosionAnim.PushBack({ 341, 338, 58, 63 });
	explosionAnim.PushBack({ 404, 277, 68, 56 });
	explosionAnim.PushBack({ 468, 212, 66, 68 });
	explosionAnim.PushBack({ 539, 154, 70, 86 });
	explosionAnim.PushBack({ 608, 68, 48, 77 });
	explosionAnim.PushBack({ 620, 33, 67, 53 });
	explosionAnim.PushBack({ 722, 4, 27, 74 });
	explosionAnim.PushBack({ 697, 26, 26, 25 });
	explosionAnim.loop = true;
	explosionAnim.speed = 0.3f;


	timer = 1.0f;
}

ModuleHelicopter::~ModuleHelicopter()
{

}

bool ModuleHelicopter::Start()
{
	LOG("Loading helicopter textures");
	textureH = App->textures->Load("Assets/Sprites/Enemies/Helicoptero.png");

	helicopterDestroyedFx = App->audio->LoadFx("Assets/Fx/Helicopter breaking.wav");
	helicopterShotFx = App->audio->LoadFx("Assets/Fx/Helicopter shots.wav");
	helicopterMovingFx = App->audio->LoadFx("Assets/Fx/Helicopter arrival.wav");

	currentFAnim = &flyAnim;
	currentShotAnim = &shotYAnim;

	bool ret = true;
	startTime = SDL_GetTicks();

	position.x = 967;
	position.y = 1928;

	//// TODO 4: Retrieve the player when playing a second time
	//destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 110, 98 }, Collider::Type::HELICOPTER, this);

	return ret;
}
Update_Status ModuleHelicopter::Update()
{
	Uint32 currentTime = SDL_GetTicks() - startTime;

	if (!helicopterDestroyed) {

		if (state == 1)
		{
			currentFAnim = &flyAnim;
			if (position.y > 1794) { position.y--; }
			if (position.y == 1794) { App->audio->PlayFx(helicopterMovingFx); }
		}

		if (currentTime >= 7000) //(2 seconds!)
		{
			Uint32 delayTime = 2000;

			if (currentTime >= 7000)
			{
				if (App->player->position.x < position.x)
				{
					directionX = -1;
				}

				else if (App->player->position.x > position.x)
				{
					directionX = 1;
				}

				position.x += speed * directionX;

				if (position.x <= -100 || position.x >= SCREEN_WIDTH + 100)
				{
				directionX = -directionX;
				}
			}
		}


		/*	Idle();*/
		if (ModuleHelicopter::find_player())
		{
			if (timer <= 0.0f && isShooting == false) Attack();
			/*		else if (timer > 0.0f && isShooting == false)Idle();*/
		}


		collider->SetPos(position.x, position.y);
		currentFAnim->Update();
		currentShotAnim->Update();
		calculateAngle();
		timer -= 1.0f / 60.0f;
		if (timer <= 4.2) isShooting = false;

		if (helicopterShot > 0 && life > 50)
		{
			if (helicopterShot % 2 == 0)
			{
				currentFAnim = &flickerAnim;
			}
			helicopterShot--;
		}
		if (life < 50) { currentFAnim = &flyAnim; }
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

double ModuleHelicopter::calculateAngle()
{
	dx = (position.x + 54.5) - (App->player->position.x + 17.5);
	dy = (position.y + 64) - (App->player->position.y + 17.5);
	angle = atan2(dy, dx) * 180.0 / M_PI;
	/*LOG("Angle: %f", angle);*/
	return angle;

}
void ModuleHelicopter::Idle()
{
	if (life > 50) {
		if (ModuleHelicopter::calculateAngle() >= -101.25 && ModuleHelicopter::calculateAngle() < -78.75) {
			currentShotAnim = &shotYAnim;

		}
		else if (ModuleHelicopter::calculateAngle() <= -22.5 && ModuleHelicopter::calculateAngle() > -56.25) {
			currentShotAnim = &shotYAnim;

		}
		else if (ModuleHelicopter::calculateAngle() <= -123.75 && ModuleHelicopter::calculateAngle() > -157.5) {
			currentShotAnim = &shotYAnim;

		}
		else if (ModuleHelicopter::calculateAngle() <= -56.25 && ModuleHelicopter::calculateAngle() > -78.75) {
			currentShotAnim = &shotYAnim;

		}
		else if (ModuleHelicopter::calculateAngle() <= -101.25 && ModuleHelicopter::calculateAngle() > -123.75) {
			currentShotAnim = &shotYAnim;

		}

		if (ModuleHelicopter::calculateAngle() >= -112.5 && ModuleHelicopter::calculateAngle() < -67.5) currentShotAnim = &shotYAnim;
		else if (ModuleHelicopter::calculateAngle() <= -22.5 && ModuleHelicopter::calculateAngle() > -67.5) currentShotAnim = &shotYAnim;
		else if (ModuleHelicopter::calculateAngle() <= -112.5 && ModuleHelicopter::calculateAngle() > -157.5) currentShotAnim = &shotYAnim;

		//LOG("Torreta pos x: %d", torretaPosX);
		//LOG("Torreta pos x: %d", torretaPosX);
	}
}

void ModuleHelicopter::Attack()
{
	if (life > 50) {
		if (ModuleHelicopter::calculateAngle() >= -101.25 && ModuleHelicopter::calculateAngle() < -78.75) {
			App->particles->AddParticle(App->particles->helicopterShotDown, position.x + 40, position.y + 87, NULL, NULL, Collider::Type::HELICOPTER_SHOT);
		}
		else if (ModuleHelicopter::calculateAngle() <= -33.75 && ModuleHelicopter::calculateAngle() > -56.25) {
			App->particles->AddParticle(App->particles->helicopterShotSudoest, position.x - 20, position.y + 60, NULL, NULL, Collider::Type::HELICOPTER_SHOT);
		}
		else if (ModuleHelicopter::calculateAngle() <= -123.75 && ModuleHelicopter::calculateAngle() > -146.25) {
			App->particles->AddParticle(App->particles->helicopterShotSudest, position.x + 95, position.y + 66, NULL, NULL, Collider::Type::HELICOPTER_SHOT);
		}
	}
	isShooting = true;
	App->audio->PlayFx(helicopterShotFx);
	timer = SHOOT_INTERVAL;
}

Update_Status ModuleHelicopter::PostUpdate()
{
	Idle();
	if (currentFAnim != nullptr) {
		App->render->Blit(textureH, position.x, position.y, &(currentFAnim->GetCurrentFrame()));
		if (currentFAnim != &flickerAnim) {
			App->render->Blit(textureH, position.x + 5, position.y + 21, &(currentShotAnim->GetCurrentFrame()));
		}
	}

	if (life < 50)
	{
		if (BTint <= 30) { BTintInc = 10; }
		if (BTint >= 255) { BTintInc = -10; }
		BTint += BTintInc;
		SDL_SetTextureColorMod(textureH, 255, BTint, BTint);
	}
	else
	{
		SDL_SetTextureColorMod(textureH, 255, 255, 255);
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

	if (c1 == collider && c2->type == Collider::Type::PLAYER)
	{
		if (currentFAnim == &flyAnim) {
			if (App->player->position.y > position.y + 160) { //diagonales para abajo no van 
				App->player->position.y++;
			}
		}
		LOG("Touching player. Pos Helicopter: %d. Pos player: %d", position.y, App->player->position.y)
	}

}