#ifndef HITABLEH
#define HITABLEH

#include <memory>

#include "vec3.h"
#include "ray.h"

class material;
class aabb;

struct hit_record
{
    float t;
    float u, v;
    vec3 hit_point;
    vec3 normal;
    std::shared_ptr<material> material_ref;
};

// an interface for hittable classes to implement
class hitable
{
public:
    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const = 0;
    // return true if this object should be restricted by a bounding box, 
    // and also fill in the aabb argument with min, max info.
    virtual bool bounding_box(float t0, float t1, aabb& _box) const = 0;
};

#endif