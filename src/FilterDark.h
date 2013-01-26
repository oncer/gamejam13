#pragma once
#include "Sprite.h"
class FilterDark :
	public Sprite
{
public:
	FilterDark(void);
	~FilterDark(void);
	
	void draw(void);
	void update(void);
};

