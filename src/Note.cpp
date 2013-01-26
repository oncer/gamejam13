#include "Note.h"
#include "Globals.h"

Note::Note()
{
	alive = false;
	anim_frame_duration=10;
	anim_frames = 3;
	anim = true;
}


Note::~Note(void)
{
}

void Note::respawn(int _pitch) {
	sprite_rects.clear();

	pitch = _pitch;

	//init bitmap
	add_sprite_rect("notes",0,32*pitch,32,32);
	add_sprite_rect("notes",32,32*pitch,32,32);
	add_sprite_rect("notes",64,32*pitch,32,32);
	
	//set starting position
	setPosition(pos_max_x * PX, (pitch + 1) * 16 * PX);

	velocity.x = -128;

	alive = true;
}

void Note::draw(void){
	if (alive) {
		Sprite::draw();
	}
}

void Note::update(void){

	if (alive) {
		Sprite::update();

		if ((pos.x>>FPSH) < pos_min_x) {
			alive = false;
			//note death
		}
		
		Stave& stave = g_game->getStave();
		if (stave.hitNote(*this)) {
			alive = false;
			std::cout << "hit note" << std::endl;
		}
	}
}

bool Note::isAlive(void) {
	return alive;
}
