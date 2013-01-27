#include "AfterNote.h"

AfterNote::AfterNote()
{
	alive = false;
}


AfterNote::~AfterNote(void)
{
}

void AfterNote::respawn(int _type, int x, int y) {
	sprite_rects.clear();

	type = _type;

	//init bitmap
	add_sprite_rect("afterNotes",32*type,0,32,32);
	
	//set starting position
	setPosition(x * PX, y * PX);

	switch (type) {
	case 0:
		velocity.y = -16;
		break;
	case 1:
		velocity.y = 16;
		break;
	}

	alive = true;
}

void AfterNote::draw(void){
	if (alive) {
		Sprite::draw();
	}
}

void AfterNote::update(void){

	if (alive) {
		Sprite::update();

		if ((pos.y>>FPSH) < -32 || (pos.y>>FPSH) > 240) { //y offscreen -> death
			alive = false;
		}
	}
}

bool AfterNote::isAlive(void) {
	return alive;
}