#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
/*
int main(){
	std::string input;
	int n;
	while(std::getline(std::cin, input)){
		std::vector<int> vec;
		std::istringstream numStream(input);
		while(numStream >> n){
			vec.push_back(n);
		}
		std::sort(vec.begin(), vec.end());
		for(unsigned int i = 0; i < vec.size(); i++){
			std::cout << vec[i] << " ";
		}
		std::cout << std::endl;
	}
}*/

struct vec3
{
    int x, y, z;
};

float dot(vec3 v1, vec3 v2)
{
    return v1.x * v2.x
         + v1.y * v2.y
         + v1.z * v2.z;
}

inline float length(vec3 const &v)
{
    return std::sqrt(dot(v, v));
}

int main(){
	std::vector<vec3> vecs;
	vec3 deltavec;
	int len = 0;
	while(std::scanf("(%d, %d, %d) ", &deltavec.x, &deltavec.y, &deltavec.z) == 3){
		vecs.push_back(deltavec);
		len++;
	}
	auto less = [](vec3 v1, vec3 v2){return length(v1) < length(v2);};
	std::sort(vecs.begin(), vecs.end(), less);
	for(unsigned int i = 0; i < vecs.size(); i++){
		std::cout << "(" << vecs[i].x << ", " << vecs[i].y << ", " << vecs[i].z << ") ";
	}
	std::cout << std::endl;
}
