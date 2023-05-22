#ifndef __PICKUPS_LIFE_H__
#define __PICKUPS_LIFE_H__

#include "PickUps.h"
#include "Path.h"

class PickUps_LIFE : public PickUps
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	PickUps_LIFE(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation Life;
};

#endif // __PICKUPS_BLUEDIAMOND_H__