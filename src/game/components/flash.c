#include "engine/component.h"

#include "game/components/flash.h"

void flash_update(component* c, game_data* data) {
	switch (c->flash.state) {
		case FLASH_FADE_IN:
			c->flash.alpha += c->flash.speed * GetFrameTime();
			if (c->flash.alpha >= 1) {
				c->flash.alpha = 1;
				c->flash.state = FLASH_FADE_OUT;
			}
			break;

		case FLASH_FADE_OUT:
			c->flash.alpha -= c->flash.speed * GetFrameTime();
			if (c->flash.alpha <= 0) {
				c->flash.alpha = 0;
				c->flash.state = FLASH_FADE_IN;

				c->flash.flashing = false;
			}
			break;
	}
}

component* flash_create(Color colour, Rectangle size, float speed) {
	component* flash = component_create(TYPE_FLASH, flash_update, NULL, NULL);
	flash->flash.alpha = 0;
	flash->flash.colour = colour;
	flash->flash.flashing = false;
	flash->flash.size = size;
	flash->flash.speed = speed;
	flash->flash.state = FLASH_FADE_IN;

	return flash;
}
