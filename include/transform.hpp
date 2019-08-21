#ifndef TRANSFORMH
#define TRANSFORMH

#include "hitable.hpp"

#include "aabb.hpp"

class translate : public hitable
{
public:
    translate(std::shared_ptr<hitable> _target, const vec3& _displacement)
        : target(_target), displacement(_displacement) {}

    bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    bool bounding_box(float t0, float t1, aabb& _box) const override;

private:
    std::shared_ptr<hitable> target;
    vec3 displacement;
};

class rotate_y : public hitable
{
public:
    rotate_y(std::shared_ptr<hitable> _target, float _angle);

    bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    bool bounding_box(float t0, float t1, aabb& _box) const override;

private:
    std::shared_ptr<hitable> target;

    float sin_theta;
    float cos_theta;
    bool isBoundedByBox;
    aabb target_aabb;
};


#endif