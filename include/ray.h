#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray
{
public:
    ray() {}
    ray(const vec3& a, const vec3& b, float _time)
    {
        ori = a;
        dir = b;
        time = _time;
    }

    inline vec3 origin() const       { return ori; }
    inline vec3 direction() const    { return dir; }
    inline vec3 point_at_parameter(float t) const { return ori + t * dir; }

    inline float get_time() const { return time; }

private:
    vec3 ori;
    vec3 dir;
    float time;
};

#endif 


