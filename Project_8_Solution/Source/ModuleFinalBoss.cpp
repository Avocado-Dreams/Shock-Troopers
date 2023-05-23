#include "ModuleFinalBoss.h"

#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_timer.h"
#include "SDL_image/include/SDL_image.h"


ModuleFinalBoss::ModuleFinalBoss(bool startEnabled) : Module(startEnabled)
{
	//IDLE ANIMATION
	idleAnim.PushBack({ 372, 156, 109, 162 });
	idleAnim.loop = false;
	idleAnim.speed = 0.3f;
	//DOWN ANIMATION
	downAnim.PushBack({ 372, 156, 109, 162 });
	downAnim.PushBack({ 253, 156, 109, 162 });
	downAnim.PushBack({ 134, 156, 109, 162 });
	downAnim.PushBack({ 15, 156, 109, 162 });
	downAnim.loop = true;
	downAnim.speed = 0.3f;
	//UP ANIMATION
	upAnim.PushBack({ 15, 156, 109, 162 });
	upAnim.PushBack({ 134, 156, 109, 162 });
	upAnim.PushBack({ 253, 156, 109, 162 });
	upAnim.PushBack({ 372, 156, 109, 162 });
	upAnim.loop = true;
	upAnim.speed = 0.3f;
	//FLICKER ANIMATION
	flickerAnim.PushBack({ 20, 364, 109, 162 });
	flickerAnim.loop = false;
	flickerAnim.speed = 0.3f;
	//DAMAGED ANIMATION
	damagedAnim.PushBack({ 151, 364, 109, 162 });
	damagedAnim.loop = false;
	damagedAnim.speed = 0.3f;
	//DESTROYED ANIMATION
	destroyedAnim.PushBack({ 548, 367, 29, 52 });
	destroyedAnim.PushBack({ 580, 367, 29, 52 });
	destroyedAnim.PushBack({ 607, 367, 30, 52 });
	destroyedAnim.PushBack({ 639, 367, 36, 52 });
	destroyedAnim.loop = false;
	destroyedAnim.speed = 0.3f;
	//NORMAL SHOT ANIMATION
	//FIRE SHOT ANIMATION DOWN
	downBSAnim.PushBack({ 15, 62, 99, 67 });
	downBSAnim.loop = false;
	downBSAnim.speed = 0.3f;
	//FIRE SHOT ANIMATION LEFT
	leftBSAnim.PushBack({ 124, 62, 100, 71 });
	leftBSAnim.loop = false;
	leftBSAnim.speed = 0.3f;
	//FIRE SHOT ANIMATION RIGHT
	rightBSAnim.PushBack({ 234, 62, 100, 71 });
	rightBSAnim.loop = false;
	rightBSAnim.speed = 0.3f;
	//FIRE SHOT ANIMATION SUDOEST
	sudoestBSAnim.PushBack({ 344, 62, 107, 74 });
	sudoestBSAnim.loop = false;
	sudoestBSAnim.speed = 0.3f;
	//FIRE SHOT ANIMATION SUDEST
	sudestBSAnim.PushBack({ 461, 62, 107, 74 });
	sudestBSAnim.loop = false;
	sudestBSAnim.speed = 0.3f;
	//FIRE SHOT ANIMATION SUD RIGHT
	sudRBSAnim.PushBack({ 695, 62, 100, 70 });
	sudRBSAnim.loop = false;
	sudRBSAnim.speed = 0.3f;
	//FIRE SHOT ANIMATION SUDO LEFT
	sudoLBSAnim.PushBack({ 585, 62, 100, 70 });
	sudoLBSAnim.loop = false;
	sudoLBSAnim.speed = 0.3f;

	timer = 1.0f;

}

ModuleFinalBoss::~ModuleFinalBoss()
{

}

