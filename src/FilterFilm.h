#pragma once
#include "Sprite.h"
class FilterFilm :
	public Sprite
{
public:
	FilterFilm(void);
	~FilterFilm(void);
	
	void FilterFilm::draw(void);
	void FilterFilm::update(void);
};

