#include "Sprite.h"
#include "GFX.h"
#include "Globals.h"
#include "Define.h"

Sprite::Sprite(void) :
    sprite_rects(), is_cut(false), cur_frame(0), h_flip(false), v_flip(false), anim_frame_duration(0), anim(false)
{
    reset();
}

Sprite::~Sprite(void)
{
}

void Sprite::reset()
{
    setPosition(0, 0);
    maxVelocity.x = maxVelocity.y = 16<<FPSH;
    pos.w = pos.h = 0;
    sprite_rects.clear();
    display_offset.x = display_offset.y = 0;
    is_cut = false;
    cur_frame = 0;
	anim_frame_counter = 0;
    h_flip = v_flip = false;
    opacity = 255;
    rotation = 0;
}

void Sprite::setPosition(s32 x, s32 y)
{
    pos.x = x;
    pos.y = y;
    velocity.x = velocity.y = 0;
    accel.x = accel.y = 0;
    drag.x = drag.y = 0;
}

void Sprite::update_movement(void)
{
    old_pos = pos;
    old_velocity = velocity;
    pos.y += velocity.y; // update y pos
    pos.x += velocity.x; // update x pos
}

void Sprite::update_velocity(void)
{
    if (accel.x != 0) {
        velocity.x += accel.x;
    } else {
        if (velocity.x - drag.x > 0) {
            velocity.x -= drag.x;
        } else if (velocity.x + drag.x < 0) {
            velocity.x += drag.x;
        } else {
            velocity.x = 0;
        }
    }
    if (accel.y != 0) {
        velocity.y += accel.y;
    } else {
        if (velocity.y - drag.y > 0) {
            velocity.y -= drag.y;
        } else if (velocity.y + drag.y < 0) {
            velocity.y += drag.y;
        } else {
            velocity.y = 0;
        }
    }
    if (velocity.x < -maxVelocity.x) velocity.x = -maxVelocity.x;
    if (velocity.x > maxVelocity.x) velocity.x = maxVelocity.x;
    if (velocity.y < -maxVelocity.y) velocity.y = -maxVelocity.y;
    if (velocity.y > maxVelocity.y) velocity.y = maxVelocity.y;
}

void Sprite::update_animation(void)
{
	if (anim) {
		if (anim_frame_counter++ >= anim_frame_duration) {
			cur_frame = ( cur_frame + 1 ) % anim_frames;
			anim_frame_counter = 0;
		}
	}
}

void Sprite::update(void)
{
    update_velocity();
    update_movement();
    update_animation();
}

void Sprite::draw(void) const
{
    if (cur_frame >= sprite_rects.size()) return;
    const SpriteRect& sr = sprite_rects[cur_frame];
    s32 x = (pos.x>>FPSH) + display_offset.x;
    s32 y = (pos.y>>FPSH) + display_offset.y;
    rect bounds = sr.bounds;
    if (is_cut) {
        bounds.x += cut_rect.x;
        bounds.y += cut_rect.y;
        bounds.w = cut_rect.w;
        bounds.h = cut_rect.h;
    }
    GFX::blit_rotated(sr.sheet, bounds, x, y, opacity, rotation>>FPSH, h_flip, v_flip);
     /*x -= display_offset.x;
       y -= display_offset.y;
       s32 w = pos.w>>FPSH;
       s32 h = pos.h>>FPSH;
       al_draw_filled_rectangle(x, y, x+w, y+h, al_map_rgb(255, 255, 255));*/
}

void Sprite::add_sprite_rect(const char *bmp, s32 x, s32 y, s32 w, s32 h)
{
    SpriteRect sr = {bmp, {x, y, w, h}};
    sprite_rects.push_back(sr);
}
