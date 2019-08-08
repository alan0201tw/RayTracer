#ifndef TEXTUREH
#define TEXTUREH

#include <memory>

#include "vec3.h"

class texture
{
public:
    virtual vec3 value_at_uv(float _u, float _v, const vec3& _hit_point) const = 0;
};

class constant_texture : public texture
{
public:
    constant_texture() {}
    constant_texture(vec3 _color) : color(_color) {}

    virtual vec3 value_at_uv(float _u, float _v, const vec3& _hit_point) const override;

private:
    vec3 color;
};

class checker_texture : public texture
{
public:
    checker_texture(std::shared_ptr<texture> _even_texture, std::shared_ptr<texture> _odd_texture) 
        : even_texture(_even_texture), odd_texture(_odd_texture) {}

    virtual vec3 value_at_uv(float _u, float _v, const vec3& _hit_point) const override;

private:
    std::shared_ptr<texture> even_texture;
    std::shared_ptr<texture> odd_texture;
};


#endif