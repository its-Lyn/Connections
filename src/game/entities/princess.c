#include "game/entities/princess.h"

#include "game/layers.h"

entity* princess_create(scene* s, Vector2 position, entity* player) {
	entity* princess = entity_create((Vector2){20, 10}, 40.0f);
	entity_add_component(princess, rectangle_create((Vector2){8, 8}, PINK));
	entity_add_component(princess, connection_create(player, BROWN, 32.0f, 8.0f));
	entity_add_component(princess, princess_move_create(player));

	component* princess_collider = collider_create(s, (Vector2) {4, 4}, 5, LAYER_PRINCESS, LAYER_ENEMIES, NULL);
	entity_add_component(princess, princess_collider);

	return princess;
}
