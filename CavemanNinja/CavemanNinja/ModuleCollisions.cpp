#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "File.h"

using namespace std;

bool ModuleCollisions::Start()
{
	LoadData();

	return true;
}

ModuleCollisions::ModuleCollisions(bool active = true) : Module(active)
{
	debug = false;
}

ModuleCollisions::~ModuleCollisions()
{}

update_status ModuleCollisions::PreUpdate()
{
	for (auto it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_destroy)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else if ((*it)->to_detach)
		{
			it = colliders.erase(it);
		}
		else ++it;
	}
	return UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	Collider* c1;
	Collider* c2;

	for (auto it = colliders.begin(); it != colliders.end();)
	{
		c1 = *it;

		for (auto it2 = ++it; it2 != colliders.end(); ++it2)
		{
			c2 = *it2;

			if (c1->IsColliding(c2))
			{
				if (collision_matrix[c1->type][c2->type] && c1->callback != nullptr)
					c1->callback->OnCollision(c1, c2);

				if (collision_matrix[c2->type][c1->type] && c2->callback != nullptr)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		debug = !debug;

	if (debug)
	{
		for (auto it = colliders.begin(); it != colliders.end(); ++it)
		{
			Collider* col = *it;
			Uint8 alpha = 100;

			switch (col->type)
			{
			case COLLIDER_GROUND:
				App->renderer->DrawQuad(col->rect, 0, 0, 255, alpha);
				break;
			case COLLIDER_PLATFORM:
				App->renderer->DrawQuad(col->rect, 0, 255, 0, alpha);
				break;
			case COLLIDER_PLAYER_BODY:
				App->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
				break;
			case COLLIDER_PLAYER_ATTACK:
				App->renderer->DrawQuad(col->rect, 255, 255, 0, alpha);
				break;
			case COLLIDER_PLAYER_GROUND:
				App->renderer->DrawQuad(col->rect, 255, 0, 255, alpha);
				break;
			case COLLIDER_PLAYER_SHOT:
				App->renderer->DrawQuad(col->rect, 100, 100, 100, alpha);
				break;
			case COLLIDER_ENEMY:
				App->renderer->DrawQuad(col->rect, 128, 0, 128, alpha);
				break;
			case COLLIDER_DINO:
				App->renderer->DrawQuad(col->rect, 0, 128, 128, alpha);
				break;
			case COLLIDER_BORDER:
				App->renderer->DrawQuad(col->rect, 5, 10, 200, alpha);
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleCollisions::CleanUp()
{
	LOG("Detaching all colliders");

	for (auto& it : colliders) RELEASE(it);
	colliders.clear();

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Point offset, int frame_w, collider_type type, Module* callback = nullptr)
{
	Collider* ret = new Collider(rect, offset, frame_w, type, callback);
	colliders.push_back(ret);
	return ret;
}

void ModuleCollisions::AddCollider(Collider* collider)
{
	collider->to_detach = false;
	colliders.push_back(collider);
}

void ModuleCollisions::LoadData()
{
	Generic_data data;

	File player_data(DATA_MATRIX);

	while (player_data.GetMatrixInfo(data))
	{
		collision_matrix[data.val1][data.val2] = data.yes_no;
		collision_matrix[data.val2][data.val1] = data.yes_no;
	}
}