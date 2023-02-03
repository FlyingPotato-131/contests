#include <iostream>
#include <vector>

template<typename T>
T min(T a, T b){
	return(a < b ? a : b);
}

template<typename T, typename U>
T bit_cast(U thing){
	return(*(reinterpret_cast<T*>(&thing)));
}

template<typename T>
void sswap(T pa, T pb)
{
    auto const copy = *pa;
    *pa = *pb;
    *pb = copy;
}

template<typename RandomIt, typename Pred>
RandomIt partition(RandomIt begin, RandomIt end, Pred predicate){
	//int len = end - begin;
	RandomIt left = begin;
	int right = 0;
	while((left - begin) + right < end - begin){
		if(predicate(left) == 0 && predicate(begin + (end - begin - right - 1)) == 1){
			sswap(left, end - right - 1);
			//left ++;
			//right ++;
		}else if(predicate(left) == 1){
			left ++;
		}else if(predicate(begin + (end - begin - right - 1)) == 0){
			right ++;
		}
	}
	return left;
}

template<typename RandomIt, typename Compare>

void quicksort(RandomIt begin, RandomIt end, Compare cmp){
	if(end - begin > 1){
		auto leseq = [begin, cmp](RandomIt x){return cmp(*x, *begin);};
		RandomIt pos = partition(begin, end, leseq);
		//sswap(begin, pos);
		// std::cout << *pos << " ";
		// std::cout << *begin << " " << end[-1] << " ";
		// for(int i = 0; i < end - begin; i++){
		// 	std::cout << begin[i];
		// }
		// std::cout << std::endl;
		sswap(begin, pos);
		
//		if(pos - begin > 1){
			quicksort(begin, pos, cmp);
//		}
//		if(end - pos > 2){
			quicksort(pos + 1, end, cmp);
//		}
	}
}

template<std::uint64_t n>
std::uint64_t fib64(){
	return fib64<n - 2>() + fib64<n-1>();
}

template<>
std::uint64_t fib64<0>(){return 0;}

template<>
std::uint64_t fib64<1>(){return 1;}

#include <utility>
template<std::size_t... I>
void print(std::index_sequence<I...>)
{
    ((std::cout << fib64<I>() << ' '),...);
    std::cout << std::endl;
}

template<typename T>
struct Node
{
    T value;
    Node<T> *next;
};
template<typename T>
using List = Node<T> *;

template<typename T>
List<T> cons(T val, List<T> next = nullptr){
	List<T> nd = static_cast<List<T>>(std::malloc(sizeof(Node<T>)));
	nd->value = val;
	nd->next = next;
	return nd;
}

template<typename T>
void destroyList(List<T> lst){
	if(lst->next != nullptr)
		destroyList(lst->next);
	std::free(lst);
}

template<typename T>
struct is_floating_point{
	static constexpr bool value = 0;
};

template<>
struct is_floating_point<float>{
	static constexpr bool value = 1;
};

template<>
struct is_floating_point<double>{
	static constexpr bool value = 1;
};

template<>
struct is_floating_point<long double>{
	static constexpr bool value = 1;
};

int main()
{
	is_floating_point<int>::value;
	std::cout << a.value;
}