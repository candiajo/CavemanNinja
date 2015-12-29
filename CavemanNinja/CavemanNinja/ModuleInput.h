#ifndef __MODULEINPUT_H__
#define __MODULEINPUT_H__

#include <array>
#include "Module.h"

class ModuleInput : public Module
{
public:
	ModuleInput(bool active);
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	key_state GetKey(int id) const;

private:	
	std::array<key_state, MAX_KEYS> keyboard;
};


#endif // __MODULEINPUT_H__