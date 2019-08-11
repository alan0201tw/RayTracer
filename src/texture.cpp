#include "texture.h"

#include <cmath>
#include <algorithm>

#include "stb_image.h"

#include "perlin.h"

vec3 constant_texture::value_at_uv(float _u, float _v, const vec3& _hit_point) const
{
    return color;
}

vec3 checker_texture::value_at_uv(float _u, float _v, const vec3& _hit_point) const
{
    // TODO : 
    // need a way to distinguish sampling from odd and even texture.
    // currently using world space position to do the determination.
    // which will cause artifacts on bending surfaces like a sphere.

    float sines = std::sin(10 * _hit_point.x()) * std::sin(10 * _hit_point.y()) * std::sin(10 * _hit_point.z());
    if(sines < 0.0f)
    {
        return odd_texture->value_at_uv(_u, _v, _hit_point);
    }
    return even_texture->value_at_uv(_u, _v, _hit_point);
}

vec3 perlin_noise_texture::value_at_uv(float _u, float _v, const vec3& _hit_point) const
{
    return vec3(1, 1, 1) * perlin::get_noise(_hit_point);
}

image_texture::image_texture(std::string _file_name)
{
    data = stbi_load(_file_name.c_str(), &width, &height, &channel, 0);
    std::cout << "SYS : Loading texture : " << _file_name << ", width = " << width << ", height = " << height << ", channel = " << channel << "\n";
    if(data == nullptr)
    {
        std::cerr << "Error when loading texture : " << _file_name << "\n";
    }
}

vec3 image_texture::value_at_uv(float _u, float _v, const vec3& _hit_point) const
{
    // do some repeating and fraction
    // _u *= 5.0f;
    // _v *= 5.0f;

    // _u = _u -(long)_u;
    // _v = _v -(long)_v;

    int width_index = _u * width;
    //int height_index = _v * height;
    int height_index = ( 1 - _v ) * height - 0.001f;

    width_index = std::clamp(width_index, 0, width - 1);
    height_index = std::clamp(height_index, 0, height - 1);

    float normalized_r = int(data[ height_index * width * 3 + width_index * 3 + 0 ]) / 255.0f;
    float normalized_g = int(data[ height_index * width * 3 + width_index * 3 + 1 ]) / 255.0f;
    float normalized_b = int(data[ height_index * width * 3 + width_index * 3 + 2 ]) / 255.0f;

    //std::cout << "input uv = " << _u << " , " << _v << std::endl;
    //std::cout << "width_index = " << width_index << " , height_index = " << height_index << std::endl;

    return vec3(normalized_r, normalized_g, normalized_b);
}
