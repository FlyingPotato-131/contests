
#include <iostream>
#include <fstream>
#include <cmath>
#include "triangle.h"

struct oct{
	vec3 pos;
	float size;
};

float abss(float x){return x >= 0 ? x : -x;}

int main(){
	int const width = 1920u;
	int const height = 1080u;

	std::ofstream out("render.ppm");
	out << "P3" << std::endl;
	out << width << " " << height << std::endl;
	out << "255" << std::endl;

	oct ramiel;
	ramiel.pos = {0, 0, 0};
	ramiel.size = 1;

	Camera view;
	view.position = {0.25, -0.15, -1.5};
	view.at = ramiel.pos;
	view.up = {0, -1, 0};
//	view.aspectRatio = 1920/1080;
	view.aspectRatio = 1.7;
	view.verticalFOV = 3;

//	vec3 light = {1.f, 1.f, -1.f};
//	vec3 light = {2,1,-5};

/*	Camera light;
	light.position = {2, 2, -2};
;	light.at = ramiel.pos;
	light.up = {0, 1, 0};
	light.aspectRatio = 1920/1080;
	light.verticalFOV = 1;
*/
	vec3 x = {1, 0, 0};
	vec3 y = {0, 1, 0};
	vec3 z = {0, 0, 1};

	vec3 light = view.position + y;

	for(float h = -height/2; h < height/2; h++)
	for(float w = -width/2; w < width/2; w++){
		Ray ray = view.castRay(w/width/2, h/height/2);
		Triangle side1 = {ramiel.pos + x*ramiel.size, ramiel.pos - y*ramiel.size, ramiel.pos - z*ramiel.size};
		vec3 intr1 = rayTriangle(ray, side1);
		vec3 a1 = side1.a - side1.c;
		vec3 b1 = side1.b - side1.c;
		vec3 lightRay1 = intr1 - light;
		vec3 n1 = cross(a1, b1);

		float brightness1 = 1 - (1 - abss(dot(lightRay1, n1)/(length(lightRay1)*length(n1)))) * (1 - abss(dot(lightRay1 + intr1 - view.position, n1)/(length(lightRay1 + intr1 - view.position)*length(n1))));
//		float brightness = 0.5;
//		std::cout << brightness << std::endl;

		Triangle side2 = {ramiel.pos + x*ramiel.size, ramiel.pos + y*ramiel.size, ramiel.pos - z*ramiel.size};
		vec3 intr2 = rayTriangle(ray, side2);
		vec3 a2 = side2.a - side2.c;
		vec3 b2 = side2.b - side2.c;
		vec3 lightRay2 = intr2 - light;
		vec3 n2 = cross(a2, b2);
		
		float brightness2 = 1 - (1 - abss(dot(lightRay2, n2)/(length(lightRay2)*length(n2)))) * (1 - abss(dot(lightRay2 + intr2 - view.position, n2)/(length(lightRay2 + intr2 - view.position)*length(n2))));

		Triangle side3 = {ramiel.pos - x*ramiel.size, ramiel.pos - y*ramiel.size, ramiel.pos - z*ramiel.size};
		vec3 intr3 = rayTriangle(ray, side3);
		vec3 a3 = side3.a - side3.c;
		vec3 b3 = side3.b - side3.c;
		vec3 lightRay3 = intr3 - light;
		vec3 n3 = cross(a3, b3);
				
		float brightness3 = 1 - (1 - abss(dot(lightRay3, n3)/(length(lightRay3)*length(n3)))) * (1 - abss(dot(lightRay3 + intr3 - view.position, n3)/(length(lightRay3 + intr3 - view.position)*length(n3))));

		Triangle side4 = {ramiel.pos - x*ramiel.size, ramiel.pos + y*ramiel.size, ramiel.pos - z*ramiel.size};
		vec3 intr4 = rayTriangle(ray, side4);
		vec3 a4 = side4.a - side4.c;
		vec3 b4 = side4.b - side4.c;
		vec3 lightRay4 = intr4 - light;
		vec3 n4 = cross(a4, b4);
						
		float brightness4 = 1 - (1 - abss(dot(lightRay4, n4)/(length(lightRay4)*length(n4)))) * (1 - abss(dot(lightRay4 + intr4 - view.position, n4)/(length(lightRay4 + intr4 - view.position)*length(n4))));

		if(intr1.x != 0 && intr1.y != 0 && intr1.z != 0){
			unsigned int const r = brightness1*2.;
			unsigned int const g = brightness1*60.;
			unsigned int const b = brightness1*252;
			out << r << " " << g << " " << b << " ";
//			out << 15 << " " << 34 << " " << 252 << " ";
		}else if(intr2.x != 0 && intr2.y != 0 && intr2.z != 0){
			unsigned int const r = brightness2*2.;
			unsigned int const g = brightness2*60.;
			unsigned int const b = brightness2*252;
			out << r << " " << g << " " << b << " ";
		}else if(intr3.x != 0 && intr3.y != 0 && intr3.z != 0){
			unsigned int const r = brightness3*2.;
			unsigned int const g = brightness3*60.;
			unsigned int const b = brightness3*252;
			out << r << " " << g << " " << b << " ";
		}else if(intr4.x != 0 && intr4.y != 0 && intr4.z != 0){
			unsigned int const r = brightness4*2.;
			unsigned int const g = brightness4*60.;
			unsigned int const b = brightness4*252;
			out << r << " " << g << " " << b << " ";			
		}
		else{
			out << 15 << " " << 149 << " " << 252 << " ";
		}
//		std::cout << ray.direction.x << " " << ray.direction.y << " " << ray.direction.z  << std::endl;
	}
}
