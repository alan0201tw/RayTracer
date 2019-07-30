#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere : public hitable
{
public:
    sphere() {}
    sphere(const vec3& _center, float _radius, std::shared_ptr<material> _material) : center(_center), radius(_radius), sphere_mat(_material) {}
    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;

private:
    vec3 center;
    float radius;
    std::shared_ptr<material> sphere_mat;
};


#endif