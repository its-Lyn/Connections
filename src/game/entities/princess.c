#include "game/entities/princess.h"

entity* princess_create(Vector2 position, entity* player) {
	entity* princess = entity_create((Vector2){20, 10}, 40.0f);
	entity_add_component(princess, rectangle_create((Vector2){8, 8}, PINK));
	entity_add_component(princess, connection_create(player, BROWN, 40.0f));
	entity_add_component(princess, princess_move_create(player));

	return princess;
}
