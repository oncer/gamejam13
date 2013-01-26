#include "SND.h"

ALLEGRO_SAMPLE *SND::s_whistle;
ALLEGRO_SAMPLE *SND::s_heartbeat;

void SND::load()
{
	s_whistle = al_load_sample("sfx/whistle-c.ogg");
	s_heartbeat = al_load_sample("sfx/heartbeat.ogg");
}

// obertöne: A B C D E
void SND::whistle(int pitch)
{
	const float pitch_table[] = {
		3520.0/4186.0,
		3951.0/4186.0,
		4186.0/4186.0,
		4699.0/4186.0,
		5274.0/4186.0
	};

	if (pitch >= 0 && pitch < 5) {
		al_play_sample(s_whistle, 1.0, 0.0, pitch_table[pitch], ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

void SND::heartbeat() {
	al_play_sample(s_heartbeat, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
