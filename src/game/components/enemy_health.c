#include "engine/component.h"
#include "engine/entity.h"

#include "game/components/enemy_health.h"

component* enemy_health_create(int hp) {
	component* enemy_health = component_create(TYPE_ENEMY_HEALTH, NULL, NULL, NULL);
	enemy_health->enemy_health.hp = hp;

	return enemy_health;
}
