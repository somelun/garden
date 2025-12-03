#pragma once

#include "types.h"
#include "vec.h"

#include <algorithm>

struct Light {
    Vec3 position;
    Vec3 direction;
    Color8 color;
    float intensity;

    float ambient  = 0.1f;
    float diffuse  = 1.0f;
    float specular = 1.0f;
    float shininess = 32.0f;
};

inline ColorF ComputePhong(const Vec3& world_pos, const Vec3& normal,
                           const Vec3& view_pos, const Light& light,
                           const Color8& base_color) {
    Vec3 N = Normalize(normal);

    Vec3 light_dir = Normalize(light.position - world_pos);
    Vec3 view_dir = Normalize(view_pos - world_pos);
    Vec3 reflection_dir = Normalize((N * (2.0f * Dot(N, light_dir))) - light_dir);

    float diffuse = light.diffuse * std::max(Dot(N, light_dir), 0.0f);
    float specular = light.specular * powf(std::max(Dot(view_dir, reflection_dir), 0.0f), light.shininess);
    float strength = (light.ambient + diffuse + specular) * light.intensity;

    float r = (base_color.r / 255.0f) * (light.color.r / 255.0f) * strength;
    float g = (base_color.g / 255.0f) * (light.color.g / 255.0f) * strength;
    float b = (base_color.b / 255.0f) * (light.color.b / 255.0f) * strength;

    r = std::min(r, 1.0f);
    g = std::min(g, 1.0f);
    b = std::min(b, 1.0f);

    return { r, g, b, 1.0f };
}
