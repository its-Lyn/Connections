#include "engine/scenes/scene.h"
#include "engine/entity.h"
#include "engine/component.h"

#include "game/components/bullet_handler.h"

entity* enemy_shoot_create(Vector2 position, float speed, scene* handler_scene, entity* princess) {
	entity* enemy_shoot = entity_create(position, speed);
	entity_add_component(enemy_shoot, sprite_create("assets/bat.png", (Vector2){-2, 0}, BLACK, false));
	entity_add_component(enemy_shoot, constant_mover_create(speed, princess));

	entity_add_component(enemy_shoot, bullet_handler_create(1.5f, handler_scene, princess));

	return enemy_shoot;
}
