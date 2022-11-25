#include <iostream>
using std::cout;
using std::endl;
using std::cin;

double root(double n){
	double attempt = 256;
	while(abs(attempt*attempt - n)/(n) >= 1e-10){
		attempt = 0.5*(attempt+n/attempt);
//		cout<<attempt<<endl;
	}
	return attempt;
}

int main(){
	double in;
	cin>>in;
	cout<<root(in)<<endl;
}
