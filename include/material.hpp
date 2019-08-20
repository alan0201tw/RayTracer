#ifndef MATERIALH
#define MATERIALH

#include <algorithm>

#include "vec3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "texture.hpp"

class material
{
public:
    virtual bool scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const = 0;
    // the default emit function will just emit black
    virtual vec3 emitted(float _u, float _v, const vec3& _hit_point) const;
};

class lambertian : public material
{
public:
    lambertian(vec3 _albedo) : albedo( std::make_shared<constant_texture>(_albedo) ) {}
    lambertian(std::shared_ptr<texture> _albedo) : albedo(_albedo) {}

    virtual bool scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const override;

    std::shared_ptr<texture> albedo;
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

class diffuse_light : public material
{
public:
    diffuse_light(std::shared_ptr<texture> _emit) : emit(_emit) {}

    virtual bool scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const override;
    virtual vec3 emitted(float _u, float _v, const vec3& _hit_point) const override;

private:
    std::shared_ptr<texture> emit;
};

class isotropic : public material
{
public:
    isotropic(std::shared_ptr<texture> _albedo) : albedo(_albedo) {}

    virtual bool scatter(const ray& _incoming_ray,  const hit_record& _record,vec3& _attenuation, ray& _scattered_ray) const override;
    
private:
    std::shared_ptr<texture> albedo;
};


#endif