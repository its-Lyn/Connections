#include "engine/entity.h"
#include "engine/component.h"
#include "game/components/connection.h"

#include <raymath.h>

#include <stdio.h>

void update(component* c, game_data* data) {
    float dist = Vector2Distance(c->owner->pos, c->connection.connected->pos);
    if (dist > c->connection.max_dist) {
        c->connection.connected->speed = 20;

        c->owner->pos = Vector2MoveTowards(c->owner->pos, c->connection.connected->pos, c->owner->speed);
    }
    else {
        c->connection.connected->speed = 100;
    }
}

void draw(component* c, game_data* data) {
    DrawLineV(Vector2AddValue(c->owner->pos, 4), Vector2AddValue(c->connection.connected->pos, 4), c->connection.connection_colour);
}

component* connection_create(entity* connected, Color colour, float max_dist) {
    component* c = component_create(TYPE_CONNECTION, update, draw, NULL);
    c->connection.connected = connected;
    c->connection.connection_colour = colour;
    c->connection.max_dist = max_dist;

    return c;
}
