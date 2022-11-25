#include <iostream>

std::size_t strlen(const char *str){
	int len = 0;
	while(str[len] != 0){
		len++;
	}
	return len;
}
/*
void reverse(char *str){
	int len = strlen(str);
	for(int i = 0; i < len/2; i++){
		str[i] += str[len - i - 1];
		str[len - i - 1] = str[i] - str[len - i - 1];
		str[i] -= str[len - i - 1];
	}
}
*/
char *strcat(char const *str1, char const *str2){
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	char *rstr = static_cast<char *>(malloc(len1 + len2 + 2));
	for(int i = 0; i < len1; i++){
		rstr[i] = str1[i];
	}
	for(int i = 0; i < len2; i++){
		rstr[len1 + i] = str2[i];
	}
	rstr[len1 + len2] = '\0';
	return rstr;
}

struct vec3
{
    float x, y, z;
/*    float &operator[](std::ptrdiff_t const i) noexcept
    {
        return (&x)[i];
    }*/
};

struct mat3
{
    vec3 x, y, z;
    float *operator[](std::ptrdiff_t const i) noexcept
    {
        return reinterpret_cast<float *>(&x + i);
    }
    float const *operator[](std::ptrdiff_t const i) const noexcept
    {
        return reinterpret_cast<float const *>(&x + i);
    }
};

mat3 transpose(mat3 mtr){
	for(int i = 0; i < 3; i++){
		int h = (i+1)/2+1;
		int l = i/2;
		mtr[h][l] = mtr[l][h] + mtr[h][l];
		mtr[l][h] = mtr[h][l] - mtr[l][h];
		mtr[h][l] = mtr[h][l] - mtr[l][h];
	}
	return mtr;
}

float *point(vec3 vtr){
	float *pnt = static_cast<float *>(std::malloc(50));
	pnt[0] = vtr.x;
	pnt[1] = vtr.y;
	pnt[2] = vtr.z;
	return pnt;
}

vec3 tovec(float *pnt){
	return{pnt[0], pnt[1], pnt[2]};
}

vec3 operator*(mat3 mtr, vec3 vtr0){
	float *vtr = point(vtr0);
	float rvtr[3] = {0,0,0};
	for(int i = 0; i < 3; i++){
		float el = 0;
		for(int j = 0; j < 3; j++){
			el += mtr[i][j] * vtr[j];
		}
		rvtr[i] = el;
	}
	std::free(vtr);
	return tovec(rvtr);
}

mat3 operator*(mat3 mtr1, mat3 mtr2){
	mat3 resmtr;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			resmtr[i][j] = mtr1[i][0]*mtr2[0][j] + mtr1[i][1]*mtr2[1][j] + mtr1[i][2]*mtr2[2][j];
		}
	}
	return resmtr;
}

int main(){
	mat3 mtr1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	mat3 mtr2 = {{1, -2, 3}, {-4, 5, -6}, {7, -8, 9}};
	mat3 mtr = mtr1 * mtr2;
	for(int i = 0; i < 3; i++){
		std::cout << mtr[i][0] << " " << mtr[i][1] << " " << mtr[i][2] << std::endl;
	}
}
