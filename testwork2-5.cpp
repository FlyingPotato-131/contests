#include <iostream>
#include <string>
#include <cmath>

int main(){
	std::string raw;
	std::cin >> raw;
	std::uint32_t id = 0;
	for(int ptr = 0; ptr < 32; ptr++){
		id += (static_cast<int>(raw[ptr]) - '0') << (31 - ptr);
	}
	std::cout << id << std::endl;
	std::string name;
	int chr;
	int nameend;
	for(int ptr = 32; name[ptr] != '\0'; ptr++){
		chr = 0;
		for(int i = 0; i < 8; i++){
			chr += (static_cast<int>(raw[ptr]) - '0') << (7 - i);
		}
		name.push_back(static_cast<char>(chr));
		nameend = ptr;
	}
	std::cout << name << std::endl;

}