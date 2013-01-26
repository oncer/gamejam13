#pragma once
#include "Sprite.h"
#include "KBD.h"
class Player :
	public Sprite
{
public:
	Player(void);
	~Player(void);
	
	void Player::update(void);
	void Player::draw(void);

protected:
	enum States {
		IDLE,
		PUMP
	};

	States state;

	void Player::setState(States _state);
};

