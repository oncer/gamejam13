#include "Background.h"


Background::Background(void)
{
	add_sprite_rect("background",0,0,400,240);
}


Background::~Background(void)
{
}

void Background::draw(void) {
	Sprite::draw();
}
void Background::update(void) {
	Sprite::update();
}
