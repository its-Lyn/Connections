#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "game/components/connection.h"
#include "game/entities/player.h"

void connection_update(component* c, game_data* data) {
	entity* princess = c->owner;
	entity* player = c->connection.connected;

	float dist = Vector2Distance(princess->pos, player->pos);

	if (dist > c->connection.max_dist) {
		// slowing down the player if they're going against the rope
		if (!Vector2Equals(player->vel, (Vector2){0, 0})) {
			Vector2 rope_dir = Vector2Normalize(Vector2Subtract(princess->pos, player->pos));
			Vector2 move_dir = Vector2Normalize(player->vel);
			player->speed = Lerp(PLAYER_MIN_SPEED, PLAYER_MAX_SPEED, (Vector2DotProduct(rope_dir, move_dir) + 1.0f)/2.0f);
		}

		if (dist < c->connection.max_dist + c->connection.leeway) {
			// rope is stretching, pull the entities together slightly

			return;
		}

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

