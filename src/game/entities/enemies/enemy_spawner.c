#include "game/entities/enemies/enemy_spawner.h"

#include <raylib.h>
#include <raymath.h>

entity* enemy_spawner_create() {
	return entity_create(Vector2Zero(), 0);
}
