#include "FilterDark.h"


FilterDark::FilterDark(void)
{
	add_sprite_rect("filter_dark",0,0,400,240);
	opacity = 0;
}


FilterDark::~FilterDark(void)
{
}

void FilterDark::draw(void) {
	Sprite::draw();
}
void FilterDark::update(void) {
	Sprite::update();
}
