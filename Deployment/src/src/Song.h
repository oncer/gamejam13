# pragma once

#include "sdk.h"
#include "Note.h"

class Song {
	public:
		Song(void);
		~Song(void);
		void update(void);
		void updateNotes(void);
		void drawNotes(void);

	protected:
		
		enum Difficulty {
			EASY = 0,
			MEDIUM = 1,
			HARD = 2
		};
		
		static float bar_generator1_placement[];
		static float bar_generator1_pitch[];
		static float bar_generator2_placement[];
		static float bar_generator2_pitch[];
		static float bar_generator3_placement[];
		static float bar_generator3_pitch[];

		void generateNextBar(void);

		const unsigned int bpm;
		const unsigned int frames_per_16beat; //derived from bpm and fps
		unsigned int frame_counter; //count of frames at 1/8 position
		unsigned int beat_counter;
		unsigned int bar_counter;
		Note::Pitch next_bar_pitch[8]; //pitches for the next bar
		Difficulty difficulty;


		//spawned notes
		std::vector<Note> notes;
		s32 backgroundNote;
};
