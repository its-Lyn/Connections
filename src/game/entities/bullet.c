#include "engine/entity.h"
#include "engine/component.h"

#include "game/components/rectangle.h"
#include "game/components/bullet_mover.h"
#include "game/entities/bullet.h"

entity* bullet_create(entity* target, Vector2 start_pos, float speed) {
	entity* bullet = entity_create(start_pos, speed);
	entity_add_component(bullet, rectangle_create((Vector2){4, 4}, BLACK));
	entity_add_component(bullet, bullet_mover_create(target->pos, speed));

	return bullet;
}
