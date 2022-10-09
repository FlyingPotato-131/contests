#include <iostream>
#include <cmath>

struct vec3{
	float x, y, z;
};

struct Ray
{
    vec3 origin;
    vec3 direction;
};

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

vec3 cross(vec3 a, vec3 b){
	vec3 c;
	c.x = a.y*b.z-a.z*b.y;
	c.y = -a.x*b.z+a.z*b.x;
	c.z = a.x*b.y-a.y*b.x;
	return c;
}

vec3 operator+(vec3 a, vec3 b){
	return {a.x + b.x, a.y + b.y, a.z + b.z};
}

vec3 operator-(vec3 a, vec3 b){
	return {a.x-b.x, a.y-b.y, a.z-b.z};
}

vec3 operator*(vec3 a, float b){
	return {a.x*b, a.y*b, a.z*b};
}

float dot(vec3 a, vec3 b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

vec3 relativeRayPlane(Ray r, Plane p){
	return r.direction*(dot(p.point-r.origin, p.norm)/dot(r.direction, p.norm));
}

vec3 rayTriangle(Ray r, Triangle t){
	vec3 a = t.a - t.c;
	vec3 b = t.b - t.c;
	vec3 n = cross(a, b);
	vec3 c = relativeRayPlane(r, {t.c, n}) + r.origin - t.c;
	float alpha = (b.y*c.z-b.z*c.y)/(a.z*b.y-a.y*b.z);
	float beta = (a.z*c.y-a.y*c.z)/(a.z*b.y-a.y*b.z);
	vec3 nanv = {nanf("0"), nanf("0"), nanf("0")};
	return alpha >= 0 && beta >= 0 && alpha + beta <= 1 ?
	c + t.c
	: nanv;
}
