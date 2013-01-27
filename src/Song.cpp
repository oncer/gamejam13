#include "Song.h"
#include "SND.h"

float Song::bar_generator1_placement[] = {1.0f, 0.05f, 0.3f, 0.05f, 0.4f, 0.05f, 0.3f, 0.05f};
float Song::bar_generator1_pitch[] = {0.2f,0.4f,0.6f,0.8f}; //note: cummulative probability, fith element would be sum = 1
float Song::bar_generator2_placement[] = {1.0f, 0.3f, 0.5f, 0.2f, 0.7f, 0.2f, 0.5f, 0.3f};
float Song::bar_generator2_pitch[] = {0.3f,0.4f,0.6f,0.7f}; 
float Song::bar_generator3_placement[] = {1.0f, 0.4f, 0.6f, 0.3f, 0.8f, 0.3f, 0.6f, 0.4f};
float Song::bar_generator3_pitch[] = {0.4f,0.5f,0.6f,0.7f}; 
//float Song::bar_generator1_placement[] = {0.5f, 0.025f, 0.15f, 0.025f, 0.2f, 0.025f, 0.15f, 0.025f};
//float Song::bar_generator2_placement[] = {0.5f, 0.15f, 0.25f, 0.1f, 0.35f, 0.1f, 0.25f, 0.15f};

Song::Song()
	:notes(128), bpm(120), frames_per_16beat(bpm_to_frames(120)), bar_counter(0), beat_counter(8)
{
	frame_counter = frames_per_16beat;
	std::cout << "frames_per_16beat: " << frames_per_16beat << std::endl;
	backgroundNote = 0;
	difficulty = EASY;

	for (int i = 0; i < 8; i++) {
		next_bar_pitch[i] = Note::NONE;
	}
}

Song::~Song(void){

}

void Song::update(void) {
	
	
	frame_counter++;
	if(difficulty == HARD) frame_counter++;

	if(frame_counter >= frames_per_16beat) {
		//Beat
			

		if(beat_counter%4 == 0) {
			SND::timbal();
		}
		if(beat_counter >= 8) { //bar
			backgroundNote += randint(1,3);
			backgroundNote %= 3;
			SND::background(backgroundNote);

			beat_counter = 0;

			bar_counter++;
			if (bar_counter == 7 && difficulty == EASY) {
				difficulty = MEDIUM;
				std::cout<<"Switching to MEDIUM difficulty!"<<std::endl;
			} else if (bar_counter == 15 && difficulty == MEDIUM) {
				difficulty = HARD;
				std::cout<<"Switching to HARD difficulty!"<<std::endl;
			}
			
			generateNextBar();
		}
		
		
		Note::Pitch pitch = next_bar_pitch[beat_counter];

		beat_counter++;
		frame_counter = 0;

		if(pitch != Note::NONE) {

			SND::whistle(pitch);

			Note* available_note;
			for(std::vector<Note>::iterator it = notes.begin(); it != notes.end(); ++it) {
				if (!it->isAlive()) { //find dead note to respawn
					available_note = &(*it);
				}
			}

			//get random note type
			Note::Type type;
			float seed = ( (float)randint(0,100) ) / 100;
			if (seed < 0.5f) {
				type = Note::NOTE_1;
			} else {
				type = Note::NOTE_2;
			}

			available_note->respawn(pitch, type);
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

void Song::generateNextBar(void){
	std::stringstream bar_string;
	bar_string << "Bar: ";
	for (int i = 0; i < 8; i++) { //for each 1/8 beat

		float placement_seed = ( (float)randint(0,100) ) / 100;
		bool place_note;
		if(difficulty == EASY) {
			place_note = placement_seed < bar_generator1_placement[i]; //e.g. 0.4f < 1.0f --> 100%, 0.6f < 0.3f --> note not placed
		} else if (difficulty == MEDIUM) {
			place_note = placement_seed < bar_generator2_placement[i];
		} else {
			place_note = placement_seed < bar_generator3_placement[i];
		}
		//std::cout<<"rand__ seed: "<<placement_seed<<" prob: "<<bar_generator1_placement[i]<<" place: "<<place_note<<std::endl;
		bar_string << place_note;

		if (place_note) {
			//find random pitch 
			float pitch_seed =  ( (float)randint(0,100) ) / 100;
			//std::cout<<"rand-pitch-seed: "<<pitch_seed<<std::endl;

			if(difficulty == EASY) {
				if (pitch_seed < bar_generator1_pitch[0]) {
					next_bar_pitch[i] = Note::E;
				} else if (pitch_seed < bar_generator1_pitch[1]) {
					next_bar_pitch[i] = Note::D;
				} else if (pitch_seed < bar_generator1_pitch[2]) {
					next_bar_pitch[i] = Note::C;
				} else if (pitch_seed < bar_generator1_pitch[3]) {
					next_bar_pitch[i] = Note::H;
				} else {
					next_bar_pitch[i] = Note::A;
				}
			} else if(difficulty == MEDIUM) {
				if (pitch_seed < bar_generator2_pitch[0]) {
					next_bar_pitch[i] = Note::E;
				} else if (pitch_seed < bar_generator2_pitch[1]) {
					next_bar_pitch[i] = Note::D;
				} else if (pitch_seed < bar_generator2_pitch[2]) {
					next_bar_pitch[i] = Note::C;
				} else if (pitch_seed < bar_generator2_pitch[3]) {
					next_bar_pitch[i] = Note::H;
				} else {
					next_bar_pitch[i] = Note::A;
				}
			} else {
				if (pitch_seed < bar_generator3_pitch[0]) {
					next_bar_pitch[i] = Note::E;
				} else if (pitch_seed < bar_generator3_pitch[1]) {
					next_bar_pitch[i] = Note::D;
				} else if (pitch_seed < bar_generator3_pitch[2]) {
					next_bar_pitch[i] = Note::C;
				} else if (pitch_seed < bar_generator3_pitch[3]) {
					next_bar_pitch[i] = Note::H;
				} else {
					next_bar_pitch[i] = Note::A;
				}
			}


		} else {
			next_bar_pitch[i] = Note::NONE;
		}

	}
	
	//std::cout<<bar_string.str()<<std::endl;
	//std::cout<<"Generated Bar: "<<next_bar_pitch[0]<<" "<<next_bar_pitch[1]<<" "<<next_bar_pitch[2]<<" "<<next_bar_pitch[3]<<" "<<next_bar_pitch[4]<<" "<<next_bar_pitch[5]<<" "<<next_bar_pitch[6]<<" "<<next_bar_pitch[7]<<std::endl;
}
