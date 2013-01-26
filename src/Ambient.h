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
	static const unsigned int min_delay = 750;
	static const unsigned int max_delay = 1500;

	void setNextDelay(void);
	
};