#ifndef __PICKUPS_H__
#define __PICKUPS_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class PickUps
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	PickUps(int x, int y);

	// Destructor
	virtual ~PickUps();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering PickUps' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModulePickUps' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);

public:
	// The current position in the world
	iPoint position;

	// The PickUps's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int getPickUps = 0;


protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The PickUps's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __PICKUPS_H__