#pragma once
#include "Sprite.h"
class GameOverBg :
	public Sprite
{
public:
	GameOverBg(void);
	~GameOverBg(void);
	
	void draw(void);
	void update(void);
};

