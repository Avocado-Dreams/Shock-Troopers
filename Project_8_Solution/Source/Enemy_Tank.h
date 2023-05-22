#ifndef __ENEMY_Enemy_Tank_H__
#define __ENEMY_Enemy_Tank_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Tank : public Enemy
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
	bool moveToPlayer = false;
	bool melee = false;
	bool isShooting = false;

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Tank(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

	void Attack();

	void Idle();

	bool find_player();

	double  Enemy_Tank::calculateAngle();

	void OnCollision(Collider* collider) override;

	float timer;
	float SHOOT_INTERVAL = 5;
	bool isSpawning;
	float scale;
	bool hasDropped = false;

private:
	// The position (as ratio) in the wave at a specific momen
	// The speed at which the wave ratio is increased
	// The original spawning position. The wave will be calculated from that
	Path path;
	// The total height of the wave

	// The enemy animation
	Animation idleDown, shootDown, idleSE1, shootSE1, idleSE2, shootSE2, idleSE3, shootSE3, idleRight, shootRight, idleNE1, shootNE1, idleNE2, shootNE2,idleNE3,shootNE3, idleUp, shootUp, idleSW1, shootSW1, idleSW2, shootSW2,idleSW3,shootSW3, idleLeft, shootLeft, idleNW1, shootNW1, idleNW2, shootNW2, idleNW3, shootNW3;
	Animation tankStop, tankMove;
	uint tankShotFx = 0;
};

#endif // __ENEMY_Enemy_Tank_H__