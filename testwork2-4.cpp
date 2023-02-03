#include <iostream>
#include <vector>
#include <algorithm>

struct shower{
	int cm, time, id;
};

bool lessid(shower s1, shower s2){
	return s1.id < s2.id;
}

bool lesst(shower s1, shower s2){
	return s1.time < s2.time;
}

int main(){
	int t0, t1, n;
	std::vector<shower> data;
	std::cin >> t0 >> t1 >> n;
	int cm, t, id;
	for(int i = 0; i < n; i++){
		std::cin >> cm >> t >> id;
		data.push_back({cm, t, id});
	}
	std::sort(data.begin(), data.end(), lessid);
	int begin = 0;
	for(unsigned int i = 0; i < data.size(); i++){
		if(i + 1 == data.size() || data[i+1].id != data[i].id){
			std::sort(&data[begin], &data[i+1], lesst);
			begin = i + 1;
		}
	}
	int maxtid = 0;
	for(unsigned int i = 0; i + 1 < data.size(); i++){
		if(data[i+1].id == data[i].id && data[i+1].time - data[i].time > data[maxtid + 1].time - data[maxtid].time){
			maxtid = i;
		}
	}/*
	std::cout << std::endl;
	for(unsigned int i = 0; i < data.size(); i++){
		std::cout << data[i].cm << " " << data[i].time << " " << data[i].id << std::endl;
	}*/
	std::cout << data[maxtid].id;
}