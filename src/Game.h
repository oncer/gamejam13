#ifndef GAME_H
#define GAME_H

#include "sdk.h"
#include "Stave.h"
#include "Background.h"

class Game
{
    public:
        Game(void);
        ~Game(void);

        void pause(bool enabled);
        void run(void);

		s32 getCurrentFrameID() { return frameID; }

    protected:
        ALLEGRO_TIMER* timer;

		Stave stave;
		Background background;

		s32 frameID;

        bool paused;
};

#endif
