#ifndef __MODULECOLLISIONS_H__
#define __MODULECOLLISIONS_H__

#include "Module.h"
#include <list>

class ModuleCollisions : public Module
{
public:
	ModuleCollisions() : Module(true) {};

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	bool IsCollidingWithGround(Collider& me) const;

	void AddCollider(Collider* collider);
	
private:
	void LoadData();

	std::list<Collider*> colliders;
	bool debug;
	bool collision_matrix[NUM_COLLIDERS][NUM_COLLIDERS];
};

#endif // __MODULECOLLISIONS_H__