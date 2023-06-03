#include "SceneTeam.h"

#include "SDL/include/SDL.h" //NECESARIO AÑADIR ESTO!!!! sino hay error (para el SDL_RenderCopyEx)
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"


SceneTeam::SceneTeam(bool startEnabled) : Module(startEnabled)
{

}

SceneTeam::~SceneTeam()
{

}

// Load assets
bool SceneTeam::Start()
{
	LOG("Loading assets");

	bool ret = true;

	teamTexture = App->textures->Load("Assets/Sprites/intro_sprites/TeamPhoto.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneTeam::Update()
{
	GamePad& pad = App->input->pads[0];
	/*SDL_Rect srcRect = { 0,0, teamTexture.w, teamTexture.h }; //ESTO LO COMENTO PARA QUE FUNCIONE PERO SIRVE PARA REDUCIR LA IMAGEN ENTRE 3 YA QUE EL LIENZO LO HE HECHO x3
	SDL_Rect dstRect = { 0,0, (teamTexture.w / 3), (teamTexture.h / 3) };
	SDL_RenderCopyEx(App->render->renderer, teamTexture, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);*/
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneTeam::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(teamTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}