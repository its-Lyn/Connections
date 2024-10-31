#include "engine/scenes/scene.h"
#include "engine/scenes/scene_utilities.h"
#include "engine/component.h"
#include "engine/entity.h"

#include "engine/utilities/rand.h"

#include "game/entities/bullet.h"
#include "game/components/bullet_handler.h"

#include <raylib.h>

void bullet_handler_update(component* c, game_data* data) {
	c->bullet_handler.bullet_timer += GetFrameTime();
	if (c->bullet_handler.bullet_timer >= c->bullet_handler.buller_timeout) {
		c->bullet_handler.bullet_timer = 0;

		if (rand_int(0, 2) == 1)
			scene_add_entity(c->bullet_handler.handler_scene, bullet_create(c->bullet_handler.princess, c->owner->pos, 100.0f, data));
	}
}

component* bullet_handler_create(float bullet_timeout, scene* handler_scene, entity* princess) {
	component* bullet_handler = component_create(TYPE_BULLET_HANDLER, bullet_handler_update, NULL, NULL);
	bullet_handler->bullet_handler.bullet_timer = 0;
	bullet_handler->bullet_handler.buller_timeout = bullet_timeout;

	bullet_handler->bullet_handler.princess = princess;
	bullet_handler->bullet_handler.handler_scene = handler_scene;

	return bullet_handler;
}
