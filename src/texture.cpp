#include "texture.h"

#include <cmath>

vec3 constant_texture::value_at_uv(float _u, float _v, const vec3& _hit_point) const
{
    return color;
}

vec3 checker_texture::value_at_uv(float _u, float _v, const vec3& _hit_point) const
{
    float sines = std::sin(10 * _hit_point.x()) * std::sin(10 * _hit_point.y()) * std::sin(10 * _hit_point.z());
    if(sines < 0.0f)
    {
        return odd_texture->value_at_uv(_u, _v, _hit_point);
    }
    return even_texture->value_at_uv(_u, _v, _hit_point);
}
