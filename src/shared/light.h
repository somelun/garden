#pragma once

#include "types.h"
#include "vec.h"

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

// inline ColorF ComputePhong(
//     const Vec3& worldPos,
//     const Vec3& normal,
//     const Vec3& viewPos,
//     const Light& light,
//     const Color8& baseColor) {
//     Vec3 N = Normalize(normal);
// 
//     // Light direction
//     Vec3 L = Normalize(light.position - worldPos);
// 
//     // View direction
//     Vec3 V = Normalize(viewPos - worldPos);
// 
//     // Reflection direction
//     Vec3 R = Normalize( (N * (2.0f * Dot(N,L))) - L );
// 
//     // === Ambient ===
//     float ambient = light.ambient;
// 
//     // === Diffuse ===
//     float diff = std::max(Dot(N, L), 0.0f);
//     float diffuse = light.diffuse * diff;
// 
//     // === Specular ===
//     float spec = powf(std::max(Dot(V, R), 0.0f), light.shininess);
//     float specular = light.specular * spec;
// 
//     float strength = (ambient + diffuse + specular) * light.intensity;
// 
//     return {
//         baseColor.r * light.color.r * strength,
//         baseColor.g * light.color.g * strength,
//         baseColor.b * light.color.b * strength,
//         1.0f
//     };
// }
