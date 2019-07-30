#include "material.h"

#include "util.h"

bool lambertian::scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const
{
    vec3 target = _record.hit_point + _record.normal + random_in_unit_sphere();
    _scattered_ray = ray(_record.hit_point, target - _record.hit_point);
    _attenuation = albedo;
    
    return true;
}

bool metal::scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const
{
    vec3 reflected = reflect(unit_vector(_incoming_ray.direction()), _record.normal);
    _scattered_ray = ray(_record.hit_point, reflected + fuzziness * random_in_unit_sphere());
    _attenuation = albedo;

    return true;
}

bool dielectric::scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const
{
    vec3 reflected = reflect(_incoming_ray.direction(), _record.normal);
    
    float ni_over_nt;
    _attenuation = vec3(1.0f, 1.0f, 1.0f);
    
    vec3 outward_normal;
    float cosine;
    if(dot(_incoming_ray.direction(), _record.normal) > 0.0f)
    {
        outward_normal = -1 * _record.normal;
        ni_over_nt = refractive_index;
        cosine = refractive_index * dot(_incoming_ray.direction(), _record.normal) / _incoming_ray.direction().length();
    }
    else
    {
        outward_normal = _record.normal;
        ni_over_nt = 1.0f / refractive_index;
        cosine = -1 * dot(_incoming_ray.direction(), _record.normal) / _incoming_ray.direction().length();
    }
    
    vec3 refracted;
    float reflect_prob;
    if(refract(_incoming_ray.direction(), outward_normal, ni_over_nt, refracted))
    {
        reflect_prob = schlick(cosine, refractive_index);
    }
    else
    {
        reflect_prob = 1.0f;
    }

    if(drand48() < reflect_prob)
    {
        _scattered_ray = ray(_record.hit_point, reflected);
    }
    else
    {
        _scattered_ray = ray(_record.hit_point, refracted);
    }
    
    return true;
}