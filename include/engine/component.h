#pragma once

struct component;

typedef enum {
	TYPE_LABEL = 0,
	TYPE_CONSTANT_MOVER,
	TYPE_RECTANGLE,
	TYPE_PLAYER_MOVE,
	TYPE_PRINCESS_MOVE,
	TYPE_CONNECTION,
	TYPE_TIMER,
	TYPE_COLLIDER,
	TYPE_TUGGER,
	TYPE_SPRITE,
} component_type;

#include "engine/entity.h"

#include "game/game_data.h"
#include "game/components/label.h"
#include "game/components/constant_mover.h"
#include "game/components/rectangle.h"
#include "game/components/player_move.h"
#include "game/components/connection.h"
#include "game/components/timer.h"
#include "game/components/princess_move.h"
#include "game/components/collider.h"
#include "game/components/tugger.h"
#include "game/components/sprite.h"

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
		player_move_data player_move;
		princess_move_data princess_move;
		connection_data connection;
		timer_data timer;
		collider_data collider;
		tugger_data tugger;
		sprite_data sprite;
	};
} component;

component* component_create(component_type type, void (*update)(component*, game_data*), void (*draw)(component*, game_data*), void (*destroy)(component*, game_data*));
void component_destroy(component* component, game_data* data);

