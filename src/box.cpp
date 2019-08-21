#include "box.hpp"

#include "flip_normals.hpp"
#include "aarect.hpp"
#include "aabb.hpp"

box::box(const vec3& _min, const vec3& _max, std::shared_ptr<material> _material)
    : min_point(_min), max_point(_max)
{
    std::vector<std::shared_ptr<hitable>> list;
    list.reserve(6);

    //std::cout << min_point << " , " << max_point << std::endl;

    list.push_back(std::make_shared<xy_rect>(
            min_point.x(), max_point.x(), min_point.y(), max_point.y(), max_point.z(), _material));
    list.push_back(std::make_shared<flip_normals>(std::make_shared<xy_rect>(
            min_point.x(), max_point.x(), min_point.y(), max_point.y(), min_point.z(), _material)));

    list.push_back(std::make_shared<xz_rect>(
            min_point.x(), max_point.x(), min_point.z(), max_point.z(), max_point.y(), _material));
    list.push_back(std::make_shared<flip_normals>(std::make_shared<xz_rect>(
            min_point.x(), max_point.x(), min_point.z(), max_point.z(), min_point.y(), _material)));

    list.push_back(std::make_shared<yz_rect>(
            min_point.y(), max_point.y(), min_point.z(), max_point.z(), max_point.x(), _material));
    list.push_back(std::make_shared<flip_normals>(std::make_shared<yz_rect>(
            min_point.y(), max_point.y(), min_point.z(), max_point.z(), min_point.x(), _material)));

    rect_list = hitable_list(list);
}

bool box::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
    return rect_list.hit(_ray, t_min, t_max, rec);
}

bool box::bounding_box(float t0, float t1, aabb& _box) const
{
    _box = aabb(min_point, max_point);
    return true;
}