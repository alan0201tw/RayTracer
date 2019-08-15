#ifndef UTILH
#define UTILH

#include <memory>

#include "vec3.h"
#include "hitable.h"

vec3 random_in_unit_disk();
vec3 random_in_unit_sphere();
vec3 reflect(const vec3& _ray_direction, const vec3& _surface_normal);
bool refract(const vec3& _ray_direction, const vec3& _normal, float ni_over_nt, vec3& refracted);
float schlick(float _cosine, float _refractive_index);

// texture sampling
void get_sphere_uv(const vec3& point_on_surface, float& _u, float& _v);

// interpolating
float perlin_interpolate(vec3 _data[2][2][2], float _u, float _v, float _w);

// scene generation
std::shared_ptr<hitable> random_scene();
std::shared_ptr<hitable> two_sphere();
std::shared_ptr<hitable> two_perlin_sphere();
std::shared_ptr<hitable> simple_light();
std::shared_ptr<hitable> cornell_box();

#endif