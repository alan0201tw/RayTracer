#include "aarect.h"

#include "aabb.h"

bool xy_rect::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const 
{
    float t = (k - _ray.origin().z()) / _ray.direction().z();
    if(t < t_min || t > t_max)
    {
        return false;
    }
    float x = _ray.origin().x() + t * _ray.direction().x();
    float y = _ray.origin().y() + t * _ray.direction().y();
    if(x < x0 || x > x1 || y < y0 || y > y1)
    {
        return false;
    }
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    rec.material_ref = rect_material;
    rec.hit_point = _ray.point_at_parameter(t);
    rec.normal = vec3(0.0f, 0.0f, 1.0f);
    return true;
}

bool xy_rect::bounding_box(float t0, float t1, aabb& _box) const
{
    _box = aabb(vec3(x0, y0, k - 0.0001f), vec3(x1, y1, k + 0.0001f));
    return true;
}