#include "engine/entity.h"
#include "engine/component.h"

#include "game/components/rectangle.h"
#include "game/components/collider.h"
#include "game/components/bullet_mover.h"
#include "game/entities/bullet.h"

#include "engine/scenes/scene_utilities.h"

#include "game/layers.h"

// Nyaaa~
void on_bullet_collide(scene* s, component* self, component* other, game_data* data) {
	scene_queue_remove(s, self->owner);
}

entity* bullet_create(entity* target, Vector2 start_pos, float speed, game_data* data) {
	entity* bullet = entity_create(start_pos, speed);
	entity_add_component(bullet, rectangle_create((Vector2){4, 4}, BLACK));
	entity_add_component(bullet, bullet_mover_create(target->pos, speed));
	entity_add_component(bullet, collider_create(data->main_scene, (Vector2){2, 2}, 3, LAYER_ENEMIES, LAYER_PRINCESS, on_bullet_collide));

	return bullet;
}
