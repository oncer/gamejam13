#include "GFX.h"

BitmapLib& bmplib()
{
    static BitmapLib _bmp;
    return _bmp;
}

BitmapLib::BitmapLib(void)
{
}

BitmapLib::~BitmapLib(void)
{
}

void BitmapLib::LOAD(const char* id, const char* fname)
{
    ALLEGRO_BITMAP* bmp = al_load_bitmap(fname);
    if (bmp == NULL) throw std::runtime_error(std::string("[BitmapLib] Error loading ") + fname);
    int format = al_get_bitmap_format(bmp);
    if (format & ALLEGRO_PIXEL_FORMAT_ANY_NO_ALPHA) {
        al_convert_mask_to_alpha(bmp, al_map_rgb(39, 151, 255));
    }
    m_index[id] = bmp;
}

void BitmapLib::load()
{
    LOAD("background",      "gfx/background.png");
    LOAD("demon",           "gfx/demon.png");
    LOAD("font0",           "gfx/font.png");
    LOAD("notes",           "gfx/notes.png");
	LOAD("blood",			"gfx/blood.png");
    LOAD("player",          "gfx/player.png");
	LOAD("ghost",			"gfx/ghost.png");
	LOAD("particles",		"gfx/particles.png");
    LOAD("filter_dark",     "gfx/filter_dark.png");
    LOAD("filter_film",     "gfx/filter_film.png");

    int rng0[] = {32, 127};
    font[FONT_DEFAULT] = al_grab_font_from_bitmap(get("font0"), 1, rng0);
}

ALLEGRO_BITMAP* BitmapLib::get(const char* id)
{
    IndexMap::iterator it = m_index.find(std::string(id));
    if (it != m_index.end()) {
        return it->second;
    }
    throw std::runtime_error(std::string("[BitmapLib] No bitmap with id ") + id + std::string(" found"));
}

point BitmapLib::getDimensions(const char* id)
{
    ALLEGRO_BITMAP* bmp = get(id);
    point dimensions = {al_get_bitmap_width(bmp), al_get_bitmap_height(bmp)};
    return dimensions;
}

GFX::GFX(void)
{
}

GFX::~GFX(void)
{
}

void GFX::init(void)
{
    bmplib().load();
}

void GFX::blit(const char* bmp, const rect& src, s32 dst_x, s32 dst_y)
{
    ALLEGRO_BITMAP* allegro_bitmap = bmplib().get(bmp);
    al_draw_bitmap_region(allegro_bitmap, src.x, src.y, src.w, src.h, (float)dst_x, (float)dst_y, 0);
}

void GFX::blit_alpha(const char* bmp, const rect& src, s32 dst_x, s32 dst_y, u8 alpha, bool h_flip, bool v_flip)
{
    ALLEGRO_BITMAP* allegro_bitmap = bmplib().get(bmp);
    s32 flags = 0;
    if (h_flip) flags |= ALLEGRO_FLIP_HORIZONTAL;
    if (v_flip) flags |= ALLEGRO_FLIP_VERTICAL;
    al_draw_tinted_bitmap_region(allegro_bitmap, al_map_rgba(alpha, alpha, alpha, alpha),
            src.x, src.y, src.w, src.h, (float)dst_x, (float)dst_y, 0);
}

void GFX::blit_flipped(const char* bmp, const rect& src, s32 dst_x, s32 dst_y, bool h_flip, bool v_flip)
{
    ALLEGRO_BITMAP* allegro_bitmap = bmplib().get(bmp);
    s32 flags = 0;
    if (h_flip) flags |= ALLEGRO_FLIP_HORIZONTAL;
    if (v_flip) flags |= ALLEGRO_FLIP_VERTICAL;
    al_draw_bitmap_region(allegro_bitmap,
            src.x, src.y, src.w, src.h, (float)dst_x, (float)dst_y, flags);
}

void GFX::blit_rotated(const char *bmp, const rect &src, s32 dst_x, s32 dst_y, u8 alpha, s32 angle, bool h_flip, bool v_flip)
{
    const float DEG2RAD = 0.017453293f;
    ALLEGRO_BITMAP* allegro_bitmap = bmplib().get(bmp);
    s32 flags = 0;
    if (h_flip) flags |= ALLEGRO_FLIP_HORIZONTAL;
    if (v_flip) flags |= ALLEGRO_FLIP_VERTICAL;
    al_draw_tinted_scaled_rotated_bitmap_region(allegro_bitmap,
            src.x, src.y, src.w, src.h,
            al_map_rgba(alpha, alpha, alpha, alpha),
            (float)src.w/2.0f, (float)src.h/2.0f,
            (float)dst_x + (float)src.w/2.0f, (float)dst_y + (float)src.h/2.0f,
            1.0f, 1.0f,
            (float)angle * DEG2RAD, flags);
}

void GFX::text(FontType font, s32 dst_x, s32 dst_y, const char *str, u32 color)
{
    ALLEGRO_FONT* alFont = bmplib().getFont(font);
    ALLEGRO_COLOR alColor = al_map_rgba(color>>24, (color>>16)&0xff, (color>>8)&0xff, color&0xff);
    al_draw_text(alFont, alColor, dst_x, dst_y, 0, str);
}

