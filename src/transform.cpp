#include "transform.h"

#include "aabb.h"

#define DEGREE_TO_RADIAN_COEF_F (M_PI / 180.0f)

const static float FLOAT_MAX = std::numeric_limits<float>::max();

bool translate::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
    ray moved_ray(_ray.origin() - displacement, _ray.direction(), _ray.get_time());
    if(target->hit(moved_ray, t_min, t_max, rec) == true)
    {
        rec.hit_point += displacement;
        return true;
    }
    return false;
}

bool translate::bounding_box(float t0, float t1, aabb& _box) const
{
    if(target->bounding_box(t0, t1, _box) == true)
    {
        _box = aabb(_box.get_min() + displacement, _box.get_max() + displacement);
        return true;
    }
    return false;
}

rotate_y::rotate_y(std::shared_ptr<hitable> _target, float _angle)
    : target(_target)
{
    float angle_in_radians = DEGREE_TO_RADIAN_COEF_F * _angle;
    sin_theta = std::sin(angle_in_radians);
    cos_theta = std::cos(angle_in_radians);
    isBoundedByBox = target->bounding_box(0.0f, 1.0f, target_aabb);


    vec3 minimal(FLOAT_MAX, FLOAT_MAX, FLOAT_MAX);
    vec3 maximal(-FLOAT_MAX, -FLOAT_MAX, -FLOAT_MAX);

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                float x = i * target_aabb.get_max().x()
                    + (1 - i) * target_aabb.get_min().x();
                float y = j * target_aabb.get_max().y()     
                    + (1 - j) * target_aabb.get_min().y();
                float z = k * target_aabb.get_max().z()
                    + (1 - k) * target_aabb.get_min().z();

                float new_x = cos_theta * x + sin_theta * z;
                float new_z = -sin_theta * x + cos_theta * z;
                vec3 tester(new_x, y, new_z);
                for(int c = 0; c < 3; c++)
                {
                    if(tester[c] > maximal[c])
                        maximal[c] = tester[c];
                    if(tester[c] < minimal[c])
                        minimal[c] = tester[c];
                }
            }
        }
    }
    target_aabb = aabb(minimal, maximal);
}

bool rotate_y::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
    vec3 origin = _ray.origin();
    vec3 direction = _ray.direction();
    origin[0] = cos_theta * _ray.origin()[0] - sin_theta * _ray.origin()[2];
    origin[2] = sin_theta * _ray.origin()[0] + cos_theta * _ray.origin()[2];
    direction[0] = cos_theta * _ray.direction()[0] - sin_theta * _ray.direction()[2];
    direction[2] = sin_theta * _ray.direction()[0] + cos_theta * _ray.direction()[2];

    ray rotated_ray(origin, direction, _ray.get_time());
    if(target->hit(rotated_ray, t_min, t_max, rec) == true)
    {
        vec3 hit_point = rec.hit_point;
        vec3 normal = rec.normal;

        hit_point[0] = cos_theta * rec.hit_point[0] + sin_theta * rec.hit_point[2];
        hit_point[2] = -sin_theta * rec.hit_point[0] + cos_theta * rec.hit_point[2];
        normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
        normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

        rec.hit_point = hit_point;
        rec.normal = normal;
        return true;
    }
    return false;
}

bool rotate_y::bounding_box(float t0, float t1, aabb& _box) const
{
    _box = target_aabb;
    return true;
}
