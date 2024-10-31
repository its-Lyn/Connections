#include <stdbool.h>

#include <raylib.h>

#include "engine/component.h"

typedef struct {
	Texture2D texture;
	Vector2 offset;
	Color tint;
	bool fliph;
} sprite_data;

struct component* sprite_create(const char* filename, Vector2 offset, Color tint, bool fliph);
