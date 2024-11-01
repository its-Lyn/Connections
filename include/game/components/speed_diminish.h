#include "engine/component.h"

typedef struct {
	float deaccel;
} speed_diminish_data;

struct component* speed_diminish_create(float deaccel);

