#include "engine/scenes/scene.h"
#include "engine/entity.h"
#include "engine/component.h"
#include "engine/utilities/rand.h"
#include "engine/scenes/scene_utilities.h"

#include "game/entities/enemies/enemy_shoot.h"
#include "game/components/bullet_handler.h"
#include "game/layers.h"

#include <raymath.h>

#include "game/components/enemy_health.h"
static void on_collision(scene* s, component* self, component* other, game_data* data) {
	if (other->collider.layer == LAYER_PLAYER) {
		// colliding with the player will push the enemy
		Vector2 dir = Vector2Normalize(Vector2Subtract(self->owner->pos, other->owner->pos));
		self->owner->vel = Vector2Scale(dir, SKULLBAT_PLAYER_KNOCKBACK);
		return;
	}

	component* timer = entity_get_component(self->owner, TYPE_TIMER);
	if (timer->timer.enabled) return;

	component* health = entity_get_component(self->owner, TYPE_ENEMY_HEALTH);
	health->enemy_health.hp--;
	if (health->enemy_health.hp <= 0) {
		data->score += 30;
		scene_queue_remove(s, self->owner);
	}

	timer->timer.timer = 0;
	timer->timer.enabled = true;

	//Vector2 dir = Vector2Normalize(Vector2Subtract(self->owner->pos, other->owner->pos));
	Vector2 dir = entity_get_component(other->owner, TYPE_BULLET_MOVER)->bullet_mover.direction;
	self->owner->vel = Vector2Scale(dir, SKULLBAT_KNOCKBACK);
}

entity* enemy_shoot_create(scene* s, Vector2 position, entity* princess) {
	float speed = rand_float(SKULLBAT_SPEED_MIN, SKULLBAT_SPEED_MAX);

	entity* enemy_shoot = entity_create(position, speed);

	entity_add_component(enemy_shoot, sprite_create("assets/skullbat.png", (Vector2){-2, 0}, WHITE, false, 0.0f, (Vector2){0, 0}));
	entity_add_component(enemy_shoot, constant_mover_create(SKULLBAT_ACCEL, princess));
	entity_add_component(enemy_shoot, mover_sprite_flip_create(enemy_shoot));

	entity_add_component(enemy_shoot, bullet_handler_create(BULLET_TIME, s, princess));

	entity_add_component(enemy_shoot, collider_create(s, (Vector2){5, 4}, 3, LAYER_ENEMIES, LAYER_SLASH | LAYER_PLAYER, on_collision));

	entity_add_component(enemy_shoot, timer_engine_create(SKULLBAT_IFRAMES, false, true, NULL));

	entity_add_component(enemy_shoot, enemy_health_create(SKULLBAT_HEALTH));

	return enemy_shoot;
}
