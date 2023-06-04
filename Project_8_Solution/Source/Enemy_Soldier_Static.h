#ifndef __Enemy_Soldier_Static_H__
#define __Enemy_Soldier_Static_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Soldier_Static : public Enemy
{
public:
	double playerX;
	double playerY;
	double dx;
	double dy;
	int distance;
	float angle;
	int numShots = 0;
	int MAXSHOTS = 5;
	bool isShooting = false;
	bool hasDecided = false;
	bool isIdle = false;
	bool isMoving = false;
	bool hasMeleed = false;
	int loop = 3;
	int tempTimer;
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Soldier_Static(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Attack();

	void Idle();

	void Move();

	void Melee();

	bool find_player();

	double  Enemy_Soldier_Static::calculateAngle();

	void OnCollision(Collider* collider) override;

	//Timer to control the enemy attack cooldown
	float timer;
	float SHOOT_INTERVAL = 5;
	bool isSpawning = false;
	float scale;
	bool hasDropped = false;

public:
	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation moveUp, moveDown, moveLeft, moveRight, moveNE, moveNW, moveSE, moveSW;
	Animation enemy_airspawnL, getUpL, enemy_airspawnR, getUpR;
	Animation idleDownL, shootDownL, idleDownR, shootDownR, idleSE1, shootSE1, idleSE2, shootSE2, idleRight, shootRight, idleNE1, shootNE1, idleNE2, shootNE2, idleUpL, shootUpL, idleUpR, shootUpR, idleSW1, shootSW1, idleSW2, shootSW2, idleLeft, shootLeft, idleNW1, shootNW1, idleNW2, shootNW2;
	Animation meleeDown, meleeUp, meleeRight, meleeLeft, meleeNW, meleeNE, meleeSW, meleeSE;

	//uint enemyShotFx = 0;
	//uint enemyKnifeFx = 0;
};

#endif // __Enemy_Soldier_Static_H__