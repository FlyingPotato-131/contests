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

// template<std::uint64_t a0, std::uint64_t a1>
// std::uint64_t fibtemp<a0, a1, 0>(){return a0;}

// template<std::uint64_t a0, std::uint64_t a1>
// std::uint64_t fibtemp<a0, a1, 1>(){return a1;}

// template<std::uint64_t a0, std::uint64_t a1, std::uint16_t const n>
// std::uint64_t fibtemp(){
// 	return fibtemp<a0, a1, n - 2>() + fibtemp<a0, a1, n-1>();
// }

#include <utility>
// template<std::size_t... I>
// void print(std::index_sequence<I...>)
// {
//     ((std::cout << fib64<I>() << ' '),...);
//     std::cout << std::endl;
// }

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

template<typename T>
struct is_pointer{
	static constexpr bool value = 0;
};

template<typename T>
struct is_pointer<T*>{
	static constexpr bool value = 1;
};

template<typename T>
struct is_pointer<T* const>{
	static constexpr bool value = 1;
};

template<typename T>
struct remove_pointer{
	using type = T;
};
template<typename T>
struct remove_pointer<T*>{
	using type = T;
};

template<typename T>
struct remove_pointer<T* const>{
	using type = T;
};

template<std::uint64_t a0, std::uint64_t a1, std::uint16_t... fib>
std::uint64_t fib64_impl(std::uint8_t const n, std::integer_sequence<std::uint16_t, fib...> nums){
	constexpr std::uint64_t array[256] = {(fib == 0 ? a0 : fib == 1 ? a1 : array[fib-1] + array[fib-2])...};
	return array[n];
}

template<std::uint64_t a0, std::uint64_t a1>
std::uint64_t fib64(std::uint8_t const n){
	return fib64_impl<a0, a1>(n, std::make_integer_sequence<std::uint16_t, 256>{});
}

// int main()
// {
// 	int n;
// 	std::cin >> n;
// 	int const m = n;
// 	std::cout << fibtemp<1, 2, 6>();
// }

int main()
{
    using u64 = std::uint64_t;
    u64 const N = 400000;
    u64 sum1 = 0;
    for(u64 i = 0; i < N; ++i)
        sum1 += fib64<1, 3>(i % 256);
    u64 sum2 = 0;
    for(u64 i = 0; i < N; ++i)
        sum2 += fib64<2, 5>(i % 256);
    std::cout << sum1 << ' ' << sum2 << std::endl;
}