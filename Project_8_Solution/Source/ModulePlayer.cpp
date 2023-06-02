#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleCollisions.h"
#include "ModuleHelicopter.h"
#include "ModuleFinalBoss.h"
#include "ModuleObstacles.h"
#include "ModuleFadeToBlack.h"
#include "SceneLayer2.h"
#include "SDL/include/SDL.h"
#include <stdio.h>

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

	//WIN ANIMATION
	winAnim.PushBack({ 1, 0, 29, 59 });
	winAnim.PushBack({ 29, 0, 29, 59 });
	winAnim.PushBack({ 58, 0, 29, 59 });
	winAnim.PushBack({ 85, 0, 30, 59 });
	winAnim.PushBack({ 115, 0, 27, 59 });
	winAnim.PushBack({ 142, 0, 27, 59 });
	winAnim.PushBack({ 169, 0, 27, 59 });

	winAnim.PushBack({ 2, 59, 30, 59 });
	winAnim.PushBack({ 32, 59, 29, 59 });
	winAnim.PushBack({ 60, 59, 29, 59 });
	winAnim.PushBack({ 89, 59, 29, 59 });
	winAnim.PushBack({ 117, 59, 29, 59 });
	winAnim.PushBack({ 146, 59, 29, 59 });
	winAnim.PushBack({ 175, 59, 29, 59 });

	winAnim.PushBack({ 27, 117, 29, 59 });
	winAnim.PushBack({ 59, 117, 29, 59 });
	winAnim.PushBack({ 93, 117, 29, 59 });
	winAnim.PushBack({ 126, 117, 29, 59 });
	winAnim.loop = false;
	winAnim.speed = 0.15f; 

	//DEATH ANIMATION up
	upDAnim.PushBack({ 2, 175, 35, 61 });
	upDAnim.PushBack({ 42, 175, 42, 61 });
	upDAnim.PushBack({ 86, 175, 37, 61 });
	upDAnim.PushBack({ 122, 175, 35, 61 });
	upDAnim.PushBack({ 157, 175, 34, 61 });
	upDAnim.PushBack({ 198, 175, 34, 66 });
	upDAnim.PushBack({ 231, 175, 30, 66 });
	upDAnim.PushBack({ 262, 175, 34, 66 });
	upDAnim.PushBack({ 296, 175, 33, 66 });
	upDAnim.loop = false;
	upDAnim.speed = 0.15f;

	//DEATH ANIMATION norest
	norestDAnim.PushBack({ 0, 241, 33, 57 });
	norestDAnim.PushBack({ 34, 241, 43, 57 });
	norestDAnim.PushBack({ 77, 241, 36, 57 });
	norestDAnim.PushBack({ 113, 241, 31, 56 });
	norestDAnim.PushBack({ 144, 241, 31, 57 });
	norestDAnim.PushBack({ 175, 241, 36, 61 });
	norestDAnim.PushBack({ 215, 241, 37, 61 });
	norestDAnim.PushBack({ 256, 241, 47, 61 });
	norestDAnim.PushBack({ 307, 241, 49, 61 });
	norestDAnim.loop = false;
	norestDAnim.speed = 0.15f;

	//DEATH ANIMATION right
	rightDAnim.PushBack({ 2, 296, 30, 59 });
	rightDAnim.PushBack({ 37, 296, 40, 59 });
	rightDAnim.PushBack({ 82, 296, 31, 59 });
	rightDAnim.PushBack({ 113, 296, 31, 59 });
	rightDAnim.PushBack({ 144, 296, 30, 59 });
	rightDAnim.PushBack({ 175, 302, 34, 51 });
	rightDAnim.PushBack({ 214, 302, 43, 51 });
	rightDAnim.PushBack({ 262, 302, 48, 51 });
	rightDAnim.PushBack({ 315, 302, 51, 51 });
	rightDAnim.loop = false;
	rightDAnim.speed = 0.15f;

	//DEATH ANIMATION sudest
	sudestDAnim.PushBack({ 0, 358, 36, 59 });
	sudestDAnim.PushBack({ 37, 358, 45, 59 });
	sudestDAnim.PushBack({ 86, 358, 31, 59 });
	sudestDAnim.PushBack({ 118, 358, 31, 59 });
	sudestDAnim.PushBack({ 151, 358, 27, 59 });
	sudestDAnim.PushBack({ 180, 358, 38, 59 });
	sudestDAnim.PushBack({ 221, 358, 42, 59 });
	sudestDAnim.PushBack({ 266, 358, 48, 59 });
	sudestDAnim.PushBack({ 319, 358, 48, 59 });
	sudestDAnim.loop = false;
	sudestDAnim.speed = 0.15f;

	//DEATH ANIMATION down
	downDAnim.PushBack({ 0, 416, 34, 59 });
	downDAnim.PushBack({ 38, 416, 45, 59 });
	downDAnim.PushBack({ 83, 416, 37, 59 });
	downDAnim.PushBack({ 120, 416, 36, 59 });
	downDAnim.PushBack({ 156, 416, 33, 59 });
	downDAnim.PushBack({ 189, 416, 35, 59 });
	downDAnim.PushBack({ 222, 416, 33, 59 });
	downDAnim.PushBack({ 260, 416, 36, 59 });
	downDAnim.PushBack({ 301, 416, 38, 59 });
	downDAnim.loop = false;
	downDAnim.speed = 0.15f;

	//DEATH ANIMATION sudoest
	sudoestDAnim.PushBack({ 0, 475, 36, 59 });
	sudoestDAnim.PushBack({ 35, 475, 48, 59 });
	sudoestDAnim.PushBack({ 81, 475, 39, 59 });
	sudoestDAnim.PushBack({ 120, 475, 35, 59 });
	sudoestDAnim.PushBack({ 154, 475, 32, 59 });
	sudoestDAnim.PushBack({ 188, 475, 39, 59 });
	sudoestDAnim.PushBack({ 228, 475, 41, 59 });
	sudoestDAnim.PushBack({ 271, 475, 49, 59 });
	sudoestDAnim.PushBack({ 319, 475, 49, 59 });
	sudoestDAnim.loop = false;
	sudoestDAnim.speed = 0.15f;

	//DEATH ANIMATION left
	leftDAnim.PushBack({ 0, 535, 31, 56 });
	leftDAnim.PushBack({ 34, 535, 40, 56 });
	leftDAnim.PushBack({ 74, 535, 45, 56 });
	leftDAnim.PushBack({ 120, 535, 39, 56 });
	leftDAnim.PushBack({ 159, 535, 33, 56 });
	leftDAnim.PushBack({ 190, 535, 41, 56 });
	leftDAnim.PushBack({ 231, 535, 46, 56 });
	leftDAnim.PushBack({ 279, 535, 49, 56 });
	leftDAnim.PushBack({ 330, 535, 54, 56 });
	leftDAnim.loop = false;
	leftDAnim.speed = 0.15f;

	//DEATH ANIMATION noroest
	noroestDAnim.PushBack({ 1, 593, 37, 62 });
	noroestDAnim.PushBack({ 37, 593, 45, 62 });
	noroestDAnim.PushBack({ 81, 593, 42, 62 });
	noroestDAnim.PushBack({ 123, 593, 33, 62 });
	noroestDAnim.PushBack({ 156, 593, 27, 62 });
	noroestDAnim.PushBack({ 185, 593, 36, 62 });
	noroestDAnim.PushBack({ 223, 593, 37, 62 });
	noroestDAnim.PushBack({ 263, 593, 46, 62 });
	noroestDAnim.PushBack({ 317, 593, 48, 62 });
	noroestDAnim.loop = false;
	noroestDAnim.speed = 0.15f;

	//HIT ANIMATION up
	upHAnim.PushBack({ 405, 195, 28, 56 });
	upHAnim.PushBack({ 433, 195, 28, 56 });
	upHAnim.PushBack({ 461, 195, 29, 56 });
	upHAnim.PushBack({ 490, 195, 32, 56 });
	upHAnim.loop = false;
	upHAnim.speed = 0.15f;

	//HIT ANIMATION norest
	norestHAnim.PushBack({ 403, 256, 29, 55 });
	norestHAnim.PushBack({ 432, 256, 32, 55 });
	norestHAnim.PushBack({ 464, 256, 31, 55 });
	norestHAnim.PushBack({ 495, 256, 28, 55 });
	norestHAnim.loop = false;
	norestHAnim.speed = 0.15f;

	//HIT ANIMATION right
	rightHAnim.PushBack({ 398, 311, 29, 52 });
	rightHAnim.PushBack({ 428, 311, 34, 52 });
	rightHAnim.PushBack({ 463, 311, 35, 52 });
	rightHAnim.PushBack({ 494, 311, 28, 52 });
	rightHAnim.loop = false;
	rightHAnim.speed = 0.15f;

	//HIT ANIMATION sudest
	sudestHAnim.PushBack({ 403, 367, 27, 52 });
	sudestHAnim.PushBack({ 430, 367, 34, 52 });
	sudestHAnim.PushBack({ 465, 367, 30, 52 });
	sudestHAnim.PushBack({ 495, 367, 27, 52 });
	sudestHAnim.loop = false;
	sudestHAnim.speed = 0.15f;

	//HIT ANIMATION down
	downHAnim.PushBack({ 402, 426, 29, 47 });
	downHAnim.PushBack({ 431, 426, 33 , 47 });
	downHAnim.PushBack({ 462, 426, 29, 47 });
	downHAnim.PushBack({ 491, 426, 32, 47 });
	downHAnim.loop = false;
	downHAnim.speed = 0.15f;

	//HIT ANIMATION sudoest
	noroestHAnim.PushBack({ 553, 251, 30, 55 });
	noroestHAnim.PushBack({ 583, 251, 31, 55 });
	noroestHAnim.PushBack({ 614, 251, 32, 55 });
	noroestHAnim.PushBack({ 646, 251, 31, 55 });
	noroestHAnim.loop = false;
	noroestHAnim.speed = 0.15f;

	//HIT ANIMATION left
	leftHAnim.PushBack({ 547, 311, 27, 52 });
	leftHAnim.PushBack({ 580, 311, 26, 52 });
	leftHAnim.PushBack({ 614, 311, 27, 52 });
	leftHAnim.PushBack({ 641, 311, 28, 52 });
	leftHAnim.loop = false;
	leftHAnim.speed = 0.15f;

	//HIT ANIMATION noroest
	sudoestHAnim.PushBack({ 548, 367, 29, 52 });
	sudoestHAnim.PushBack({ 580, 367, 29, 52 });
	sudoestHAnim.PushBack({ 607, 367, 30, 52 });
	sudoestHAnim.PushBack({ 639, 367, 36, 52 });
	sudoestHAnim.loop = false;
	sudoestHAnim.speed = 0.15f;

	//Door animation
	door.PushBack({ 10, 205, 153, 19 });
	door.PushBack({ 10, 166, 153, 19 });
	door.PushBack({ 10, 127, 153, 19 });
	door.PushBack({ 10, 88, 153, 19 });
	door.PushBack({ 10, 49, 153, 19 });
	door.PushBack({ 10, 10, 153, 19 });
	door.loop = false;
	door.speed = 0.1f;
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
	textureState = App->textures->Load("Assets/Sprites/Animations/stateAnim.png");
	currentStateAnimation = &winAnim;
	textureD = App->textures->Load("Assets/Sprites/Animations/OpenDoor.png");
	currentAnimationDoor = &door;

	laserFx = App->audio->LoadFx("Assets/Fx/Main gun shots.wav");
	deathFx = App->audio->LoadFx("Assets/Fx/Milky death.wav");
	winFx = App->audio->LoadFx("Assets/Fx/winLine.wav");
	hitFx = App->audio->LoadFx("Assets/Fx/DamagedMilky.wav");
	doorFx = App->audio->LoadFx("Assets/Fx/Door opening.wav");

	char lookupTableStages[] = { "    ABCDEFGHIJKLMNOPQRSTUVWXYZ   1234567890?!;:-" };
	stageFont = App->fonts->Load("Assets/Sprites/Fonts/FontStage.png", lookupTableStages, 6);
	stageFontRect = { 0, 0, 128, 16 };

	position.x = 150;
	position.y = (120 + 2715);

	// TODO 4: Retrieve the player when playing a second time
	destroyed = false;

	collider = App->collisions->AddCollider({ position.x-800, position.y, 33, 43 }, Collider::Type::PLAYER, this);


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
		App->render->camera.y -= SCREEN_SIZE * speed;
	}

	if ((position.x * 3 > App->render->camera.x + 550) && App->render->camera.x < 222)
	{
		App->render->camera.x += SCREEN_SIZE * speed;
	}

	if ((position.x * 3 < App->render->camera.x + 150) && App->render->camera.x > 0)
	{
		App->render->camera.x -= SCREEN_SIZE * speed;
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
		App->render->camera.x += SCREEN_SIZE * speed;
	}

	if ((position.y * 3 > App->render->camera.y + (216 - 40) * 3) && App->render->camera.y < (1797+17) * 3)
	{
		App->render->camera.y += SCREEN_SIZE * speed;
	}

	if ((position.y * 3 < App->render->camera.y + 40*3 ) && App->render->camera.y > 1797*3)
	{
		App->render->camera.y -= SCREEN_SIZE * speed;
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
		App->render->camera.y += SCREEN_SIZE * speed;
	}

	if ((position.y * 3 < App->render->camera.y + 180 * 3) && App->render->camera.y > 1797 * 3)
	{
		App->render->camera.y -= SCREEN_SIZE * speed;
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
	if (position.y > 1998) position.y--;
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
		App->render->camera.y -= SCREEN_SIZE * speed;
	}

	if ((position.x * 3 > App->render->camera.x + 135*3) && App->render->camera.x < 2095*3)
	{
		App->render->camera.x += SCREEN_SIZE * speed;
	}

	if ((position.x * 3 < App->render->camera.x + 150) && App->render->camera.x > 2051*3)
	{
		App->render->camera.x -= SCREEN_SIZE * speed;
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
		App->render->camera.x += SCREEN_SIZE * speed;
	}

	if ((position.x * 3 < App->render->camera.x + 150) && App->render->camera.x > 2051 * 3)
	{
		App->render->camera.x -= SCREEN_SIZE * speed;;
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
		if ((App->render->camera.y / 3) - position.y + 216 < 10)
		{
			position.y = (App->render->camera.y / 3) + 216 - 10;
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
		App->helicopter->Enable();
		zone = 4;
	}
	else if (zone == 4 && App->helicopter->life == 0)  //C = continue, until we have the enemy condition
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
		App->finalBoss->Enable();
		App->audio->PlayMusic("Assets/Music/DarkMatter.ogg", 1.0f);
	}

	if (App->input->keys[SDL_SCANCODE_T] == Key_State::KEY_DOWN) { //TOGGLE TURBO MODE
		speed = (speed == 1 ? 2 : 1);
		LOG("Speed %d", speed)
	}
	
	if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN) { //SHORTCUT TO FINAL BOSS
		App->render->camera.y = 2*3;
		App->render->camera.x = 2100 * 3; 
		position.y = 150;
		position.x = 2200; 
		zone = 7; 
		App->finalBoss->Enable();
		App->audio->PlayMusic("Assets/Music/DarkMatter.ogg", 1.0f);
	}

	if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN) { //SHORTCUT TO HELICOPTER
		App->render->camera.y = 1795 * 3;
		App->render->camera.x = 880 * 3;
		position.y = 1970;
		position.x = 1020;
		zone = 3;
		App->helicopter->Enable();
		App->audio->PlayMusic("Assets/Music/RideOn.ogg", 1.0f);
	}

	if (position.y < 1070 && position.y > 808)
	{
		if (position.x <= 2158) position.x++;
		else if (position.x >= 2289) position.x--;
	}
	if (position.y < 738 && position.y > 550)
	{
		if (position.x <= 2158) position.x++;
		else if (position.x >= 2215) position.x--;
	}
	if (position.x > 735 && position.x < 780 && position. y < 1900 && zone != 4) position.x--;
	if (position.x > 780 && position.x < 1250 && position.y < 1900 && zone != 4) position.y++;
	
	UpdateAnim();
	if (!destroyed)
	{
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
	}
	
	//SHOOTING

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && win == 0 && death == 0 && hit == 0)
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
 			if (currentAnimation == &upSAnim) 
 				App->particles->AddParticle(App->particles->sUp, position.x + 16, position.y, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &downSAnim) 
				App->particles->AddParticle(App->particles->sDown, position.x + 6, position.y + 20, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &rightSAnim)
				App->particles->AddParticle(App->particles->sRight, position.x + 22, position.y + 17, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &leftSAnim) 
				App->particles->AddParticle(App->particles->sLeft, position.x - 5, position.y + 13, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &norestSAnim) 
				App->particles->AddParticle(App->particles->sNorest, position.x + 20, position.y + 4, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &noroestSAnim) 
				App->particles->AddParticle(App->particles->sNoroest, position.x + 3, position.y + 2, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &sudestSAnim) 
				App->particles->AddParticle(App->particles->sSudest, position.x + 10, position.y + 20, NULL, NULL, Collider::Type::PLAYER_SHOT);
			if (currentAnimation == &sudoestSAnim) 
				App->particles->AddParticle(App->particles->sSudoest, position.x, position.y + 18, NULL, NULL, Collider::Type::PLAYER_SHOT);
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
	door.Update();

	//Timer
	timerCounter++;
	if (timerCounter == 240)
	{
		timerCounter = 0;
		if (timer != 0)
		{
			timer--;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
 	if (win > 0)
	{
		if (win < 70) {
			SDL_Rect rectL = currentLAnimation->GetCurrentFrame();
			App->render->Blit(textureL, position.x, position.y + 18, &rectL);
			SDL_Rect rect = currentAnimation->GetCurrentFrame();
			App->render->Blit(texture, position.x, position.y, &rect);
		}
  		if (win == 70) {
  			App->finalBoss->currentBAnim = nullptr;
			App->finalBoss->currentBSAnim = nullptr;
			currentStateAnimation = &winAnim;
			winAnim.Reset();

		}
		if (win > 70) {
			currentStateAnimation->Update();
			SDL_Rect rectS = currentStateAnimation->GetCurrentFrame();
			App->render->Blit(textureState, position.x, position.y, &rectS);
			sprintf_s(LevelFont, 49, "%c", App->sceneLayer2->bgTexture3);
			App->fonts->BlitText(100, 80, stageFont, "STAGE 1");
			App->fonts->BlitText(110, 100, stageFont, "CLEAR");
		}
		if (win < 221) { win++;}
		if (win == 140) { App->audio->PlayFx(winFx); }
		if (win == 220) {
			App->audio->PlayMusic("Assets/Music/StageClear.ogg", 0.0f);
			SDL_Delay(3600);
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
		}
	}
	else if (death > 0)
	{
		currentStateAnimation->Update();
		SDL_Rect rectS = currentStateAnimation->GetCurrentFrame();
		App->render->Blit(textureState, position.x + 3, position.y - 10, &rectS);
		if (death < 61) { death++; }
		if (death == 20) { App->audio->PlayFx(deathFx);	}
		if (death == 60)
		{
			SDL_Delay(1000);
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneOver, 60);
		}
		LOG("death: %d", death)
	}
	else if (hit > 0 && vida > 0)
	{
		currentStateAnimation->Update();
		SDL_Rect rectS = currentStateAnimation->GetCurrentFrame();
		App->render->Blit(textureState, position.x - 3, position.y - 10, &rectS);
		if (hit < 26) { hit++; }
		if (hit == 2) { 
			App->audio->PlayFx(hitFx); }
		if (hit == 25)
		{
			if (currentStateAnimation == &upHAnim) { currentLAnimation = &upLAnim; currentAnimation = &upAnim; }
			if (currentStateAnimation == &downHAnim) { currentLAnimation = &downLAnim; currentAnimation = &downAnim; }
			if (currentStateAnimation == &rightHAnim) { currentLAnimation = &rightLAnim; currentAnimation = &rightAnim; }
			if (currentStateAnimation == &leftHAnim) { currentLAnimation = &leftLAnim; currentAnimation = &leftAnim; }
			if (currentStateAnimation == &norestHAnim) { currentLAnimation = &norestLAnim; currentAnimation = &norestAnim; }
			if (currentStateAnimation == &noroestHAnim) { currentLAnimation = &noroestLAnim; currentAnimation = &noroestAnim; }
			if (currentStateAnimation == &sudestHAnim) { currentLAnimation = &sudestLAnim; currentAnimation = &sudestAnim; }
			if (currentStateAnimation == &sudoestHAnim) { currentLAnimation = &sudoestLAnim; currentAnimation = &sudoestAnim; }
			hit = 0;
		}
		//LOG("Player hit")
	}
	else if (!destroyed)
	{
		SDL_Rect rectL = currentLAnimation->GetCurrentFrame();
		App->render->Blit(textureL, position.x, position.y + 18, &rectL);
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	
	
	//Door
	if (zone == 1)
	{
		SDL_Rect doorClosed = { 10, 205, 153, 19 };
		App->render->Blit(textureD, 100, 1795, &doorClosed);
		soundPlayed = false;
	}
	if (zone == 3)
	{
		SDL_Rect openDoor = { 10, 10, 153, 19 };
		App->render->Blit(textureD, 100, 1795, &openDoor);
		soundPlayed = false;
	}
	if (zone == 2 && currentZone != 2) {
		door.Reset();
		currentZone = 2;
	}
	if (zone == 2)
	{
		SDL_Rect rectD = door.GetCurrentFrame();
		App->render->Blit(textureD, 100, 1795, &rectD);

		if (!soundPlayed)
		{
			App->audio->PlayFx(doorFx);
			soundPlayed = true;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == Collider::Type::FINALBOSS)
	{
		if (App->finalBoss->currentBAnim == &App->finalBoss->downAnim) {
			if (position.y > App->finalBoss->position.y + 160) { 
				position.y+=2;
			}
		}
		if ((currentLAnimation == &upLAnim || currentLAnimation == &upWAnim) && (position.y < App->finalBoss->position.y + 161)) { position.y += 2; }
		if ((currentLAnimation == &downLAnim || currentLAnimation == &downWAnim) && (position.y < App->finalBoss->position.y + 161)) { position.y -= 2; }
		if ((currentLAnimation == &rightLAnim || currentLAnimation == &rightWAnim) && (position.y < App->finalBoss->position.y + 161)) { position.x -= 2; }
		if ((currentLAnimation == &leftLAnim || currentLAnimation == &leftWAnim) && (position.y < App->finalBoss->position.y + 161)) { position.x += 2; }
		if ((currentLAnimation == &norestLAnim || currentLAnimation == &norestWAnim) && (position.y < App->finalBoss->position.y + 161)) { position.y += 2; position.x -= 2; }
		if ((currentLAnimation == &noroestLAnim || currentLAnimation == &noroestWAnim) && (position.y < App->finalBoss->position.y + 161)) { position.y += 2; position.x += 2; }
		if ((currentLAnimation == &sudestLAnim || currentLAnimation == &sudestWAnim) && (position.y < App->finalBoss->position.y + 161)) { position.y -= 2; position.x -= 2; }
		if ((currentLAnimation == &sudoestLAnim || currentLAnimation == &sudoestWAnim) && (position.y < App->finalBoss->position.y + 161)) { position.y -= 2; position.x += 2; }

		//LOG("Touching boss posy+161: %d FBposy: %d", position.y, App->finalBoss->position.y+161);
	}
	//else if (c1 == collider && c2->type == Collider::Type::SOLDIER)
	//{
	//	if ((currentLAnimation == &upLAnim || currentLAnimation == &upWAnim)) { position.y += 2; }
	//	if ((currentLAnimation == &downLAnim || currentLAnimation == &downWAnim)) { position.y -= 2; }
	//	if ((currentLAnimation == &rightLAnim || currentLAnimation == &rightWAnim)) { position.x -= 2; }
	//	if ((currentLAnimation == &leftLAnim || currentLAnimation == &leftWAnim)) { position.x += 2; }
	//	if ((currentLAnimation == &norestLAnim || currentLAnimation == &norestWAnim)) { position.y += 2; position.x -= 2; }
	//	if ((currentLAnimation == &noroestLAnim || currentLAnimation == &noroestWAnim)) { position.y += 2; position.x += 2; }
	//	if ((currentLAnimation == &sudestLAnim || currentLAnimation == &sudestWAnim)) { position.y -= 2; position.x -= 2; }
	//	if ((currentLAnimation == &sudoestLAnim || currentLAnimation == &sudoestWAnim)) { position.y -= 2; position.x += 2; }
	//}
		//LOG("Touching boss posy+161: %d FBposy: %d", position.y, App->finalBoss->position.y+161);
	if (c1 == collider && (c2->type == Collider::Type::ENEMY_SHOT || c2->type == Collider::Type::BOSS_SHOT || c2->type == Collider::Type::MELEE || c2->type == Collider::Type::TANK_SHOT) && destroyed == false && vida > 0)
	{
		if (vida > 0) {
			vida -= 10; 
			if (vida < 0) vida = 0;
			App->sceneLayer2->hp = vida;

		hit = 1;
		if (currentLAnimation == &upLAnim || currentLAnimation == &upWAnim) { currentStateAnimation = &upHAnim; upHAnim.Reset(); }
		if (currentLAnimation == &downLAnim || currentLAnimation == &downWAnim) { currentStateAnimation = &downHAnim; downHAnim.Reset(); }
		if (currentLAnimation == &rightLAnim || currentLAnimation == &rightWAnim) { currentStateAnimation = &rightHAnim; rightHAnim.Reset(); }
		if (currentLAnimation == &leftLAnim || currentLAnimation == &leftWAnim) { currentStateAnimation = &leftHAnim; leftHAnim.Reset(); }
		if (currentLAnimation == &norestLAnim || currentLAnimation == &norestWAnim) { currentStateAnimation = &norestHAnim; norestHAnim.Reset(); }
		if (currentLAnimation == &noroestLAnim || currentLAnimation == &noroestWAnim) { currentStateAnimation = &noroestHAnim; noroestHAnim.Reset(); }
		if (currentLAnimation == &sudestLAnim || currentLAnimation == &sudestWAnim) { currentStateAnimation = &sudestHAnim; sudestHAnim.Reset(); }
		if (currentLAnimation == &sudoestLAnim || currentLAnimation == &sudoestWAnim) { currentStateAnimation = &sudoestHAnim; sudoestHAnim.Reset(); }
		if (vida == 0) { destroyed = true; }
		}
		LOG("vida: %d", vida)
		
	}
	if (c1 == collider && (c2->type == Collider::Type::LIFE))
	{
		/*vida += 64;
		App->sceneLayer2->hp += 64;*/
		App->sceneLayer2->currentHP += 64;
	}
	if (destroyed && death == 0)
	{
		death = 1;

		if (currentLAnimation == &upLAnim || currentLAnimation == &upWAnim) { currentStateAnimation = &upDAnim; upDAnim.Reset(); }
		if (currentLAnimation == &downLAnim || currentLAnimation == &downWAnim) { currentStateAnimation = &downDAnim; downDAnim.Reset(); }
		if (currentLAnimation == &rightLAnim || currentLAnimation == &rightWAnim) { currentStateAnimation = &rightDAnim; rightDAnim.Reset(); }
		if (currentLAnimation == &leftLAnim || currentLAnimation == &leftWAnim) { currentStateAnimation = &leftDAnim; leftDAnim.Reset(); }
		if (currentLAnimation == &norestLAnim || currentLAnimation == &norestWAnim) { currentStateAnimation = &norestDAnim; norestDAnim.Reset(); }
		if (currentLAnimation == &noroestLAnim || currentLAnimation == &noroestWAnim) { currentStateAnimation = &noroestDAnim; noroestDAnim.Reset(); }
		if (currentLAnimation == &sudestLAnim || currentLAnimation == &sudestWAnim) { currentStateAnimation = &sudestDAnim; sudestDAnim.Reset(); }
		if (currentLAnimation == &sudoestLAnim || currentLAnimation == &sudoestWAnim) { currentStateAnimation = &sudoestDAnim; sudoestDAnim.Reset(); }
		LOG("Player dead")
	}
}