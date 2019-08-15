#ifndef BOXH
#define BOXH

#include "hitable.h"

#include <vector>

#include "hitable_list.h"

class box : public hitable
{
public:
    box(const vec3& _min, const vec3& _max, std::shared_ptr<material> _material);

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

private:
    vec3 min_point, max_point;
    hitable_list rect_list;
};

#endif