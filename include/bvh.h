#ifndef BVHH
#define BVHH

#include "hitable.h"
#include "aabb.h"

#include <memory>
#include <vector>

class bvh_node : public hitable
{
private:
    typedef std::shared_ptr<hitable> hitable_reference;

public:
    bvh_node() {}
    bvh_node(const std::vector<hitable_reference>& _list, int _list_size, float _t0, float _t1);

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

    // this is used for representing a node tree with a single reference to a root node
    hitable_reference left;
    hitable_reference right;
    aabb box;
};

#endif