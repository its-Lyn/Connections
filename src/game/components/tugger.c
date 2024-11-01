#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"

#include "game/game_data.h"
#include "game/entities/player.h"

void update(component* c, game_data* data) {
	if (c->tugger.cooldown->timer.enabled || (!IsKeyPressed(KEY_SPACE) && !IsKeyPressed(KEY_Z))) return;
	// pressed tug button and isnt on cooldown

	// applying force to princess
	Vector2 tug_dir = Vector2Normalize(Vector2Subtract(data->player->pos, data->princess->pos));
	data->princess->vel = Vector2Add(data->princess->vel, Vector2Scale(tug_dir, PLAYER_TUG_FORCE));

	// stunning princess for a bit if she was agitated
	if (data->princess_state == STATE_AGITATED) {
		data->princess_state = STATE_CALM; // making her calm
		data->princess_run_timer->timer.enabled = false; // pausing timer that would end agitated state
		data->princess_stun_timer->timer.enabled = true; // starting timer to stun her temporarily
	}

	// restart cooldown
	c->tugger.cooldown->timer.enabled = true;
}

void tugger_draw(component* c, game_data* data) {
}

component* tugger_create(entity* player) {
	component* c = component_create(TYPE_TUGGER, update, tugger_draw, NULL);

	c->tugger.cooldown = timer_engine_create(PLAYER_TUG_COOLDOWN, false, true, NULL);

	entity_add_component(player, c->tugger.cooldown);

	return c;
}

