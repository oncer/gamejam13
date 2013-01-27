#pragma once
#include "Sprite.h"
#include "KBD.h"
#include "SND.h"

class Player :
	public Sprite
{
public:
	Player(void);
	~Player(void);
	
	void update(void);
	void draw(void);

	void pump(void);

protected:
	enum States {
		IDLE,
		PUMP
	};

	States state;

	void setState(States _state);
};

