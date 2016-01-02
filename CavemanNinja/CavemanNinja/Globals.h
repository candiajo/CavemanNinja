#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <list>
#include "SDL_rect.h"

class Collider;

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

enum Direction
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum info_type
{
	FRAME_INFO,
	SPEED_INFO,
	LOOP_INFO,
	OFFSET_INFO,
	FRAME_COLLIDER,
	ANIMATION_COLLIDER
};

enum collider_type
{
	COLLIDER_GROUND = 1,		// down limit of the screen
	COLLIDER_PLATFORM = 2,		// the player can walk on it, but can also jump down
	COLLIDER_PLAYER_BODY = 3,	// where player receives damage
	COLLIDER_PLAYER_ATTACK = 4,	// hand weapon and feet (on jump)
	COLLIDER_PLAYER_GROUND = 5,	// for detecting contact with the ground (collider on the feet)
	COLLIDER_PLAYER_SHOT = 6,	// throwable weapon
	COLLIDER_ENEMY = 7,			// where enemies can get damage and cause damage to the player
	COLLIDER_DINO = 8,			// for the dinosaur's head
	COLLIDER_BORDER = 9,		// for detecting platform borders and fall down
	NUM_COLLIDERS				// 
};

enum jump_substate
{
	NO_FIRE,
	NORMALJUMP,
	SUPERJUMP,
	PRE_DOWNJUMP,
	DOWNJUMP,
	PRE_FALLING,
	FALLING,
	PRE_SHOT_H,
	SHOT_H,
	PRE_SHOT_V,
	SHOT_V
};

enum game_events
{
	PLAYER_STEP_GROUND,
	WALK_OFF_PLATFORM
};

struct Frame_info
{
	SDL_Rect section;
	int x_offset = 0;
	int y_offset = 0;
	std::list<Collider*> colliders;
};

struct Point
{
	float x, y;
};

struct Generic_data
{
	int val1, val2, val3, val4;
	float val5;
	collider_type type;
	bool yes_no;
};

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_KEYS 300
#define PRESSED 1

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240
#define SCREEN_SIZE 2
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Joe & Mac Caveman Ninja"

#define IMG_TITLE_SCREEN "Content\\Graphics\\title_screen.png"
#define IMG_SCENE_DINO "Content\\Graphics\\scene_dino.png"
#define IMG_READY "Content\\Graphics\\ready.png"
#define IMG_PLAYER "Content\\Graphics\\joe.png"
#define DATA_SCENE_DINO "Content\\Data\\scene_dino.ini"
#define DATA_PLAYER "Content\\Data\\joe.ini"
#define DATA_MATRIX "Content\\Data\\collision matrix.ini"

#define	LEFT_LIMIT -20
#define	RIGHT_LIMIT 200

#define DEFAULT_X_SPEED 1
#define NORMAL_JUMP_SPEED -6
#define SUPER_JUMP_SPEED -8
#define DOWN_JUMP_SPEED 0.4

#define CAN_FLIP true

#define RELEASE( x ) \
    { \
       if( x != nullptr ) \
	          { \
         delete x; \
	     x = nullptr; \
	          } \
    }

#endif //__GLOBALS_H__

/* DEBUG - TODELETE
#include "ModuleInput.h"

if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) x++;
if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) x--;
if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) y--;
if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) y++;
LOG("x: %d \n", x);
LOG("y: %d \n", y);
*/