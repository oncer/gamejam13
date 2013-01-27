#include "SND.h"

ALLEGRO_SAMPLE *SND::s_whistle;
ALLEGRO_SAMPLE *SND::s_hitnote;
ALLEGRO_SAMPLE *SND::s_timbal;
ALLEGRO_SAMPLE *SND::s_background;
ALLEGRO_SAMPLE *SND::s_ambient[] = {NULL, NULL, NULL};
ALLEGRO_SAMPLE *SND::s_heartbeat;
ALLEGRO_SAMPLE *SND::s_dead;
ALLEGRO_SAMPLE_INSTANCE *SND::i_treble;

static ALLEGRO_SAMPLE* _loadSample(const char* f) {
	ALLEGRO_SAMPLE *s = al_load_sample(f);
	if (s == NULL) {
		std::cout << "[error] Could not load " << f << std::endl;
	}
	return s;
}
void SND::load()
{
	s_whistle = _loadSample("sfx/whistle-c.ogg");
	s_background = _loadSample("sfx/background-c.ogg");
	s_ambient[0] = _loadSample("sfx/ambient_breath1.ogg");
	s_ambient[1] = _loadSample("sfx/ambient_breath2.ogg");
	s_ambient[2] = _loadSample("sfx/ambient1.ogg");
	s_heartbeat = _loadSample("sfx/heartbeat.ogg");
	s_dead = _loadSample("sfx/dead.ogg");
	s_hitnote = _loadSample("sfx/catchnote.ogg");
	s_timbal = _loadSample("sfx/timbal.ogg");

	i_treble = al_create_sample_instance(_loadSample("sfx/hightremolo.ogg"));
	al_attach_sample_instance_to_mixer(i_treble, al_get_default_mixer());
}

// obertöne: E D C B A
void SND::whistle(int pitch)
{/*
	const float pitch_table[] = {
		4699.0/4186.0,  // D (was E)
		4435.0/4186.0, // C# (was D)
		4186.0/4186.0, // C (was C)
		3951.0/4186.0, // B (was B)
		3729.0/4186.0 // A# (was A)
	};
	*/
	const float pitch_table[] = {
		4699.0/4186.0, // D2
		3729.0/4186.0, // B  //3951.0/4186.0, // H
		3520.0/4186.0, // A
		2794.0/4186.0, // F
		2349.0/4186.0  // D
		/*
		5274.0/4186.0, // E
		4699.0/4186.0, // D
		4186.0/4186.0, // C
		3951.0/4186.0, // B
		3520.0/4186.0  // A
		*/
	};
	
	if (pitch >= 0 && pitch < 5) {
		al_play_sample(s_whistle, 1.0, 0.0, pitch_table[pitch], ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

void SND::hitnote(int pitch)
{
	const float pitch_table[] = {
		4699.0/4186.0, // D2
		3729.0/4186.0, // B  //3951.0/4186.0, // H
		3520.0/4186.0, // A
		2794.0/4186.0, // F
		2349.0/4186.0  // D
		/*
		5274.0/4186.0, // E
		4699.0/4186.0, // D
		4186.0/4186.0, // C
		3951.0/4186.0, // B
		3520.0/4186.0  // A
		*/
	};

	if (pitch >= 0 && pitch < 5) {
		al_play_sample(s_hitnote, 1.0, 0.0, pitch_table[pitch], ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

// untertöne: F G A
void SND::background(int pitch)
{
	/*
	const float pitch_table[] = {
		3520.0/4186.0, // A (was A)
		3322.0/4186.0, // G# (was G)
		3136.0/4186.0  // G (was F)
	};
	*/
	
	const float pitch_table[] = {
		/*
		3520.0/4186.0, // A
		3136.0/4186.0, // G
		2794.0/4186.0  // F
		*/
		2794.0/4186.0, // F
		2637.0/4186.0, // E
		2349.0/4186.0  // D
	};
	
	if (pitch >= 0 && pitch < 3) {
		al_play_sample(s_background, 1.0, 0.0, pitch_table[pitch], ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

void SND::heartbeat() {
	al_play_sample(s_heartbeat, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void SND::timbal() {
	al_play_sample(s_timbal, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}


void SND::dead() {
	al_play_sample(s_dead, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void SND::ambient(int type) {
	if (type > 2 || type < 0) type = 0;
	al_play_sample(s_ambient[type], 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void SND::startLoopedAmbient(void) {
	al_play_sample(s_ambient[2], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void SND::startLoopedTreble(void) {
	al_set_sample_instance_gain(i_treble, 0.0);
	al_set_sample_instance_playmode(i_treble, ALLEGRO_PLAYMODE_LOOP);
	al_play_sample_instance(i_treble);
}

void SND::setLoopedTrepleGain(float gain) {
	al_set_sample_instance_gain(i_treble, gain);
}

void SND::stopLoopedTreble(void) {
	al_stop_sample_instance(i_treble);
}
