#include "triangle.hpp"

#include "aabb.hpp"

static const float kEpsilon = std::numeric_limits<float>::epsilon();

triangle::triangle(const vec3& _v0, const vec3& _v1, const vec3& _v2, std::shared_ptr<material> _material)
    : v0(_v0), v1(_v1), v2(_v2), triangle_mat(_material)
    {
        normal = unit_vector( cross(v1 - v0, v2 - v0) );
    }

bool triangle::hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const
{
    // Reference : 
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
    // https://github.com/netolcc06/BabyRayTracer/blob/master/Triangle.hpp
    vec3 v0v1 = v1 - v0;
    vec3 v0v2 = v2 - v0;
    vec3 pvec = cross(_ray.direction(), v0v2);
    float det = dot(v0v1, pvec);

    // culling
    //if(det < kEpsilon) return false;
    // no culling
    if (fabs(det) < kEpsilon) return false; 

    float invDet = 1.0f / det;

    vec3 tvec = _ray.origin() - v0;
    float u = dot(tvec, pvec) * invDet;
    if(u < 0 || u > 1) return false;

    vec3 qvec = cross(tvec, v0v1);
    float v = dot(_ray.direction(), qvec) * invDet;
    if(v < 0 || u + v > 1) return false;

    float t = dot(v0v2, qvec) * invDet;
    if (t < 0) return false;

    // fill in collision info
    rec.hit_point = _ray.point_at_parameter(t);
    if(dot(normal, _ray.direction()) > 0.0f)
        rec.normal = -1.0f * normal;
    else
        rec.normal = normal;
    rec.t = t;
    rec.u = u;
    rec.v = v;
    rec.material_ref = triangle_mat;

    return true;
}

bool triangle::bounding_box(float t0, float t1, aabb& _box) const
{
    float minX = std::min(v0.x(), std::min(v1.x(), v2.x()));
    float minY = std::min(v0.y(), std::min(v1.y(), v2.y()));
    float minZ = std::min(v0.z(), std::min(v1.z(), v2.z()));

    float maxX = std::max(v0.x(), std::max(v1.x(), v2.x()));
    float maxY = std::max(v0.y(), std::max(v1.y(), v2.y()));
    float maxZ = std::max(v0.z(), std::max(v1.z(), v2.z()));

    vec3 min_point = vec3(minX, minY, minZ);
    vec3 max_point = vec3(maxX, maxY, maxZ);

    _box = aabb(min_point, max_point);
    return true;
}