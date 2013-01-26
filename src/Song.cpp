
#include "Song.h"

Song::Song(const std::string& _song)
	:notes(128), song(_song), bpm(120), frames_per_16beat(bpm_to_frames(120)/4)
{
	cursor = 0;
	frame_counter = 0;
	pause_counter = 0;
}

Song::~Song(void){

}

void Song::update(void) {
	
	if(cursor >= song.length()) {
		cursor = 0; //TODO END SONG
	}
	
	frame_counter++;
	if(frame_counter >= frames_per_16beat) {
		//Beat

		frame_counter = 0;
		if (pause_counter > 0) { //WAIT
			pause_counter--;

		} else {

			pause_counter  = 0;

			char current_value = song.at(cursor);

			

			if(current_value >= '0' && current_value <= '9') { //PAUSE

				pause_counter = current_value - '0' - 1; //-1 because this beat included
				
				//std::cout << "START PAUSE c:" << pause_counter << std::endl;

			} else { // NOTE

				//TODO play note
				std::cout << "PLAY " << current_value << std::endl;

				Note* available_note;
				for(std::vector<Note>::iterator it = notes.begin(); it != notes.end(); ++it) {
					if (!it->isAlive()) { //find dead note to respawn
						available_note = &(*it);
					}
				}
				available_note->respawn(1);

			}
			
			cursor++;
		}

	}
}

void Song::updateNotes(void){
	for(std::vector<Note>::iterator it = notes.begin(); it != notes.end(); ++it) {
		it->update();
	}
}

void Song::drawNotes(void){
	for(std::vector<Note>::iterator it = notes.begin(); it != notes.end(); ++it) {
		it->draw();
	}
}