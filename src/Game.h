#ifndef GAME_H
#define GAME_H

#include "sdk.h"

class Game
{
    public:
        Game(void);
        ~Game(void);

        void pause(bool enabled);
        void run(void);

    protected:
        ALLEGRO_TIMER* timer;

        bool paused;
};

#endif
