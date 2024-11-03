#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"
#include "engine/scenes/scene_utilities.h"

#include "game/game_data.h"
#include "game/entities/slash.h"
#include "game/entities/player.h"

static void update(component* c, game_data* data) {
	if (c->player_attack.cooldown->timer.enabled) return;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		data->shaking = true;

		data->duration = 0.06f;
		data->intensity = 1.0f;

		Vector2 pos = Vector2Add(data->player->pos, (Vector2){PLAYER_WIDTH/2, PLAYER_HEIGHT/2});
		scene_add_entity(data->main_scene, slash_create(data, pos, Vector2Normalize(Vector2Subtract(data->virt_mouse, pos))));

		c->player_attack.cooldown->timer.enabled = true;
		c->player_attack.cooldown->timer.timer = 0;
	} else if (IsKeyPressed(KEY_X) || IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) {
		data->shaking = true;

		data->duration = 0.06;
		data->intensity = 1.0f;

		Vector2 pos = Vector2Add(data->player->pos, (Vector2){PLAYER_WIDTH/2, PLAYER_HEIGHT/2});

		// get input dir
		float x = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
		float y = (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  - (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
		Vector2 dir = Vector2Normalize((Vector2){x, y});

		// only update direction if its not 0 (to attack in last pressed direction)
		if (!Vector2Equals(dir, (Vector2){0, 0})) c->player_attack.dir = dir;

		scene_add_entity(data->main_scene, slash_create(data, pos, c->player_attack.dir));

		c->player_attack.cooldown->timer.enabled = true;
		c->player_attack.cooldown->timer.timer = 0;
	}
}

// ew... wrong english
#include "game/colors.h"

#define HEIGHT 3
#define WIDTH 10

#define OFFSET_Y (HEIGHT + 3)
#define OFFSET_X 1
void player_attack_draw(component* c, game_data* data) {
	if (c->player_attack.cooldown->timer.timer == 0) return;

	// Background
	DrawRectangle(c->owner->pos.x - OFFSET_X, c->owner->pos.y - OFFSET_Y, WIDTH, HEIGHT, COLOR_RED);

	// Fill
	DrawRectangle(c->owner->pos.x - OFFSET_X, c->owner->pos.y - OFFSET_Y, (c->player_attack.cooldown->timer.timer / SLASH_COOLDOWN) * WIDTH, HEIGHT, COLOR_PINK);

	// Border
	DrawRectangleLines(c->owner->pos.x - OFFSET_X, c->owner->pos.y - OFFSET_Y, WIDTH, HEIGHT, COLOR_DARK_RED);
}

component* player_attack_create(entity* owner) {
	component* c = component_create(TYPE_PLAYER_ATTACK, update, player_attack_draw, NULL);

	component* cooldown = timer_engine_create(SLASH_COOLDOWN, false, true, NULL);
	entity_add_component(owner, cooldown);

	c->player_attack.dir = (Vector2){0, -1};
	c->player_attack.cooldown = cooldown;

	return c;
}

