#pragma once

#include "sdk.h"
#include "Sprite.h"

class Particle: public Sprite
{
public:
    enum ParticleType {
        SMOKE,
        AIRJUMP
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
    void setDrag(s32 x, s32 y) {
        drag.x = x; drag.y = y;
    }
    void setFlip(bool h_flip, bool v_flip) { this->h_flip = h_flip; this->v_flip = v_flip; }
private:
    bool alive;
    s32 anim_wait;
    s32 anim_delay;
};

enum EffectType {
    EFFECT_DEATH,
    EFFECT_AIRJUMP
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
