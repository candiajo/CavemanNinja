#include "ModuleHud.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "File.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleDino.h"
#include "Timer.h"

ModuleHud::~ModuleHud()
{
	RELEASE(timer);
}

bool ModuleHud::Start()
{
	LoadData();

	timer = new Timer(500);
	timer->StartTimer();

	return true;
}

update_status ModuleHud::Update()
{
	ModulePlayer& player = *App->player1;
	ModuleDino& dino = *App->dino;

	DrawHudItem(HISCORE);

	if (timer->ElapsedTime() < 750)	DrawHudItem(PRESS_START);
	else if (timer->ElapsedTime() > 1500) timer->StartTimer();
	
	if (player.is_defeated) DrawHudItem(JOE_DEAD);
	else if (player.is_hit || player.is_tired)	DrawHudItem(JOE_HIT);
	else DrawHudItem(JOE_NORMAL);

	if (App->lives == 2) DrawHudItem(LIVES_2);
	else if (App->lives == 1) DrawHudItem(LIVES_1);
	else if (App->lives == 0) DrawHudItem(LIVES_0);

	DrawPlayerLife(player.energy);
	if (App->dino->IsEnabled())
	{
		DrawDinoHits(dino.energy);
		DrawDinoEnergy(dino.energy);
	}

	DrawScore(player.score);
	
	return UPDATE_CONTINUE;
}

bool ModuleHud::CleanUp()
{
	RELEASE(timer);

	App->textures->Unload(texture_hud);
	return true;
}

void ModuleHud::LoadData()
{
	std::string name;
	info_type info;
	GenericData data;

	texture_hud= App->textures->Load(IMG_HUD);

	File player_data(DATA_HUD);

	while (player_data.GetAnimInfo(info, name, data))
	{
		StoreData(info, data, hud, this);
	}
}

void ModuleHud::DrawHudItem(hud_index item)
{
	FrameInfo frame = hud.PeekFrame(item);
	App->renderer->Blit(texture_hud, (int)frame.offset.x, (int)frame.offset.y, frame.section, SDL_FLIP_NONE);
}

void ModuleHud::DrawPlayerLife(int energy)
{
	FrameInfo frame;
	hud_index color;
	int i;

	if (energy <= 5) color = RED_LIFEDOT;
	else if (energy <= 10) color = ORANGE_LIFEDOT;
	else if (energy <= 15) color = YELLOW_LIFEDOT;
	else if (energy <= 18) color = GREEN_LIFEDOT;

	for (i = 0; i < PLAYER_MAX_ENERGY; i++)
	{
		if (i + 1 > energy) frame = hud.PeekFrame(VOID_LIFEDOT);
		else frame = hud.PeekFrame(color);
		frame.offset.x += (i * 4);
		App->renderer->Blit(texture_hud, (int)frame.offset.x, (int)frame.offset.y, frame.section, SDL_FLIP_NONE);
	}
}

void ModuleHud::DrawDinoHits(int energy)
{
	FrameInfo frame;
	int i;
	int hits = DINO_MAX_ENERGY - energy;

	for (i = 0; i < hits; i++)
	{
		frame = hud.PeekFrame(HITDOT);
		frame.offset.x += (i * 8);
		App->renderer->Blit(texture_hud, (int)frame.offset.x, (int)frame.offset.y, frame.section, SDL_FLIP_NONE);
	}
}

void ModuleHud::DrawDinoEnergy(int energy)
{
	FrameInfo frame;
	int i;
	int lifedots = (int)ceil((float)energy / 2.6f);

	for (i = 0; i < lifedots; i++)
	{
		frame = hud.PeekFrame(DINO_LIFEDOT);
		frame.offset.x += (i * 9);
		App->renderer->Blit(texture_hud, (int)frame.offset.x, (int)frame.offset.y, frame.section, SDL_FLIP_NONE);
	}
}

void ModuleHud::DrawScore(int score)
{
	FrameInfo frame;
	int digit;
	int pos = 2;
	score /= 100;

	frame = hud.PeekFrame(NUMBER_0);
	App->renderer->Blit(texture_hud, (int)frame.offset.x, (int)frame.offset.y, frame.section, SDL_FLIP_NONE);
	App->renderer->Blit(texture_hud, (int)frame.offset.x - 8, (int)frame.offset.y, frame.section, SDL_FLIP_NONE);

	while (score > 0)
	{
		digit = score % 10;
		score -= digit;
		score /= 10;

		frame = hud.PeekFrame(digit);
		frame.offset.x -= (pos * 8);
		pos++;

		App->renderer->Blit(texture_hud, (int)frame.offset.x, (int)frame.offset.y, frame.section, SDL_FLIP_NONE);
	}
}