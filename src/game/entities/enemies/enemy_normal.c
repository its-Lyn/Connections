#include "game/entities/enemies/enemy_normal.h"

#include "engine/entity.h"
#include "engine/component.h"

entity* enemy_normal_create(Vector2 position, float speed, entity* princess) {
	entity* enemy_normal = entity_create(position, speed);
	entity_add_component(enemy_normal, rectangle_create((Vector2) {8, 8}, GREEN));
	entity_add_component(enemy_normal, constant_mover_create(speed, princess));

	return enemy_normal;
}
