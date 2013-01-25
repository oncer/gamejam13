#include "KBD.h"

ALLEGRO_KEYBOARD_STATE KBD::kbd_state;
u32 KBD::keystate = 0;
u32 KBD::keytrg = 0;

void KBD::Update()
{
    al_get_keyboard_state(&kbd_state);
    u32 previous_keystate = keystate;
    keystate = 0;
    if (al_key_down(&kbd_state, ALLEGRO_KEY_A)) keystate |= KEY_JUMP;
    if (al_key_down(&kbd_state, ALLEGRO_KEY_S)) keystate |= KEY_ATTACK;
    if (al_key_down(&kbd_state, ALLEGRO_KEY_LEFT)) keystate |= KEY_LEFT;
    if (al_key_down(&kbd_state, ALLEGRO_KEY_RIGHT)) keystate |= KEY_RIGHT;
    if (al_key_down(&kbd_state, ALLEGRO_KEY_UP)) keystate |= KEY_UP;
    if (al_key_down(&kbd_state, ALLEGRO_KEY_DOWN)) keystate |= KEY_DOWN;

    keytrg = (keystate ^ previous_keystate) & keystate;
}

bool KBD::IsKeyPressed(int key)
{
    return (keystate & key);
}

bool KBD::JustPressed(int key)
{
    return (keytrg & key);
}

KBD::KBD(void)
{
}

KBD::~KBD(void)
{
}
