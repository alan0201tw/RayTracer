#include "hitable_list.h"

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