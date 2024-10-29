#pragma once

#include "engine/component.h"
#include "game/game_data.h"

#include <stdbool.h>

typedef struct {
	float timer;
	float timeout;

	bool enabled;
	bool one_shot;
	void (*on_timeout)(game_data*);
} timer_data;

struct component* timer_engine_create(float timeout, bool enabled, bool one_shot, void (*on_timeout)(game_data*));
