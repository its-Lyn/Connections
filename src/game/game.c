#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/scenes/scene.h"
#include "engine/scenes/scene_utilities.h"
#include "engine/entity.h"
#include "engine/component.h"

#include "game/game.h"
#include "game/scenes/game_scene.h"
#include "game/scenes/main_menu.h"
#include "game/components/label.h"
#include "game/entities/enemies/enemy_spawner.h"

void init(game_data* data) {
	// initializing all to 0 to make sure no values are left uninitialized
	memset(data, 0, sizeof(game_data));

	// Set random seed
	srand(time(NULL));

	data->game_size = (Vector2) { 128, 128 };
	data->game_scale = 0.0f;
	data->virt_mouse = (Vector2) { 0,  0 };

	data->renderer = LoadRenderTexture(data->game_size.x, data->game_size.y);

	data->main_scene = main_menu_create(data);

	data->bg_texture = LoadTexture("assets/bg.png");
	data->waves_texture = LoadTexture("assets/waves.png");
	data->waves_frame_h = data->waves_texture.height / ENEMY_SPAWN_WAVE_COUNT;

	data->score = 0;
	data->high_score = 0;
	data->drawn_score = 0;
	data->score_measure = MeasureText("0", 10);
	data->score_text = malloc(sizeof(char) * 2);
	memcpy(data->score_text, "0", 2);

	data->tutorial0_texture = LoadTexture("assets/bg-tutorial0.png");
	data->tutorial1_texture = LoadTexture("assets/bg-tutorial1.png");

	data->is_paused = false;
	data->can_pause = false;

	data->end = false;

	Camera2D game_camera = { 0 };
	game_camera.target = Vector2Zero();
	game_camera.offset = Vector2Zero();

	game_camera.rotation = 0;
	game_camera.zoom = 1.0f;

	data->game_camera = game_camera;
	data->shaking = false;
	data->magnitude = 1.0f;
	data->intensity = 0;
	data->shake_offset = Vector2Zero();
	data->duration = 0.3f;
}

void process(game_data* data) {
	// Calculate scale
	data->game_scale = fmin(
		(float)GetScreenWidth() / data->game_size.x,
		(float)GetScreenHeight() / data->game_size.y
	);

	// Calculate virtual mouse position
	Vector2 mouse = GetMousePosition();
	data->virt_mouse.x = (mouse.x - (GetScreenWidth() - (data->game_size.x * data->game_scale)) * 0.5f) / data->game_scale;
	data->virt_mouse.y = (mouse.y - (GetScreenHeight() - (data->game_size.y * data->game_scale)) * 0.5f) / data->game_scale;

	// Stop calculating once the mouse leaves the game world.
	data->virt_mouse = Vector2Clamp(data->virt_mouse, (Vector2){ 0, 0 }, (Vector2){ (float)data->game_size.x, (float)data->game_size.y });

	scene_update_entities(data->main_scene, data);
}

#include "game/colors.h"
void render(game_data* data) {
	// This is where we draw inside the game world
	BeginTextureMode(data->renderer);
		ClearBackground(COLOR_GREEN);
		BeginMode2D(data->game_camera);
			scene_draw_entities(data->main_scene, data);
		EndMode2D();
	EndTextureMode();

	// This is where we draw inside the screen world
	BeginDrawing();
		ClearBackground(COLOR_BROWN);

		// Draw the render texture.
		// PARAMS
		// Texture, Source Rect, Dest Rect, Origin, Rotation and Tint.
		DrawTexturePro(
			data->renderer.texture,
			(Rectangle) {
				0.0f,
				0.0f,
				(float)data->renderer.texture.width,
				(float)-data->renderer.texture.height
			},
			(Rectangle) {
				(GetScreenWidth() - (data->game_size.x * data->game_scale)) * 0.5f,
				(GetScreenHeight() - ((float)data->game_size.y * data->game_scale)) * 0.5f,
				data->game_size.x * data->game_scale,
				data->game_size.y * data->game_scale
			},
			(Vector2) { 0, 0 },
			0.0f,
			WHITE
		);
	EndDrawing();
}

void kill(game_data* data) {
	// Unload the game window renderer
	UnloadRenderTexture(data->renderer);

	// Unload textures
	UnloadTexture(data->bg_texture);
	UnloadTexture(data->waves_texture);

	// freeing score text
	free(data->score_text);

	// unloading tutorial textures
	UnloadTexture(data->tutorial0_texture);
	UnloadTexture(data->tutorial1_texture);

	scene_destroy(data->main_scene, data);
	free(data);
}
