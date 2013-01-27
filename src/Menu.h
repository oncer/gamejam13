#pragma once
#include "Sprite.h"
class Menu :
	public Sprite
{
public:
	Menu(void);
	~Menu(void);
	
	void draw(void);
	void update(void);
};

