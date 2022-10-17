#pragma once
#include "vec3.h"
struct Ray
{
    vec3 origin;
    vec3 direction;

    vec3 point(float const t) const {return origin + direction * t;}
};
