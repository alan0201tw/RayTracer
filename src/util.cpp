#include "util.h"

#include <vector>

#include "sphere.h"
#include "material.h"
#include "hitable_list.h"
#include "texture.h"

#include "bvh.h"

vec3 random_in_unit_disk()
{
    vec3 direction(drand48(), drand48(), 0);
    float mag = cbrtf(drand48());

    return mag * unit_vector(direction);
}

vec3 random_in_unit_sphere()
{
    // This is a rejection method, which i s not that good for performance

    // vec3 p;
    // do
    // {
    //     p = 2 * vec3(drand48(), drand48(), drand48()) - vec3(1.0f, 1.0f, 1.0f);
    // } while (p.squared_length() >= 1.0f);
    // return p;

    // Reference : 
    // https://karthikkaranth.me/blog/generating-random-points-in-a-sphere/#using-normally-distributed-random-numbers
    
    vec3 direction(drand48(), drand48(), drand48());
    float mag = cbrtf(drand48());

    return mag * unit_vector(direction);
}

vec3 reflect(const vec3& _ray_direction, const vec3& _surface_normal)
{
    // this is because dot(_ray, _surface_normal) is actually negative
    // so we use the minus sign here

    return _ray_direction - 2 * dot(_ray_direction, _surface_normal) * _surface_normal;
}

bool refract(const vec3& _ray_direction, const vec3& _normal, float ni_over_nt, vec3& refracted)
{
    vec3 unit_direction = unit_vector(_ray_direction);
    float dt = dot(unit_direction, _normal);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if(discriminant > 0.0f)
    {
        refracted = ni_over_nt * (unit_direction - _normal * dt) - _normal * sqrt(discriminant);
        return true;
    }
    return false;
}

float schlick(float _cosine, float _refractive_index)
{
    float r0 = (1 - _refractive_index) / (1 + _refractive_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - _cosine), 5);
}

std::shared_ptr<hitable> random_scene()
{
    int n = 500;
    std::vector<std::shared_ptr<hitable>> list;
    list.reserve(n + 1);

    std::shared_ptr<texture> _checker_texture = std::make_shared<checker_texture>(
        std::make_shared<constant_texture>(vec3(0.2f, 0.3f, 0.1f)),
        std::make_shared<constant_texture>(vec3(0.9f, 0.9f, 0.9f))
    );

    list.push_back(std::make_shared<sphere>(vec3(0,-1000,0), 1000, std::make_shared<lambertian>(_checker_texture)));

    for (int a = -10; a < 10; a++) {
        for (int b = -10; b < 10; b++) {
            float choose_mat = drand48();
            vec3 center(a + 0.9 * drand48(), 0.2f, b + 0.9 * drand48()); 
            if ((center-vec3(4,0.2,0)).length() > 0.9) { 
                if (choose_mat < 0.8f) 
                {
                    // diffuse
                    //list.push_back(std::make_shared<sphere>(center, 0.2, std::make_shared<lambertian>(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48()))));
                    std::shared_ptr<texture> random_texture = std::make_shared<constant_texture>(
                        vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48()));

                    list.push_back(std::make_shared<moving_sphere>(
                        center, center + vec3(0, 0.5f * drand48(), 0.0f), 
                        0.0f, 1.0f, // start and end time
                        0.2f, std::make_shared<lambertian>(random_texture)));
                }
                else if (choose_mat < 0.95f)
                {
                    // metal
                    list.push_back(std::make_shared<sphere>(center, 0.2,
                        std::make_shared<metal>(vec3(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())),  0.5*drand48())));
                }
                else
                {
                    // glass
                    list.push_back(std::make_shared<sphere>(center, 0.2, std::make_shared<dielectric>(1.5)));
                }
            }
        }
    }

    list.push_back(std::make_shared<sphere>(vec3(0, 1, 0), 1.0, std::make_shared<dielectric>(1.5)));
    list.push_back(std::make_shared<sphere>(vec3(-4, 1, 0), 1.0, std::make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));
    list.push_back(std::make_shared<sphere>(vec3(4, 1, 0), 1.0, std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));

    //return std::make_shared<hitable_list>(list, list.size());

    // change to bvh
    return std::make_shared<bvh_node>(list, 0.0f, 1.0f);

    // using O(N) search ( hitable_list )
    // real    4m49.214s
    // user    13m57.995s
    // sys     0m7.843s
    //
    // using BVH
    // real    1m21.986s
    // user    4m50.992s
    // sys     0m4.199s
    //
    // using BVH and functors
    // real    1m18.025s
    // user    4m20.477s
    // sys     0m3.869s
}

std::shared_ptr<hitable> two_sphere()
{
    std::shared_ptr<texture> _checker_texture = std::make_shared<checker_texture>(
        std::make_shared<constant_texture>(vec3(0.1f, 0.2f, 0.3f)),
        std::make_shared<constant_texture>(vec3(0.9f, 0.9f, 0.9f))
    );

    std::vector<std::shared_ptr<hitable>> list;
    list.reserve(50);

    list.push_back(std::make_shared<sphere>(vec3(0.0f, -10.0f, 0.0f), 10.0f, std::make_shared<lambertian>(_checker_texture)));
    list.push_back(std::make_shared<sphere>(vec3(0.0f,  10.0f, 0.0f), 10.0f, std::make_shared<lambertian>(_checker_texture)));

    return std::make_shared<bvh_node>(list, 0.0f, 1.0f);
}