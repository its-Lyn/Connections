#include <raylib.h>
#include <raymath.h>

#include "engine/scenes/scene.h"
#include "engine/scenes/scene_utilities.h"

#include "game/game.h"
#include "game/entities/princess.h"
#include "game/layers.h"
#include "game/scenes/game_scene.h"
#include "game/colors.h"

#include "game/scenes/end_screen.h"

void on_panic_time_out(component* _timer, game_data* data) {
	// setting state to agitated to move around
	data->princess_state = STATE_AGITATED;
	data->princess_run_timer->timer.enabled = true; // restart timer to go back to calm
}

void on_run_time_out(component* _timer, game_data* data) {
	// Calm the woman down
	if (data->princess_state != STATE_AGITATED) return;
	data->princess_state = STATE_CALM;
	data->princess_timer->timer.enabled = true; // restart timer to go back to agitated
}

void on_collided(scene* s, component* self, component* other, game_data* data) {
	if (!data->princess_iframe->timer.enabled) {
		// damage
		data->princess_lives--;
		if (data->princess_lives <= 0) {
			// NYAhhhah
			data->can_pause = false;
			scene_change(data->main_scene, end_screen_create(data));
			return;
		}

		// Shake
		data->shaking = true;

		data->duration = 0.3f;
		data->intensity = 1.0f;

		// iframes
		data->princess_iframe->timer.timer = 0;
		data->princess_iframe->timer.enabled = true;

		// Begin flash
		data->princess_flash_sprite->animated_spritesheet.visible  = true;
		data->princess_normal_sprite->animated_spritesheet.visible = false;

		data->princess_flash_timer->timer.enabled = true;

		// knockback
		Vector2 dir = Vector2Normalize(Vector2Subtract(self->owner->pos, other->owner->pos));
		self->owner->vel = Vector2Scale(dir, PRINCESS_KNOCKBACK);
	}
}

void on_iframe_time_out(component* _timer, game_data* data) {}

void on_flash_time_out(component* c, game_data* data) {
	data->princess_flash_sprite->animated_spritesheet.visible  = false;
	data->princess_normal_sprite->animated_spritesheet.visible = true;
}

entity* princess_create(game_data* data, scene* s, Vector2 position, entity* player) {
	entity* princess = entity_create(position, PRINCESS_SPEED);

	// SpriteSheet Data.
	data->princess_flash_sprite  = create_animated_spritesheet(0.25f, (Vector2){2, 1}, (Vector2){-2, -4}, false, LoadTexture("assets/princess_flash.png"), 0.0f, (Vector2){0, 0});
	data->princess_flash_sprite->animated_spritesheet.enabled = true;
	data->princess_flash_sprite->animated_spritesheet.visible = false;

	data->princess_normal_sprite = create_animated_spritesheet(0.25f, (Vector2){2, 1}, (Vector2){-2, -4}, false, LoadTexture("assets/princess.png"), 0.0f, (Vector2){0, 0});

	entity_add_component(princess, data->princess_normal_sprite);
	entity_add_component(princess, data->princess_flash_sprite);

	// Flash timer
	data->princess_flash_timer = timer_engine_create(0.15f, false, true, on_flash_time_out);
	entity_add_component(princess, data->princess_flash_timer);

	entity_add_component(princess, connection_create(player, COLOR_BROWN, 24.0f, 6.0f));
	entity_add_component(princess, princess_move_create(princess, player, data->princess_normal_sprite, data->princess_flash_sprite));

	component* princess_collider = collider_create(s, (Vector2) {4, 4}, 4, LAYER_PRINCESS, LAYER_ENEMIES, on_collided);
	entity_add_component(princess, princess_collider);

	// Add panic timer.
	data->princess_timer = timer_engine_create(PRINCESS_CALM_TIME, true, true, on_panic_time_out);

	// Add run timer.
	data->princess_run_timer = timer_engine_create(PRINCESS_AGITATED_TIME, false, true, on_run_time_out);

	// Add stun timer (when tugged)
	data->princess_stun_timer = timer_engine_create(PRINCESS_STUN_TIME, false, true, on_panic_time_out);

	// Add iframes
	data->princess_iframe = timer_engine_create(1.0f, false, true, on_iframe_time_out);

	entity_add_component(princess, data->princess_run_timer);
	entity_add_component(princess, data->princess_timer);
	entity_add_component(princess, data->princess_stun_timer);
	entity_add_component(princess, data->princess_iframe);

	data->princess_state = STATE_CALM;

	return princess;
}
