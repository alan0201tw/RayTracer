#include "flip_normals.h"

bool flip_normals::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
    if(target->hit(_ray, t_min, t_max, rec) == true)
    {
        rec.normal = -rec.normal;
        return true;
    }
    return false;
}

bool flip_normals::bounding_box(float t0, float t1, aabb& _box) const
{
    return target->bounding_box(t0, t1, _box);
}