#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/scenes/game_scene.h"
#include "game/entities/player.h"
#include "game/entities/princess.h"

#include "game/components/timer.h"

void on_panic_time_out(game_data* data) {
	// 1/3 chance for the princess to get agitated.
	if (rand() % 4 == 0) data->princess_state = STATE_AGITATED;
}

void on_run_time_out(game_data* data) {
	// Calm the woman down
	if (data->princess_state == STATE_AGITATED) data->princess_state = STATE_CALM;
}

void game_process(scene *game_scene, game_data *data) {
}

void game_render(scene* game_scene, game_data* data) {
}

scene* game_scene_create(game_data* data) {
	scene* s = scene_create(game_process, game_render);

	// creating player and adding to scene
	entity* player = player_create((Vector2){0, 0});
	scene_add_entity(s, player);

	// Princess
	entity* princess = princess_create((Vector2){20, 10}, player);

	// Add panic timer.
	data->princess_timer = timer_engine_create(2.0f, true, false, on_panic_time_out);
	data->princess_state = STATE_CALM;

	// Add run imer.
	data->princess_run_timer = timer_engine_create(1.5f, false, true, on_run_time_out);

	entity_add_component(princess, data->princess_run_timer);
	entity_add_component(princess, data->princess_timer);

	scene_add_entity(s, princess);

	return s;
}

