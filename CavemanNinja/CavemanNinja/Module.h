#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

class Animation;

class Module
{
public:
	Module() {};
	Module(bool active) : active(active) { started = false; };
	virtual ~Module() {};

	bool IsEnabled() const;
	
	bool HasStarted() const;

	bool Enable();

	bool Disable();

	virtual bool Init();

	virtual bool Start();

	virtual update_status PreUpdate();

	virtual update_status Update();

	virtual update_status PostUpdate();

	virtual bool CleanUp();

	virtual void OnCollision(Collider* a, Collider* b);

	bool started;

protected:
	void StoreData(info_type info, GenericData& data, Animation& animation, Module* module);

	bool active;
};

#endif // __MODULE_H__