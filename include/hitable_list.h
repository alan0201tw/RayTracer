#ifndef HITTABLELISTH
#define HITTABLELISTH

#include <vector>
#include <memory>

#include "hitable.h"

class hitable_list : public hitable
{
public:

    typedef std::shared_ptr<hitable> hitable_reference;

    hitable_list() {}
    hitable_list(const std::vector<hitable_reference>& _list, int n)
    {
        list = _list;
        list_size = n;
    }
    
    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

    std::vector<hitable_reference> list;
    int list_size;
};

#endif