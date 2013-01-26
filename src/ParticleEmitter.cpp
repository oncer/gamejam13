#include "ParticleEmitter.h"
#include "Define.h"
#include "Globals.h"

ParticleEmitter::ParticleEmitter()
    :particles(MAX_PARTICLES)
{
}

void ParticleEmitter::addEffect(EffectType effect, const point &pos)
{
    int i, len;
	switch (effect) {
		case EFFECT_BLOODSQUIRT:
			{
				len = randint(14,28);
				for (i=0; i<len; i++) {
					Particle* p;
					if (i < 20) {
						p = addParticle(Particle::BLOOD_SMALL);
					} else {
						p = addParticle(Particle::BLOOD_BIG);
					}
					if (p != NULL) {
						p->setCenter(pos);
						point dir = {randint(-PX/2, PX/2), randint(-PX, 0)};
						p->setVelocity(dir.x, dir.y);
						p->setAcceleration(0, PX/16); // gravity
					}
				}
				break;
			}
		case EFFECT_NOTE1:
		case EFFECT_NOTE2:
		case EFFECT_NOTE3:
		case EFFECT_NOTE4:
		case EFFECT_NOTE5:
			{
				Particle::ParticleType particleType;
				if (effect == EFFECT_NOTE1) particleType = Particle::NOTE1;
				else if (effect == EFFECT_NOTE2) particleType = Particle::NOTE2;
				else if (effect == EFFECT_NOTE3) particleType = Particle::NOTE3;
				else if (effect == EFFECT_NOTE4) particleType = Particle::NOTE4;
				else if (effect == EFFECT_NOTE5) particleType = Particle::NOTE5;
				len = randint(20,30);
				for (i=0; i<len; i++) {
					Particle* p = addParticle(particleType);
					if (p != NULL) {
						p->setCenter(pos);
						point dir = {randint(-PX, PX), randint(-PX*2, 0)};
						p->setVelocity(dir.x, dir.y);
						p->setAcceleration(0, PX/16); // gravity
					}
				}
				break;
			}
	}
}

Particle* ParticleEmitter::addParticle(Particle::ParticleType particleType)
{
    for (PL::iterator it = particles.begin(); it != particles.end(); ++it) {
        Particle& p = *it;
        if (!p.isAlive()) {
            p.init(particleType);
            return &p;
        }
    }
    return NULL;
}

void ParticleEmitter::update()
{
    for (PL::iterator it = particles.begin(); it != particles.end(); ++it) {
        Particle& p = *it;
        if (p.isAlive()) p.update();
    }
}

void ParticleEmitter::draw() const
{
    for (PL::const_iterator cit = particles.begin(); cit != particles.end(); ++cit) {
        const Particle& p = *cit;
        if (p.isAlive()) p.draw();
    }
}

void Particle::init(ParticleType type)
{
    Sprite::reset();
	this->type = type;
    maxVelocity.x = maxVelocity.y = 16<<FPSH; // sufficiently large value
	looping = false;
	fadeout = 0;
	autorotate = true;
			
    int i;
	if (type == NOTE1 || type == NOTE2 || type == NOTE3 || type == NOTE4 || type == NOTE5) {
		display_offset.x = display_offset.y = -4;
		pos.w = pos.h = 1<<FPSH;
		anim_wait = 16;
		anim_delay = 8;
		alive = true;
		collisionResponse = false;
	}
    switch (type) {
		case BLOOD_BIG:
			for (i=0; i<7; i++) {
				add_sprite_rect("blood", i*4, 32, 8, 8);
			}
			display_offset.x = display_offset.y = -2;
			pos.w = pos.h = 4<<FPSH;
			anim_delay = randint(4,8);
			anim_wait = anim_delay * randint(1, 2);
			alive = true;
			collisionResponse = false;
			break;
		case BLOOD_SMALL:
		{
			s32 bloodtype = randint(0,4);
			for (i=0; i<4; i++) {
				add_sprite_rect("blood", i*4, bloodtype*4, 4, 4);
			}
			display_offset.x = display_offset.y = -1;
			pos.w = pos.h = 2<<FPSH;
			anim_delay = randint(8, 12);
			anim_wait = anim_delay * randint(1, 3);
			alive = true;
			collisionResponse = false;
			break;
		}
		case OSCILLO:
		{
			add_sprite_rect("particles", 0, 0, 8, 8);
			add_sprite_rect("particles", 8, 0, 8, 8);
			add_sprite_rect("particles",16, 0, 8, 8);
			add_sprite_rect("particles",24, 0, 8, 8);
			display_offset.x = display_offset.y = -4;
			pos.w = pos.h = 1<<FPSH;
			anim_wait = 4;
			anim_delay = anim_wait;
			alive = true;
			collisionResponse = false;
			looping = true;
			fadeout = 2;
			autorotate = false;
			break;
		}
		case NOTE1:
		{
			add_sprite_rect("particles", 0, 16, 8, 8);
			add_sprite_rect("particles", 8, 16, 8, 8);
			add_sprite_rect("particles",16, 16, 8, 8);
			add_sprite_rect("particles",24, 16, 8, 8);
			break;
		}
		case NOTE2:
		{
			add_sprite_rect("particles", 0, 28, 8, 8);
			add_sprite_rect("particles", 8, 28, 8, 8);
			add_sprite_rect("particles",16, 28, 8, 8);
			add_sprite_rect("particles",24, 28, 8, 8);
			break;
		}
		case NOTE3:
		{
			add_sprite_rect("particles", 0, 32, 8, 8);
			add_sprite_rect("particles", 8, 32, 8, 8);
			add_sprite_rect("particles",16, 32, 8, 8);
			add_sprite_rect("particles",24, 32, 8, 8);
			break;
		}
		case NOTE4:
		{
			add_sprite_rect("particles", 0, 40, 8, 8);
			add_sprite_rect("particles", 8, 40, 8, 8);
			add_sprite_rect("particles",16, 40, 8, 8);
			add_sprite_rect("particles",24, 40, 8, 8);
			break;
		}
		case NOTE5:
		{
			add_sprite_rect("particles", 0, 48, 8, 8);
			add_sprite_rect("particles", 8, 48, 8, 8);
			add_sprite_rect("particles",16, 48, 8, 8);
			add_sprite_rect("particles",24, 48, 8, 8);
			break;
		}
	}
}

void Particle::update()
{
	ParticleEmitter& emitter = g_game->getParticles();
    Sprite::update();
	if (autorotate) rotation = fp_atan2(velocity);
    anim_wait--;
    if (anim_wait < 0) {
        anim_wait = anim_delay;
        cur_frame++;
        if (cur_frame >= sprite_rects.size()) {
			if (!looping) {
				alive = false;
			} else {
				cur_frame = 0;
			}
        } else if (type == BLOOD_BIG) {
			Particle* p = emitter.addParticle(BLOOD_SMALL);
			if (p != NULL) {
				p->setCenter(getCenter());
				p->setAcceleration(0, PX/8);
			}
		}
    }
	opacity -= fadeout;
	if (opacity <= 0) {
		alive = false;
	}
}


Particle::Particle()
    :alive(false)
{
}

Particle::~Particle()
{
}
