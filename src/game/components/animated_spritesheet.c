#include "engine/entity.h"
#include "engine/component.h"

#include "game/components/animated_spritesheet.h"

#include <raymath.h>

void animated_spritesheet_update(component* c, game_data* data) {
	if (!c->animated_spritesheet.enabled) return;

	c->animated_spritesheet.timer += GetFrameTime();
	if (c->animated_spritesheet.timer >= c->animated_spritesheet.speed) {
		c->animated_spritesheet.timer = 0;

		c->animated_spritesheet.frame++;
		// Only on the X axis because I can't be fucked
		if (c->animated_spritesheet.frame >= c->animated_spritesheet.frame_count.x)
			c->animated_spritesheet.frame = 0;

		c->animated_spritesheet.source.x = c->animated_spritesheet.frame * c->animated_spritesheet.frame_dimensions.x;
	}
}

void animated_spritesheet_draw(component* c, game_data* data) {
	if (!c->animated_spritesheet.visible) return;

	c->animated_spritesheet.source.width = c->animated_spritesheet.fliph ? -c->animated_spritesheet.frame_dimensions.x : c->animated_spritesheet.frame_dimensions.x;

	Vector2 pos = Vector2Add(c->owner->pos, c->animated_spritesheet.offset);
	Rectangle dst = (Rectangle){pos.x, pos.y, c->animated_spritesheet.frame_dimensions.x, c->animated_spritesheet.frame_dimensions.y};

	DrawTexturePro(c->animated_spritesheet.texture, c->animated_spritesheet.source, dst, c->animated_spritesheet.pivot, c->animated_spritesheet.rotation, WHITE);
}

void animated_spritesheet_destroy(component* c, game_data* data) {
	UnloadTexture(c->animated_spritesheet.texture);
}

void animated_spritesheet_set_enabled(component* c, bool enabled) {
	if (!enabled) {
		c->animated_spritesheet.timer = 0;
		c->animated_spritesheet.frame = 0;

		c->animated_spritesheet.source.x = c->animated_spritesheet.frame * c->animated_spritesheet.frame_dimensions.x;
	}

	c->animated_spritesheet.enabled = enabled;
}

component* create_animated_spritesheet(float speed_per_frame, Vector2 frame_count, Vector2 offset, bool fliph, Texture2D texture, float rotation, Vector2 pivot) {
	component* spritesheet = component_create(TYPE_ANIMATED_SPRITESHEET, animated_spritesheet_update, animated_spritesheet_draw, animated_spritesheet_destroy);
	spritesheet->animated_spritesheet.enabled = false;

	spritesheet->animated_spritesheet.frame_count = frame_count;
	spritesheet->animated_spritesheet.texture = texture;
	spritesheet->animated_spritesheet.speed = speed_per_frame;

	spritesheet->animated_spritesheet.offset = offset;
	spritesheet->animated_spritesheet.fliph = fliph;

	spritesheet->animated_spritesheet.rotation = rotation;
	spritesheet->animated_spritesheet.pivot = pivot;

	spritesheet->animated_spritesheet.frame = 0;
	spritesheet->animated_spritesheet.timer = 0;

	spritesheet->animated_spritesheet.frame_dimensions = (Vector2) {
		texture.width  / frame_count.x,
		texture.height / frame_count.y
	};

	spritesheet->animated_spritesheet.source = (Rectangle) {
		0, 0,
		spritesheet->animated_spritesheet.frame_dimensions.x,
		spritesheet->animated_spritesheet.frame_dimensions.y
	};

	spritesheet->animated_spritesheet.visible = true;

	return spritesheet;
}
