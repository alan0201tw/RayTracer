#include "bvh.h"

bool bvh_node::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
    if(box.hit(_ray, t_min, t_max))
    {
        hit_record left_record, right_record;
        bool hit_left = left->hit(_ray, t_min, t_max, left_record);
        bool hit_right = right->hit(_ray, t_min, t_max, right_record);

        if(hit_left && hit_right)
        {
            if(left_record.t < right_record.t)
            {
                rec = left_record;
                return true;
            }
            else
            {
                rec = right_record;
                return true;
            }
        }
        else if(hit_left)
        {
            rec = left_record;
            return true;
        }
        else if(hit_right)
        {
            rec = right_record;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool bvh_node::bounding_box(float t0, float t1, aabb& _box) const
{
    _box = box;
    return true;
}
