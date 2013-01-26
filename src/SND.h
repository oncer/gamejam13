#pragma once

#include "sdk.h"

class SND
{
	public:
		static void load();
		// obertöne: 0=E 1=D 2=C 3=B 4=A
		static void whistle(int pitch);
		// untertöne: 0=F 1=G 2=A
		static void background(int pitch);
		static void heartbeat();
	protected:
		static ALLEGRO_SAMPLE* s_whistle;
		static ALLEGRO_SAMPLE* s_background;
		static ALLEGRO_SAMPLE* s_heartbeat;
	private:
		SND() {}
		~SND() {}
};
