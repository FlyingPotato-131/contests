#include <iostream>
#include <cmath>
#include <span>


class Complex
{
    double x, y;
public:
    Complex(double re = 0., double im = 0.);
    double real() const;
    double imag() const;
    Complex &operator+=(Complex const &);
    Complex &operator-=(Complex const &);
    Complex &operator*=(Complex const &);
    Complex &operator/=(Complex const &);
};

Complex::Complex(double re, double im){
	x = re;
	y = im;
}

double Complex::real() const{
	return x;
}

double Complex::imag() const{
	return y;
}
Complex &Complex::operator+=(Complex const & c){
    x += c.real();
    y += c.imag();
    return *this;
}
Complex &Complex::operator-=(Complex const &c){
   	x -= c.real();
   	y -= c.imag();
   	return *this;
}
Complex &Complex::operator*=(Complex const &c){
  	*this = {x * c.real() - y * c.imag(), x * c.imag() + y * c.real()};
  	return *this;
}
Complex &Complex::operator/=(Complex const &c){
 	*this = {(x * c.real() + y * c.imag()) / (c.real() * c.real() + c.imag() * c.imag()),
 	(y * c.real() - x * c.imag()) / (c.real() * c.real() + c.imag() * c.imag())};
 	return *this;
}
double norm(Complex const &c){
	return c.real() * c.real() + c.imag() * c.imag();
}
double  arg(Complex const &c){
	return atan2(c.imag(), c.real());
}
Complex operator+(Complex const &c1, Complex const &c2){
	return {c1.real() + c2.real(), c1.imag() + c2.imag()};
}
Complex operator-(Complex const &c1, Complex const &c2){
	return {c1.real() - c2.real(), c1.imag() - c2.imag()};
}
Complex operator*(Complex const &c1, Complex const &c2){
	return {c1.real() * c2.real() - c1.imag() * c2.imag(), c1.real() * c2.imag() + c1.imag() * c2.real()};
}
Complex operator/(Complex const &c1, Complex const &c2){
	return {
		(c1.real() * c2.real() + c1.imag() * c2.imag()) / (c2.real() * c2.real() + c2.imag() * c2.imag()),
		(c1.imag() * c2.real() - c1.real() * c2.imag()) / (c2.real() * c2.real() + c2.imag() * c2.imag())
	};
}

namespace fuc{
template<typename T>
class span
{
    T *pBegin;
    T *pEnd;
public:
    using size_type = std::size_t;
    using iterator  = T *;
    span();
    span(T *begin, T *end);
    span(T *begin, size_type count);
    template<std::size_t N>
    span(T (&)[N]);
    T *          data() const;
    size_type    size() const;
    bool        empty() const;
    iterator    begin() const;
    iterator      end() const;
    T &operator[](size_type) const;
    span subspan(size_type offset, size_type count = -1) const;
};
template<typename T>
span<T>::span(){
	pBegin = nullptr;
	pEnd = nullptr;
}
template<typename T>
span<T>::span(T *begin, T* end){
	pBegin = begin;
	pEnd = end;
}
template<typename T>
span<T>::span(T *begin, size_type count){
	pBegin = begin;
	pEnd = pBegin + count;
}
template<typename T>
template<std::size_t N>
span<T>::span(T (&array)[N]){
	pBegin = array;
	pEnd = array + N;
}
template<typename T>
T *span<T>::data() const{
	return pBegin;
}
template<typename T>
std::size_t span<T>::size() const{
	return (pEnd - pBegin);
}
template<typename T>
bool span<T>::empty() const{
	return pEnd == pBegin;
}
template<typename T>
T* span<T>::begin() const{
	return pBegin;
}
template<typename T>
T* span<T>::end() const{
	return pEnd;
}
template<typename T>
T &span<T>::operator[](size_type i) const{
	return pBegin[i];
}
template<typename T>
span<T> span<T>::subspan(size_type offset, size_type count) const{
	if(count != static_cast<size_type>(-1))
		return span(pBegin + offset, count);
	return span(pBegin + offset, pEnd);
}
}

template<typename T>
class smart_ptr
{
    T *ptr;
public:
    ~smart_ptr();
    smart_ptr();
    template<typename... Args>
    smart_ptr(Args &&... args)
        : ptr(new T(static_cast<Args &&>(args)...))
    {}
    smart_ptr(smart_ptr<T> const &) = delete;
    smart_ptr<T> &operator=(smart_ptr<T> const &) = delete;
    smart_ptr(smart_ptr<T> &&);
    smart_ptr<T> &operator=(smart_ptr<T> &&);
    T *get() const;
    operator bool() const;
    T *operator->() const;
    T &operator* () const;
};
template<typename T>
smart_ptr<T>::~smart_ptr(){
	delete(ptr);
}
template<typename T>
smart_ptr<T>::smart_ptr(){
	ptr = nullptr;	
}
template<typename T>
smart_ptr<T>::smart_ptr(smart_ptr<T> &&rei){
	ptr = rei.ptr;	
	rei.ptr = nullptr;
}
template<typename T>
smart_ptr<T> &smart_ptr<T>::operator=(smart_ptr<T> &&tea){
	if(tea.ptr != ptr){
		ptr = tea.ptr;
		tea.ptr = nullptr;
	}
	return *this;
}
template<typename T>
T *smart_ptr<T>::get() const{
	return ptr;
}
template<typename T>
smart_ptr<T>::operator bool() const{
	return ptr != nullptr;
}
template<typename T>
T *smart_ptr<T>::operator->() const{
	return ptr;
}
template<typename T>
T &smart_ptr<T>::operator*() const{
	return *ptr;
}

int main(){
	int a = 0;
	smart_ptr<int> dn(a);
	smart_ptr<int> fuck = dn;
	std::cout << fuck.get() << std::endl;
}
