#include "hitable_list.hpp"

#include "aabb.hpp"

bool hitable_list::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool is_anything_hit = false;
    double closest_so_far = t_max;

    for(int i = 0; i < list_size; i++)
    {
        if(list[i]->hit(_ray, t_min, closest_so_far, temp_rec))
        {
            is_anything_hit = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return is_anything_hit;
}

bool hitable_list::bounding_box(float t0, float t1, aabb& _box) const
{
    if(list_size < 1) return false;
    aabb result;
    bool first_true = list[0]->bounding_box(t0, t1, result);
    if(!first_true)
    {
        return false;
    }
    else
    {
        _box = result;
    }
    
    for(int i = 1; i < list_size; i++)
    {
        // TODO : Is this correct?
        // Reference to github issue page : https://github.com/RayTracing/raytracingthenextweek/issues/2
        // it should be list[i] rather than list[0]
        if(list[i]->bounding_box(t0, t1, result))
        {
            _box = surrounding_box(_box, result);
        }
        else
        {
            return false;
        }
    }
    return true;
}