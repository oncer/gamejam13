#include "Stave.h"
#include "GFX.h"
#include "Globals.h"

Stave::Stave(void)
{
	pos.w = (16<<FPSH);
	pos.h = (16<<FPSH);
	display_offset.x = -16;
	display_offset.y = -16;
	add_sprite_rect("ghost",0,0,48,48);
	
	state = STATE_IDLE;
}


Stave::~Stave(void)
{
}

void Stave::update(void){
	Sprite::update();

	s32 targetY = 16*PX*4;
	rotation = fp_atan2(velocity);
	ParticleEmitter& particles = g_game->getParticles();
	Particle* p = particles.addParticle(Particle::BLOOD_SMALL);
	p->setCenter(getCenter());
	switch (state) {
		case STATE_IDLE:
			velocity.x = PX;
			velocity.y = (targetY - getCenter().y) / 16;
			break;
		case STATE_Q:
			targetY = 16*PX*9/2;
			velocity.x = PX;
			velocity.y = (targetY - getCenter().y) / 8;
			if (std::abs(targetY - getCenter().y) < PX) {
				state = STATE_R;
			}
			break;
		case STATE_R:
			velocity.x = PX*2;
			velocity.y = -PX*6;
			if (pos.y < 16*PX) {
				pos.y = 16*PX;
				state = STATE_S;
			}
			break;
		case STATE_S:
			velocity.x = PX;
			velocity.y = PX*6;
			if (pos.y > 16*6*PX) {
				pos.y = 16*6*PX;
				state = STATE_T;
			}
			break;
		case STATE_T:
			velocity.x = PX*2;
			velocity.y = -PX*6;
			if (pos.y < 16*3*PX) {
				pos.y = 16*3*PX;
				state = STATE_U;
				velocity.y = -PX*2;
			}
			break;
		case STATE_U:
			accel.y = PX/2;
			if (pos.y > 16*3*PX) {
				state = STATE_IDLE;
				accel.y = 0;
			}
			break;
	}
	if ((pos.x + pos.w) > (WIDTH<<FPSH)) {
		pos.x = -pos.w;
	}
}

void Stave::draw(void)
{
	s32 displaceY = fp_sin(g_game->getCurrentFrameID()*PX*8)*2;
	pos.y += displaceY;
	Sprite::draw();
	pos.y -= displaceY;
}

void Stave::startPulse(void)
{
	if (state == STATE_IDLE) {
		state = STATE_Q;
	}
}

bool Stave::hitNote(const Note& note)
{
	const rect& notePos = note.getPosition();
	rect noteRect = {notePos.x + (8<<FPSH), notePos.y + (10<<FPSH), (14<<FPSH), (12<<FPSH)};
	rect coll = get_collision(pos, noteRect);
	return is_collision(coll);
}

