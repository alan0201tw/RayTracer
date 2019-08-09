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

// scene generation
std::shared_ptr<hitable> random_scene();
std::shared_ptr<hitable> two_sphere();

#endif