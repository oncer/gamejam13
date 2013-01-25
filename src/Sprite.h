#pragma once

#include "sdk.h"
#include "Define.h"

class Sprite
{
    public:
        Sprite(void);
        virtual ~Sprite(void);

        void reset(void);

        inline const rect& getPosition() const { return pos; }
        inline const point& getVelocity() const { return velocity; }
        inline const point& getAcceleration() const { return accel; }

        inline point getCenter() const {
            return get_center(pos);
        }
        inline void setCenter(const point& p) {
            set_center(pos, p);
        }

        virtual void setPosition(s32 x, s32 y);
        // to compensate for display offset when placing objects based on sprite rect
        void moveByDisplayOffset() {
            pos.x -= display_offset.x << FPSH;
            pos.y -= display_offset.y << FPSH;
        }

        virtual void update(void);
        virtual void draw(void) const;

        void add_sprite_rect(const char* bmp, s32 x, s32 y, s32 w, s32 h);

        void cut(s32 x, s32 y, s32 w, s32 h) {
            cut_rect.x = x; cut_rect.y = y; cut_rect.w = w; cut_rect.h = h;
            is_cut = true;
        }

        void uncut() {
            is_cut = false;
        }

        typedef struct
        {
            const char* sheet;
            rect bounds;
        } SpriteRect;

    protected:
        // pos, old_pos, velocity, accel, drag are in subpixels
        rect pos, old_pos;
        point velocity;
        point old_velocity; // before collision
        point accel;
        point drag;
        point maxVelocity;

        bool collisionResponse;
        u32 collision_flags;
        //bool on_slope;
        //s32 slope_tile_x, slope_tile_y;
        //s8 slope_idx(void);

        void update_velocity();
        void update_movement();

        std::vector<SpriteRect> sprite_rects;
        rect cut_rect;
        bool is_cut;

        u32 cur_frame;
        point display_offset;
        u8 opacity;
        s32 rotation;

        bool h_flip, v_flip;

};
