# pragma once

#include "sdk.h"

class Song {
	public:
		void update(void);

	protected:
		const char* song;
		const unsigned int song_length; //fixed length of song-string
		int cursor; //current char
		const unsigned int bpm;
		const unsigned int frames_per_note; //derived from bpm and fps
		unsigned int frame_counter; //count of frames at current cursor position

		//spawned notes
};