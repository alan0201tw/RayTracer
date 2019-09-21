#ifndef TRIANGLEH
#define TRIANGLEH

#include "hitable.hpp"

class triangle : public hitable
{
public:
    // we can extend it to hold normal and texture coordinate information later
    triangle(const vec3& _v0, const vec3& _v1, const vec3& _v2, std::shared_ptr<material> _material);

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

private:
    vec3 v0, v1, v2;
    vec3 normal;
    std::shared_ptr<material> triangle_mat;
};

#endif
