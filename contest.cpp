#include <iostream>
#include <cstdint>
#include <cmath>

using std::cin;
using std::cout;
using std::end;
using std::exp2;
using std::log2;
using u64 = std::uint64_t;

long square(long i){
	return i*i;
}

double log2d(double x){
	return log2(x);
}

double exp2d(double x){
	return exp2(x);
}
/*
double pow(double x, double y){
	return(exp2d(log2d(x)*y));
}

double pow(double x, int a){
	double r = 1;
	for(int i = 0; i < (a > 0 ? a : -a); i++){
		a > 0 ? r *= x : r /= x;
	}
	return r;
}
*/

double pow2(double x, int a){
	return (a == 0 ? 1 : a%2 == 0 ? (pow2(x, a/2) * pow2(x, a/2)) : (a > 0 ? x * pow2(x, a-1) : pow2(x, a+1) / x));
}

int popcount(uint64_t i){
	int n = 0;
	while(i > 1){
		if(i%2 == 0){
			i /= 2;
		}
		else{
			i = (i-1)/2;
			n++;
		}
	}
	return i == 0 ? 0 : n+1;
}

int gcd(u64 a, u64 b){
	return a > b ? b == 0 ? a : gcd(b, a%b) : a == 0 ? b : gcd(a, b%a);
}

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

vec3 rayPlaneIntersection(Ray r, Plane p){
	return r.origin + r.direction*(dot(p.point-r.origin, p.norm)/dot(r.direction, p.norm));
}

u64 fib64(u64 k){
	u64 d = 1;
	u64 c = 0;
	for (u64 i = 0; i < k; i++){
		c = d + c;
		d = c - d;
	}
	return c;
}

/*
vec3 rayPlaneIntersection(Ray r, Plane p){
	return {
		(p.norm.x*p.point.x*r.direction.x + p.norm.y*p.point.y*r.direction.x + p.norm.z*p.point.z*r.direction.x - p.norm.y*r.origin.y*r.direction.x - p.norm.z*r.origin.z*r.direction.x + p.norm.y*r.direction.y*r.origin.x + p.norm.z*r.direction.z*r.origin.x)/(p.norm.x*r.direction.x + p.norm.y*r.direction.y + p.norm.z*r.direction.z),
		(p.norm.x*p.point.x*r.direction.y + p.norm.y*p.point.y*r.direction.y + p.norm.z*p.point.z*r.direction.y - p.norm.x*r.origin.x*r.direction.y - p.norm.z*r.origin.z*r.direction.y + p.norm.x*r.direction.x*r.origin.y + p.norm.z*r.direction.z*r.origin.y)/(p.norm.y*r.direction.y + p.norm.x*r.direction.x + p.norm.z*r.direction.z),
		(p.norm.x*p.point.x*r.direction.z + p.norm.y*p.point.y*r.direction.z + p.norm.z*p.point.z*r.direction.z - p.norm.y*r.origin.y*r.direction.z - p.norm.x*r.origin.x*r.direction.z + p.norm.y*r.direction.y*r.origin.z + p.norm.x*r.direction.x*r.origin.z)/(p.norm.z*r.direction.z + p.norm.y*r.direction.y + p.norm.x*r.direction.x)	
	};
}
*/


int main(){
	vec3 vtr1 = {2, 3, 1};
	vec3 vtr2 = {-1, 1, 2};
	vec3 vtr = cross(vtr1, vtr2);
	cout << vtr.x << " " << vtr.y << " " << vtr.z;
//	cin>>b;*/
//	Ray r = {{-0.72904599, 0.67001718, 0.93773556}, {-0.81608188, -0.56118459, 0.13813826}};
//	Plane p = {{-0.62323606, 0.9857626, 0.99292266}, {0.66062278, 0.31899932, 0.67957121}};
//	cin >> a;
//	cin >> b;
//	vec3 c = rayPlaneIntersection(r, p);
//	cout<<c.x<<" "<<c.y<<" "<<c.z;
}
