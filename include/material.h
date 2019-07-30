#ifndef MATERIALH
#define MATERIALH

#include <algorithm>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

class material
{
public:
    virtual bool scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const = 0;
};

class lambertian : public material
{
public:
    lambertian(const vec3& _albedo) : albedo(_albedo) {}

    virtual bool scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const override;

    vec3 albedo;
};

class metal : public material
{
public:
    metal(const vec3& _albedo, float _fuzziness) : albedo(_albedo)
    {
        fuzziness = std::clamp(_fuzziness, 0.0f, 1.0f);
    }
    
    virtual bool scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const override;

    vec3 albedo;
    float fuzziness;
};

class dielectric : public material
{
public:
    dielectric(float _ri) : refractive_index(_ri) {}

    virtual bool scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const override;

    float refractive_index;
};


#endif