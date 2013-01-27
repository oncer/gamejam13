# pragma once

#include "sdk.h"
#include "Note.h"

class Song {
	public:
		Song(const std::string& _song);
		~Song(void);
		void update(void);
		void updateNotes(void);
		void drawNotes(void);
		std::string Song::getText(void);

	protected:
		std::string song;
		int cursor; //current char
		const unsigned int bpm;
		const unsigned int frames_per_16beat; //derived from bpm and fps
		unsigned int frame_counter; //count of frames at current cursor position
		unsigned int pause_counter;
		unsigned int beat_counter;
		bool nextNoteIsObstacle;
		//spawned notes
		std::vector<Note> notes;
};
