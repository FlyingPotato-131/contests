#include <iostream>

void increase(int *a){
	*a += 1;
}

int *next(int *ptr, std::size_t n){
	return ptr + n;
}

int dereference(void const *i){
	return *static_cast<const int*>(i);
}

std::uint32_t unsafeBitCast(float i){
	return *reinterpret_cast<uint32_t*>(&i);
}

struct IntRange{
	int *begin;
	int *end;
};

struct IntConstRange

{

    int const *begin;

    int const *end;

};

std::ptrdiff_t size(IntRange r){
	return r.end - r.begin;
}

IntConstRange constify(IntRange r){
	return {static_cast<int const *>(r.begin), static_cast<int const *>(r.end)};
}

IntRange createIntRange(std::size_t n){
	int *r = static_cast<int*>(std::malloc(n*sizeof(int)));
	return {r, r+n};
}

void deleteIntRange(IntRange r){
	std::free(r.begin);
}

int accumulate(IntConstRange range){
	int n = 0;
	for (int i = 0; i < range.end-range.begin; i++){
		n = n + *(range.begin + i);
	}
	return n;
}

//int arrsize = 10;

void recsort(int *ar, int pos, int fin){
	int tmpar[26214];	
	int countl = 0;
	int countr = 1;

	for(int i = pos + 1; i <= fin; i++){
		if(ar[i] <= ar[pos]){
			tmpar[countl + pos] = ar[i];
			countl ++;
		}
		else{
			tmpar[fin + 1 - countr] = ar[i];
			countr ++;			
		}
	}
	tmpar[countl + pos] = ar[pos];

	if(countl > 1){
		recsort(tmpar, pos, countl + pos - 1);
	}
	if(countr > 2){
		recsort(tmpar, fin - countr + 2, fin);
	}
	for(int i = pos; i <= fin; i++){
		ar[i] = tmpar[i];
	}
}

void sort(IntRange ar){
	recsort(ar.begin, 0, ar.end - ar.begin - 1);
}

std::size_t strlen(char const *str){
	int len = 0;
	while(str[len] != 0){
		len++;
	}
	return len;
}

int strcmp(char const *s1, char const *s2){
	int pos = 0;
	while(s1[pos] == s2[pos] && s1[pos] != 0 && s2[pos] != 0){
		pos++;
	}
	return s1[pos] == s2[pos] ? 0 : s1[pos] > s2[pos] ? 1 : -1;
}

char const *strstr(char const *haystack, char const *needle){
	if(needle[0] == 0){
		return haystack;
	}
	int pos = 0;
	while(haystack[pos] != 0){
		if(needle[0] == haystack[pos]){
			int i = 0;
			while(needle[i] != 0){
				if(needle[i] != haystack[pos + i]){
					break;
				}
				i++;
			}
			if(needle[i] == 0){
				return &haystack[pos];
			}
		}
		pos++;
	}
	return nullptr;
	
}

std::int64_t pow(std::int64_t x, int a){
	return (a == 0 ? 1 : a%2 == 0 ? (pow(x, a/2) * pow(x, a/2)) : (a > 0 ? x * pow(x, a-1) : pow(x, a+1) / x));
}

std::int64_t atoi2(char const *str){
	std::int64_t len = strlen(str);
	std::int64_t num = 0;
	int pos = str[0] == 45 ? 1 : 0;
	while(pos < len){
		num += pow(10, len - pos - 1) * (static_cast<int>(str[pos]) - '0');
		pos ++;
	}
	return str[0] == 45 ? -num : num;
}

char *itoa(std::int64_t num){
	char *str = static_cast<char *>(std::malloc(23));
	if(num == 0){
		str[0] = '0';
		str[1] = '\0';
		return str;
	}
	str[0] = '0';
	int i = 0;
	while(i < 19){
		str[i+1] = abs(num/pow(10, 18-i) - (i == 0 ? 0 : 10*(num/pow(10, 19-i)))) + '0';
		i++;
	}
	int n = 0;
	while(str[n] == '0'){
		n++;
	}
	if(num < 0){
		str[n-1] = '-';
	}
	str[20] = '\0';
	return str + n - (num < 0 ? 1 : 0);
}

/*
void arsort(int ar[], int pos, int fin){
	int tmpar[arrsize];
	int countl = 0;
	int countr = 1;
	for(int i = pos + 1; i <= fin; i++){
		if(ar[i] <= ar[pos]){
			tmpar[countl + pos] = ar[i];
			countl ++;
		}
		else{
			tmpar[fin + 1 - countr] = ar[i];
			countr ++;			
		}
	}
	tmpar[countl + pos] = ar[pos];
	if(countl > 1){
		arsort(tmpar, pos, countl + pos - 1);
	}
	if(countr > 2){8
		arsort(tmpar, fin - countr + 2, fin);
	}
	for(int i = pos; i <= fin; i++){
		ar[i] = tmpar[i];
	}
}*/

/*
int main(){
	int a = 5;
	increase(&a);
	int n = 2;
	void *begin = std::malloc(n*sizeof(int));
	int *beg = static_cast<int*>(begin);
//	int *next = begin + 1;
	int ar[10];
	*ar = 0;
	*(ar + 1) = 1; // <=> a[1]
//	std::cout<<a<<std::endl<<*next;
}
*/

int main(){
	std::cout << atoi2("-354") + 1 << std::endl;
}
