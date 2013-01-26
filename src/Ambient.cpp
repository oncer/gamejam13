#include "ambient.h"

Ambient::Ambient(void)
	: frame_counter(0), frame_counter2(0), delay2(300)
{
	setNextDelay();
}
Ambient::~Ambient(void) {
}

void Ambient::update(void) {
	if(frame_counter++ >= next_delay) {
		frame_counter = 0;
		setNextDelay();
		int type = randint(2, 6);
		SND::ambient(type);
	}
	if(frame_counter2++ >= delay2) {
		frame_counter2 = 0;
		int type = randint(0, 2);
		SND::ambient(type);
	}
}

void Ambient::playRandom(void) {
	int type = randint(0, 6);
	std::cout<<"Playing ambient #" << type << std::endl;
	SND::ambient(type);
}

void Ambient::setNextDelay(void) {
	next_delay = randint(min_delay, max_delay);
	//std::cout<<"Next Delay: " << next_delay << std::endl;
}