#ifndef __MODULE_PICKUPS_H__
#define __MODULE_PICKUPS_H__

#include "Module.h"

#define MAX_PICKUPS 100

enum class PickUps_Type
{
	NO_TYPE,
	RIB,
	STEAK,
	BANANA,
	RICE,
	BLUEDIAMOND,
	YELLOWDIAMOND,
	REDDIAMOND,
	LIFE,
	BIGLIFE,
	BOMB,
	SPEED
};

struct PickUpsSpawnpoint
{
	PickUps_Type type = PickUps_Type::NO_TYPE;
	int x, y;
};

class PickUps;
struct SDL_Texture;

class ModulePickUps : public Module
{
public:
	// Constructor
	ModulePickUps(bool startEnabled);

	// Destructor
	~ModulePickUps();

	// Called when the module is activated
	// Loads the necessary textures for the pickups
	bool Start() override;

	// Called at the middle of the application loop
	// Handles all pickups logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the pickups and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active pickups left in the array
	bool CleanUp() override;

	// Called when an pickup collider hits another collider
	// The pickup is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an pickup into the queue to be spawned later
	bool AddPickUps(PickUps_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandlePickUpsSpawn();

	// Destroys any pickups that have moved outside the camera limits
	void HandlePickUpsDespawn();

private:
	// Spawns a new enemy using the data from the queue
	void SpawnPickUps(const PickUpsSpawnpoint& info);

private:
	// A queue with all spawn points information
	PickUpsSpawnpoint spawnQueue[MAX_PICKUPS];

	// All spawned pickups in the scene
	PickUps* pickUps[MAX_PICKUPS] = { nullptr };

	// The pickups sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for getting a pickup
	int getPickUps = 0;
};

#endif // __MODULE_PICKUPS_H__