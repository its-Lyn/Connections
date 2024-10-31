#pragma once

#include <raylib.h>

#include "engine/scenes/scene.h"
#include "engine/entity.h"

struct entity* enemy_shoot_create(Vector2 position, float speed, struct scene* handler_scene, struct entity* princess);
