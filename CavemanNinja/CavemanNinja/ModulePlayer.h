#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Sprite.h"
#include "Animation.h"
#include "Globals.h"

class ParticleArm;

class ModulePlayer : public Sprite
{
public:
	ModulePlayer(bool active) : Sprite(active) {};
	~ModulePlayer() {};

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void SetArm(ParticleArm* arm);
	void StopArm();

	void OnCollision(Collider* my_collider, Collider* other_collider);

	Animation idle;
	Animation walk;
	Animation crouch;
	Animation lookup;
	Animation normaljump;
	Animation superjump;
	Animation downjump;
	Animation shotweapon;
	Animation shotcrouch;
	Animation shotup;
	Animation frontattack;
	Animation backattack;
	Animation frontdying;
	Animation backdying;
	Animation salute;
	Animation tired;
	Animation supershot;
	Animation ch_idle;
	Animation ch_walk;
	Animation ch_crouch;
	Animation ch_lookup;
	Animation ch_normaljump;
	Animation ch_downjump;

	unsigned int fx_player_attack;
	unsigned int fx_player_superattack;
	unsigned int fx_charging;
	unsigned int fx_player_hurt;
	unsigned int fx_player_tired;
	unsigned int fx_player_jump;
	unsigned int fx_player_land;
	unsigned int fx_super_jump;

	bool rolling_arm;
	bool is_crouch;
	bool is_jumping;
	bool is_tired;
	bool charge_enough;
	bool player_end;
	bool is_defeated;
	bool is_hit;

	int hit_received_energy;

	int score;

	ParticleArm* arm = nullptr;

private:
	void LoadData();
	PlayerState* state;
	
};

#endif // __MODULEPLAYER_H__