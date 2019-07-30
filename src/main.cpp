#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>

// add parallel
#include "ThreadPool.h"

#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include "util.h"

struct color255
{
    // these members should be between 0 and 255 at all time
    // I ignore checking here for simplicity.
    int r,g,b;    
};

// anonymous namespace for global variables in single compilation unit
namespace
{
    const int image_width = 1024;
    const int image_height = 768;
    const float width_to_height_ratio = (float)image_width / (float)image_height;

    const int msaa_sample_count = 100;

    const std::shared_ptr<hitable> world = random_scene();

    const vec3 lookfrom(13.0f, 2.0f, 3.0f);
    const vec3 lookat(0.0f, 0.0f, -1.0f);
    const vec3 up(0.0f, 1.0f, 0.0f);
    const float distance_to_focus = 10.0f;
    const float aperture = 0.1f;

    const camera cam(lookfrom, lookat, up, 20.0f, width_to_height_ratio, aperture, distance_to_focus);

    color255 image[image_width][image_height];
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

void thread_entry(int i, int j)
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

    //std::cout << r01 << " " << g01 << " " << b01 << "\n";
    image[i][j].r = r01;
    image[i][j].g = g01;
    image[i][j].b = b01;
}

int main()
{
    srand48(int(time(0)));

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    
    {
        // since the destructor of ThreadPool joins all thread
        // I use a simple scope to wait for all works to be done
        ThreadPool pool(10000);

        // Into the screen is negative z axis
        for(int j = image_height - 1; j >= 0; j--)
        {
            for(int i = 0; i < image_width; i++)
            {
                pool.enqueue(thread_entry, i, j);
            }
        }
    }

    for(int j = image_height - 1; j >= 0; j--)
    {
        for(int i = 0; i < image_width; i++)
        {
            std::cout << image[i][j].r << " " 
                << image[i][j].g << " " 
                << image[i][j].b << "\n";
        }
    }
}