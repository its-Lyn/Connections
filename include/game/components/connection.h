#pragma once

#include <stdlib.h>

#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"

typedef struct {
    struct entity* connected;
    Color connection_colour;

    float max_dist;
    float leeway;
} connection_data;

struct component* connection_create(struct entity* connected, Color colour, float max_dist, float leeway);
