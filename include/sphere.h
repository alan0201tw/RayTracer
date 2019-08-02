#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere : public hitable
{
public:
    sphere() {}
    sphere(const vec3& _center, float _radius, std::shared_ptr<material> _material) : center(_center), radius(_radius), sphere_mat(_material) {}

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

private:
    vec3 center;
    float radius;
    std::shared_ptr<material> sphere_mat;
};

class moving_sphere : public hitable
{
public:
    moving_sphere() {}
    moving_sphere(const vec3& _starting_center, const vec3& _ending_center, float _start_time, float _end_time, float _radius, std::shared_ptr<material> _material) : starting_center(_starting_center), ending_center(_ending_center), start_time(_start_time), end_time(_end_time), radius(_radius), moving_sphere_mat(_material) {}

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

    inline vec3 center(float time) const
    {
        return starting_center + (time - start_time) / (end_time - start_time) * (ending_center - starting_center);
    }

    vec3 starting_center;
    vec3 ending_center;
    float start_time;
    float end_time;
    float radius;
    std::shared_ptr<material> moving_sphere_mat;
};

#endif