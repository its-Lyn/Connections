#include "engine/scenes/scene.h"
#include "engine/entity.h"
#include "engine/component.h"

#include "game/components/bullet_handler.h"
#include "game/layers.h"

entity* enemy_shoot_create(scene* s, Vector2 position, float speed, scene* handler_scene, entity* princess) {
	entity* enemy_shoot = entity_create(position, speed);

	entity_add_component(enemy_shoot, sprite_create("assets/bat.png", (Vector2){-2, 0}, BLACK, false));
	entity_add_component(enemy_shoot, constant_mover_create(speed, princess));

	entity_add_component(enemy_shoot, bullet_handler_create(1.5f, handler_scene, princess));

	entity_add_component(enemy_shoot, collider_create(s, (Vector2){5, 4}, 3, LAYER_ENEMIES, 0, NULL));

	return enemy_shoot;
}
