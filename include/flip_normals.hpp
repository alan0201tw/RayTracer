#ifndef FLIPNORMALSH
#define FLIPNORMALSH

#include "hitable.hpp"

#include <memory>

class flip_normals : public hitable
{
public:
    flip_normals(std::shared_ptr<hitable> _target) : target(_target) {}

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

private:
    std::shared_ptr<hitable> target;
};

#endif