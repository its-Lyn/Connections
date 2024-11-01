#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/components/rectangle.h"
#include "game/components/collider.h"
#include "game/components/bullet_mover.h"
#include "game/entities/bullet.h"
#include "game/entities/enemies/enemy_shoot.h"
#include "game/layers.h"
#include "game/colors.h"

// Nyaaa~
void on_bullet_collide(scene* s, component* self, component* other, game_data* data) {
	scene_queue_remove(s, self->owner);
}

entity* bullet_create(entity* target, Vector2 start_pos, float speed, game_data* data) {
	entity* bullet = entity_create(start_pos, speed);

	Vector2 dir = Vector2Normalize(Vector2Subtract(target->pos, start_pos));
	float rot = -Vector2Angle(dir, (Vector2){0, -1}) * RAD2DEG;

	component* sprite = create_animated_spritesheet(0.1f, (Vector2){2, 1}, (Vector2){2, 2}, false, LoadTexture("assets/bullet.png"), rot, (Vector2){2, 2});
	sprite->animated_spritesheet.enabled = true;
	entity_add_component(bullet, sprite);

	entity_add_component(bullet, bullet_mover_create(dir));
	entity_add_component(bullet, destroy_offscreen_create((Vector2){BULLET_WIDTH, BULLET_HEIGHT}));
	entity_add_component(bullet, collider_create(data->main_scene, (Vector2){2, 2}, 2, LAYER_ENEMIES, LAYER_PRINCESS | LAYER_SLASH | LAYER_PLAYER, on_bullet_collide));

	return bullet;
}
