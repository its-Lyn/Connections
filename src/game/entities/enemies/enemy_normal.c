#include "engine/entity.h"
#include "engine/component.h"
#include "engine/utilities/rand.h"

#include "game/layers.h"
#include "game/entities/enemies/enemy_normal.h"

entity* enemy_normal_create(scene* s, Vector2 position, entity* princess) {
	float speed = rand_float(BAT_SPEED_MIN, BAT_SPEED_MAX);

	entity* enemy_normal = entity_create(position, speed);

	entity_add_component(enemy_normal, sprite_create("assets/bat.png", (Vector2){-2, 0}, WHITE, false));
	entity_add_component(enemy_normal, constant_mover_create(speed, princess));
	entity_add_component(enemy_normal, collider_create(s, (Vector2){5, 4}, 3, LAYER_ENEMIES, 0, NULL));

	return enemy_normal;
}
