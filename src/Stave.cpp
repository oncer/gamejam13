#include "Stave.h"
#include "GFX.h"
#include "Globals.h"

Stave::Stave(void)
{
	display_offset.x = 0;
	display_offset.y = -8;
	pos.w = (32<<FPSH);
	pos.h = (48<<FPSH);
	add_sprite_rect("cursor",0,0,32,64);
	
	state = STATE_IDLE;
	note0 = note1 = -1;
}


Stave::~Stave(void)
{
}

const int minPitch = -1;
const int maxPitch = 4;

void Stave::update(void){
	Sprite::update();
	if (KBD::JustPressed(KBD::KEY_UP)) {
		selectedPitch--;
		if (selectedPitch < minPitch) selectedPitch = maxPitch;
	}
	if (KBD::JustPressed(KBD::KEY_DOWN)) {
		selectedPitch++;
		if (selectedPitch > maxPitch) selectedPitch = minPitch;
	}
	if (KBD::JustPressed(KBD::KEY_ACTION)) {
		// swap notes
		s32 tmp = note0;
		note0 = note1;
		note1 = tmp;
	}

	pos.x = 16*PX;
	pos.y = (selectedPitch + 1)*PX*16;
}

void Stave::draw(void)
{
	// draw lines
	rect rcLines[] = {
		{0, 0, 400, 16},
		{0,16, 400, 16}
	};
	rect& rcLine = rcLines[(g_game->getCurrentFrameID()/8)%2];
	for (int i=1; i<7; i++) {
		GFX::blit_alpha("lines", rcLine, 0, 16*i-8, 128);
	}
	Sprite::draw();
}

bool Stave::hitNote(const Note& note)
{
	point center = getCenter();
	s32 hitX = center.x;
	s32 noteX = note.getCenter().x;
	s32 noteVelX = note.getVelocity().x;
	if (note.getPitch() == (selectedPitch) || note.getPitch() == (selectedPitch + 1)) {
		if (noteX <= hitX && (noteX - noteVelX) > hitX) {
			return true;
		}
	}
	return false;
}

