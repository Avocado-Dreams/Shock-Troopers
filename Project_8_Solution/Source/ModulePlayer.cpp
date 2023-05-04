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

	//TORSO ANIMATION
	// Up-idle animation
	upAnim.PushBack({ 0, 4*35, 35, 35 });
	upAnim.PushBack({ 35, 4*35, 35, 35 });
	upAnim.PushBack({ 2*35, 4*35, 35, 35 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Down-idle animation 
	downAnim.PushBack({ 0, 5*35, 35, 35 });
	downAnim.PushBack({ 35, 5*35, 35, 35 });
	downAnim.PushBack({ 2*35, 5*35, 35, 35 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	// Right-idle animation
	rightAnim.PushBack({ 0, 0, 35, 35 });
	rightAnim.PushBack({ 35, 0, 35, 35 });
	rightAnim.PushBack({ 2*35, 0, 35, 35 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// Left-idle animation
	leftAnim.PushBack({ 0, 35, 33, 35 });
	leftAnim.PushBack({ 35, 35, 33, 35 });
	leftAnim.PushBack({ 2*35, 35, 30, 35 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	// Norest-idle animation
	norestAnim.PushBack({ 0, 6*35, 35, 35 });
	norestAnim.PushBack({ 35, 6 * 35, 35, 35 });
	norestAnim.PushBack({ 2*35, 6 * 35, 35, 35 });
	norestAnim.loop = true;
	norestAnim.speed = 0.1f;

	// Noroest-idle animation
	noroestAnim.PushBack({ 0, 7*35, 35, 35 });
	noroestAnim.PushBack({ 35,  7 * 35, 35, 35 });
	noroestAnim.PushBack({ 2*35,  7 * 35, 35, 35 });
	noroestAnim.loop = true;
	noroestAnim.speed = 0.1f;

	// Sudest-idle animation
	sudestAnim.PushBack({ 0, 3*35, 35, 35 });
	sudestAnim.PushBack({ 35, 3 * 35, 35, 35 });
	sudestAnim.PushBack({ 2*35, 3 * 35, 35, 35 });
	sudestAnim.loop = true;
	sudestAnim.speed = 0.1f;

	// Sudoest-idle animation
	sudoestAnim.PushBack({ 0, 2*35, 35, 35 });
	sudoestAnim.PushBack({ 35, 2 * 35, 35, 35 });
	sudoestAnim.PushBack({ 2*35, 2 * 35, 35, 35 });
	sudoestAnim.loop = true;
	sudoestAnim.speed = 0.1f;
	
	//SHOOTING ANIMATION
	// Up shooting animation
	upSAnim.PushBack({ 3 * 35, 4 * 35, 35, 35 });
	upSAnim.PushBack({ 4 * 35, 4 * 35, 35, 35 });
	upSAnim.PushBack({ 5 * 35, 4 * 35, 35, 35 });
	upSAnim.loop = true;
	upSAnim.speed = 0.3f;

	// Down shooting animation 
	downSAnim.PushBack({ 3 * 35, 5 * 35, 35, 35 });
	downSAnim.PushBack({ 4 * 35, 5 * 35, 35, 35 });
	downSAnim.PushBack({ 5 * 35, 5 * 35, 35, 35 });
	downSAnim.loop = true;
	downSAnim.speed = 0.3f;

	// Right shooting animation
	rightSAnim.PushBack({ 3 * 35 + 1, 0, 37, 35 });
	rightSAnim.PushBack({ 4 * 35 + 1, 0, 37, 35 });
	rightSAnim.PushBack({ 5 * 35 + 1, 0, 37, 35 });
	rightSAnim.loop = true;
	rightSAnim.speed = 0.3f;

	// Left shooting animation
	leftSAnim.PushBack({ 3*35, 35, 34, 35 });
	leftSAnim.PushBack({ 4*35, 35, 34, 35 });
	leftSAnim.PushBack({ 5*35, 35, 34, 35 });
	leftSAnim.loop = true;
	leftSAnim.speed = 0.3f;

	// Norest shooting animation
	norestSAnim.PushBack({ 3 * 35, 6 * 35, 35, 35 });
	norestSAnim.PushBack({ 4 * 35, 6 * 35, 35, 35 });
	norestSAnim.PushBack({ 5 * 35, 6 * 35, 35, 35 });
	norestSAnim.loop = true;
	norestSAnim.speed = 0.3f;

	// Noroest shooting animation
	noroestSAnim.PushBack({ 3 * 35, 7 * 35, 35, 35 });
	noroestSAnim.PushBack({ 4 * 35,  7 * 35, 35, 35 });
	noroestSAnim.PushBack({ 5 * 35,  7 * 35, 35, 35 });
	noroestSAnim.loop = true;
	noroestSAnim.speed = 0.3f;

	// Sudest shooting animation
	//sudestSAnim.PushBack({ 3 * 35, 3 * 35, 35, 35 });
	sudestSAnim.PushBack({ 4 * 35, 3 * 35, 35, 35 });
	sudestSAnim.PushBack({ 5 * 35, 3 * 35, 35, 35 });
	sudestSAnim.PushBack({ 5 * 35, 3 * 35, 35, 35 });
	sudestSAnim.loop = true;
	sudestSAnim.speed = 0.3f;

	// Sudoest shooting animation
	sudoestSAnim.PushBack({ 3 * 35, 2 * 35, 35, 35 });
	sudoestSAnim.PushBack({ 4 * 35, 2 * 35, 35, 35 });
	sudoestSAnim.PushBack({ 5 * 35, 2 * 35, 35, 35 });
	sudoestSAnim.loop = true;
	sudoestSAnim.speed = 0.3f;

	//LEGS ANIMATION
	// Up-idle animation
	upLAnim.PushBack({ 4*35, 0, 35, 35 });

	// Down-idle animation 
	downLAnim.PushBack({ 0, 0, 35, 35 });

	// Right-idle animation
	rightLAnim.PushBack({ 2*35, 0, 35, 35 });

	// Left-idle animation
	leftLAnim.PushBack({ 6*35, 0, 35, 35 });

	// Norest-idle animation
	norestLAnim.PushBack({ 3*35, 0, 35, 35 });

	// Noroest-idle animation
	noroestLAnim.PushBack({ 5*35, 0, 35, 35 });

	// Sudest-idle animation
	sudestLAnim.PushBack({ 35, 0, 35, 35 });

	// Sudoest-idle animation
	sudoestLAnim.PushBack({ 7*35, 0, 35, 35 });

	//WALKING ANIMATION
	// Up walking animation
	upWAnim.PushBack({ 0, 5 * 35, 35, 35 });
	upWAnim.PushBack({ 35, 5 * 35, 35, 35 });
	upWAnim.PushBack({ 2 * 35, 5 * 35, 35, 35 });
	upWAnim.PushBack({ 3*35, 5 * 35, 35, 35 });
	upWAnim.PushBack({ 4*35, 5 * 35, 35, 35 });
	upWAnim.PushBack({ 5 * 35, 5 * 35, 35, 35 });
	upWAnim.PushBack({ 6*35, 5 * 35, 35, 35 });
	upWAnim.PushBack({ 7*35, 5 * 35, 35, 35 });
	upWAnim.loop = true;
	upWAnim.speed = 0.1f;

	// Down walking animation 
	downWAnim.PushBack({ 0, 35, 35, 35 });
	downWAnim.PushBack({ 35, 35, 35, 35 });
	downWAnim.PushBack({ 2 * 35, 35, 35, 35 });
	downWAnim.PushBack({ 3*35, 35, 35, 35 });
	downWAnim.PushBack({ 4*35, 35, 35, 35 });
	downWAnim.PushBack({ 5 * 35, 35, 35, 35 });
	downWAnim.PushBack({ 6*35, 35, 35, 35 });
	downWAnim.PushBack({ 7*35, 35, 35, 35 });
	downWAnim.loop = true;
	downWAnim.speed = 0.1f;

	// Right walking animation
	rightWAnim.PushBack({ 0, 3*35, 35, 35 });
	rightWAnim.PushBack({ 35, 3*35, 35, 35 });
	rightWAnim.PushBack({ 2 * 35, 3*35, 35, 35 });
	rightWAnim.PushBack({ 3*35, 3 * 35, 35, 35 });
	rightWAnim.PushBack({ 4*35, 3 * 35, 35, 35 });
	rightWAnim.PushBack({ 5 * 35, 3 * 35, 35, 35 });
	rightWAnim.PushBack({ 6*35, 3 * 35, 35, 35 });
	rightWAnim.PushBack({ 7*35, 3 * 35, 35, 35 });
	rightWAnim.loop = true;
	rightWAnim.speed = 0.1f;

	// Left walking animation
	leftWAnim.PushBack({ 6, 7 * 35, 37, 35 });
	leftWAnim.PushBack({ 35 + 8, 7 * 35, 37, 35 });
	leftWAnim.PushBack({ 2 * 35 + 9, 7 * 35, 37, 35 });
	leftWAnim.PushBack({ 3 * 35 + 6, 7 * 35, 37, 35 });
	leftWAnim.PushBack({ 4 * 35 + 6, 7 * 35, 38, 35 });
	leftWAnim.PushBack({ 5 * 35 + 9, 7 * 35, 37, 35 });
	leftWAnim.PushBack({ 6 * 35 + 11, 7 * 35, 37, 35 });
	leftWAnim.PushBack({ 7 * 35 + 7, 7 * 35, 37, 35 });
	leftWAnim.loop = true;
	leftWAnim.speed = 0.1f;

	// Norest walking animation
	norestWAnim.PushBack({ 0, 4 * 35, 35, 35 });
	norestWAnim.PushBack({ 35, 4 * 35, 35, 35 });
	norestWAnim.PushBack({ 2 * 35, 4 * 35, 35, 35 });
	norestWAnim.PushBack({ 3 * 35, 4 * 35, 35, 35 });
	norestWAnim.PushBack({ 4 * 35, 4 * 35, 35, 35 });
	norestWAnim.PushBack({ 5 * 35, 4 * 35, 35, 35 });
	norestWAnim.PushBack({ 6 * 35, 4 * 35, 35, 35 });
	norestWAnim.PushBack({ 7 * 35, 4 * 35, 35, 35 });
	norestWAnim.loop = true;
	norestWAnim.speed = 0.1f;

	// Noroest walking animation
	noroestWAnim.PushBack({ 0, 6 * 35, 35, 35 });
	noroestWAnim.PushBack({ 35, 6 * 35, 35, 35 });
	noroestWAnim.PushBack({ 2 * 35, 6 * 35, 35, 35 });
	noroestWAnim.PushBack({ 3 * 35, 6 * 35, 35, 35 });
	noroestWAnim.PushBack({ 4 * 35, 6 * 35, 35, 35 });
	noroestWAnim.PushBack({ 5 * 35, 6 * 35, 35, 35 });
	noroestWAnim.PushBack({ 6 * 35, 6 * 35, 35, 35 });
	noroestWAnim.PushBack({ 7 * 35, 6 * 35, 35, 35 });
	noroestWAnim.loop = true;
	noroestWAnim.speed = 0.1f;

	// Sudest walking animation
	sudestWAnim.PushBack({ 0, 2 * 35, 35, 35 });
	sudestWAnim.PushBack({ 35, 2 * 35, 35, 35 });
	sudestWAnim.PushBack({ 2 * 35, 2 * 35, 35, 35 });
	sudestWAnim.PushBack({ 3 * 35, 2 * 35, 35, 35 });
	sudestWAnim.PushBack({ 4 * 35, 2 * 35, 35, 35 });
	sudestWAnim.PushBack({ 5 * 35, 2 * 35, 35, 35 });
	sudestWAnim.PushBack({ 6 * 35, 2 * 35, 35, 35 });
	sudestWAnim.PushBack({ 7 * 35, 2 * 35, 35, 35 });
	sudestWAnim.loop = true;
	sudestWAnim.speed = 0.1f;

	// Sudoest walking animation
	sudoestWAnim.PushBack({ 0, 8 * 35, 35, 35 });
	sudoestWAnim.PushBack({ 35, 8 * 35, 35, 35 });
	sudoestWAnim.PushBack({ 2 * 35, 8 * 35, 35, 35 });
	sudoestWAnim.PushBack({ 3 * 35, 8 * 35, 35, 35 });
	sudoestWAnim.PushBack({ 4 * 35, 8 * 35, 35, 35 });
	sudoestWAnim.PushBack({ 5 * 35, 8 * 35, 35, 35 });
	sudoestWAnim.PushBack({ 6 * 35, 8 * 35, 35, 35 });
	sudoestWAnim.PushBack({ 7 * 35, 8 * 35, 35, 35 });
	sudoestWAnim.loop = true;
	sudoestWAnim.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Animations/torsoF.png");	
	currentAnimation = &upAnim;
	textureL = App->textures->Load("Assets/Sprites/Animations/legsF2.png");
	currentLAnimation = &upLAnim;

	laserFx = App->audio->LoadFx("Assets/Fx/Main gun shots.wav");
	deathFx = App->audio->LoadFx("Assets/Fx/Milky death.wav");

	position.x = 150;
	position.y = (120 + 2715);

	// TODO 4: Retrieve the player when playing a second time
	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	return ret;
}
void ModulePlayer::UpdateAnim()
{

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		if (currentLAnimation != &leftWAnim)
		{
			leftAnim.Reset();
			leftWAnim.Reset();
			currentAnimation = &leftAnim;
			currentLAnimation = &leftWAnim;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_UP)
	{
		currentLAnimation = &leftLAnim;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		if (currentLAnimation != &rightWAnim)
		{
			rightAnim.Reset();
			rightWAnim.Reset();
			currentAnimation = &rightAnim;
			currentLAnimation = &rightWAnim;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_UP)
	{
		currentLAnimation = &rightLAnim;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		if (currentLAnimation != &downWAnim)
		{
			downAnim.Reset();
			downWAnim.Reset();
			currentAnimation = &downAnim;
			currentLAnimation = &downWAnim;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_UP)
	{
		currentLAnimation = &downLAnim;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		if (currentLAnimation != &upWAnim)
		{
				upAnim.Reset();
				upWAnim.Reset();
				currentAnimation = &upAnim;
				currentLAnimation = &upWAnim;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_UP)
	{
		currentLAnimation = &upLAnim;
	}

	if ((App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT))
	{
		if (currentLAnimation != &norestWAnim)
		{
			currentAnimation = shot > 0? &norestSAnim : &norestAnim;
			currentLAnimation = &norestWAnim;
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_UP) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_UP))
	{
		currentLAnimation = &norestLAnim;
	}

	if ((App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT))
	{
		if (currentLAnimation != &noroestWAnim)
		{
			currentAnimation = shot > 0? &noroestSAnim : &noroestAnim;
			currentLAnimation = &noroestWAnim;
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_UP) && (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_UP))
	{
		currentLAnimation = &noroestLAnim;
	}

	if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT))
	{
		if (currentLAnimation != &sudestWAnim)
		{
			currentAnimation = shot > 0? &sudestSAnim : &sudestAnim;
			currentLAnimation = &sudestWAnim;
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_UP) && (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_UP))
	{
		currentLAnimation = &sudestLAnim;
	}

	if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) && (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT))
	{
		if (currentLAnimation != &sudoestWAnim)
		{
			currentAnimation = shot > 0? &sudoestSAnim : &sudoestAnim;
			currentLAnimation = &sudoestWAnim;
		}
	}
	else if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_UP) && (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_UP))
	{
		currentLAnimation = &sudoestLAnim;
	}

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
		if (position.x <= 10)
		{
			position.x = 10;
		}
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		if (position.x >= 315)
		{
			position.x = 315;
		}
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y + 216 < 50)
		{
			position.y = (App->render->camera.y / 3) + 216 - 50;
		}

		position.y += speed;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
	}
}
void ModulePlayer::UpdateZoneAB()
{
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		if (position.x <= App->render->camera.x / 3 + 10)
		{
			position.x = App->render->camera.x / 3 + 10;
		}
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		if (position.x >= (315 - 75 + App->render->camera.x / 3))
		{
			position.x = (315 - 75 + App->render->camera.x / 3);
		}
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y + 216 < 50)
		{
			position.y = (App->render->camera.y / 3) + 216 - 50;
		}

		position.y += speed;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y > - 30)
		{
			position.y = (App->render->camera.y / 3) + 30;
		}

		position.y -= speed;
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
		if (position.x <= App->render->camera.x/3 + 10)
		{
			position.x = App->render->camera.x/3 + 10;
		}
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y + 216 < 50)
		{
			position.y = (App->render->camera.y / 3) + 216 - 50;
		}

		position.y += speed;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y > - 30)
		{
			position.y = (App->render->camera.y / 3) + 30;
		}
		position.y -= speed;
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
		if (position.x <= App->render->camera.x / 3 + 10)
		{
			position.x = App->render->camera.x / 3 + 10;
		}
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		if (position.x >= (315 - 75 + App->render->camera.x / 3))
		{
			position.x = (315 - 75 + App->render->camera.x / 3);
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
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y > -100)
		{
			position.y = (App->render->camera.y / 3) + 100;
		}

		position.y -= speed;
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
		if (position.x <= App->render->camera.x / 3 + 10)
		{
			position.x = App->render->camera.x / 3 + 10;
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
		if ((App->render->camera.y / 3) - position.y + 216 < 50)
		{
			position.y = (App->render->camera.y / 3) + 216 - 50;
		}

		position.y += speed;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
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
		if (position.x <= App->render->camera.x / 3 + 10)
		{
			position.x = App->render->camera.x / 3 + 10;
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
		if ((App->render->camera.y / 3) - position.y + 216 < 50)
		{
			position.y = (App->render->camera.y / 3) + 216 - 50;
		}

		position.y += speed;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		if ((App->render->camera.y / 3) - position.y > -30)
		{
			position.y = (App->render->camera.y / 3) + 30;
		}

		position.y -= speed;
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
	
	UpdateAnim();
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
		shot = 12;
		if (currentAnimation == &upAnim) currentAnimation = &upSAnim;
		if (currentAnimation == &downAnim) currentAnimation = &downSAnim;
		if (currentAnimation == &rightAnim) currentAnimation = &rightSAnim;
		if (currentAnimation == &leftAnim) currentAnimation = &leftSAnim;
		if (currentAnimation == &norestAnim) currentAnimation = &norestSAnim;
		if (currentAnimation == &noroestAnim) currentAnimation = &noroestSAnim;
		if (currentAnimation == &sudestAnim) currentAnimation = &sudestSAnim;
		if (currentAnimation == &sudoestAnim) currentAnimation = &sudoestSAnim;
	}
	if (shot > 0)
	{
		if (shot % 4 == 0)
		{
			if (currentAnimation == &upSAnim) App->particles->AddParticle(App->particles->sUp, position.x + 16, position.y, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &downSAnim) App->particles->AddParticle(App->particles->sDown, position.x + 6, position.y + 20, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &rightSAnim) App->particles->AddParticle(App->particles->sRight, position.x + 22, position.y + 17, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &leftSAnim) App->particles->AddParticle(App->particles->sLeft, position.x - 5, position.y + 13, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &norestSAnim) App->particles->AddParticle(App->particles->sNorest, position.x + 20, position.y + 4, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &noroestSAnim) App->particles->AddParticle(App->particles->sNoroest, position.x + 3, position.y + 2, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &sudestSAnim) App->particles->AddParticle(App->particles->sSudest, position.x + 10, position.y + 20, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &sudoestSAnim) App->particles->AddParticle(App->particles->sSudoest, position.x, position.y + 18, NULL, NULL, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
			
		}
		shot--;
	}
	else
	{
		if (currentAnimation == &upSAnim) currentAnimation = &upAnim;
		if (currentAnimation == &downSAnim) currentAnimation = &downAnim;
		if (currentAnimation == &rightSAnim) currentAnimation = &rightAnim;
		if (currentAnimation == &leftSAnim) currentAnimation = &leftAnim;
		if (currentAnimation == &norestSAnim) currentAnimation = &norestAnim;
		if (currentAnimation == &noroestSAnim) currentAnimation = &noroestAnim;
		if (currentAnimation == &sudestSAnim) currentAnimation = &sudestAnim;
		if (currentAnimation == &sudoestSAnim) currentAnimation = &sudoestAnim;
	}
		//App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 5, 0, Collider::Type::PLAYER_SHOT);
		//App->audio->PlayFx(laserFx);
	//}
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

	
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();
	currentLAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rectL = currentLAnimation->GetCurrentFrame();
		App->render->Blit(textureL, position.x, position.y + 18, &rectL);
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, NULL, NULL, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, NULL, NULL, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, NULL, NULL, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, NULL, NULL, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, NULL, NULL, Collider::Type::NONE, 21);

		App->audio->PlayFx(deathFx);

		//TODO 3: Go back to the intro scene when the player gets killed
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneOver, 60);

		destroyed = true;
	}
}