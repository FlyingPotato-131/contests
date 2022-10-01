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

		qsort({&rng.begin[0], &rng.begin[less]});
		qsort({&rng.begin[len - grt], &rng.begin[len]});
	}else if(rng.end - rng.begin == 2 && rng.begin[0] > rng.begin[1]){
		rng.begin[0] = rng.begin[0] + rng.begin[1];
		rng.begin[1] = rng.begin[0] - rng.begin[1];
		rng.begin[0] = rng.begin[0] - rng.begin[1];
	}
}


int main(){
	int rng[20] = {-5, -3, -7, -5, 6, -3, 0, -5, 0, 2, 3, 6, 3, -9, 8, 5, -7, 5, 2, -6};
//	int rng[6] = {0, 1, 0, 1, 1, 0};
	qsort({&rng[0], &rng[19] + 1});
//	qsort({&rng[0], &rng[11]});
	for(int i = 0; i < 20; i++){
		std::cout << rng[i] << ", ";
	}
}
