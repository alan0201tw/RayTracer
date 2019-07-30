#include "sphere.h"

bool sphere::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
    vec3 oc = _ray.origin() - center;
    float a = dot(_ray.direction(), _ray.direction());
    float b = dot(oc, _ray.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - a*c;

    if(discriminant > 0.0f)
    {
        float temp = (-b - sqrt(discriminant)) / a;

        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.hit_point = _ray.point_at_parameter(rec.t);
            rec.normal = (rec.hit_point - center) / radius;
            rec.material_ref = sphere_mat;
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;

        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.hit_point = _ray.point_at_parameter(rec.t);
            rec.normal = (rec.hit_point - center) / radius;
            rec.material_ref = sphere_mat;
            return true;
        }
    }
    
    return false;
}