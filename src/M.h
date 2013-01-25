#pragma once

#define NOMINMAX

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <cstdio>

#if _MSC_VER
#define snprintf _snprintf
#endif

#ifndef M_PI
const double M_PI = 3.141592653589793;
#endif

typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint64_t u64;
typedef int64_t s64;

struct point {
    s32 x,y;
};

struct rect {
    union { s32 x, x1; };
    union { s32 y, y1; };
    union { s32 w, x2; };
    union { s32 h, y2; };
};

point get_center(const rect& r);
void set_center(rect& r, const point& p);
rect get_collision(const rect &r1, const rect &r2);
bool is_collision(const rect& coll);
point get_distance(const rect& r1, const rect& r2);
point get_distance(const point& p1, const point& p2);
s32 get_distance_value(const point& p1, const point& p2);
s32 get_distance_qvalue(const point& p1, const point& p2); // distance value to the power of 2. this is faster than get_distance_value
point fpsh_l(const point& p);
point fpsh_r(const point& p);
s32 randint(s32 min, s32 max); // min inclusive, max exclusive
std::vector<std::string> split(const std::string &s, char delim);
s32 div_down(s32 dividend, s32 divisor); // result is rounded toward negative infinity
u32 isqrt(u32 a);
s32 fp_atan2(const point& p);
s32 fp_sin(s32 angle);
s32 fp_cos(s32 angle);
point motion_vector(const point& direction, s32 speed);

void pc_start();
void pc_end(const char* name);
