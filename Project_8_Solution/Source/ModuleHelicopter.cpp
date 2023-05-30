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
	//FLY ANIMATION
	flyAnim.PushBack({ 314, 0, 118, 102 });
	flyAnim.PushBack({ 196, 0, 118, 102 });
	flyAnim.PushBack({ 76, 0, 118, 102 });
	flyAnim.loop = true;
	flyAnim.speed = 0.2f;

/*//FLICKER ANIMATION
	flickerAnim.PushBack({ 20, 364, 109, 162 });
	flickerAnim.loop = false;
	flickerAnim.speed = 0.3f;

	//DAMAGED ANIMATION
	destroyedAnim.PushBack({ 151, 364, 109, 162 });
	destroyedAnim.loop = false;
	destroyedAnim.speed = 0.3f;

	//NORMAL SHOT
	downSSAnim.PushBack({ 15, 14, 32, 27 });
	downSSAnim.loop = false;
	downSSAnim.speed = 0.3f;*/	

	timer = 1.0f;

}

ModuleHelicopter::~ModuleHelicopter()
{

}

bool ModuleHelicopter::Start()
{
	LOG("Loading helicopter textures");
	propellers = App->textures->Load("Assets/Sprites/Enemies/Helicopter.png");

	helicopterDestroyedFx = App->audio->LoadFx("Assets/Fx/tankDestroyed.wav");
	helicopterShotFx = App->audio->LoadFx("Assets/Fx/tankShot.wav");
	helicopterMovingFx = App->audio->LoadFx("Assets/Fx/tankMoving.wav");

	currentFAnim = &flyAnim;
	currentBSAnim = &downBSAnim;
	currentSSAnim = &downSSAnim;

	bool ret = true;

	position.x = 967;
	position.y = 1806;

	//// TODO 4: Retrieve the player when playing a second time
	//destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 110, 98 }, Collider::Type::HELICOPTER, this);

	return ret;
}
Update_Status ModuleHelicopter::Update()
{
	if (!helicopterDestroyed) {

		loop++;
		ModulePlayer* player = App->player;
		if (player->position.x < position.x) 
		{
			directionX = -1; //move left
		}
		else if (player->position.x > position.x)
		{
			directionX = 1;
		}

		if (timer <= 0.0f && !isShooting)
		{
			isShooting = true;
		}

		position.x += speed * directionX;

		if (position.x <= -100 || position.x >= SCREEN_WIDTH + 100)
		{
			directionX = -directionX;
		}

		if (find_player())
		{
			if (timer <= 0.0f && isShooting == false)
			{
				Attack();
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
		currentBSAnim->Update();
		currentSSAnim->Update();
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
			currentBSAnim = &downBSAnim;
			torretaPosX = position.x + 52 + 5;
			torretaPosY = position.y + 10 + 21;
		}
		else if (ModuleHelicopter::calculateAngle() <= -22.5 && ModuleHelicopter::calculateAngle() > -56.25) {
			currentBSAnim = &sudoestBSAnim;
			torretaPosX = position.x + 47 + 5;
			torretaPosY = position.y + 27 + 21;
		}
		else if (ModuleHelicopter::calculateAngle() <= -123.75 && ModuleHelicopter::calculateAngle() > -157.5) {
			currentBSAnim = &sudestBSAnim;
			torretaPosX = position.x + 46 + 5;
			torretaPosY = position.y + 13 + 21;
		}
		else if (ModuleHelicopter::calculateAngle() <= -56.25 && ModuleHelicopter::calculateAngle() > -78.75) {
			currentBSAnim = &sudoLBSAnim;
			torretaPosX = position.x + 49 + 5;
			torretaPosY = position.y + 14 + 21;
		}
		else if (ModuleHelicopter::calculateAngle() <= -101.25 && ModuleHelicopter::calculateAngle() > -123.75) {
			currentBSAnim = &sudRBSAnim;
			torretaPosX = position.x + 50 + 5;
			torretaPosY = position.y + 9 + 21;
		}

		if (ModuleHelicopter::calculateAngle() >= -112.5 && ModuleHelicopter::calculateAngle() < -67.5) currentSSAnim = &downSSAnim;
		else if (ModuleHelicopter::calculateAngle() <= -22.5 && ModuleHelicopter::calculateAngle() > -67.5) currentSSAnim = &sudoestSSAnim;
		else if (ModuleHelicopter::calculateAngle() <= -112.5 && ModuleHelicopter::calculateAngle() > -157.5) currentSSAnim = &sudestSSAnim;

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
		App->render->Blit(propellers, position.x, position.y, &(currentFAnim->GetCurrentFrame()));
		if (currentFAnim != &flickerAnim) {
			App->render->Blit(propellers, position.x + 5, position.y + 21, &(currentBSAnim->GetCurrentFrame()));
			App->render->Blit(propellers, torretaPosX, torretaPosY, &(currentSSAnim->GetCurrentFrame()));
		}
	}

	if (life < 50)
	{
		if (BTint <= 30) { BTintInc = 10; }
		if (BTint >= 255) { BTintInc = -10; }
		BTint += BTintInc;
		SDL_SetTextureColorMod(propellers, 255, BTint, BTint);
	}
	else
	{
		SDL_SetTextureColorMod(propellers, 255, 255, 255);
	}
	return Update_Status::UPDATE_CONTINUE;
}
bool ModuleHelicopter::CleanUp()
{
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