#ifndef GAME_H
#define GAME_H

#include "sdk.h"
#include "Stave.h"
#include "Background.h"
#include "Song.h"
#include "ParticleEmitter.h"
#include "Player.h"
#include "Demon.h"
#include "FilterDark.h"
#include "FilterFilm.h"

class Game
{
    public:
        Game(void);
        ~Game(void);

        void pause(bool enabled);
        void run(void);

		s32 getCurrentFrameID() { return frameID; }

		ParticleEmitter& getParticles() { return particles; }
		Stave& getStave() { return stave; }
		FilterDark& getFilterDark() { return filterDark; }

    protected:
        ALLEGRO_TIMER* timer;

		Stave stave;
		Background background;
		FilterDark filterDark;
		FilterFilm filterFilm;
		Song song;
		ParticleEmitter particles;

		s32 frameID;
		Player player;
		Demon demon;

        bool paused;
};

#endif
