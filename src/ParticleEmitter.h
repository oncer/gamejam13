#pragma once

#include "sdk.h"
#include "Sprite.h"

class ParticleEmitter;

class Particle: public Sprite
{
public:
    enum ParticleType {
        BLOOD_BIG,
		BLOOD_SMALL,
		OSCILLO,
		NOTE1,
		NOTE2,
		NOTE3,
		NOTE4,
		NOTE5
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

	void setRotation(s32 r) {
		rotation = r;
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
	bool looping;
	s32 fadeout;
	bool autorotate;
};

enum EffectType {
    EFFECT_BLOODSQUIRT,
	EFFECT_NOTE1,
	EFFECT_NOTE2,
	EFFECT_NOTE3,
	EFFECT_NOTE4,
	EFFECT_NOTE5
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
