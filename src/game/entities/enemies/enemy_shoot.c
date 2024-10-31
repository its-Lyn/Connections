#include "engine/scenes/scene.h"
#include "engine/entity.h"
#include "engine/component.h"
#include "engine/utilities/rand.h"
#include "engine/scenes/scene_utilities.h"

#include "game/entities/enemies/enemy_shoot.h"
#include "game/components/bullet_handler.h"
#include "game/layers.h"

static void on_collision(scene* s, component* self, component* other, game_data* data) {
	scene_queue_remove(s, self->owner);
}

entity* enemy_shoot_create(scene* s, Vector2 position, entity* princess) {
	float speed = rand_float(SKULLBAT_SPEED_MIN, SKULLBAT_SPEED_MAX);

	entity* enemy_shoot = entity_create(position, speed);

	entity_add_component(enemy_shoot, sprite_create("assets/skullbat.png", (Vector2){-2, 0}, WHITE, false));
	entity_add_component(enemy_shoot, constant_mover_create(speed, princess));
	entity_add_component(enemy_shoot, mover_sprite_flip_create(enemy_shoot));

	entity_add_component(enemy_shoot, bullet_handler_create(1.5f, s, princess));

	entity_add_component(enemy_shoot, collider_create(s, (Vector2){5, 4}, 3, LAYER_ENEMIES, LAYER_SLASH, on_collision));

	return enemy_shoot;
}
