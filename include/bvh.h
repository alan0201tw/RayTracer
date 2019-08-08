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
    class box_x_compare
    {
    public:
        bool operator()(const hitable_reference& a, const hitable_reference& b) const;
    };
    class box_y_compare
    {
    public:
        bool operator()(const hitable_reference& a, const hitable_reference& b) const;
    };
    class box_z_compare
    {
    public:
        bool operator()(const hitable_reference& a, const hitable_reference& b) const;
    };

public:
    bvh_node() {}
    bvh_node(const std::vector<hitable_reference>& _list, float _t0, float _t1);

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

    // this is used for representing a node tree with a single reference to a root node
    hitable_reference left;
    hitable_reference right;
    aabb box;

    //
    std::vector<hitable_reference> list;
};

#endif