#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "game/components/connection.h"
#include "game/entities/player.h"

#define ROPE_MIN_TENSION  10.0f
#define ROPE_MAX_TENSION 750.0f
#define PRINCESS_TENSION_RESISTANCE 1.5f

void connection_update(component* c, game_data* data) {
	entity* princess = c->owner;
	entity* player = c->connection.connected;

	float dist = Vector2Distance(princess->pos, player->pos);

	if (dist > c->connection.max_dist) {
		float stretch = (dist - c->connection.max_dist) / c->connection.leeway;
		Vector2 player_rope_dir = Vector2Normalize(Vector2Subtract(princess->pos, player->pos)); // rope direction from player
		Vector2 princess_rope_dir = Vector2Normalize(Vector2Subtract(player->pos, princess->pos)); // rope direction from princess

		// slowing down the player if they're going against the rope
		if (!Vector2Equals(player->vel, (Vector2){0, 0})) {
			Vector2 move_dir = Vector2Normalize(player->vel);
			float dir_attenuation = 1 - ((Vector2DotProduct(player_rope_dir, move_dir) + 1) / 2.0f); // 1 when going against the rope, 0 when going in it's direction
			player->speed = Lerp(PLAYER_MAX_SPEED, PLAYER_MIN_SPEED, stretch * dir_attenuation);
		}

		// rope is stretching, pull the entities together slightly
		  // - only pull player if they're not pressing anything
		if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_D) &&
		!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
				player->vel = Vector2Add(player->vel, Vector2Scale(player_rope_dir, Lerp(ROPE_MIN_TENSION, ROPE_MAX_TENSION, stretch) * GetFrameTime()));
		}

		  // - pulling princess
		princess->vel = Vector2Add(princess->vel, Vector2Scale(princess_rope_dir, Lerp(ROPE_MIN_TENSION, ROPE_MAX_TENSION, stretch)/PRINCESS_TENSION_RESISTANCE * GetFrameTime()));

		// updating distance after moving player
		float dist = Vector2Distance(princess->pos, player->pos);

		if (dist < c->connection.max_dist + c->connection.leeway) return;
		// no more leeway in the rope, start pulling

		if (data->princess_state == STATE_CALM) {
			// if the princess is calm, she is pulled to the player
			Vector2 diff = Vector2Subtract(princess->pos, player->pos);
			Vector2 dir = Vector2Normalize(diff);
			princess->pos = Vector2Add(player->pos, Vector2Scale(dir, c->connection.max_dist + c->connection.leeway));
		} else {
			// if the princess is agitated, the player is pulled to her
			Vector2 diff = Vector2Subtract(player->pos, princess->pos);
			Vector2 dir = Vector2Normalize(diff);
			player->pos = Vector2Add(princess->pos, Vector2Scale(dir, c->connection.max_dist + c->connection.leeway));
		}
	} else {
		player->speed = PLAYER_MAX_SPEED;
	}
}

void draw(component* c, game_data* data) {
	DrawLineV(Vector2AddValue(c->owner->pos, 4), Vector2AddValue(c->connection.connected->pos, 4), c->connection.connection_colour);
}

component* connection_create(entity* connected, Color colour, float max_dist, float leeway) {
	component* c = component_create(TYPE_CONNECTION, connection_update, draw, NULL);
	c->connection.connected = connected;
	c->connection.connection_colour = colour;
	c->connection.max_dist = max_dist;
	c->connection.leeway = leeway;

	return c;
}

