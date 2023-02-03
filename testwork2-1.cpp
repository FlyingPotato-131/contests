#include <iostream>
#include <vector>

int main(){
	int F, N, M, D;
	std::cin >> F >> N >> M >> D;
	std::vector<int> prtime;
	std::vector<int> rltime;
	int time;
	
	for(int i = 0; i < N; i++){
		std::cin >> time;
		prtime.push_back(time);
	}
	for(int i = 0; i < N; i++){
		std::cin >> time;
		rltime.push_back(time);
	}
	int num = 0;
	for(int i = 0; i < N; i++){
		if(F > 0){
			num ++;
		}else{break;}
		if(prtime[i] < rltime[i]){
			F = F - rltime[i] - D;
		}else if(prtime[i] > rltime[i]){
			F = F - rltime[i] + M;
		}else{
			F -= rltime[i];
		}
	}
	std::cout << num;
}
