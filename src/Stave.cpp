#include "Stave.h"
#include "GFX.h"
#include "Globals.h"

Stave::Stave(void)
	:pulse(false)
{
	add_sprite_rect("lines",0,0,400,32);
	add_sprite_rect("lines",0,32,400,32);
	setPosition(0,32*PX);
}


Stave::~Stave(void)
{
}

void Stave::draw(void)
{
	point pulsePos = {pulseCount - (32<<FPSH), pos.y};
	if (pulse) {
		if (pulsePos.x > 0) {
			pos.x = 0;
			cut(0, 0, pulsePos.x>>FPSH, 32);
			Sprite::draw();
		}
		pos.x = pulsePos.x + (32<<FPSH);
		cut(pos.x>>FPSH, 0, 400 - (pos.x>>FPSH), 32);
	} else {
		uncut();
		pos.x = 0;
	}
	Sprite::draw();
	if (pulse) {
		const rect rcPulse[] = {
			{ 0,64,32,32}, // 0
			{32,64,32,32}, // 1
			{64,64,32,32}, // 2
			{96,64,32,32}, // 3
			{64,64,32,32}, // 4
			{32,64,32,32}  // 5
		};
		s32 pulseFrame = (pulseCount>>FPSH) / 32;
		if (pulseFrame > 5) {
			pulse = false;
		} else {
			const rect& rc = rcPulse[pulseFrame];
			GFX::blit("lines", rc, pulsePos.x>>FPSH, pulsePos.y>>FPSH);
		}
	}
}

void Stave::update(void){
	Sprite::update();

	if (g_game->getCurrentFrameID()%(FPS/8) == 0) {
		cur_frame = (cur_frame + 1)%2;
	}

	if (pulse) {
		pulseCount+=PX*8;
	}
}

void Stave::startPulse(void)
{
	pulse = true;
	pulseCount = 0;
}
