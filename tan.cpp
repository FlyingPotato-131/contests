#include <iostream>
#include <cmath>

float fast_tg(float x){
	while(abs(x)>1.5707963){
		x = (x > 0) ? x - 3.141592653589793 : x + 3.141592653589793;
	}
	return(pow(x, 7) - 5.02546698128*pow(x, 5)-67.907236234*pow(x, 3)-204.921708702*x)/(4.59371*pow(x, 6)+22.162923*pow(x, 4)+0.4*pow(x, 2)-204.921708702);
}

float atan_sum(float x){
	double dt = 0.0000001;
	double res = 0;
	for(double t = dt; t < std::abs(x); t += dt){
		dt = pow(t+1, 2)/10000000;
		res += dt/(1+pow(t, 2));
	}
	return x >= 0 ? res : -res;
}

float tan_iter(float x){
	float t = 0;
	float at = 0;
	
	while(std::abs(at - x) > 0.0001){
		at = atan_sum(t);
		t = t + (1 + pow(t, 2))*(x - at);
	}
	
	return t;
}

#include <iomanip>
int main(){
	float a = 0;
	std::cin >> a;

	std::cout << std::setprecision(8);
	std::cout << tan_iter(a) << std::endl;
	std::cout << std::tan(a) << std::endl;
}
