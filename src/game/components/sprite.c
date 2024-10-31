#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"

#include "game/game_data.h"

static void destroy(component* c, game_data* data) {
	UnloadTexture(c->sprite.texture);
}

static void draw(component* c, game_data* data) {
	Rectangle src = (Rectangle){0, 0, c->sprite.texture.width * (c->sprite.fliph? -1 : 1), c->sprite.texture.height};
	DrawTextureRec(c->sprite.texture, src, Vector2Add(c->owner->pos, c->sprite.offset), c->sprite.tint);
}

component* sprite_create(const char* path, Vector2 offset, Color tint, bool fliph) {
	component* c = component_create(TYPE_SPRITE, NULL, draw, destroy);

	c->sprite.texture = LoadTexture(path);
	c->sprite.offset = offset;
	c->sprite.tint = tint;
	c->sprite.fliph = fliph;

	return c;
}

