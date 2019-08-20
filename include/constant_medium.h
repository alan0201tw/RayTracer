#ifndef CONSTANTMEDIUMH
#define CONSTANTMEDIUMH

#include "hitable.h"
#include "texture.h"

class constant_medium : public hitable
{
public:
    constant_medium(std::shared_ptr<hitable> _boundary, float _density, std::shared_ptr<texture> _texture);

    virtual bool hit(const ray& _ray, float t_min, float t_max, hit_record& rec) const override;
    virtual bool bounding_box(float t0, float t1, aabb& _box) const override;

private:
    std::shared_ptr<hitable> boundary;
    float density;
    std::shared_ptr<material> phase_function;
};


#endif