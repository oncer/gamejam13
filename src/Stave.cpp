#include "Stave.h"
#include "GFX.h"
#include "Globals.h"

Stave::Stave(void)
{
	pos.w = (16<<FPSH);
	pos.h = (16<<FPSH);
	display_offset.x = -16;
	display_offset.y = -16;
	add_sprite_rect("ghost",0,0,16,16);
	
	state = STATE_IDLE;
}


Stave::~Stave(void)
{
}

void Stave::update(void){
	Sprite::update();

	s32 targetY = 16*PX*4;
	velocity.x = PX*4;
	rotation = fp_atan2(velocity);
	switch (state) {
		case STATE_IDLE:
			velocity.y = (targetY - getCenter().y);
			break;
		case STATE_BOUNCE:
			if (pos.y < 16*PX && velocity.y < 0) {
				pos.y = 16*PX;
				velocity.y = -velocity.y;
			}
			if (pos.y > 16*PX*6 && velocity.y > 0) {
				state = STATE_IDLE;
			}
			break;
	}
	if ((pos.x + pos.w) > (WIDTH<<FPSH)) {
		pos.x = -pos.w;
	}
}

void Stave::draw(void)
{
	Sprite::draw();
}

void Stave::startPulse(void)
{
	if (state != STATE_BOUNCE) {
		state = STATE_BOUNCE;
	}
}

bool Stave::hitNote(const Note& note)
{
	if (state != STATE_BOUNCE) {
		return false;
	}
	const rect& notePos = note.getPosition();
	rect noteRect = {notePos.x + (8<<FPSH), notePos.y + (10<<FPSH), (14<<FPSH), (12<<FPSH)};
	rect coll = get_collision(pos, noteRect);
	return is_collision(coll);
}

