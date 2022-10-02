#include <iostream>

struct IntRange{
	int *begin;
	int *end;
};

void qsort(IntRange rng){
	if(rng.end - rng.begin > 2){
		IntRange res;
		res.begin = static_cast<int *>(std::malloc((rng.end-rng.begin)*4));
		res.end = res.begin + (rng.end - rng.begin) + 1;

		int less = 0;
		int grt = 0;
		int len = rng.end - rng.begin;
		
		for(int i = 1; i < len; i++){
			if(rng.begin[i] <= rng.begin[0]){
				res.begin[less] = rng.begin[i];
				less ++;
			}else{
				res.begin[len - grt - 1] = rng.begin[i];
				grt ++;
			}
		}
		res.begin[less] = rng.begin[0];
//		std::cout << len << " " << less << " " << grt << std::endl;
		
		for(int i = 0; i < len; i++){
//			std::cout << res.begin[i] << ", ";
			rng.begin[i] = res.begin[i];
		}
//		std::cout << std::endl;
		std::free(res.begin);

		qsort({rng.begin, rng.begin + less});
		qsort({rng.begin + (len - grt), rng.begin + len});
	}else if(rng.end - rng.begin == 2 && rng.begin[0] > rng.begin[1]){
		rng.begin[0] = rng.begin[0] + rng.begin[1];
		rng.begin[1] = rng.begin[0] - rng.begin[1];
		rng.begin[0] = rng.begin[0] - rng.begin[1];
	}
}
/*
void qsort(IntRange rng){
	if(rng.end - rng.begin > 2){
//		IntRange res;
//		res.begin = static_cast<int *>(std::malloc((rng.end-rng.begin)*4));
//		res.end = res.begin + (rng.end - rng.begin) + 1;

		int less = 0;
		int len = rng.end - rng.begin;
		int div = rng.begin[0];
		int divpos = 0;
		for(int i = 1; i < len; i++){
			if(rng.begin[i] <= div){
				divpos += 1;
			}
		}
		int grt = 0;
		int next = rng.begin[divpos + 1];
		
		for(int i = 1; i < len; i++){
			int j = i/2 + (i%2 == 0 ? divpos + grt : 1.5 + less);
			j = j < len ? j : i;
			std::cout << j << std::endl;
			if(rng.begin[j] <= div){
				rng.begin[less] = rng.begin[j];
				less ++;
			}else{
				rng.begin[divpos + grt + 1] = rng.begin[j];
				grt ++;
			}
		}
		if(less < divpos){
			rng.begin[less] = next;
		}else{
			rng.begin[len] = next;
		}
		rng.begin[divpos] = div;

		for(int i = 0; i < len; i++){
			std::cout << rng.begin[i] << ", ";
		}
		std::cout << std::endl;

		std::cout << len << " " << less << " " <<grt << " " << divpos << std::endl;
		
//		std::cout << std::endl;

		qsort({rng.begin, rng.begin + divpos});
		qsort({rng.begin + divpos + 2, rng.begin + len});
	}else if(rng.end - rng.begin == 2 && rng.begin[0] > rng.begin[1]){
		rng.begin[0] = rng.begin[0] + rng.begin[1];
		rng.begin[1] = rng.begin[0] - rng.begin[1];
		rng.begin[0] = rng.begin[0] - rng.begin[1];
	}
}*/


int main(){
	int rng[20] = {5, 0, 1, 8, 2, 5, 1, 7, 2, 4};
//	int rng[6] = {0, 1, 0, 1, 1, 0};
	qsort({&rng[0], &rng[9] + 1});
//	qsort({&rng[0], &rng[11]});
	for(int i = 0; i < 10; i++){
		std::cout << rng[i] << ", ";
	}
}
/*
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
int main()
{
    auto const N = 1000000u;
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
    qsort(range);
    std::cout << std::is_sorted(range.begin, range.end) << std::endl;
}
*/
