#pragma once

#include "sdk.h"

enum FontType {
    FONT_DEFAULT = 0,
    NUM_FONTS
};

class BitmapLib
{
    public:
        BitmapLib(void);
        ~BitmapLib(void);

        void load(void);
        ALLEGRO_BITMAP* get(const char* id);
        ALLEGRO_FONT* getFont(FontType type) { return font[type]; }
        point getDimensions(const char *id);
    protected:

        void LOAD(const char* id, const char* fname);

        typedef std::map<std::string, ALLEGRO_BITMAP*> IndexMap;
        IndexMap m_index;
        ALLEGRO_FONT* font[NUM_FONTS];
};

extern BitmapLib& bmplib(); // singleton

class GFX
{
    public:
        static void init(void);
        static void blit(const char* bmp, const rect& src, s32 dst_x, s32 dst_y);
        static void blit_alpha(const char* bmp, const rect& src, s32 dst_x, s32 dst_y, u8 alpha, bool h_flip=false, bool v_flip=false);
        static void blit_flipped(const char* bmp, const rect& src, s32 dst_x, s32 dst_y, bool h_flip, bool v_flip);
        static void blit_rotated(const char* bmp, const rect& src, s32 dst_x, s32 dst_y, u8 alpha, s32 angle, bool h_flip=false, bool v_flip=false);

        static void text(FontType font, s32 dst_x, s32 dst_y, const char* str, u32 color=0xffffffff);
		static void text_center(FontType font, s32 dst_x, s32 dst_y, const char *str, u32 color=0xffffffff);
    private:
        GFX(void);
        virtual ~GFX(void);
};
