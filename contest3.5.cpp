#include <iostream>

struct Matrix
{
    float *data;
    std::size_t width, height;
};

Matrix createMatrix(std::size_t w, std::size_t h){
	return {static_cast<float *>(std::malloc(w*h*4)), w, h};
}

void deleteMatrix(Matrix mtr){
	std::free(mtr.data);
}

void fill(Matrix mtr){
	for(size_t h = 0; h < mtr.height; h++){
		for(size_t w = 0; w < mtr.width; w++){
			mtr.data[mtr.width*h + w] = w + h;
		}
	}
}

Matrix operator*(Matrix mtr1, Matrix mtr2){
	Matrix resmtr = createMatrix(mtr2.width, mtr1.height);
	for(size_t i = 0; i < mtr2.width * mtr1.height; i++){
		resmtr.data[i] = 0;
	}
	for(size_t h = 0; h < mtr1.height; h++){
		for(size_t w = 0; w < mtr2.width; w++){
			for(size_t pos = 0; pos < mtr1.width; pos++){
				resmtr.data[h*mtr2.width + w] += mtr1.data[h*mtr1.width + pos] * mtr2.data[pos*mtr2.width + w];
			}
		}
	}
	return resmtr;
}

int main(){
	Matrix mtr1 = createMatrix(4, 3);
	for(int i = 0; i < 12; i++){
		mtr1.data[i] = i + 1;
	}
	Matrix mtr2 = createMatrix(2, 4);
	for(int i = 0; i < 8; i++){
		mtr2.data[i] = i + 1;
	}
	Matrix resmtr = mtr1 * mtr2;
	for(size_t h = 0; h < 3; h++){
		for(size_t w = 0; w < 2; w++){
			std::cout << resmtr.data[2*h + w] << " ";
		}
		std::cout << std::endl;
	}
	deleteMatrix(mtr1);
	deleteMatrix(mtr2);
	deleteMatrix(resmtr);
}
