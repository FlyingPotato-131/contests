#include <iostream>

void swap(int *a, int *b){
	int c = *a;
	*a = *b;
	*b = c;
}

struct IntConstRange{
	int const *begin;
	int const *end;
};

struct IntRange{
	int *begin;
	int *end;
};

int *max_element(IntRange rng){
	if(rng.end - rng.begin == 0){
		return rng.end;
	}
	int pos = 0;
	for(int i = 0; i < rng.end - rng.begin; i++){
		if(rng.begin[i] > rng.begin[pos]){
			pos = i;
		}
	}
	return rng.begin + pos;
}

void selection_sort(IntRange rng){
	int len = rng.end - rng.begin;
	if(len > 1){
		int *max = max_element({rng.begin + 1, rng.end});
		if(*max > rng.begin[0]){
			swap(rng.begin, max);
		}
		selection_sort({rng.begin + 1, rng.end});
	}
}

int const *find(IntConstRange rng, int n){
	for(int i = 0; i < rng.end - rng.begin; i++){
		if(rng.begin[i] == n){
			return rng.begin + i;
		}
	}
	return rng.end;
}

int const *lower_bound(IntConstRange range, int n){
	if(range.end - range.begin == 0){
		return range.begin;
	}
	int const *mid = range.begin + (range.end - range.begin)/2;
	if(*mid >= n){
		return lower_bound({range.begin, mid}, n);
	}else{
		return lower_bound({mid + 1, range.end}, n);
	}
}

int const *binary_search(IntConstRange range, int n){
	int const *low = lower_bound(range, n);
	return *low == n ? low : range.end;
}

using F = double(double);

double func(double x){return x*x - 0.9;}

struct Segment{
    double begin, end;
};

double abss(double a){return a >= 0 ? a : -a;}

double findRoot(Segment s, F f){
	double mid = (s.begin + s.end)/2;
	if(abss(s.end - s.begin) > 1e-6){
		if((f(s.end) > f(s.begin) && f(mid) > 0) || (f(s.end) < f(s.begin) && f(mid) < 0)){
			return(findRoot({s.begin, mid}, f));
		}else{
			return(findRoot({mid, s.end}, f));
		}
	}else{
		return mid;
	}
}

int *partition(IntRange range, auto predicate){
	int len = range.end - range.begin;
	int *left = range.begin;
	int right = 0;
	while((left - range.begin) + right < len){
		if(predicate(*left) == 0 && predicate(range.begin[len - right - 1]) == 1){
			swap(left, range.end - right - 1);
			left ++;
			right ++;
		}else if(predicate(*left) == 1){
			left ++;
		}else if(predicate(range.begin[len - right - 1]) == 0){
			right ++;
		}
	}
	return left;
}

void quicksort(IntRange range){
	if(range.end - range.begin > 1){
		auto leseq = [y = range.begin[0]](int x){return x <= y;};
		int *pos = partition(range, leseq) - 1;
//		auto les = [y = range.begin[0]](int x){return x < y;};
//		pos = partition({range.begin, pos}, les);
		swap(range.begin, pos);
//		for(int i = 0; i < range.end - range.begin; i++){
//			std::cout << range.begin[i] << ", ";
//		}
//		std::cout << std::endl;
		quicksort({range.begin, pos});
		quicksort({pos + 1, range.end});
	}
}

void quickselect(IntRange range, int *ptr){
		if(range.end - range.begin > 1){
		auto leseq = [y = range.begin[0]](int x){return x <= y;};
		int *pos = partition(range, leseq) - 1;
//		auto les = [y = range.begin[0]](int x){return x < y;};
//		pos = partition({range.begin, pos}, les);
		swap(range.begin, pos);
//		for(int i = 0; i < range.end - range.begin; i++){
//			std::cout << range.begin[i] << ", ";
//		}
//		std::cout << std::endl;
		if(pos > ptr){
			quickselect({range.begin, pos}, ptr);
		}else if(pos < ptr){
			quickselect({pos + 1, range.end}, ptr);
		}
	}
}


int main(){
	int const size = 10;
//	auto predicate1 = [](int x){return x < 0;};
	int rng[size] = {-8, 7, -3, -5, -5, 2, 4, -9, 1, -3};
	quickselect({rng, rng + size}, rng + 5);
	for(int i = 0; i < size; i++){
		std::cout << rng[i] << ", ";
	}
//	std::cout << std::endl << pos - rng << std::endl;
}

/*
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
int main()
{
    auto const N = 1000000u;
//	auto const N = 10;
    std::vector<int> v(N);
    
    int seed;
    std::cin >> seed;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distr(0, 1 << 16);
    for(auto i = 0u; i < N; ++i)
        v[i] = distr(gen);

    IntRange const range =
    {
        .begin = &v[0],
        .end   = &v[0] + N,
    };
//    for(int i = 0; i < N; i++){
//       	std::cout << range.begin[i] << ", ";
//    }
//    std::cout << std::endl;
    quicksort(range);
//    for(int i = 0; i < N; i++){
//    	std::cout << range.begin[i] << ", ";
//    }
//    std::cout << std::endl;
    std::cout << std::is_sorted(range.begin, range.end) << std::endl;
}*/
