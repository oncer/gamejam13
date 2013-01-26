#include "M.h"
#include "Define.h"

point get_center(const rect &r)
{
    point p={r.x + r.w/2, r.y + r.h/2};
	return p;
}

void set_center(rect& r, const point& p)
{
    r.x = p.x - r.w/2;
    r.y = p.y - r.h/2;
}

rect get_collision(const rect& r1, const rect& r2)
{
    rect c;
    c.x1 = (r2.x + r2.w) - r1.x;
    c.x2 = (r1.x + r1.w) - r2.x;
    c.y1 = (r2.y + r2.w) - r1.y;
    c.y2 = (r1.y + r1.h) - r2.y;
    return c;
}

bool is_collision(const rect& coll)
{
    return (coll.x1 > 0 && coll.x2 > 0 && coll.y1 > 0 && coll.y2 > 0);
}

rect merge_rects(const rect& r1, const rect& r2)
{
    rect c;
    c.x1 = std::min(r1.x1, r2.x1);
    c.x2 = std::max(r1.x2, r2.x2);
    c.y1 = std::min(r1.y1, r2.y1);
    c.y2 = std::max(r1.y2, r2.y2);
    return c;
}


point get_distance(const point& p1, const point& p2)
{
    point p = {p2.x - p1.x, p2.y - p1.y};
    return p;
}

point get_distance(const rect& r1, const rect& r2)
{
    return get_distance(get_center(r1), get_center(r2));
}


s32 get_distance_value(const point& p1, const point& p2)
{
    point d = get_distance(p1, p2);
    return isqrt((u32)(d.x*d.x + d.y*d.y));
}

s32 get_distance_qvalue(const point& p1, const point& p2) {
    point d = get_distance(p1, p2);
    return d.x*d.x + d.y*d.y;
}

point fpsh_l(const point& p)
{
    point r;
    r.x = p.x<<FPSH;
    r.y = p.y<<FPSH;
    return r;
}

point fpsh_r(const point& p)
{
    point r;
    r.x = p.x>>FPSH;
    r.y = p.y>>FPSH;
    return r;
}

s32 randint(s32 min, s32 max)
{
    return min + rand()%(max-min);
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

s32 div_down(s32 dividend, s32 divisor)
{
    return (dividend / divisor) + ((dividend % divisor) >> 31);
}

u32 isqrt(u32 a)
{
    u32 op  = a;
    u32 res = 0;
    u32 one = 1uL << 30; // The second-to-top bit is set: use 1u << 14 for uint16_t type; use 1uL<<30 for uint32_t type

    // "one" starts at the highest power of four <= than the argument.
    while (one > op)
    {
        one >>= 2;
    }

    while (one != 0)
    {
        if (op >= res + one)
        {
            op = op - (res + one);
            res = res +  2 * one;
        }
        res >>= 1;
        one >>= 2;
    }
    return res;
}

point motion_vector(const point& direction, s32 speed)
{
    point v;
    s32 l = (s32)isqrt(direction.x*direction.x + direction.y*direction.y);
    if (l == 0) {
        v.x = v.y = 0;
    } else {
        v.x = direction.x * speed / l;
        v.y = direction.y * speed / l;
    }
    return v;
}

s32 fp_atan2(const point& p)
{
    double dPX = (double)PX;
    return (s32)(atan2((double)p.y / dPX, (double)p.x / dPX) * 180.0 / M_PI * dPX);
}

s32 fp_sin(s32 angle)
{
    double dPX = (double)PX;
    return (s32)(sin((double)angle / dPX * M_PI / 180.0) * dPX);
}

s32 fp_cos(s32 angle)
{
    double dPX = (double)PX;
    return (s32)(cos((double)angle / dPX * M_PI / 180.0) * dPX);
}

int bpm_to_frames(int bpm) {
	return (int) (FPS/(((double)bpm)/60));
}


static double pc_tm;
void pc_start()
{
    pc_tm = al_get_time();
}

void pc_end(const char* name)
{
    double pc_dur = al_get_time() - pc_tm;
    std::cout << "pc(" << name << "): " << pc_dur * 1000000.0 << "µs" << std::endl;
    pc_tm = al_get_time();
}

