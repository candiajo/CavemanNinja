#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL_rect.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned __int32 uint32;

enum main_states
{
	MAIN_CREATION,
	MAIN_INIT,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum key_state
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};


#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_KEYS 300
#define PRESSED 1

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240
#define SCREEN_SIZE 3
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Joe & Mac Caveman Ninja"

#endif //__GLOBALS_H__