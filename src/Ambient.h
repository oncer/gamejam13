#pragma once

#include "SND.h"

class Ambient {
public:
	Ambient(void);
	~Ambient(void);

	void update();
	void playRandom(void);
protected:
	unsigned int frame_counter;
	unsigned int next_delay;
	
	unsigned int frame_counter2;
	unsigned int delay2;
	static const unsigned int min_delay = 500;
	static const unsigned int max_delay = 1000;

	void setNextDelay(void);
	
};