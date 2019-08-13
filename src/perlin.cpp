#include "perlin.h"

#include "util.h"

float perlin::get_noise(const vec3& _p)
{
    float u = _p.x() - std::floor(_p.x());
    float v = _p.y() - std::floor(_p.y());
    float w = _p.z() - std::floor(_p.z());
    int i = std::floor(_p.x());
    int j = std::floor(_p.y());
    int k = std::floor(_p.z());

    vec3 data[2][2][2];
    for(int di = 0; di < 2; di++)
    {
        for(int dj = 0; dj < 2; dj++)
        {
            for(int dk = 0; dk < 2; dk++)
            {
                data[di][dj][dk] = 
                    random_vecs[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];
            }
        }
    }

    return perlin_interpolate(data, u, v, w);
}

float perlin::turb(const vec3& _p, int depth)
{
    float accum = 0.0f;
    vec3 temp_p = _p;
    float weight = 1.0f;
    for(int i = 0; i < depth; i++)
    {
        accum += weight * get_noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return std::abs(accum);
}

std::vector<vec3> perlin::perlin_generate()
{
    std::vector<vec3> result;
    result.reserve(256);
    for(int i = 0; i < 256; i++)
    {
        // IMPORTANT : it has to be unit_vector here.
        result.push_back(unit_vector(vec3(-1 + 2 * drand48(), -1 + 2 * drand48(), -1 + 2 * drand48())));
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

std::vector<vec3> perlin::random_vecs = perlin::perlin_generate();
std::vector<int> perlin::perm_x = perlin::perlin_generate_perm();
std::vector<int> perlin::perm_y = perlin::perlin_generate_perm();
std::vector<int> perlin::perm_z = perlin::perlin_generate_perm();