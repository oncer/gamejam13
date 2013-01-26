#pragma once

#include "sdk.h"

// untertöne: F G A
class SND
{
	public:
		static void load();
		// obertöne: 0=A 1=H 2=C 3=D 4=E
		static void whistle(int pitch);
		static void heartbeat();
	protected:
		static ALLEGRO_SAMPLE* s_whistle;
		static ALLEGRO_SAMPLE* s_heartbeat;
	private:
		SND() {}
		~SND() {}
};
