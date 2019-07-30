#ifndef HITABLEH
#define HITABLEH

#include <memory>

#include "vec3.h"
#include "ray.h"

class material;

struct hit_record
{
    float t;
    vec3 hit_point;
    vec3 normal;
    std::shared_ptr<material> material_ref;
};

// an interface for hittable classes to implement
class hitable
{
public:
    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif