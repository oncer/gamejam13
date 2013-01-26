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
