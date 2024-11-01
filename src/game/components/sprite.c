#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"

#include "game/game_data.h"

static void destroy(component* c, game_data* data) {
	UnloadTexture(c->sprite.texture);
}

static void draw(component* c, game_data* data) {
	Vector2 pos = Vector2Add(c->owner->pos, c->sprite.offset);
	Vector2 size = (Vector2){c->sprite.texture.width, c->sprite.texture.height};

	Rectangle src = (Rectangle){0, 0, size.x * (c->sprite.fliph? -1 : 1), size.y};
	Rectangle dst = (Rectangle){pos.x, pos.y, size.x, size.y};

	DrawTexturePro(c->sprite.texture, src, dst, c->sprite.pivot, c->sprite.rotation, c->sprite.tint);
}

component* sprite_create(const char* path, Vector2 offset, Color tint, bool fliph, float rotation, Vector2 pivot) {
	component* c = component_create(TYPE_SPRITE, NULL, draw, destroy);

	c->sprite.texture = LoadTexture(path);
	c->sprite.offset = offset;
	c->sprite.tint = tint;
	c->sprite.fliph = fliph;
	c->sprite.rotation = rotation;
	c->sprite.pivot = pivot;

	return c;
}

