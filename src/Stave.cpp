#include "Stave.h"
#include "GFX.h"
#include "Globals.h"

Stave::Stave(void)
	:pulse(false)
{
	add_sprite_rect("lines",0,64,32,32);
	add_sprite_rect("lines",32,64,32,32);
	add_sprite_rect("lines",64,64,32,32);
	add_sprite_rect("lines",96,64,32,32);
}


Stave::~Stave(void)
{
}

void Stave::update(void){
	Sprite::update();

	if (KBD::JustPressed(KBD::KEY_UP)) {
		selectedPitch--;
		if (selectedPitch < 0) selectedPitch = 4;
	}
	if (KBD::JustPressed(KBD::KEY_DOWN)) {
		selectedPitch++;
		if (selectedPitch > 4) selectedPitch = 0;
	}

	pos.y = (selectedPitch+1)*16*PX;

	if (pulse) {
		s32 f = (pos.x>>FPSH) / 24;
		
		if (f > 7) {
			stopPulse();
		} else {
			switch (f) {
				case 7: cur_frame = 0; break;
				case 6: cur_frame = 1; break;
				case 5: cur_frame = 2; break;
				case 4: cur_frame = 3; break;
				case 3: cur_frame = 2; break;
				case 2: cur_frame = 1; break;
				case 1: cur_frame = 0; break;
				case 0: cur_frame = 0; break;
			}
		}
	}
}

void Stave::draw(void)
{
	rect rcLine;
	if ((g_game->getCurrentFrameID()/8)%2 == 0) {
		rect r = {0, 0, 400, 32};
		rcLine = r;
	} else {
		rect r = {0, 32, 400, 32};
		rcLine = r;
	}

	if (pulse) {
		if (pos.x > 0) {
			rcLine.w = pos.x>>FPSH;
			GFX::blit("lines", rcLine, 0, (pos.y>>FPSH));
		}
		rcLine.x = (pos.x + pos.w)>>FPSH;
	}
	rcLine.w = 400 - rcLine.x;
	if (rcLine.w > 400) rcLine.w = 400;
	GFX::blit("lines", rcLine, rcLine.x, (pos.y>>FPSH));

	if (pulse) {
		Sprite::draw();
	}
}

void Stave::startPulse(void)
{
	pulse = true;
	pos.x = -pos.w;
	velocity.x = PX*6;
}

void Stave::stopPulse(void)
{
	pulse = false;
	pos.x = -pos.w;
	velocity.x = 0;
}

int Stave::hitNote(const Note& note)
{
	if (selectedPitch != note.getPitch()) {
		return HIT_NONE;
	}

	s32 noteX = note.getCenter().x;

	s32 curX = get_center(pos).x;
	s32 oldX = curX - velocity.x + note.getVelocity().x;

	if (oldX < noteX && curX >= noteX) {
		stopPulse();
		if (cur_frame == 0) return HIT_BAD;
		else if (cur_frame == 1 || cur_frame == 2) return HIT_GOOD;
		else if (cur_frame == 3) return HIT_PERFECT;
	}
	return HIT_NONE;
}


