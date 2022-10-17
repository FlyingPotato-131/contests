#pragma once
#include "ray.h"

struct Camera
{
    vec3 position;
    vec3 at;
    vec3 up;
    float aspectRatio;
    float verticalFOV;

    // u, v ∈ [-1;1]
    Ray castRay(float const u, float const v) const
    {
        vec3 const z = normalize(position - at);
        vec3 const x = normalize(cross(up, z));
        vec3 const y = cross(z, x);

        vec3 const d = x * (u * verticalFOV * aspectRatio)
                     + y * (v * verticalFOV)
                     - z;
        return
        {
            .origin = position,
            .direction = normalize(d),
        };
    }
};
