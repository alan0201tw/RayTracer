#include "perlin.h"

float perlin::get_noise(const vec3& _p)
{
    float u = _p.x() - std::floor(_p.x());
    float v = _p.x() - std::floor(_p.y());
    float w = _p.x() - std::floor(_p.z());
    int i = int(4*_p.x()) & 255;
    int j = int(4*_p.y()) & 255;
    int k = int(4*_p.z()) & 255;

    return random_floats[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
}

std::vector<float> perlin::perlin_generate()
{
    std::vector<float> result;
    result.reserve(256);
    for(int i = 0; i < 256; i++)
    {
        result.push_back(drand48());
    }
    return result;
}

void perlin::permute(std::vector<int>& _p, int _n)
{
    for(int i = _n - 1; i > 0; i--)
    {
        int target = int(drand48() * (i+1));
        int tmp = _p[i];
        _p[i] = _p[target];
        _p[target] = tmp;
    }
    return;
}

std::vector<int> perlin::perlin_generate_perm()
{
    std::vector<int> result;
    result.reserve(256);

    for(int i = 0; i < 256; i++)
    {
        result.push_back(i);
    }
    permute(result, 256);
    return result;
}

std::vector<float> perlin::random_floats = perlin::perlin_generate();
std::vector<int> perlin::perm_x = perlin::perlin_generate_perm();
std::vector<int> perlin::perm_y = perlin::perlin_generate_perm();
std::vector<int> perlin::perm_z = perlin::perlin_generate_perm();