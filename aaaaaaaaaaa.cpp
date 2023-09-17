#include <iostream>
#include <string>
#include <vector>
#include <map>

unsigned int complexity(std::string s){
	unsigned int light = 0;
	unsigned int dark = 0;
	for(auto i : s){
		if(i == 'l' || i == 'i' || i == 'g' || i == 'h' || i == 't')
			light ++;
		if(i == 'd' || i == 'a' || i == 'r' || i == 'k')
			dark ++;
	}
	return light + dark;
}

unsigned int sentencecomplexity(std::string s){
	unsigned int max = 0;
	std::size_t pos = s.find(' ', 0);
	if(pos == std::string::npos){
		return complexity(s);
	}
	std::size_t old = 0;
	while(pos != std::string::npos){
	// std::cout << s.substr(old, pos - old) << std::endl;
	// std::cout << complexity(s.substr(old, pos - old));
		max = complexity(s.substr(old, pos - old)) > max ? complexity(s.substr(old, pos - old)) : max;
		old = pos;
		pos = s.find(' ', pos + 1);
	}
	return max;
}

int main(){
	unsigned int n;
	std::cin >> n;
	std::vector<std::string> sentences;

	for (unsigned int i = 0; i < n; ++i){
		// std::vector<std::string> input;
		std::string input;
		std::cin >> input;
		if(input.find('&') != std::string::npos){
			sentences.push_back(input);
			continue;
		}
		std::string tmp;
		std::cin >> tmp;
		while(tmp.back() != '&'){
			input = input + ' ' + tmp;
			std::cin >> tmp;
			// std::cout << 'f' << std::endl;
		}
		input = input + ' ' + tmp;
		// std::cout << std::endl << input << std::endl;
		sentences.push_back(input);
	}

	// std::cout << std::endl;

	std::map<unsigned int, std::string> out;
	for (unsigned int i = 0; i < n; ++i){
		// std::cout << std::endl;
		// std::cout << sentences[i] << ' ' << sentencecomplexity(sentences[i]) << std::endl;
		sentences[i].pop_back();
		out.emplace(sentencecomplexity(sentences[i] + '&'), sentences[i]);
	}
	// std::cout << std::endl << "max" << std::endl;
	std::cout << (--out.end())->second << std::endl;
}