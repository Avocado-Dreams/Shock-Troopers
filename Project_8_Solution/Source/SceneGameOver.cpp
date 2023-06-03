#include "SceneGameOver.h"

#include "SDL/include/SDL.h" 
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleFinalBoss.h"
#include "ModuleHelicopter.h"

SceneGameOver::SceneGameOver(bool startEnabled) : Module(startEnabled)
{

}

SceneGameOver::~SceneGameOver()
{

}

// Load assets
bool SceneGameOver::Start()
{
	LOG("Loading assets");

	bool ret = true;

	teamTexture = App->textures->Load("Assets/Sprites/intro_sprites/GameOver.png");
	gameOver = App->audio->LoadFx("Assets/Music/Game Over.wav");
	//App->audio->PlayMusic("Assets/Music/silence.wav", 0.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->death = 0;
	App->finalBoss->Disable();
	App->helicopter->Disable();

	return ret;
}

Update_Status SceneGameOver::Update()
{
	GamePad& pad = App->input->pads[0];
	/*SDL_Rect srcRect = { 0,0, teamTexture.w, teamTexture.h }; //ESTO LO COMENTO PARA QUE FUNCIONE PERO SIRVE PARA REDUCIR LA IMAGEN ENTRE 3 YA QUE EL LIENZO LO HE HECHO x3
	SDL_Rect dstRect = { 0,0, (teamTexture.w / 3), (teamTexture.h / 3) };
	SDL_RenderCopyEx(App->render->renderer, teamTexture, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);*/
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 60);
		/*App->fade->FadeToBlack(this, (Module*)App->sceneLayer2, 60);*/
	}

	if (firstTime)
	{
		App->audio->PlayMusic("Assets/Music/SilenceGameOver.ogg", 1.0f);
		App->audio->PlayFx(gameOver);
		App->collisions->CleanUp();
		firstTime = false; 
	}
	
	

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneGameOver::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(teamTexture, 0, 0, NULL);
	return Update_Status::UPDATE_CONTINUE;

}