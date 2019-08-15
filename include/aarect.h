#ifndef AARECTH
#define AARECTH

#include "hitable.h"

#include <memory>

class xy_rect : public hitable
{
public:
    xy_rect() {}
    xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, 
        std::shared_ptr<material> _material)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), rect_material(_material) {}

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

private:
    float x0, x1, y0, y1, k;
    std::shared_ptr<material> rect_material;
};

class xz_rect : public hitable
{
public:
    xz_rect() {}
    xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, 
        std::shared_ptr<material> _material)
        : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), rect_material(_material) {}

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

private:
    float x0, x1, z0, z1, k;
    std::shared_ptr<material> rect_material;
};

class yz_rect : public hitable
{
public:
    yz_rect() {}
    yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, 
        std::shared_ptr<material> _material)
        : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), rect_material(_material) {}

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

private:
    float y0, y1, z0, z1, k;
    std::shared_ptr<material> rect_material;
};


#endif