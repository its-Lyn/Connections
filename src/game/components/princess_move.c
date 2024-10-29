#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "game/components/princess_move.h"

#define PRINCESS_RUN 80

void princess_move_update(component* c, game_data* data) {
	// We are agitated
	if (data->princess_state == STATE_AGITATED) {
		// We have not picked a new direction yet.
		if (Vector2Equals(c->princess_move.dir, Vector2Zero())) {
			float angle = ((float)rand() / (float)RAND_MAX) * 2.0f * PI;
			c->princess_move.dir = (Vector2) { sin(angle), cos(angle) };

			data->princess_run_timer->timer.enabled = true;
		}

		c->owner->pos.x += c->princess_move.dir.x * PRINCESS_RUN * GetFrameTime();
		c->owner->pos.y += c->princess_move.dir.y * PRINCESS_RUN * GetFrameTime();

		// Clamp the princess position inside the screen
		c->owner->pos.x = Clamp(c->owner->pos.x, 0, data->game_size.x - 8);
		c->owner->pos.y = Clamp(c->owner->pos.y, 0, data->game_size.y - 8);

		// Move the player towards the princess.
		c->princess_move.player->pos = Vector2MoveTowards(c->princess_move.player->pos, c->owner->pos, 40 * GetFrameTime());
	} else if (data->princess_state == STATE_CALM && !Vector2Equals(c->princess_move.dir, Vector2Zero())) {
		c->princess_move.dir = Vector2Zero();
	}
}

component* princess_move_create(entity* player) {
	component* c = component_create(TYPE_PRINCESS_MOVE, princess_move_update, NULL, NULL);
	c->princess_move.player = player;
	c->princess_move.dir = Vector2Zero();

	return c;
}
