#ifndef __ENEMY_MECH_H__
#define __ENEMY_MECH_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Mech : public Enemy
{
public:
	double playerX;
	double playerY;
	double dx;
	double dy;
	int distance;
	float angle;
	float shotX;
	float shotY;
	int numShots = 0;
	int MAXSHOTS = 5;
	bool moveToPlayer = false;
	bool melee = false;
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Mech(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Attack();

	void Idle();

	bool find_player();

	double  Enemy_Mech::calculateAngle();

	//Timer to control the enemy attack cooldown
	float timer = 0.0f;
	float SHOOT_INTERVAL = 5;

private:
	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation idleDownL,shootDownL, idleDownR, shootDownR, idleSE1, shootSE1, idleSE2, shootSE2, idleRight, shootRight, idleNE1, shootNE1, idleNE2, shootNE2,idleUp,shootUp;
};

#endif // __ENEMY_MECH_H__