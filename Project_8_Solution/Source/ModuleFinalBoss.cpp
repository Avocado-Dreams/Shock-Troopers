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

	//NORMAL SHOT DOWN
	downSSAnim.PushBack({ 15, 14, 32, 27 });
	downSSAnim.loop = false;
	downSSAnim.speed = 0.3f;
	//NORMAL SHOT LEFT
	leftSSAnim.PushBack({ 293, 14, 42, 27 });
	leftSSAnim.loop = false;
	leftSSAnim.speed = 0.3f;
	//NORMAL SHOT ANIMATION RIGHT
	rightSSAnim.PushBack({ 344, 14, 42, 27 });
	rightSSAnim.loop = false;
	rightSSAnim.speed = 0.3f;
	//NORMAL SHOT ANIMATION SUDOEST
	sudoestSSAnim.PushBack({ 99, 14, 38, 27 });
	sudoestSSAnim.loop = false;
	sudoestSSAnim.speed = 0.3f;
	//NORMAL SHOT ANIMATION SUDEST
	sudestSSAnim.PushBack({ 147, 14, 38, 27 });
	sudestSSAnim.loop = false;
	sudestSSAnim.speed = 0.3f;
	//NORMAL SHOT ANIMATION SUD RIGHT
	noroestSSAnim.PushBack({ 244, 14, 38, 27 });
	noroestSSAnim.loop = false;
	noroestSSAnim.speed = 0.3f;
	//NORMAL SHOT ANIMATION SUDO LEFT
	norestSSAnim.PushBack({ 195, 14, 38, 27 });
	norestSSAnim.loop = false;
	norestSSAnim.speed = 0.3f;

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
	timer2 = 1.0f;

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
	enemyShotFx = App->audio->LoadFx("Assets/Fx/enemy_single_shot.wav");
	currentBAnim = &downAnim;
	currentBSAnim = &downBSAnim; 
	currentSSAnim = &downSSAnim; 

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
	if (!bossDestroyed) {

		loop++;
		if (loop % 3 == 0 && life > 30) {
			if (state == 1)
			{
				currentBAnim = &downAnim;
				if (position.y < 13) { position.y++; }
				if (position.y == 13) { state = 3; currentBAnim = &upAnim; upAnim.Reset(); App->audio->PlayFx(tankMovingFx); }
			}
			if (state == 2)  
			{
				currentBAnim = &idleAnim;
				if (time < 50) { time++; }
				else { state = 3; int time = 0; currentBAnim = &upAnim; upAnim.Reset(); App->audio->PlayFx(tankMovingFx); }
			}
			if (state == 3)
			{
				currentBAnim = &upAnim;
				if (position.y > -20) { position.y--; }
				if (position.y == -20) { state = 4; count++; currentBAnim = &idleAnim; }
				if (count == 2) { state = 6; count = 0; currentBAnim = &downAnim; downAnim.Reset();  App->audio->PlayFx(tankMovingFx); }
			}
			if (state == 4)  
			{
				currentBAnim = &idleAnim;
				if (time < 50) { time++; }
				else { state = 5; time = 0; currentBAnim = &downAnim; downAnim.Reset(); App->audio->PlayFx(tankMovingFx); }
			}
			if (state == 5)
			{
				currentBAnim = &downAnim;
				if (position.y < 13) { position.y++; }
				if (position.y == 13) { state = 2; currentBAnim = &idleAnim; }
			}
			if (state == 6)
			{
				currentBAnim = &downAnim;
				if (position.y < 43) { position.y++; }
				if (position.y == 43) { state = 7; currentBAnim = &idleAnim; }
			}
			if (state == 7)
			{
				currentBAnim = &idleAnim;
				if (time < 50) { time++; }
				else { state = 8; time = 0; currentBAnim = &upAnim;	upAnim.Reset(); App->audio->PlayFx(tankMovingFx); }
			}
			if (state == 8)
			{
				currentBAnim = &upAnim;
				if (position.y > -20) { position.y--; }
				if (position.y == -20) { state = 9; currentBAnim = &idleAnim; }
			}
			if (state == 9)
			{
				currentBAnim = &idleAnim;
				if (time < 50) { time++; }
				else { state = 1; time = 0; currentBAnim = &downAnim; downAnim.Reset(); App->audio->PlayFx(tankMovingFx); loop = 0; }
			}
		}
		
	/*	Idle();*/
		if (ModuleFinalBoss::find_player())
		{
			if (timer <= 0.0f && isShooting == false) Attack();
			if (timer2 <= 0.0f && isShooting == false) NormalAttack();
	/*		else if (timer > 0.0f && isShooting == false)Idle();*/
		}
		
		
		collider->SetPos(position.x, position.y);
		currentBAnim->Update();
		currentBSAnim->Update();
		currentSSAnim->Update();
		calculateAngle();
		timer -= 1.0f / 60.0f;
		timer2 -= 2.0f / 60.0f;
		if (timer <= 4.2) isShooting = false;
		if (timer2 <= 4.2) isShooting = false;

		if (bossShot > 0 && life > 30)
		{
			if (bossShot % 2 == 0)
			{
				currentBAnim = &flickerAnim;
			}
			bossShot--;
		}
		if (life < 30) { currentBAnim = &idleAnim; }
	}

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
	/*LOG("Angle: %f", angle);*/
	return angle;
	
}
void ModuleFinalBoss::Idle()
{
	if (life > 30) {
		if (ModuleFinalBoss::calculateAngle() >= -101.25 && ModuleFinalBoss::calculateAngle() < -78.75) {
			currentBSAnim = &downBSAnim;
			torretaPosX = position.x + 52 + 5;
			torretaPosY = position.y + 10 + 21;
		}
		else if (ModuleFinalBoss::calculateAngle() <= -157.5 || ModuleFinalBoss::calculateAngle() > 90) {
			currentBSAnim = &rightBSAnim;
			torretaPosX = position.x + 23 + 5;
			torretaPosY = position.y + 8 + 21;
		}
		else if (ModuleFinalBoss::calculateAngle() >= -22.5 && ModuleFinalBoss::calculateAngle() < 90) {
			currentBSAnim = &leftBSAnim;
			torretaPosX = position.x + 33 + 5;
			torretaPosY = position.y + 26 + 21;
		}
		else if (ModuleFinalBoss::calculateAngle() <= -22.5 && ModuleFinalBoss::calculateAngle() > -56.25) {
			currentBSAnim = &sudoestBSAnim;
			torretaPosX = position.x + 47 + 5;
			torretaPosY = position.y + 27 + 21;
		}
		else if (ModuleFinalBoss::calculateAngle() <= -123.75 && ModuleFinalBoss::calculateAngle() > -157.5) {
			currentBSAnim = &sudestBSAnim;
			torretaPosX = position.x + 46 + 5;
			torretaPosY = position.y + 13 + 21;
		}
		else if (ModuleFinalBoss::calculateAngle() <= -56.25 && ModuleFinalBoss::calculateAngle() > -78.75) {
			currentBSAnim = &sudoLBSAnim;
			torretaPosX = position.x + 49 + 5;
			torretaPosY = position.y + 14 + 21;
		}
		else if (ModuleFinalBoss::calculateAngle() <= -101.25 && ModuleFinalBoss::calculateAngle() > -123.75) {
			currentBSAnim = &sudRBSAnim;
			torretaPosX = position.x + 50 + 5;
			torretaPosY = position.y + 9 + 21;
		}

		if (ModuleFinalBoss::calculateAngle() >= -112.5 && ModuleFinalBoss::calculateAngle() < -67.5) currentSSAnim = &downSSAnim;
		else if (ModuleFinalBoss::calculateAngle() <= -157.5 || ModuleFinalBoss::calculateAngle() > 157.5) currentSSAnim = &rightSSAnim;
		else if (ModuleFinalBoss::calculateAngle() >= -22.5 && ModuleFinalBoss::calculateAngle() < 22.5) currentSSAnim = &leftSSAnim;
		else if (ModuleFinalBoss::calculateAngle() <= -22.5 && ModuleFinalBoss::calculateAngle() > -67.5) currentSSAnim = &sudoestSSAnim;
		else if (ModuleFinalBoss::calculateAngle() <= -112.5 && ModuleFinalBoss::calculateAngle() > -157.5) currentSSAnim = &sudestSSAnim;
		else if (ModuleFinalBoss::calculateAngle() <= 90 && ModuleFinalBoss::calculateAngle() > 15.5) currentSSAnim = &leftSSAnim;
		else if (ModuleFinalBoss::calculateAngle() >= 90 && ModuleFinalBoss::calculateAngle() > 157.5) currentSSAnim = &rightSSAnim;

		//LOG("Torreta pos x: %d", torretaPosX);
		//LOG("Torreta pos x: %d", torretaPosX);
	}
	

}
void ModuleFinalBoss::Attack()
{
	if (life > 30) {
		if (ModuleFinalBoss::calculateAngle() >= -101.25 && ModuleFinalBoss::calculateAngle() < -78.75) {
			App->particles->AddParticle(App->particles->bossDown, position.x + 40, position.y + 87, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -157.5 && ModuleFinalBoss::calculateAngle() < 90) {
			App->particles->AddParticle(App->particles->bossRight, position.x + 106, position.y + 40, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() >= -22.5 && ModuleFinalBoss::calculateAngle() < 90) {
			App->particles->AddParticle(App->particles->bossLeft, position.x - 30, position.y + 35, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -33.75 && ModuleFinalBoss::calculateAngle() > -56.25) {
			App->particles->AddParticle(App->particles->bossSudoest, position.x - 20, position.y + 60, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -123.75 && ModuleFinalBoss::calculateAngle() > -146.25) {
			App->particles->AddParticle(App->particles->bossSudest, position.x + 95, position.y + 66, NULL, NULL, Collider::Type::BOSS_SHOT);
		}
	}
	isShooting = true;
	App->audio->PlayFx(tankShotFx);
	timer = SHOOT_INTERVAL;
}
void ModuleFinalBoss::NormalAttack()
{
	if (life > 30) {
		if (ModuleFinalBoss::calculateAngle() >= -112.5 && ModuleFinalBoss::calculateAngle() < -67.5) {
			App->particles->AddParticle(App->particles->normalBShot, torretaPosX + 11, torretaPosY + 28, NULL, 1, Collider::Type::ENEMY_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -157.5 || ModuleFinalBoss::calculateAngle() > 157.5) {
			App->particles->AddParticle(App->particles->normalBShot, torretaPosX + 42, torretaPosY + 4, 1, NULL, Collider::Type::ENEMY_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() >= -22.5 && ModuleFinalBoss::calculateAngle() < 22.5) {
			App->particles->AddParticle(App->particles->normalBShot, torretaPosX - 5, torretaPosY + 4, -1, NULL, Collider::Type::ENEMY_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -22.5 && ModuleFinalBoss::calculateAngle() > -67.5) {
			App->particles->AddParticle(App->particles->normalBShot, torretaPosX - 5, torretaPosY + 17, -1, 1, Collider::Type::ENEMY_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= -112.5 && ModuleFinalBoss::calculateAngle() > -157.5) {
			App->particles->AddParticle(App->particles->normalBShot, torretaPosX + 38, torretaPosY + 17, 1, 1, Collider::Type::ENEMY_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() <= 90 && ModuleFinalBoss::calculateAngle() > 15.5) {
			App->particles->AddParticle(App->particles->normalBShot, torretaPosX - 5, torretaPosY - 5, -1, -1, Collider::Type::ENEMY_SHOT);
		}
		else if (ModuleFinalBoss::calculateAngle() >= 90 && ModuleFinalBoss::calculateAngle() > 157.5) {
			App->particles->AddParticle(App->particles->normalBShot, torretaPosX + 39, torretaPosY - 5, 1, -1, Collider::Type::ENEMY_SHOT);
		}

	}
	isShooting2 = true;
	App->audio->PlayFx(enemyShotFx);
	timer2 = SHOOT_INTERVAL;
}

Update_Status ModuleFinalBoss::PostUpdate()
{	
	Idle();
	if (currentBAnim != nullptr) { 
		App->render->Blit(texture, position.x, position.y, &(currentBAnim->GetCurrentFrame())); 
		if (currentBAnim != &flickerAnim) {
			App->render->Blit(texture, position.x + 5, position.y + 21, &(currentBSAnim->GetCurrentFrame()));
			App->render->Blit(texture, torretaPosX, torretaPosY, &(currentSSAnim->GetCurrentFrame()));
		}
	}

	if (life < 30)
	{
 		if (BTint <= 30) {BTintInc = 10; }
		if (BTint >= 255) { BTintInc = -10; }
		BTint += BTintInc;
		SDL_SetTextureColorMod(texture, 255, BTint, BTint);
	}
	else
	{
		SDL_SetTextureColorMod(texture, 255, 255, 255);
	}
	return Update_Status::UPDATE_CONTINUE;
}
bool ModuleFinalBoss::CleanUp()
{
	App->finalBoss->Disable();
	return true; 
}

void ModuleFinalBoss::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == Collider::Type::PLAYER_SHOT)
	{
		bossShot = 2; 
		LOG("Boss being shot")
			life--;
		if (life == 0) { bossDestroyed = true; }
	}

	//if (c1 == collider && c2->type == Collider::Type::PLAYER)
	//{
	//	if (currentBAnim == &downAnim) {
	//		if (App->player->position.y > position.y + 160) { //diagonales para abajo no van 
	//			App->player->position.y++; } 
	//	}

	//	LOG("Touching player. Pos boss: %d. Pos player: %d", position.y, App->player->position.y)
	//}

	if (bossDestroyed && App->player->win == 0)
	{	
		App->audio->PlayMusic("Assets/Music/silence.wav", 0.0f);
		App->particles->AddParticle(App->particles->bossExplosion, position.x + 15, position.y + 35, NULL, NULL, Collider::Type::EXPLOSION);
		App->audio->PlayFx(tankDestroyedFx);
		App->player->win = 1;
		App->player->winAnim.Reset();
		App->particles->bossExplosion.anim.Reset();
	}

}