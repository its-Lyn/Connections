#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "game/components/princess_move.h"
#include "game/entities/princess.h"

void princess_move_update(component* c, game_data* data) {
	if (data->princess_state == STATE_CALM) {
		// princess is calm - direction is 0,0
		c->princess_move.dir = Vector2Zero();
	} else if (Vector2Equals(c->princess_move.dir, Vector2Zero())) {
		// We have not picked a new direction yet.
		float angle = ((float)rand() / (float)RAND_MAX) * 2.0f * PI;
		c->princess_move.dir = (Vector2) { sin(angle), cos(angle) };
	} else {
		// We already picked a direction, redirect based on player's pulling
		Vector2 vel_dir = Vector2Normalize(c->owner->vel);
		float t = Clamp(PRINCESS_PULL_INFLUENCE * GetFrameTime(), 0, 1);
		Vector2 influenced_dir = Vector2Lerp(c->princess_move.dir, vel_dir, t);
		c->princess_move.dir = Vector2Normalize(influenced_dir);
	}

	// update sprite direction
	c->princess_move.sprite->sprite.fliph = (c->princess_move.dir.x > 0.0f) || (c->princess_move.dir.x == 0.0f && c->princess_move.sprite->sprite.fliph);

	// Clamp the princess position inside the screen and bounce on the edges
	Vector2 pos = c->owner->pos;
	if (pos.x < 0) {
		c->princess_move.dir.x *= -1;
		c->owner->vel.x *= -0.5;
		c->owner->pos.x = 0;
	} else if (pos.x > data->game_size.x - 8) {
		c->princess_move.dir.x *= -1;
		c->owner->vel.x *= -1;
		c->owner->pos.x = data->game_size.x - 8;
	}

	if (pos.y < 0) {
		c->princess_move.dir.y *= -1;
		c->owner->vel.y *= -0.5;
		c->owner->pos.y = 0;
	} else if (pos.y > data->game_size.y - 8) {
		c->princess_move.dir.y *= -1;
		c->owner->vel.y *= -0.5;
		c->owner->pos.y = data->game_size.y - 8;
	}

	Vector2 goal_vel = Vector2Scale(c->princess_move.dir, c->owner->speed);
	c->owner->vel = Vector2MoveTowards(c->owner->vel, goal_vel, PRINCESS_ACCEL * GetFrameTime());
}

component* princess_move_create(entity* princess, entity* player) {
	component* c = component_create(TYPE_PRINCESS_MOVE, princess_move_update, NULL, NULL);

	c->princess_move.player = player;
	c->princess_move.dir = Vector2Zero();
	c->princess_move.sprite = entity_get_component(princess, TYPE_SPRITE);

	return c;
}
