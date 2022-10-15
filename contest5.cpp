#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <array>

/*
int main(){
	std::string str;
	std::getline(std::cin, str);
	auto pos = std::find(str.begin(), str.end(), ' ');
	if(pos == str.end()){
		std::cout << "not found" << std::endl;
	}else{
		std::cout << pos - str.begin() << std::endl;
	}
}*/
/*
int main(){
	std::vector<int> vec = {};
	int num;
	while(std::cin >> num){
		vec.push_back(num);
	}
	std::sort(vec.begin(), vec.end(), std::greater<int>());
	for(int i : vec){
		std::cout << i << " ";
	}
	std::cout << std::endl;
}*/

int main(){
//	std::vector<int> input = {0, 0, 0};
	std::array<int, 3> input = {0, 0, 0};
	std::array<int, 3> vec = {};
//	int n = 3;
	while(std::scanf("(%d, %d, %d)\n", &input[0], &input[1], &input[2]) == 3){
//		n = std::scanf("(%d, %d, %d)\n", &input[0], &input[1], &input[2]);
//		std::cout << n << std::endl;
		for(int i = 0; i < 3; i++){
			vec[i] += input[i];
		}
	}
	std::cout << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")" << std::endl;
}
