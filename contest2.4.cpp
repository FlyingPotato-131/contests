#include <iostream>

void print(int        &) {std::cout << "int        &" << std::endl;}
void print(int       &&) {std::cout << "int       &&" << std::endl;}
void print(int const  &) {std::cout << "int const  &" << std::endl;}
void print(int const &&) {std::cout << "int const &&" << std::endl;}

// void forward_print(int        &i){print(i);}
// void forward_print(int       &&i){print(static_cast<int &&>(i));}
// void forward_print(int const  &i){print(i);}
// void forward_print(int const &&i){print(static_cast<int const &&>(i));}

template<typename T>
void forward_print(T &&i){
    print(static_cast<T&&>(i));	
}

int main(){
	int i = 0;
	forward_print(i);
	forward_print(0);
    forward_print(static_cast<int const  &>(i));
    forward_print(static_cast<int const &&>(i));
    // int const ci = 0;
    // auto const func = []() {return 0;};
    // print(i);       // int &
    // print(ci);      // int const &
    // print(0);       // int &&
    // print(func());  // int &&
    // print(static_cast<int       &&>(i)); // int &&
    // print(static_cast<int const &&>(i)); // int const &&
}
