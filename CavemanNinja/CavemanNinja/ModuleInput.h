#ifndef __MODULEINPUT_H__
#define __MODULEINPUT_H__

#include <array>
#include "Module.h"

class Timer;

class ModuleInput : public Module
{
public:
	ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	key_state GetKey(int id) const;
	void debug();
	void DeactivateInput(int time);

private:	
	std::array<key_state, MAX_KEYS> keyboard;
	Timer* timer;
	bool input_active;
};


#endif // __MODULEINPUT_H__