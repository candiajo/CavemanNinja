#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <list>
#include "SDL_rect.h"

class Collider;

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned __int32 uint32;

enum weapon_type
{
	AXE = 0,
	WHEEL,
	BONE,
	TUSK,
	BOOMERANG
};

enum weapon_subtype
{
	HORIZONTAL,
	VERTICAL,
	SUPER,
	CROUCH
};

enum particle_type
{
	HIT_PLAYER = 0,
	KUP = 1,
	WAM_H = 2,
	WAM_V = 3,
	WOMP = 4,
	HIT_DINO = 5,

	ITEM_WHEEL,
	ITEM_BONE,
	ITEM_BOOMERANG,
	ITEM_TUSK,

	AXE_HORZ,
	AXE_VERT,
	AXE_CROUCH,
	SUPER_AXE,

	WHEEL_HORZ,
	WHEEL_VERT,
	WHEEL_CROUCH,
	SUPER_WHEEL,

	BONE_HORZ,
	BONE_VERT,
	BONE_CROUCH,
	SUPER_BONE,

	TUSK_HORZ,
	TUSK_VERT,
	TUSK_CROUCH,
	SUPER_TUSK,

	SLOW_STONE,
	FAST_STONE,

	ENEMY,
	FAKE_ATTACK,
	DINO_TAIL,
	ARM,
	NO_PARTICLE
};
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

enum type_direction
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
	NO_COLLIDER = 0,
	COLLIDER_GROUND = 1,		// down limit of the screen
	COLLIDER_PLATFORM = 2,		// the player can walk on it, but can also jump down
	COLLIDER_PLAYER_BODY = 3,	// where player receives damage
	COLLIDER_PLAYER_ATTACK = 4,	// hand weapon and feet (on jump)
	COLLIDER_DETECT_GROUND = 5,	// for detecting contact with the ground (collider on the feet)
	COLLIDER_PLAYER_SHOT = 6,	// throwable weapon
	COLLIDER_ENEMY = 7,			// where enemies can get damage and cause damage to the player
	COLLIDER_DINO = 8,			// for the dinosaur's head
	COLLIDER_PROXIMITY = 9,		// for detecting if the player is too near from dino (in that case, the dino attacks with it's tail)
	COLLIDER_ITEM = 10,			// weapon items
	NUM_COLLIDERS				// 
};

enum game_events
{
	NO_EVENT,
	PLAYER_STEP_GROUND,
	PLAYER_STEP_ENEMY,
	WALK_OFF_PLATFORM,
	DINO_GET_HIT,
	DINO_GET_SUPERHIT,
	DINO_IS_DEFEATED,
	PLAYER_HIT_FRONT,
	PLAYER_HIT_BACK
};

enum attack_direction
{
	ATTACKED_FROM_FRONT,
	ATTACKED_FROM_BEHIND
};

struct Point
{
	float x = 0;
	float y = 0;
};

struct FrameInfo
{
	SDL_Rect original, alternate;
	SDL_Rect* section;
	Point offset;
	std::list<Collider*> colliders;
};

struct GenericData
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
#define SAME_STATE nullptr
#define AVAILABLE_WEAPONS 4

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240
#define SCREEN_SIZE 2
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Joe & Mac Caveman Ninja"

#define IMG_TITLE_SCREEN "Content\\Graphics\\title_screen.png"
#define IMG_SCENE_DINO "Content\\Graphics\\scene_dino.png"
#define IMG_TRANSITION "Content\\Graphics\\transition.png"
#define IMG_PLAYER "Content\\Graphics\\joe.png"
#define IMG_DINO "Content\\Graphics\\dino.png"
#define IMG_PARTICLES "Content\\Graphics\\particles.png"
#define IMG_HUD "Content\\Graphics\\hud.png"

#define DATA_SCENE_DINO "Content\\Data\\scene_dino.ini"
#define DATA_PLAYER "Content\\Data\\joe.ini"
#define DATA_DINO "Content\\Data\\dino.ini"
#define DATA_MATRIX "Content\\Data\\collision matrix.ini"
#define DATA_PARTICLES "Content\\Data\\particles.ini"
#define DATA_TRANSITION "Content\\Data\\transition.ini"
#define DATA_HUD "Content\\Data\\hud.ini"						// hud.ini... ja! :D

#define MUSIC_BOSS_LEVEL "Content\\Audio\\boss theme.ogg"
#define MUSIC_WIN "Content\\Audio\\win theme.ogg"
#define FX_PLAYER_ATTACK "Content\\Audio\\player attack.wav"
#define FX_PLAYER_SUPERATTACK "Content\\Audio\\player superattack.wav"
#define FX_PLAYER_CHARGING "Content\\Audio\\charging.wav"
#define FX_PLAYER_HURT "Content\\Audio\\player hurt.wav"
#define FX_DINO_DEFEATED "Content\\Audio\\dino defeated.wav"
#define FX_DINO_ROAR "Content\\Audio\\dino roar.wav"
#define FX_ENEMY_HURT "Content\\Audio\\enemy hurt.wav"
#define FX_WEAPON_HIT "Content\\Audio\\weapon hit.wav"
#define FX_PLAYER_TIRED "Content\\Audio\\player tired.wav"
#define FX_PLAYER_JUMP "Content\\Audio\\player jump.wav"
#define FX_PLAYER_LAND "Content\\Audio\\player land.wav"
#define FX_SUPER_JUMP "Content\\Audio\\super jump.wav"
#define FX_DINO_ROAR "Content\\Audio\\dino roar.wav"
#define FX_DINO_STOPMS "Content\\Audio\\dino stomps.wav"
#define FX_DINO_TAIL "Content\\Audio\\dino tail.wav"
#define FX_BEGIN_PLAY "Content\\Audio\\begin play.wav"

#define	LEFT_LIMIT -25
#define	RIGHT_LIMIT 195
#define DINO_BLINK 200
#define DINO_HIT 800

#define DEFAULT_X_SPEED 1
#define PLAYER_MAX_ENERGY 18
#define DINO_MAX_ENERGY 13

#define CAN_FLIP true
#define ANGRY_VERSION true
#define CLOSED_EYE_VERSION true
#define NO_REPEAT 0

#define JUMP_BUTTON SDL_SCANCODE_X
#define UP_BUTTON SDL_SCANCODE_UP
#define DOWN_BUTTON SDL_SCANCODE_DOWN
#define LEFT_BUTTON SDL_SCANCODE_LEFT
#define RIGHT_BUTTON SDL_SCANCODE_RIGHT
#define FIRE_BUTTON SDL_SCANCODE_Z

#define RELEASE( x ) \
    { \
       if( x != nullptr ) \
	          { \
         delete x; \
	     x = nullptr; \
	          } \
    }

#endif //__GLOBALS_H__
