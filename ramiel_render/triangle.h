#pragma once
#include "camera.h"

#include <iostream>
#include <cmath>

struct Plane
{
    vec3 point;
    vec3 norm;
};

struct Triangle{
	vec3 a;
	vec3 b;
	vec3 c;
};

inline vec3 relativeRayPlane(Ray r, Plane p){
	return r.direction*(dot(p.point-r.origin, p.norm)/dot(r.direction, p.norm));
}

inline vec3 rayTriangle(Ray r, Triangle t){
	vec3 a = t.a - t.c;
	vec3 b = t.b - t.c;
	vec3 r0 = r.origin - t.c;
//	vec3 n = cross(a, b);
//	vec3 c = relativeRayPlane(r, {t.c, n}) + r.origin - t.c;
	
	float const det0 = dot(-r.direction, cross(a, b));
    float const det1 = dot( r0, cross(a, b));
	float const det2 = dot(-r.direction, cross(r0, b));
	float const det3 = dot(-r.direction, cross(a, r0));

	float len = det1 / det0;
	float alpha = det2 / det0;
	float beta = det3 / det0;

	vec3 nanv = {nanf("0"), nanf("0"), nanf("0")};
	vec3 nullv = {0,0,0};
	return alpha >= 0 && beta >= 0 && alpha + beta <= 1 ?
	r.direction*len + r.origin
	: nullv;
}
