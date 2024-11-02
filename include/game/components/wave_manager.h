#pragma once

#include "engine/component.h"
#include "engine/entity.h"

#include "game/entities/enemies/enemy_spawner.h"

typedef struct {
	float wave_length;
	float spawn_time;
	float double_chance;
	float shooter_chance;
} wave_data;

typedef struct {
	int curr_wave;
	wave_data waves[ENEMY_SPAWN_WAVE_COUNT];
} wave_manager_data;

struct component* wave_manager_create(struct entity* owner);

