#include "SND.h"

ALLEGRO_SAMPLE *SND::s_whistle;
ALLEGRO_SAMPLE *SND::s_background[] = {NULL, NULL, NULL};
ALLEGRO_SAMPLE *SND::s_heartbeat;

static ALLEGRO_SAMPLE* _loadSample(const char* f) {
	ALLEGRO_SAMPLE *s = al_load_sample(f);
	if (s == NULL) {
		std::cout << "[error] Could not load " << f << std::endl;
	}
}
void SND::load()
{
	s_whistle = _loadSample("sfx/whistle-c.ogg");
	s_background[0] = _loadSample("sfx/background-f.ogg");
	s_background[1] = _loadSample("sfx/background-g.ogg");
	s_background[2] = _loadSample("sfx/background-a.ogg");
	s_heartbeat = _loadSample("sfx/heartbeat.ogg");
}

// obertöne: E D C B A
void SND::whistle(int pitch)
{
	const float pitch_table[] = {
		5274.0/4186.0, // E
		4699.0/4186.0, // D
		4186.0/4186.0, // C
		3951.0/4186.0, // B
		3520.0/4186.0  // A
	};

	if (pitch >= 0 && pitch < 5) {
		al_play_sample(s_whistle, 1.0, 0.0, pitch_table[pitch], ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

// untertöne: F G A
void SND::background(int pitch)
{
	if (pitch >= 0 && pitch < 3) {
		al_play_sample(s_background[pitch], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

void SND::heartbeat() {
	al_play_sample(s_heartbeat, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}