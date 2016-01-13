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
	debug = false;
	LoadData();

	return true;
}

// detach (removes from list)
// or
// destroy (removes from list and deletes from memory)
// the colliders marked as to_detach or to_destroy
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
			(*it)->OnList = false;
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
			case COLLIDER_DETECT_GROUND:
				App->renderer->DrawQuad(col->rect, 255, 0, 255, alpha);
				break;
			case COLLIDER_PLAYER_SHOT:
				App->renderer->DrawQuad(col->rect, 0, 200, 50, alpha);
				break;
			case COLLIDER_ENEMY:
				App->renderer->DrawQuad(col->rect, 128, 0, 128, alpha);
				break;
			case COLLIDER_DINO:
				App->renderer->DrawQuad(col->rect, 0, 128, 128, alpha);
				break;
			case COLLIDER_PROXIMITY:
				App->renderer->DrawQuad(col->rect, 225, 70, 30, alpha);
				break;
			case COLLIDER_ITEM:
				App->renderer->DrawQuad(col->rect, 30, 70, 200, alpha);
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleCollisions::CleanUp()
{
	LOG("Destroying all colliders");

	for (auto& collider : colliders) 
		RELEASE(collider);
	
	colliders.clear();

	return true;
}

void ModuleCollisions::AddCollider(Collider* collider)
{
	collider->to_detach = false;
	collider->OnList = true;
	colliders.push_back(collider);
}

void ModuleCollisions::LoadData()
{
	GenericData data;

	File player_data(DATA_MATRIX);

	while (player_data.GetMatrixInfo(data))
	{
		collision_matrix[data.val1][data.val2] = data.yes_no;
		collision_matrix[data.val2][data.val1] = data.yes_no;
	}
}

bool ModuleCollisions::IsCollidingWithGround(Collider& me) const
{
	for (auto& collider : colliders)
	{
		if ((collider->type == COLLIDER_GROUND || collider->type == COLLIDER_PLATFORM) && 
			me.IsColliding(collider)) return true;
	}

	return false;
}