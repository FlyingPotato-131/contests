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

struct IntRange{
	int *begin;
	int *end;
};

void swap(int *a, int *b){
	int c = *a;
	*a = *b;
	*b = c;
}

void siftdown(IntRange rng, int i){
	int len = rng.end - rng.begin;
	if(i < (len + 2) / 2 && (rng.begin[i] < rng.begin[2*i + 1] || rng.begin[i] < rng.begin[2*i + 2])){
		if(rng.begin[2*i + 1] > rng.begin[2*i + 2]){
			swap(rng.begin + i, rng.begin + 2*i + 1);
			siftdown(rng, 2*i + 1);
		}else{
			swap(rng.begin + i, rng.begin + 2*i + 2);
			siftdown(rng, 2*i + 2);
		}
	}else if(i <= (len + 1) / 2 && rng.begin[i] < rng.begin[2*i + 1]){
		swap(rng.begin + i, rng.begin + 2*i + 1);
	}
}

void make_heap(IntRange rng){
	for(int i = (rng.end - rng.begin) / 2; i >= 0; i -= 1){
		siftdown(rng, i);
	}
}

void pop_heap(IntRange rng){
	swap(rng.begin, rng.end - 1);
	siftdown({rng.begin, rng.end - 1}, 0);
	siftdown({rng.begin, rng.end - 1}, 0);
}

void heap_sort(IntRange rng){
	make_heap(rng);
	for(int i = 0; i < rng.end - rng.begin; i++){
		for(int i = 0; i < rng.end - rng.begin; i++){
				std::cout << rng.begin[i] << " ";
		}
		std::cout << std::endl;
		pop_heap({rng.begin, rng.end - i});
	}
}

/*
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
}*/

int main(){
	int const len = 10;
	int rng[] = {0, -5, 3, -2, 6, 2, 2, 3, -9, 8};
	heap_sort({rng, rng + len});
	for(int i = 0; i < len; i++){
		std::cout << rng[i] << " ";
	}
	std::cout << std::endl;
}
