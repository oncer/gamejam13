#include "Demon.h"
#include "KBD.h"
#include "Globals.h"

Demon::Demon(void) {
	
	add_sprite_rect("demon",0,0,96,112);
	add_sprite_rect("demon",96,0,96,112);
	add_sprite_rect("demon",192,0,96,112);
	add_sprite_rect("demon",288,0,96,112);

	setPosition(320 * PX, 96 * PX);

	velocity.x = -16;

	setState(NORMAL);
}

Demon::~Demon(void) {
}

void Demon::update(void){
	Sprite::update();

	if (anim_frame_counter++ >= anim_frame_duration) {
		anim_frame_counter = 0;
		if (state == NORMAL) {
			cur_frame = ( cur_frame + 1 ) % 2; //alternate 0, 1
		} else if (state == HAPPY) {
			setState(NORMAL);
		} else if (state == HURT) {
			setState(NORMAL);
		}
	}

	if(KBD::IsKeyPressed(KBD::KEY_DOWN)) {
		happy();
	}
	if(KBD::IsKeyPressed(KBD::KEY_UP)) {
		hurt();
	}


	int pxpos = pos.x>>FPSH;
	if (pxpos < 100) {
		//map from [50, 100] to [1, 0] to [255, 0]
		int opacity;
		if (pxpos <= 50) {
			opacity = 255;
		} else opacity = (int) (255 * ((double)(100-pxpos))/50);

		FilterDark& filter = g_game->getFilterDark();

		filter.setOpacity(opacity);

	}
}

void Demon::draw(void){
	Sprite::draw();
}

void Demon::hurt(void){
	setState(HURT);
	velocity.x += 4;
	if(velocity.x > min_velocity) {
		velocity.x = min_velocity;
	}
}

void Demon::happy(void){
	setState(HAPPY);
	velocity.x -= 4;
	if(velocity.x < max_velocity) {
		velocity.x = max_velocity;
	}
}

void Demon::setState(State _state){
	state = _state;
	if(state == NORMAL) {
		anim_frame_duration=10;
		anim_frame_counter = 0;
		cur_frame = 0;
	} else if (state == HURT) {
		anim_frame_duration=20;
		anim_frame_counter = 0;
		cur_frame = 2;
	} else if (state == HAPPY) {
		anim_frame_duration=20;
		anim_frame_counter = 0;
		cur_frame = 3;
	}
}