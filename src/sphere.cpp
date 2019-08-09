#include "sphere.h"

#include "aabb.h"
#include "util.h"

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
            // obtaining texture coordinate
            get_sphere_uv((rec.hit_point - center) / radius, rec.u, rec.v);
            //
            rec.normal = (rec.hit_point - center) / radius;
            rec.material_ref = sphere_mat;
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;

        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.hit_point = _ray.point_at_parameter(rec.t);
            // obtaining texture coordinate
            get_sphere_uv((rec.hit_point - center) / radius, rec.u, rec.v);
            //
            rec.normal = (rec.hit_point - center) / radius;
            rec.material_ref = sphere_mat;
            return true;
        }
    }
    
    return false;
}

bool sphere::bounding_box(float t0, float t1, aabb& _box) const
{
    vec3 radius_vector(radius, radius, radius);

    _box = aabb( center - radius_vector, center + radius_vector );
    return true;
}

bool moving_sphere::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
    vec3 current_center = center(_ray.get_time());
    vec3 oc = _ray.origin() - current_center;
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
            // obtaining texture coordinate
            get_sphere_uv((rec.hit_point - current_center) / radius, rec.u, rec.v);
            //
            rec.normal = (rec.hit_point - current_center) / radius;
            rec.material_ref = moving_sphere_mat;
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;

        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.hit_point = _ray.point_at_parameter(rec.t);
            // obtaining texture coordinate
            get_sphere_uv((rec.hit_point - current_center) / radius, rec.u, rec.v);
            //
            rec.normal = (rec.hit_point - current_center) / radius;
            rec.material_ref = moving_sphere_mat;
            return true;
        }
    }
    
    return false;
}

bool moving_sphere::bounding_box(float t0, float t1, aabb& _box) const
{
    vec3 radius_vector(radius, radius, radius);
    aabb box_at_t0( center(t0) - radius_vector, center(t0) + radius_vector );
    aabb box_at_t1( center(t1) - radius_vector, center(t1) + radius_vector );

    _box = surrounding_box(box_at_t0, box_at_t1);
    return true;
}