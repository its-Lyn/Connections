#pragma once

#include "engine/entity.h"
#include "engine/component.h"

#include <raylib.h>

typedef struct {
	Texture2D texture;
	Vector2 frame_dimensions;
	Vector2 frame_count;
	Vector2 offset;

	Rectangle source;
	bool fliph;

	float rotation;
	Vector2 pivot;

	float speed;
	float timer;
	int frame;

	bool enabled;
	bool visible;
} animated_spritesheet_data;

struct component* create_animated_spritesheet(float speed_per_frame, Vector2 frame_count, Vector2 offset, bool fliph, Texture2D texture, float rotation, Vector2 pivot);
void animated_spritesheet_set_enabled(struct component* c, bool enabled);