bool ModuleFinalBoss::Start()
{	
	LOG("Loading final boss textures");
	texture = App->textures->Load("Assets/Sprites/Enemies/FinalBoss.png");
	tankDestroyedFx = App->audio->LoadFx("Assets/Fx/tankDestroyed.wav");
	tankShotFx = App->audio->LoadFx("Assets/Fx/tankShot.wav");
	tankMovingFx = App->audio->LoadFx("Assets/Fx/tankMoving.wav");
	currentBAnim = &downAnim;
	currentBSAnim = &downBSAnim; 

	bool ret = true;

	position.x = 2182;
	position.y = -162;

	//// TODO 4: Retrieve the player when playing a second time
	//destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 109, 162 }, Collider::Type::FINALBOSS, this);

	return ret;
}
Update_Status ModuleFinalBoss::Update()
{
	loop++;
	if (loop % 3 == 0 && life > 50) {
		if (state == 1)
		{
			currentBAnim = &downAnim;
			if (position.y < 13) { position.y++; }
			if (position.y == 13) { state = 3; currentBAnim = &upAnim; upAnim.Reset(); App->audio->PlayFx(tankMovingFx);}
		}
		if (state == 2)  //C = continue, until we have the enemy condition
		{
			currentBAnim = &idleAnim;
			if (time < 50) { time++; }
			else { state = 3; int time = 0; currentBAnim = &upAnim; upAnim.Reset(); App->audio->PlayFx(tankMovingFx);}
		}
		if (state == 3)
		{
			currentBAnim = &upAnim;
			if (position.y > -20) { position.y--; }
			if (position.y == -20) { state = 4; count++; currentBAnim = &idleAnim;}
			if (count == 2) { state = 6; count = 0; currentBAnim = &downAnim; downAnim.Reset();  App->audio->PlayFx(tankMovingFx); }
		}
		if (state == 4)  //C = continue, until we have the enemy condition
		{ 
			currentBAnim = &idleAnim;
			if (time < 50) { time++; }
			else { state = 5; time = 0; currentBAnim = &downAnim; downAnim.Reset(); App->audio->PlayFx(tankMovingFx); }
		}
		if (state == 5)
		{
			currentBAnim = &downAnim;
			if (position.y < 13) { position.y++; }
			if (position.y == 13) { state = 2; currentBAnim = &idleAnim;}
		}
		if (state == 6)
		{
			currentBAnim = &downAnim;
			if (position.y < 43) { position.y++;  }
			if (position.y == 43) { state = 7; currentBAnim = &idleAnim;}
		}
		if (state == 7)
		{
			currentBAnim = &idleAnim;
			if (time < 50) { time++; }
			else { state = 8; time = 0; currentBAnim = &upAnim;	upAnim.Reset(); App->audio->PlayFx(tankMovingFx);}
		}
		if (state == 8)
		{
			currentBAnim = &upAnim;
			if (position.y > -20) { position.y--;  }
			if (position.y == -20) { state = 9; currentBAnim = &idleAnim;}
		}
		if (state == 9)
		{
			currentBAnim = &idleAnim;
			if (time < 50) { time++; }
			else { state = 1; time = 0; currentBAnim = &downAnim; downAnim.Reset(); App->audio->PlayFx(tankMovingFx); loop = 0;}
		}
	}
	if (bossShot > 0 && life > 50)
	{
		if (bossShot % 2 == 0)
		{	
			currentBSAnim = nullptr;
			currentBAnim = &flickerAnim;
			
		}
		bossShot--;
	}
	if (life < 50) { currentBAnim = &idleAnim; }
	//if (life == 0) { currentBAnim = &destroyedAnim; bossDestroyed = true; }

	if (ModuleFinalBoss::find_player())
	{
		if (timer <= 0.0f && isShooting == false)
		{
			Attack();
		}
		else if (timer > 0.0f && isShooting == false)Idle();
	}
	collider->SetPos(position.x, position.y);
	currentBAnim->Update();
	calculateAngle();
	timer -= 1.0f / 60.0f;
	if (timer <= 4.2) isShooting = false;

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleFinalBoss::find_player()
{
	dx = position.x - (App->player->position.x);
	dy = position.y - (App->player->position.y);
	distance = sqrt((dx * dx) + (dy * dy));
	if (distance < 550) return true;
	else return false;
}

double ModuleFinalBoss::calculateAngle()
{
	dx = (position.x + 54.5) - (App->player->position.x + 17.5);
	dy = (position.y + 64) - (App->player->position.y + 17.5);
	angle = atan2(dy, dx) * 180.0 / M_PI;
	LOG("Angle: %f", angle);
	return angle;
	
}
void ModuleFinalBoss::Idle()
{
	if (life > 50) {
		if (ModuleFinalBoss::calculateAngle() >= -101.25 && ModuleFinalBoss::calculateAngle() < -78.75) currentBSAnim = &downBSAnim;
		else if (ModuleFinalBoss::calculateAngle() <= -157.5 && ModuleFinalBoss::calculateAngle() < 90) currentBSAnim = &rightBSAnim;
		else if (ModuleFinalBoss::calculateAngle() >= -22.5 && ModuleFinalBoss::calculateAngle() < 90) currentBSAnim = &leftBSAnim;	
		else if (ModuleFinalBoss::calculateAngle() <= -33.75 && ModuleFinalBoss::calculateAngle() > -56.25) currentBSAnim = &sudoestBSAnim;
		else if (ModuleFinalBoss::calculateAngle() <= -123.75 && ModuleFinalBoss::calculateAngle() > -146.25) currentBSAnim = &sudestBSAnim;
		else if (ModuleFinalBoss::calculateAngle() <= -56.25 && ModuleFinalBoss::calculateAngle() > -78.75) currentBSAnim = &sudoLBSAnim;
		else if (ModuleFinalBoss::calculateAngle() <= -101.25 && ModuleFinalBoss::calculateAngle() > -123.75) currentBSAnim = &sudRBSAnim;
	}
}
void ModuleFinalBoss::Attack()
{
	if (life > 50) {
		if (ModuleFinalBoss::calculateAngle() >= -101.25 && ModuleFinalBoss::calculateAngle() < -78.75) {
			currentBSAnim = &downBSAnim;
			App->particles->AddParticle(App->particles->bossDown, position.x + 44, position.y + 91, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -157.5 && ModuleFinalBoss::calculateAngle() < 90) {
			currentBSAnim = &rightBSAnim;
			App->particles->AddParticle(App->particles->bossRight, position.x + 106, position.y + 60, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() >= -22.5 && ModuleFinalBoss::calculateAngle() < 90) {
			currentBSAnim = &leftBSAnim;
			App->particles->AddParticle(App->particles->bossLeft, position.x + 5, position.y + 60, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -33.75 && ModuleFinalBoss::calculateAngle() > -56.25) {
			currentBSAnim = &sudoestBSAnim;
			App->particles->AddParticle(App->particles->bossSudoest, position.x + 10, position.y + 82, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -123.75 && ModuleFinalBoss::calculateAngle() > -146.25) {
			currentBSAnim = &sudestBSAnim;
			App->particles->AddParticle(App->particles->bossSudest, position.x + 105, position.y + 82, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -56.25 && ModuleFinalBoss::calculateAngle() > -78.75) {
			currentBSAnim = &sudoLBSAnim;
			App->particles->AddParticle(App->particles->bossSudoL, position.x + 37, position.y + 91, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -101.25 && ModuleFinalBoss::calculateAngle() > -123.75) {
			currentBSAnim = &sudRBSAnim;
			App->particles->AddParticle(App->particles->bossSudR, position.x + 58, position.y + 91, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
	}
	isShooting = true;
	//App->audio->PlayFx(enemyShotFx);
	timer = SHOOT_INTERVAL;
}

Update_Status ModuleFinalBoss::PostUpdate()
{	

	if (currentBAnim != nullptr) { App->render->Blit(texture, position.x, position.y, &(currentBAnim->GetCurrentFrame())); }	
	if (currentBSAnim != nullptr) { App->render->Blit(texture, position.x + 5, position.y + 21, &(currentBSAnim->GetCurrentFrame())); }

	if (life < 50)
	{
		if (BTint <= 30) {BTintInc = 10; }
		if (BTint >= 255) { BTintInc = -10; }
		BTint += BTintInc;
		SDL_SetTextureColorMod(texture, 255, BTint, BTint);
	}
	return Update_Status::UPDATE_CONTINUE;
}
bool ModuleFinalBoss::CleanUp()
{
	return true; 
}

void ModuleFinalBoss::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == Collider::Type::PLAYER_SHOT)
	{
		bossShot = 2; 
		LOG("Boss being shot")
			life--;
	}

	if (c1 == collider && c2->type == Collider::Type::PLAYER)
	{
		if (currentBAnim == &downAnim) {
			if (App->player->position.y > position.y + 160) { //diagonales para abajo no van 
				App->player->position.y++; } 
		}
		LOG("Touching player. Pos boss: %d. Pos player: %d", position.y, App->player->position.y)
	}


}