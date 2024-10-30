#include "game/entities/princess.h"
#include "game/layers.h"

void on_panic_time_out(game_data* data) {
	// setting state to agitated to move around
	data->princess_state = STATE_AGITATED;
	data->princess_run_timer->timer.enabled = true; // restart timer to go back to calm
}

void on_run_time_out(game_data* data) {
	// Calm the woman down
	if (data->princess_state != STATE_AGITATED) return;
	data->princess_state = STATE_CALM;
	data->princess_timer->timer.enabled = true; // restart timer to go back to agitated
}

entity* princess_create(game_data* data, scene* s, Vector2 position, entity* player) {
	entity* princess = entity_create(position, PRINCESS_SPEED);

	entity_add_component(princess, rectangle_create((Vector2){8, 8}, PINK));
	entity_add_component(princess, connection_create(player, BROWN, 28.0f, 8.0f));
	entity_add_component(princess, princess_move_create(player));

	component* princess_collider = collider_create(s, (Vector2) {4, 4}, 5, LAYER_PRINCESS, LAYER_ENEMIES, NULL);
	entity_add_component(princess, princess_collider);

	// Add panic timer.
	data->princess_timer = timer_engine_create(4.0f, true, true, on_panic_time_out);

	// Add run timer.
	data->princess_run_timer = timer_engine_create(4.0f, false, true, on_run_time_out);

	entity_add_component(princess, data->princess_run_timer);
	entity_add_component(princess, data->princess_timer);

	data->princess_state = STATE_CALM;

	return princess;
}
