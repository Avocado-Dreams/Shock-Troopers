#ifndef __ENEMY_REDBIRD_H__
#define __ENEMY_REDBIRD_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RedBird : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_RedBird(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The position (as ratio) in the wave at a specific momen
	// The speed at which the wave ratio is increased
	// The original spawning position. The wave will be calculated from that
	Path path;
	// The total height of the wave

	// The enemy animation
	Animation flyAnim;
};

#endif // __ENEMY_REDBIRD_H__