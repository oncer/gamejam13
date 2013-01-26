#pragma once

#include "sdk.h"
#include "Sprite.h"

class ParticleEmitter;

class Particle: public Sprite
{
public:
    enum ParticleType {
        BLOOD_BIG,
		BLOOD_SMALL
    };

    Particle();
    ~Particle();

    void init(ParticleType type);
    void update();

    bool isAlive() const { return alive; }

    void setVelocity(s32 x, s32 y) {
        velocity.x = x;
        velocity.y = y;
    }

	void setAcceleration(s32 x, s32 y) {
		accel.x = x;
		accel.y = y;
	}

    void setDrag(s32 x, s32 y) {
        drag.x = x; drag.y = y;
    }
    void setFlip(bool h_flip, bool v_flip) { this->h_flip = h_flip; this->v_flip = v_flip; }
private:
	ParticleType type;
    bool alive;
    s32 anim_wait;
    s32 anim_delay;
};

enum EffectType {
    EFFECT_BLOODSQUIRT,
	EFFECT_BLOODDROP
};

class ParticleEmitter
{
public:
    ParticleEmitter();

    void addEffect(EffectType effect, const point& pos);
    Particle* addParticle(Particle::ParticleType particleType);

    void update();
    void draw() const;
private:
    typedef std::vector<Particle> PL;
    PL particles;
};
