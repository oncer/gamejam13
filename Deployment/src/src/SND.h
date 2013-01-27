#pragma once

#include "sdk.h"

class SND
{
	public:
		static void load();
		// obertöne: 0=E 1=D 2=C 3=B 4=A
		static void whistle(int pitch);
		static void hitnote(int pitch);
		// untertöne: 0=F 1=G 2=A
		static void background(int pitch);
		static void heartbeat();
		static void timbal();
		static void dead();
		static void failnote();
		static void ambient(int type);
		static void startLoopedAmbient(void);
		static void startLoopedTreble(void);
		static void setLoopedTrepleGain(float gain);
		static void stopLoopedTreble(void);
	protected:
		static ALLEGRO_SAMPLE* s_whistle;
		static ALLEGRO_SAMPLE* s_background;
		static ALLEGRO_SAMPLE* s_heartbeat;
		static ALLEGRO_SAMPLE* s_ambient[];
		static ALLEGRO_SAMPLE* s_hitnote;
		static ALLEGRO_SAMPLE* s_timbal;
		static ALLEGRO_SAMPLE* s_dead;
		static ALLEGRO_SAMPLE* s_failnote;
		
		static ALLEGRO_SAMPLE_INSTANCE* i_treble;
	private:
		SND() {}
		~SND() {}
};
