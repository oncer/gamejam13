#pragma once

#include "sdk.h"

class KBD
{
public:
	static void Update(); // call this once per frame to update keyboard state
    static bool IsKeyPressed(int key);
    static bool JustPressed(int key);

    enum {
        KEY_JUMP   = 0x01,
        KEY_ATTACK = 0x02,
        KEY_LEFT   = 0x04,
        KEY_RIGHT  = 0x08,
        KEY_UP     = 0x10,
        KEY_DOWN   = 0x20
    };
private:
    static ALLEGRO_KEYBOARD_STATE kbd_state;
    static u32 keystate;
    static u32 keytrg;

	KBD(void);
	~KBD(void);
};

