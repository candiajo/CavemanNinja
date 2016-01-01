#ifndef __MODULE_H__
#define __MODULE_H__

//#include "Animation.h"
#include "Globals.h"

class Animation;

class Module
{
public:
	Module();
	Module(bool active);
	virtual ~Module();

	bool IsEnabled() const;

	bool Enable();

	bool Disable();

	virtual bool Init();

	virtual bool Start();

	virtual update_status PreUpdate();

	virtual update_status Update();

	virtual update_status PostUpdate();

	virtual bool CleanUp();

	virtual void OnCollision(Collider* a, Collider* b);

protected:
	void StoreData(info_type info, Generic_data& data, Animation& animation, Module* module);

	bool active;

};

#endif // __MODULE_H__