#ifndef AABBH
#define AABBH

#include "ray.h"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class aabb
{
public:
    aabb() {}
    aabb(const vec3& _min, const vec3& _max) : min(_min), max(_max) {}

    vec3 get_min() { return min; }
    vec3 get_max() { return max; }

    bool hit(const ray& _ray, float t_min, float t_max) const;

private:
    vec3 min;
    vec3 max;
};

aabb surrounding_box(aabb box0, aabb box1);


#endif