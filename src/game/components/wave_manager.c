#include <stdbool.h>

#include "engine/component.h"
#include "engine/entity.h"

#include "game/game_data.h"
#include "game/entities/enemies/enemy_spawner.h"

static void on_wave_change(component* timer, game_data* data) {
	component* c = entity_get_component(timer->owner, TYPE_WAVE_MANAGER);

	// increment wave
	if (++c->wave_manager.curr_wave >= ENEMY_SPAWN_WAVE_COUNT - 1) {
		// disable wave change timer if its the last wave
		timer->timer.enabled = false;
	} else {
		// otherwise, set new time until next wave
		timer->timer.timeout = c->wave_manager.waves[c->wave_manager.curr_wave].wave_length;
	}
}

component* wave_manager_create(entity* owner) {
	component* c = component_create(TYPE_WAVE_MANAGER, NULL, NULL, NULL);

	c->wave_manager.curr_wave = 0;
	c->wave_manager.waves[0] = (wave_data){
		.wave_length    = 14.0f,
		.spawn_time     =  5.0f,
		.double_chance  =  0.1f,
		.shooter_chance =  0.0f,
	};
	c->wave_manager.waves[1] = (wave_data){
		.wave_length    = 16.0f,
		.spawn_time     =  3.0f,
		.double_chance  =  0.2f,
		.shooter_chance =  0.0f,
	};
	c->wave_manager.waves[2] = (wave_data){
		.wave_length    = 30.0f,
		.spawn_time     =  3.0f,
		.double_chance  =  0.3f,
		.shooter_chance =  0.2f,
	};
	c->wave_manager.waves[3] = (wave_data){
		.wave_length    = 30.0f,
		.spawn_time     =  2.0f,
		.double_chance  =  0.4f,
		.shooter_chance =  0.3f,
	};
	c->wave_manager.waves[4] = (wave_data){
		.wave_length    = 30.0f,
		.spawn_time     =  1.0f,
		.double_chance  =  0.5f,
		.shooter_chance =  0.4f,
	};

	entity_add_component(owner, timer_engine_create(c->wave_manager.waves[0].wave_length, true, false, on_wave_change));

	return c;
}

