#ifndef GAME_H
#define GAME_H

#include "sdk.h"
#include "Stave.h"
#include "Background.h"
#include "Song.h"
#include "Player.h"
#include "Demon.h"

class Game
{
    public:
        Game(void);
        ~Game(void);

        void pause(bool enabled);
        void run(void);

    protected:
        ALLEGRO_TIMER* timer;

		//Stave stave;
		Background background;
		Song song;
		Player player;
		Demon demon;

        bool paused;
};

#endif
