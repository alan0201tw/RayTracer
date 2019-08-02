#ifndef CAMERAH
#define CAMERAH

#include "ray.h"
#include "util.h"

class camera
{
public:

    camera(const vec3& _lookfrom, const vec3& _lookat, const vec3& _up , float _vfov, float _aspect, float _aperture, float _focus_distance)
    {
        float theta = _vfov * M_PI / 180.0f;
        float half_height = tan(theta / 2.0f);
        float half_width = _aspect * half_height;

        origin = _lookfrom;
        camera_forward = unit_vector(_lookfrom - _lookat);
        camera_right = unit_vector( cross(_up, camera_forward) );
        camera_up = unit_vector( cross(camera_forward, camera_right) );

        lens_radius = _aperture / 2.0f;

        lower_left_corner = origin - half_width * _focus_distance * camera_right 
            - half_height * _focus_distance * camera_up - _focus_distance * camera_forward;
        
        horizontal = 2.0f * half_width * _focus_distance * camera_right;
        vertical = 2.0f * half_height * _focus_distance * camera_up;
    }
        
    inline ray get_ray(float u, float v) const
    {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = camera_right * rd.x() + camera_up * rd.y();
        return ray(origin + offset, lower_left_corner + u * horizontal + v * vertical - origin - offset);
    }

    vec3 lower_left_corner; 
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;

    vec3 camera_forward;
    vec3 camera_right;
    vec3 camera_up;

    float lens_radius;
};

#endif