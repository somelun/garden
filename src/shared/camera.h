#pragma once

#include "vec.h"
#include "mat.h"

struct Camera {
    Vec3 position = {0.0f, 0.0f, -3.0f};
    Vec3 target = {0.0f, 0.0f, 0.0f};

    Vec3 up = {0.0f, 1.0f, 0.0f};
    float fov_deg;
    float aspect;
    float z_near = 1.0f;
    float z_far = 1.0f;

    Mat4 GetProjectionMatrix() const {
        float fov_rad = fov_deg * 3.14159265f / 180.0f;
        float y_scale = 1.0f / tanf(fov_rad * 0.5f);
        float x_scale = y_scale / aspect;

        float z_range = z_far / (z_far - z_near);

        return {{
                {x_scale, 0.0f,    0.0f,             0.0f},
                {0.0f,    y_scale, 0.0f,             0.0f},
                {0.0f,    0.0f,    z_range,          1.0f},
                {0.0f,    0.0f,   -z_near * z_range, 0.0f}
        }};
    }

    Mat4 GetViewMatrix() const {
        Vec3 f = Normalize(target - position); // forward (+Z)
        Vec3 r = Normalize(Cross(up, f));      // right
        Vec3 u = Cross(f, r);                  // recomputed up

        return {{
            {r.x,               r.y,                r.z,              0.0f},
            {u.x,               u.y,                u.z,              0.0f},
            {f.x,               f.y,                f.z,              0.0f},
            {-Dot(r, position), -Dot(u, position), -Dot(f, position), 1.0f}
        }};
    }
};
