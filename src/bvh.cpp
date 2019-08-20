#include "bvh.hpp"

#include <algorithm>

bool bvh_node::box_x_compare::operator() (const hitable_reference& a, const hitable_reference& b) const
{
    aabb box_left, box_right;
    if(a->bounding_box(0, 0, box_left) == false || b->bounding_box(0, 0, box_right) == false)
    {
        std::cerr << "No bounding box in bvh_node constructor!\n";
    }

    // IMPORTANT !!!
    // Reference : https://stackoverflow.com/questions/1541817/sort-function-c-segmentation-fault
    // In C++, your "compare" predicate must be a strict weak ordering.
    // In particular, "compare(X,X)" must return "false" for any X.
    // ... (Otherwise) Therefore, this "compare" predicate does not impose a strict weak ordering,
    // and the result of passing it to "sort" is undefined.

    if(box_left.get_min().x() - box_right.get_min().x() <= 0.0f)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool bvh_node::box_y_compare::operator() (const hitable_reference& a, const hitable_reference& b) const
{
    aabb box_left, box_right;
    if(a->bounding_box(0, 0, box_left) == false || b->bounding_box(0, 0, box_right) == false)
    {
        std::cerr << "No bounding box in bvh_node constructor!\n";
    }

    if(box_left.get_min().y() - box_right.get_min().y() <= 0.0f)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool bvh_node::box_z_compare::operator() (const hitable_reference& a, const hitable_reference& b) const
{
    aabb box_left, box_right;
    if(a->bounding_box(0, 0, box_left) == false || b->bounding_box(0, 0, box_right) == false)
    {
        std::cerr << "No bounding box in bvh_node constructor!\n";
    }

    if(box_left.get_min().z() - box_right.get_min().z() <= 0.0f)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bvh_node::bvh_node(const std::vector<hitable_reference>& _list, float _t0, float _t1)
{
    list = _list;

    int list_size = (int)list.size();

    //std::cout << "list_size = " << list_size << "\n";

    int random_axis = int(3 * drand48());
    if(random_axis == 0)
    {
        // Reference : 
        // according to https://stackoverflow.com/questions/12308243/trying-to-use-qsort-with-vector
        // using std::sort with functor is the fastest, comparing to qsort and
        // std::sort with custom function as compare operator
        std::sort(list.begin(), list.end(), box_x_compare());
    }
    else if(random_axis == 1)
    {
        std::sort(list.begin(), list.end(), box_y_compare());
    }
    else
    {
        std::sort(list.begin(), list.end(), box_z_compare());
    }

    // edge cases when the bounding volume contains only one or two elements
    if(list_size == 1)
    {
        left = right = _list[0];
    }
    else if(list_size == 2)
    {
        left = _list[0];
        right = _list[1];
    }
    else
    {
        int half_size = list_size / 2;
        std::vector<hitable_reference> left_list(list.begin(), list.begin() + half_size);
        std::vector<hitable_reference> right_list(list.begin() + half_size, list.end());

        left = std::make_shared<bvh_node>(left_list, _t0, _t1);
        right = std::make_shared<bvh_node>(right_list, _t0, _t1);
    }

    aabb box_left, box_right;
    if(left->bounding_box(_t0, _t1, box_left) == false || right->bounding_box(_t0, _t1, box_right) == false)
    {
        std::cerr << "No bounding box in bvh_node constructor!\n";
    }
    box = surrounding_box(box_left, box_right);
}

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
