#include "Note.h"
#include "Globals.h"

Note::Note()
{
	alive = false;
	anim_frame_duration=10;
	anim_frames = 3;
	anim = true;
	obstacle = false;
}


Note::~Note(void)
{
}

void Note::respawn(int _pitch, bool isObstacle) {
	sprite_rects.clear();

	obstacle = isObstacle;
	pitch = _pitch;

	//init bitmap
	if(isObstacle) {
		add_sprite_rect("notes",0,32*5,32,32);
		add_sprite_rect("notes",32,32*5,32,32);
		add_sprite_rect("notes",64,32*5,32,32);
	} else {
		add_sprite_rect("notes",0,32*pitch,32,32);
		add_sprite_rect("notes",32,32*pitch,32,32);
		add_sprite_rect("notes",64,32*pitch,32,32);
	}

	display_offset.x = -8;
	display_offset.y = -10;
	pos.w = (14<<FPSH);
	pos.h = (12<<FPSH);
	
	//set starting position
	setPosition(pos_max_x * PX - pos.w/2, (pitch + 2) * 16 * PX - pos.h/2);

	velocity.x = -256;
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
			if (!obstacle) g_game->getDemon().happy(64);
			point effectPos = {pos.x + 16*PX, pos.y + 15*PX};
			
			g_game->getParticles().addEffect(EFFECT_BLOODSQUIRT, effectPos);
		}
		
		Stave& stave = g_game->getStave();
		if (alive && stave.hitNote(*this)) {
			SND::hitnote(pitch);
			std::cout << "hit note" << std::endl;	
			alive = false;
			//g_game->getDemon().hurt(1);
			EffectType effectType;
			switch (pitch) {
				case 0: effectType = EFFECT_NOTE1; break;
				case 1: effectType = EFFECT_NOTE2; break;
				case 2: effectType = EFFECT_NOTE3; break;
				case 3: effectType = EFFECT_NOTE4; break;
				case 4: effectType = EFFECT_NOTE5; break;
			}
			if (obstacle) {
				g_game->getDemon().happy(64); //obstacle hit
				//effectType = EFFECT_OBSTACLE;
			}

			g_game->getParticles().addEffect(effectType, getCenter());
		}
	}
}

bool Note::isAlive(void) {
	return alive;
}
