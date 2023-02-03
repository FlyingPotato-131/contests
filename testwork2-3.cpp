/*input
12
*/

#include <iostream>

const unsigned int N_MEASUREMENTS = 11;
struct Pilot {
    unsigned int id; // уникальный номер пилота
    double measurements[N_MEASUREMENTS]; // набор его измеренных параметров

    // вы можете почитать расшифровку, какие числа что значат, но для решения это не обязательно
    // weight height chest_circumference
    // neck_length neck_circumference
    // thight_length thight_circumference
    // shin_length shin_circumference
    // sleeve_length wrist_circumference
};

void getStats(Pilot* pilots, unsigned int n, double deviation_rate, unsigned int* n_average_total, unsigned int* n_average_by_measurements){
	double average[N_MEASUREMENTS];
	for(unsigned int d = 0; d < N_MEASUREMENTS; d++){
		n_average_by_measurements[d] = 0;
		average[d] = 0;
	}
	for(unsigned int i = 0; i < n; i++){
		for(unsigned int d = 0; d < N_MEASUREMENTS; d++){
			average[d] += pilots[i].measurements[d];
		}
	}
	for(unsigned int d = 0; d < N_MEASUREMENTS; d++){
		average[d] /= n;
	}
	*n_average_total = 0;
	for(unsigned int i = 0; i < n; i++){
		bool flag = 1;
		for(unsigned int d = 0; d < N_MEASUREMENTS; d++){
			if(pilots[i].measurements[d] > average[d]*(1.f+deviation_rate) || pilots[i].measurements[d] < average[d]*(1.f-deviation_rate)){
				flag = 0;
			}else{
				n_average_by_measurements[d] ++;
			}
		}
		if(flag == 1){
			*n_average_total = *n_average_total + 1;
		}
	}
}

int main()
{
    unsigned int n;
    std::cin >> n;
    Pilot pilots[30];
    for (unsigned int i = 0; i < n; i++)
    {
        std::cin >> pilots[i].id;
        for (unsigned int j = 0; j < N_MEASUREMENTS; j++)
            std::cin >> pilots[i].measurements[j];
    }
    double deviation_rate;
    std::cin >> deviation_rate;

    unsigned int n_average_total, n_average_by_measurements[N_MEASUREMENTS];
    getStats(pilots, n, deviation_rate, &n_average_total, n_average_by_measurements);
    for (unsigned int i = 0; i < N_MEASUREMENTS; i++)
        std::cout << n_average_by_measurements[i] << ' ';
    std::cout << std::endl << n_average_total << std::endl;

    return 0;
}