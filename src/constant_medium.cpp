#include "constant_medium.hpp"

#include "material.hpp"

const static float FLOAT_MAX = std::numeric_limits<float>::max();

constant_medium::constant_medium(std::shared_ptr<hitable> _boundary, float _density, std::shared_ptr<texture> _texture)
    : boundary(_boundary), density(_density)
{
    phase_function = std::make_shared<isotropic>(_texture);
}

bool constant_medium::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
    //bool db = false;
    hit_record rec1, rec2;

    if(boundary->hit(_ray, -FLOAT_MAX, FLOAT_MAX, rec1) == true)
    {
        if(boundary->hit(_ray, rec1.t + 0.0001f, FLOAT_MAX, rec2) == true)
        {
            if(rec1.t < t_min)
            {
                rec1.t = t_min;
            }
            if(rec2.t > t_max)
            {
                rec2.t = t_max;
            }
            if(rec1.t >= rec2.t)
            {
                return false;
            }
            if(rec1.t < 0)
            {
                rec1.t = 0;
            }
            float distance_inside_boundary = (rec2.t - rec1.t) * _ray.direction().length();
            float hit_distance = -(1 / density) * std::log(drand48());
            if(hit_distance < distance_inside_boundary)
            {
                rec.t = rec1.t + hit_distance / _ray.direction().length();
                rec.hit_point = _ray.point_at_parameter(rec.t);
                rec.normal = vec3(1, 0, 0); // arbitrary
                rec.material_ref = phase_function;
                return true;
            }
        }
    }
    return false;
}

bool constant_medium::bounding_box(float t0, float t1, aabb& _box) const
{
    return boundary->bounding_box(t0, t1, _box);
}
