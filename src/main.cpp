#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>

// add parallel
#include "ThreadPool.h"

#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

#include "util.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// anonymous namespace for global variables in single compilation unit
namespace
{
    const int image_width = 800;
    const int image_height = 800;
    const float width_to_height_ratio = (float)image_width / (float)image_height;

    const int msaa_sample_count = 1000;

    const std::shared_ptr<hitable> world = next_week_final();

    // used for regular scene
    // const vec3 lookfrom(13.0f, 2.0f, 3.0f);
    // const vec3 lookat(0.0f, 0.0f, 0.0f);
    // const vec3 up(0.0f, 1.0f, 0.0f);
    // const float distance_to_focus = 10.0f;
    // const float aperture = 0.0f;
    // const float fov = 40.0f;
    // used for cornell box
    const vec3 lookfrom(278.0f + 100.0f, 278.0f, -800.0f);
    const vec3 lookat(278.0f, 278.0f, 0.0f);
    const vec3 up(0.0f, 1.0f, 0.0f);
    const float distance_to_focus = 10.0f;
    const float aperture = 0.0f;
    const float fov = 40.0f;

    const camera cam(lookfrom, lookat, up, fov, width_to_height_ratio, aperture, distance_to_focus, 0.0f, 1.0f);

    unsigned char image[3 * image_width * image_height];
}

vec3 get_color(const ray& _ray, std::shared_ptr<hitable> _world, int depth)
{
    hit_record rec;
    if(_world->hit(_ray, 0.001f, MAXFLOAT, rec))
    {
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.material_ref->emitted(rec.u, rec.v, rec.hit_point);

        if(depth < 50 && rec.material_ref->scatter(_ray, rec, attenuation, scattered))
        {
            return emitted + attenuation * get_color(scattered, _world, depth + 1);
        }
        else
        {
            return emitted;
        }
    }
    else // here is where the "clear color", or the "background color" lays
    {
        return vec3(0.0f, 0.0f, 0.0f);

        // the color here will also provide "brightness" when returning to last recursion

        // vec3 unit_direction = unit_vector(_ray.direction());
        // float t = 0.5f * (unit_direction.y() + 1.0f);
        // return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
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
    accumulated_col /= (float)msaa_sample_count;

    // accumulated_col[0] = std::clamp(accumulated_col[0], 0.0f, 1.0f);
    // accumulated_col[1] = std::clamp(accumulated_col[1], 0.0f, 1.0f);
    // accumulated_col[2] = std::clamp(accumulated_col[2], 0.0f, 1.0f);

    accumulated_col = vec3(std::sqrt(accumulated_col[0]), std::sqrt(accumulated_col[1]), std::sqrt(accumulated_col[2]));
    int r255 = int(255.99f * accumulated_col[0]);
    int g255 = int(255.99f * accumulated_col[1]);
    int b255 = int(255.99f * accumulated_col[2]);

    r255 = std::clamp(r255, 0, 255);
    g255 = std::clamp(g255, 0, 255);
    b255 = std::clamp(b255, 0, 255);

    //std::cout << r01 << " " << g01 << " " << b01 << "\n";
    //  
    //  r[j][i]
    //  
    //  r01 g01 b01, r02 g02 b02, r03 g03 b03 .... , r0<width> b0<width> g0<width>,
    //  r11 g11 b11 ( = rgb[ width + 1 ] )
    //
    image[j * 3 * image_width + i * 3 + 0] = r255;
    image[j * 3 * image_width + i * 3 + 1] = g255;
    image[j * 3 * image_width + i * 3 + 2] = b255;
}

int main()
{
    //srand48(int(time(nullptr)));

    {
        // since the destructor of ThreadPool joins all threads
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
    
    stbi_flip_vertically_on_write(true);
    if(stbi_write_png("output.png", image_width, image_height, 3, image, 0) == 0)
    {
        std::cerr << "Error when saving image\n";
    }
}