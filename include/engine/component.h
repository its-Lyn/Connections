#pragma once

struct component;

typedef enum {
	TYPE_LABEL = 0,
	TYPE_CONSTANT_MOVER,
	TYPE_RECTANGLE,
	TYPE_PLAYER_MOVE,
	TYPE_CONNECTION
} component_type;

#include "engine/entity.h"

#include "game/game_data.h"
#include "game/components/label.h"
#include "game/components/constant_mover.h"
#include "game/components/rectangle.h"
#include "game/components/player_move.h"
#include "game/components/connection.h"

typedef struct component {
	struct entity* owner;

	void (*update)(struct component*, game_data*);
	void (*draw)(struct component*, game_data*);
	void (*destroy)(struct component*, game_data*);

	component_type type;
	union {
		label_data label;
		constant_mover_data constant_mover;
		rectangle_data rectangle;
		connection_data connection;
	};
} component;

component* component_create(component_type type, void (*update)(component*, game_data*), void (*draw)(component*, game_data*), void (*destroy)(component*, game_data*));
void component_destroy(component* component, game_data* data);

