#ifndef PERLINH
#define PERLINH

#include "vec3.h"

#include <vector>

class perlin
{
public:
    static float get_noise(const vec3& _p);
    static float turb(const vec3& _p, int depth = 7);

    static std::vector<vec3> random_vecs;
    static std::vector<int> perm_x;
    static std::vector<int> perm_y;
    static std::vector<int> perm_z;

private:
    static std::vector<vec3> perlin_generate();
    // this method will write to _p
    static void permute(std::vector<int>& _p, int _n);
    static std::vector<int> perlin_generate_perm();
};


#endif