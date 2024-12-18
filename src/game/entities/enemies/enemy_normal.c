#include "engine/entity.h"
#include "engine/component.h"
#include "engine/utilities/rand.h"
#include "engine/scenes/scene_utilities.h"

#include "game/layers.h"
#include "game/entities/enemies/enemy_normal.h"

#include <raymath.h>

#include "game/components/enemy_health.h"
static void on_collision(scene* s, component* self, component* other, game_data* data) {
	if (other->collider.layer == LAYER_PLAYER) {
		// colliding with the player will push the enemy
		Vector2 dir = Vector2Normalize(Vector2Subtract(self->owner->pos, other->owner->pos));
		self->owner->vel = Vector2Scale(dir, BAT_PLAYER_KNOCKBACK);
		return;
	}

	component* timer = entity_get_component(self->owner, TYPE_TIMER);
	if (timer->timer.enabled) return;

	component* health = entity_get_component(self->owner, TYPE_ENEMY_HEALTH);
	health->enemy_health.hp--;
	if (health->enemy_health.hp <= 0) {
		data->score += 15;
		scene_queue_remove(s, self->owner);
	}

	timer->timer.timer = 0;
	timer->timer.enabled = true;

	//Vector2 dir = Vector2Normalize(Vector2Subtract(self->owner->pos, other->owner->pos));
	Vector2 dir = entity_get_component(other->owner, TYPE_BULLET_MOVER)->bullet_mover.direction;
	self->owner->vel = Vector2Scale(dir, BAT_KNOCKBACK);
}

entity* enemy_normal_create(scene* s, Vector2 position, entity* princess) {
	float speed = rand_float(BAT_SPEED_MIN, BAT_SPEED_MAX);

	entity* enemy_normal = entity_create(position, speed);

	entity_add_component(enemy_normal, sprite_create("assets/bat.png", (Vector2){-2, 0}, WHITE, false, 0.0f, (Vector2){0, 0}));
	entity_add_component(enemy_normal, constant_mover_create(BAT_ACCEL, princess));
	entity_add_component(enemy_normal, mover_sprite_flip_create(enemy_normal));
	entity_add_component(enemy_normal, collider_create(s, (Vector2){5, 4}, 3, LAYER_ENEMIES, LAYER_SLASH | LAYER_PLAYER, on_collision));

	entity_add_component(enemy_normal, timer_engine_create(BAT_IFRAMES, false, true, NULL));

	entity_add_component(enemy_normal, enemy_health_create(BAT_HEALTH));
	return enemy_normal;
}
