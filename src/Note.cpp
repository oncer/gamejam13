#include "Note.h"
#include "Globals.h"

Note::Note()
{
	alive = false;
	anim_frame_duration=10;
	anim_frames = 3;
	anim = true;
	type = NOTE_1;
	pitch = C;
}


Note::~Note(void)
{
}

void Note::respawn(Pitch _pitch, Type _type) {
	sprite_rects.clear();

	type = _type;
	pitch = _pitch;

	//init bitmap
	add_sprite_rect("notes",0,32*type,32,32);
	add_sprite_rect("notes",32,32*type,32,32);
	add_sprite_rect("notes",64,32*type,32,32);

	display_offset.x = -8;
	display_offset.y = -10;
	pos.w = (14<<FPSH);
	pos.h = (12<<FPSH);
	
	//set starting position
	setPosition(pos_max_x * PX - pos.w/2, (pitch + 2) * 16 * PX - pos.h/2);

	velocity.x = -128;
	maxVelocity.x = 512;
	//accel.x = -2;

	alive = true;
}

void Note::draw(void){
	if (alive) {
		Sprite::draw();
	}
}

void Note::update(void){

	point center = getCenter();
	if (alive) {
		Sprite::update();

		if ((center.x>>FPSH) < pos_min_x) {
			alive = false;
			//note death
			g_game->getDemon().happy(64);
			g_game->getParticles().addEffect(EFFECT_BLOODSQUIRT, getCenter());
		}
		
		Stave& stave = g_game->getStave();
		if (alive && stave.hitNote(*this)) {
			alive = false;
			//g_game->getDemon().hurt(1);
		}
	}
}

bool Note::isAlive(void) {
	return alive;
}
