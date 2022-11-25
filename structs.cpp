#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct pair{
	int first;
	int second;
};

int pairsum(pair i){
	return i.first + i.second;
}

bool operator<(pair lhs, pair rhs){
	return lhs.first != rhs.first
	? lhs.first < rhs.first
	: lhs.second < rhs.second;
}

int main(){
	pair const yeet = {.first = 1, .second = 2,};

	pair sdf = {1, 2};

	pair eff;
	eff.first = 1;
	eff.second = 2;
	bool b = yeet<eff;
}
