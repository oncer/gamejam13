#ifndef GAME_H
#define GAME_H

#include "sdk.h"
#include "Stave.h"
#include "Background.h"
#include "Song.h"
#include "ParticleEmitter.h"
#include "Player.h"

class Game
{
    public:
        Game(void);
        ~Game(void);

        void pause(bool enabled);
        void run(void);

		s32 getCurrentFrameID() { return frameID; }

		ParticleEmitter& getParticles() { return particles; }

    protected:
        ALLEGRO_TIMER* timer;

		//Stave stave;
		Background background;
		Song song;
		ParticleEmitter particles;

		s32 frameID;
		Player player;

        bool paused;
};

#endif
