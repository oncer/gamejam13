#include "ParticleEmitter.h"
#include "Define.h"

ParticleEmitter::ParticleEmitter()
    :particles(MAX_PARTICLES)
{
}

void ParticleEmitter::addEffect(EffectType effect, const point &pos)
{
    int i, len;
    switch (effect) {
    case EFFECT_AIRJUMP:
    {
        Particle* p = addParticle(Particle::AIRJUMP);
        if (p != NULL) {
            p->setCenter(pos);
        }
    }
        break;
    case EFFECT_DEATH:
    {
        len = randint(4,7);
        for (i=0; i<len; i++) {
            Particle* p = addParticle(Particle::SMOKE);
            if (p != NULL) {
                p->setCenter(pos);
                point dir = {randint(-1024, 1024), randint(-1024, 256)};
                point v = motion_vector(dir, PX/2);
                p->setVelocity(v.x, v.y);
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
    maxVelocity.x = maxVelocity.y = 16<<FPSH; // sufficiently large value
	velocity.y = PX;
    int i;
    switch (type) {
    case AIRJUMP:
        for (i=0; i<5; i++) {
            add_sprite_rect("effects", i*32, 16, 32, 16);
        }
        display_offset.x = display_offset.y = 0;
        pos.w = 32<<FPSH;
        pos.h = 16<<FPSH;
        anim_delay = anim_wait = 2;
        alive = true;
        collisionResponse = false;
        break;
    case SMOKE:
        for (i=0; i<7; i++) {
            add_sprite_rect("effects", i*16, 0, 16, 16);
        }
        display_offset.x = display_offset.y = -4;
        pos.w = pos.h = 8<<FPSH;
        anim_delay = randint(2, 6);
        anim_wait = anim_delay * randint(1, 2);
        alive = true;
        collisionResponse = false;
        break;
    }
}

void Particle::update()
{
    Sprite::update();
    anim_wait--;
    if (anim_wait < 0) {
        anim_wait = anim_delay;
        cur_frame++;
        if (cur_frame >= sprite_rects.size()) {
            alive = false;
        }
    }
}


Particle::Particle()
    :alive(false)
{
}

Particle::~Particle()
{
}
