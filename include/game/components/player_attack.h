#include "engine/component.h"
#include "engine/entity.h"

typedef struct {
	Vector2 dir;
	struct component* cooldown;
} player_attack_data;

struct component* player_attack_create(struct entity* owner);

