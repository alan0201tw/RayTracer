#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>

#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include "util.h"

namespace
{
    const int image_width = 1366;
    const int image_height = 768;
    const float width_to_height_ratio = (float)image_width / (float)image_height;

    const int msaa_sample_count = 10;
}

vec3 get_color(const ray& _ray, std::shared_ptr<hitable> _world, int depth)
{
    hit_record rec;
    if(_world->hit(_ray, 0.001f, MAXFLOAT, rec))
    {
        ray scattered; 
        vec3 attentuation;

        if(depth < 50 && 
            rec.material_ref->scatter(_ray, rec, attentuation, scattered))
        {
            return attentuation * get_color(scattered, _world, depth + 1);
        }
        return vec3(0, 0, 0);
    }
    else
    {
        vec3 unit_direction = unit_vector(_ray.direction());
        float t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    
    std::shared_ptr<hitable> world = random_scene();

    vec3 lookfrom(13.0f, 2.0f, 3.0f);
    vec3 lookat(0.0f, 0.0f, -1.0f);
    vec3 up(0.0f, 1.0f, 0.0f);
    float distance_to_focus = 10.0f;
    float aperture = 0.1f;

    camera cam(lookfrom, lookat, up, 20.0f, width_to_height_ratio, aperture, distance_to_focus);

    // Into the screen is negative z axis
    for(int j = image_height - 1; j >= 0; j--)
    {
        for(int i = 0; i < image_width; i++)
        {
            vec3 accumulated_col(0, 0, 0);

            for(int s = 0; s < msaa_sample_count; s++)
            {
                float u = float(i + drand48()) / float(image_width);
                float v = float(j + drand48()) / float(image_height);

                ray r = cam.get_ray(u, v);
                accumulated_col += get_color(r, world, 0);
            }
            accumulated_col /= msaa_sample_count;
            accumulated_col = vec3(sqrt(accumulated_col[0]), sqrt(accumulated_col[1]), sqrt(accumulated_col[2]));
            int r01 = int(255.99 * accumulated_col[0]);
            int g01 = int(255.99 * accumulated_col[1]);
            int b01 = int(255.99 * accumulated_col[2]);

            std::cout << r01 << " " << g01 << " " << b01 << "\n";
        }
    }

}