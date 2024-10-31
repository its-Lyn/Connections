#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"

#include "game/game_data.h"

static void destroy(component* c, game_data* data) {
	UnloadTexture(c->sprite.texture);
}

static void draw(component* c, game_data* data) {
	DrawTextureV(c->sprite.texture, Vector2Add(c->owner->pos, c->sprite.offset), c->sprite.tint);
}

component* sprite_create(const char* path, Vector2 offset, Color tint) {
	component* c = component_create(TYPE_SPRITE, NULL, draw, destroy);

	c->sprite.texture = LoadTexture(path);
	c->sprite.offset = offset;
	c->sprite.tint = tint;

	return c;
}

