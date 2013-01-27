#include "Song.h"
#include "SND.h"

float Song::bar_generator1_placement[] = {1.0f, 0.1f, 0.4f, 0.1f, 0.6f, 0.1f, 0.4f, 0.1f};
float Song::bar_generator1_pitch[] = {0.2f,0.4f,0.6f,0.8f}; //note: cummulative probability, fith element would be sum = 1
float Song::bar_generator2_placement[] = {1.0f, 0.3f, 0.5f, 0.2f, 0.7f, 0.2f, 0.5f, 0.3f};
float Song::bar_generator2_pitch[] = {0.3f,0.4f,0.6f,0.7f}; 

Song::Song()
	:notes(128), bpm(120), frames_per_16beat(bpm_to_frames(120)/2), bar_counter(0)
{
	frame_counter = frames_per_16beat;
	std::cout << "frames_per_16beat: " << frames_per_16beat << std::endl;
	backgroundNote = 0;
	generateNextBar();
	difficulty = EASY;
}

Song::~Song(void){

}

void Song::update(void) {
	
	
	frame_counter++;
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
			generateNextBar();
			if (bar_counter == 8) {
				if (difficulty == EASY) {
					difficulty = MEDIUM;
					std::cout<<"Switching to MEDIUM difficulty!"<<std::endl;
				}
			}
		}
		beat_counter++;

		frame_counter = 0;
		
		//TODO SPAWN NOTE
		
		Note::Pitch pitch = next_bar_pitch[beat_counter];

		if(pitch != Note::Pitch::NONE) {

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
				type = Note::Type::NOTE_1;
			} else {
				type = Note::Type::NOTE_2;
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
	std::cout<<"Generating rand bar with difficulty "<<difficulty<<std::endl;
	for (int i = 0; i < 8; i++) { //for each 1/8 beat

		float placement_seed = ( (float)randint(0,100) ) / 100;
		//std::cout<<"rand-placement-seed: "<<placement_seed<<std::endl;
		bool place_note;
		if(difficulty == EASY) {
			place_note = placement_seed < bar_generator1_placement[i]; //e.g. 0.4f < 1.0f --> 100%, 0.6f < 0.3f --> note not placed
		} else {
			place_note = placement_seed < bar_generator2_placement[i];
		}

		if (place_note) {
			//find random pitch 
			float pitch_seed =  ( (float)randint(0,100) ) / 100;
			//std::cout<<"rand-pitch-seed: "<<pitch_seed<<std::endl;

			if(difficulty == EASY) {
				if (pitch_seed < bar_generator1_pitch[0]) {
					next_bar_pitch[i] = Note::Pitch::E;
				} else if (pitch_seed < bar_generator1_pitch[1]) {
					next_bar_pitch[i] = Note::Pitch::D;
				} else if (pitch_seed < bar_generator1_pitch[2]) {
					next_bar_pitch[i] = Note::Pitch::C;
				} else if (pitch_seed < bar_generator1_pitch[3]) {
					next_bar_pitch[i] = Note::Pitch::H;
				} else {
					next_bar_pitch[i] = Note::Pitch::A;
				}
			} else {
				if (pitch_seed < bar_generator2_pitch[0]) {
					next_bar_pitch[i] = Note::Pitch::E;
				} else if (pitch_seed < bar_generator2_pitch[1]) {
					next_bar_pitch[i] = Note::Pitch::D;
				} else if (pitch_seed < bar_generator2_pitch[2]) {
					next_bar_pitch[i] = Note::Pitch::C;
				} else if (pitch_seed < bar_generator2_pitch[3]) {
					next_bar_pitch[i] = Note::Pitch::H;
				} else {
					next_bar_pitch[i] = Note::Pitch::A;
				}
			}


		} else {
			next_bar_pitch[i] = Note::Pitch::NONE;
		}
	}

	//std::cout<<"Generated Bar: "<<next_bar_pitch[0]<<" "<<next_bar_pitch[1]<<" "<<next_bar_pitch[2]<<" "<<next_bar_pitch[3]<<" "<<next_bar_pitch[4]<<" "<<next_bar_pitch[5]<<" "<<next_bar_pitch[6]<<" "<<next_bar_pitch[7]<<std::endl;
}