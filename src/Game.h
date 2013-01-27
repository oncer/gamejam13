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
#include "Ambient.h"
#include "util.h"
#include "GameOverBg.h"
#include "Heartbeat.h"
#include "Menu.h"

class Game
{
    public:
        Game(void);
        ~Game(void);
		enum Gamestate {
			MENU,
			GAME,
			GAMEOVER
		};

        void pause(bool enabled);
        void run(void);
		void setGamestate(Gamestate state);

		s32 getCurrentFrameID() { return frameID; }

		ParticleEmitter& getParticles() { return particles; }
		Stave& getStave() { return stave; }
		FilterDark& getFilterDark() { return filterDark; }
		Demon& getDemon() { return demon; }

		void failnote(const Sprite& s, s32 type);
		void hitnote(const Sprite& s, s32 pitch);

    protected:
        ALLEGRO_TIMER* timer;

		Gamestate state;
		Menu menu;

		Ambient ambient;

		Stave stave;
		Background background;
		GameOverBg gameOverBg;
		FilterDark filterDark;
		FilterFilm filterFilm;
		Song song;
		ParticleEmitter particles;
		Heartbeat heartbeat;

		s32 frameID;
		Player player;
		Demon demon;

		s32 score;
		s32 combo;
		s32 maxCombo;

        bool paused;
		unsigned int playtime;
};

#endif
