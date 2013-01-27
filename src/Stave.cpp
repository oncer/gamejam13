#include "Stave.h"
#include "GFX.h"
#include "Globals.h"

Stave::Stave(void)
{
	pos.w = (16<<FPSH);
	pos.h = (14<<FPSH);
	display_offset.x = -16;
	display_offset.y = -17;
	add_sprite_rect("ghost",0,0,48,48);
	
	state = STATE_IDLE;
	velocity.x = PX;
}


Stave::~Stave(void)
{
}

void Stave::update(void){
	Sprite::update();

	s32 targetY = 16*PX*4;
	rotation = fp_atan2(velocity);
	ParticleEmitter& particles = g_game->getParticles();
	Particle* p = particles.addParticle(Particle::OSCILLO);
	p->setCenter(getCenter());
	p->setRotation(rotation);

	point center = getCenter();
	switch (state) {
		case STATE_IDLE:
			combo = 0;
			velocity.y = (targetY - center.y) / 16;
			break;
		case STATE_Q:
			maxVelocity.y = PX*16;
			accel.y = 0;
			drag.x = 0;
			targetY = 16*PX*5;
			velocity.x = PX;
			velocity.y = (targetY - center.y) / 4;
			if (std::abs(targetY - center.y) < PX) {
				state = STATE_R;
			}
			break;
		case STATE_R:
			velocity.x = PX*2;
			velocity.y = -PX*6;
			if (center.y < 16*PX*2) {
				pos.y = 16*PX;
				state = STATE_S;
			}
			break;
		case STATE_S:
			velocity.x = PX;
			velocity.y = PX*6;
			if (center.y > 16*6*PX) {
				pos.y = 16*6*PX - pos.h/2;
				state = STATE_T;
			}
			break;
		case STATE_T:
			velocity.x = PX*2;
			velocity.y = -PX*6;
			if (center.y < 16*4*PX) {
				pos.y = 16*4*PX - pos.h/2;
				state = STATE_U;
				velocity.y = -PX*2;
			}
			break;
		case STATE_U:
			accel.y = PX/2;
			velocity.x = PX*2;
			if (center.y > 16*4*PX) {
				state = STATE_IDLE;
				accel.y = 0;
				velocity.x = PX;
			}
			break;
	}
	if ((pos.x + pos.w) > (WIDTH<<FPSH)) {
		pos.x = -pos.w;
	}

	if (combo > 0 && state == STATE_IDLE) {
		std::cout << "combo: " << combo << std::endl;
		combo = 0;
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
	const rect& noteRect = note.getPosition();
	rect coll = get_collision(pos, noteRect);
	bool hit = is_collision(coll);
	if (hit) {
		if (note.isObstacle()) {
			combo = 0;
		} else combo++;
	}
	return hit;
}

