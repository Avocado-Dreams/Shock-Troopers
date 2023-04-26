#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_timer.h"

enum DIRECTION
{
	NONE = -1,
	LEFT,
	RIGHT,
	DOWN,
	UP,
	DOWNLEFT,
	DOWNRIGHT,
	UPLEFT,
	UPRIGHT,


	MAX
};

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{

	// idle animation - just one sprite
	idleAnim.PushBack({ 66, 1, 32, 14 });

	// move upwards
	upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/ship.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 150;
	position.y = (120 + 2715);

	// TODO 4: Retrieve the player when playing a second time
	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	return ret;
}

void ModulePlayer::UpdateZoneA()
{
	//camera movement relative to player movement
	if (position.y * 3 < App->render->camera.y + 200)
	{
		App->render->camera.y -= 3;
	}

	if ((position.x * 3 > App->render->camera.x + 550) && App->render->camera.x < 222)
	{
		App->render->camera.x += 3;
	}

	if ((position.x * 3 < App->render->camera.x + 150) && App->render->camera.x > 0)
	{
		App->render->camera.x -= 3;
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		if (position.x <= 0)
		{
			position.x = 0;
		}
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		if (position.x >= 330)
		{
			position.x = 330;
		}
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y + 216 < 15)
		{
			position.y = (App->render->camera.y / 3) + 216 - 15;
		}

		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
}
void ModulePlayer::UpdateZoneAB()
{
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		if (position.x <= App->render->camera.x / 3)
		{
			position.x = App->render->camera.x / 3;
		}
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		if (position.x >= (330 - 75 + App->render->camera.x / 3))
		{
			position.x = (330 - 75 + App->render->camera.x / 3);
		}
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y + 216 < 15)
		{
			position.y = (App->render->camera.y / 3) + 216 - 15;
		}

		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y > - 30)
		{
			position.y = (App->render->camera.y / 3) + 30;
		}

		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
}
void ModulePlayer::UpdateZoneB()
{
	//camera movement relative to player movement
	if (position.x * 3 > App->render->camera.x + 135*3)
	{
		App->render->camera.x += 3;
	}

	if ((position.y * 3 > App->render->camera.y + (216 - 40) * 3) && App->render->camera.y < (1797+17) * 3)
	{
		App->render->camera.y += 3;
	}

	if ((position.y * 3 < App->render->camera.y + 40*3 ) && App->render->camera.y > 1797*3)
	{
		App->render->camera.y -= 3;
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		if (position.x <= App->render->camera.x/3)
		{
			position.x = App->render->camera.x/3;
		}
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y + 216 < 15)
		{
			position.y = (App->render->camera.y / 3) + 216 - 15;
		}

		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y > - 30)
		{
			position.y = (App->render->camera.y / 3) + 30;
		}
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
}
void ModulePlayer::UpdateZoneBC()
{
	if ((position.y * 3 > App->render->camera.y + (216 - 40) * 3) && App->render->camera.y < (1797 + 17) * 3)
	{
		App->render->camera.y += 3;
	}

	if ((position.y * 3 < App->render->camera.y + 180 * 3) && App->render->camera.y > 1797 * 3)
	{
		App->render->camera.y -= 3;
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		if (position.x <= App->render->camera.x / 3)
		{
			position.x = App->render->camera.x / 3;
		}
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		if (position.x >= (330 - 75 + App->render->camera.x / 3))
		{
			position.x = (330 - 75 + App->render->camera.x / 3);
		}
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y + 216 < 30)
		{
			position.y = (App->render->camera.y / 3) + 216 - 30;
		}

		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y > -130)
		{
			position.y = (App->render->camera.y / 3) + 130;
		}

		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
}
void ModulePlayer::UpdateZoneC()
{
	UpdateZoneB();
}
void ModulePlayer::UpdateZoneD()
{
	//camera movement relative to player movement
	if (position.y * 3 < App->render->camera.y + 200)
	{
		App->render->camera.y -= 3;
	}

	if ((position.x * 3 > App->render->camera.x + 135*3) && App->render->camera.x < 2095*3)
	{
		App->render->camera.x += 3;
	}

	if ((position.x * 3 < App->render->camera.x + 150) && App->render->camera.x > 2051*3)
	{
		App->render->camera.x -= 3;
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		if (position.x <= App->render->camera.x / 3)
		{
			position.x = App->render->camera.x / 3;
		}
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		if (position.x >= (App->render->camera.x/3) + 288 - 33)
		{
			position.x = (App->render->camera.x/3) + 288 - 33; //33: player sprite width aprox
		}
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y + 216 < 15)
		{
			position.y = (App->render->camera.y / 3) + 216 - 15;
		}

		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
}
void ModulePlayer::UpdateZoneE() {
	//camera movement relative to player movement

	if ((position.x * 3 > App->render->camera.x + 135*3) && App->render->camera.x < 2095 * 3)
	{
		App->render->camera.x += 3;
	}

	if ((position.x * 3 < App->render->camera.x + 150) && App->render->camera.x > 2051 * 3)
	{
		App->render->camera.x -= 3;
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		if (position.x <= App->render->camera.x / 3)
		{
			position.x = App->render->camera.x / 3;
		}
		position.x -= speed;;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		if (position.x >= (App->render->camera.x / 3) + 288 - 33)
		{
			position.x = (App->render->camera.x / 3) + 288 - 33; //33: player sprite width aprox
		}
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y + 216 < 15)
		{
			position.y = (App->render->camera.y / 3) + 216 - 15;
		}

		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y > -30)
		{
			position.y = (App->render->camera.y / 3) + 30;
		}

		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
}

Update_Status ModulePlayer::Update()
{

	if (zone == 1 && App->render->camera.y < 1796 * 3)
	{
		zone = 2;
	}
	else if (zone == 2 && (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN))  //C = continue, until we have the enemy condition
	{
		zone = 3; 
	}
	else if (zone == 3 && App->render->camera.x > 880 * 3)
	{
		zone = 4;
	}
	else if (zone == 4 && (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN))  //C = continue, until we have the enemy condition
	{
		zone = 5;
	}
	else if (zone == 5 && App->render->camera.x > 2050 * 3)
	{
		zone = 6;
	}
	else if (zone == 6 && App->render->camera.y < 6)
	{
		zone = 7;
		App->audio->PlayMusic("Assets/Music/DarkMatter.ogg", 1.0f);
	}
	else if (zone == 7 && (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN))  //C = continue, until we have the enemy condition
	{
		//END OF LEVEL (After defeating enemies)
		App->audio->PlayMusic("Assets/Music/StageClear.ogg", 1.0f);
	}
	
	switch (zone)
	{
	case 1:UpdateZoneA(); break;
	case 2:UpdateZoneAB(); break;
	case 3:UpdateZoneB(); break;
	case 4:UpdateZoneBC(); break;
	case 5:UpdateZoneC(); break;
	case 6:UpdateZoneD(); break;
	case 7:UpdateZoneE();
	}

	//SHOOTING

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}
	/*if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && isDodging == false)
	{
		if (App->player->shootCoolDown > 5 && isDodging == false) {
			switch (bulletDir)
			{
			case LEFT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, -5, 0, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case RIGHT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 5, 0, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case DOWN:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 0, 5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case UP:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 0, -5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case DOWNLEFT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, -5, 5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case DOWNRIGHT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 5, 5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case UPLEFT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, -5, -5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			case UPRIGHT:
				App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 5, -5, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				shootCoolDown = 0;
				break;
			}
		}


	}*/

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE)
		currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		//TODO 3: Go back to the intro scene when the player gets killed
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}
}