#include "aabb.h"

bool aabb::hit(const ray& _ray, float t_min, float t_max) const
{
    for (int a = 0; a < 3; a++)
    {
        float t0 = ffmin((min[a] - _ray.origin()[a]) / _ray.direction()[a],
                        (max[a] - _ray.origin()[a]) / _ray.direction()[a]);
        float t1 = ffmax((min[a] - _ray.origin()[a]) / _ray.direction()[a],
                        (max[a] - _ray.origin()[a]) / _ray.direction()[a]);
        t_min = ffmax(t0, t_min);
        t_max = ffmin(t1, t_max);
        if (t_max <= t_min)
        {
            return false;
        }
    }
    return true;

    // Reference : Andrew Kensler at Pixar ( mentioned in Ray Tracing: The Next Week, page 11 )

    // for (int a = 0; a < 3; a++)
    // {
    //     float invD = 1.0f / _ray.direction()[a];
    //     float t0 = (min[a] - _ray.origin()[a]) * invD;
    //     float t1 = (max[a] - _ray.origin()[a]) * invD;

    //     if(invD < 0.0f)
    //     {
    //         std::swap(t0, t1);
    //     }

    //     t_min = t0 > t_min ? t0 : t_min;
    //     t_max = t1 > t_max ? t1 : t_max;
        
    //     if(t_max <= t_min)
    //     {
    //         return false;
    //     }
    // }
    // return true;
}

aabb surrounding_box(aabb box0, aabb box1)
{
    vec3 minimum( fmin(box0.get_min().x(), box1.get_min().x() ),
                  fmin(box0.get_min().y(), box1.get_min().y() ),
                  fmin(box0.get_min().z(), box1.get_min().z() ));
    vec3 maximum( fmax(box0.get_max().x(), box1.get_max().x() ),
                  fmax(box0.get_max().y(), box1.get_max().y() ),
                  fmax(box0.get_max().z(), box1.get_max().z() ));
    
    return aabb(minimum, maximum);
}