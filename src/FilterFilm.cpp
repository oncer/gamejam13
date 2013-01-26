#include "FilterFilm.h"


FilterFilm::FilterFilm(void)
{
	add_sprite_rect("filter_film",0,0,400,240);
	add_sprite_rect("filter_film",400,0,400,240);
	add_sprite_rect("filter_film",800,0,400,240);
	add_sprite_rect("filter_film",1200,0,400,240);
	add_sprite_rect("filter_film",1600,0,400,240);
	anim_frame_duration=5;
	anim_frames = 5;
	anim = true;
}


FilterFilm::~FilterFilm(void)
{
}

void FilterFilm::draw(void) {
	Sprite::draw();
}
void FilterFilm::update(void) {
	Sprite::update();
}
