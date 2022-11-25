#include <iostream>
#include <vector>
#include <string>

bool isprime(int n){
	for(int i = 2; i <= n/2; i++){
		if(n % i == 0){
			return false;
		}
	}
	return true;
}

unsigned long long int primorial(int n){
	unsigned long long int prim = 1;
	for(int i = 1; i <= n; i++){
		if(isprime(i) == true){
			prim *= i;
		}
	}
	return prim;
}

char ouija[3][13]  = {
                {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'},
                {'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'},
                {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '!', '?'}
};

struct AlienLifeForm
{
        char name[50];
        unsigned int id;
        unsigned int weight;
        unsigned int length;
        unsigned int speed;
        unsigned int tentacles;
        unsigned int color[4];
        bool sentient;
        bool carnivore;
};

int len(char *str){
	int pos = 0;
	while(str[pos] != 0){
		pos++;
	}
	return pos;
}

long long wow(AlienLifeForm alien){
	return (alien.carnivore == 1 ? 5 : 1) * (alien.sentient == 1 ?
	len(alien.name) * 126 + alien.length * 5 + alien.tentacles * 97 + alien.color[0] * 4 + alien.color[1] * 4 + alien.color[2] * 30 + alien.color[3] * 138 - alien.weight * 2 - alien.speed * 5 :
	len(alien.name) * 23 + alien.weight * alien.speed * 52 + alien.length * 27 + alien.tentacles * 5 + alien.color[0] * 75 + alien.color[1] * 2 - alien.color[3] * 27) / (alien.carnivore == 0 ? 3 : 1);
}

int compare (AlienLifeForm a, AlienLifeForm b){
	long long wowa = wow(a);
	long long wowb = wow(b);
	return wowa < wowb ? -1 : wowa == wowb ? 0 : 1;
}

void message(int i_start, int j_start, int length){
	std::vector<char> str;
	str.push_back(ouija[i_start][j_start]);

	int h;
	int w;
	
	for(int n = 0; n < length - 1; n++){
		std::cin >> h >> w;
		
		i_start += h;
		j_start += w;

		if(i_start > 2 || i_start < 0 || j_start > 12 || j_start < 0){
			std::cout << "THE SPIRITS ARE RESTLESS";
			return;
		}else{
			str.push_back(ouija[i_start][j_start]);
		}
	}
	for(int i = 0; i < length; i++){
		std::cout << str[i];
	}
}

int main(){
	std::string board1;
	std::getline(std::cin, board1);

	std::string board2;
	std::getline(std::cin, board2);

	std::string board3;
	std::getline(std::cin, board3);

	std::string board = board1 + board2 + board3;
	
	for(int i = 0; i < 3; i++){
		if(board[i*3] + board[i*3 + 1] + board[i*3 + 2] == 'x' + 'x' + ' '){
//			std::cout << "line" << i << std::endl;
			board[i*3] = 'x';
			board[i*3 + 1] = 'x';
			board[i*3 + 2] = 'x';
		}
	}

	for(int i = 0; i < 3; i++){
		if(board[i] + board[i+3] + board[i+6] == 'x' + 'x' + ' '){
//			std::cout << "column" << i << std::endl;
			board[i] = 'x';
			board[i+3] = 'x';
			board[i+6] = 'x';
		}
	}

	if(board[0] + board[4] + board[8] == 'x' + 'x' + ' '){
		board[0] = 'x';
		board[4] = 'x';
		board[8] = 'x';
	}else if(board[2] + board[4] + board[6] == 'x' + 'x' + ' '){
		board[2] = 'x';
		board[4] = 'x';
		board[6] = 'x';
	}
	for(int h = 0; h < 3; h++){
		for(int w = 0; w < 3; w++){
			std::cout << board[3*h + w];
		}
		std::cout << std::endl;
	}
}

/*
int main()
{
        int n;
        std::cin >> n;
        AlienLifeForm zoo[100];
        for (int i = 0; i < n; i++)
                std::cin >> zoo[i].name >> zoo[i].id >> zoo[i].weight
                    >> zoo[i].length >> zoo[i].speed >> zoo[i].tentacles
                    >> zoo[i].color[0] >> zoo[i].color[1] >> zoo[i].color[2] >> zoo[i].color[3]
                    >> zoo[i].sentient >> zoo[i].carnivore;

        for (int i = 0; i < n; i++)
                for (int j = 0; j < n - i - 1; j++)
                        if (compare(zoo[j], zoo[j + 1]) > 0)
                        {
                                AlienLifeForm tmp = zoo[j];
                                zoo[j] = zoo[j + 1];
                                zoo[j + 1] = tmp;
                        }

        for (int i = 0; i < n; i++)
                std::cout << zoo[i].name << " ";
        std::cout << std::endl;
        return 0;
}*/

/*
int main(){
	char a[] = "as";
	std::cout << len(a);
}*/

/*
int main(){
	int n;
	std::cin >> n;
	int nums[120] = {0};

	int input;
	for(int i = 0; i < n - 1; i++){
		std::cin >> input;
		nums[input] = input;
	}
	for(int i = 1; i < n; i++){
		if(nums[i] == 0){
			std::cout << i;
			break;
		}
	}
}*/

/*
int main(){
	int n;
	std::cin >> n;
	int pos = 0;
	int len;
	for(int i = 0; i < n; i++){
		std::cin >> len;
		pos += i % 2 == 0 ? len : -len;
	}
	std::cout << pos << std::endl;
}*/
