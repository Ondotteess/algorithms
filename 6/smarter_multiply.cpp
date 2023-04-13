#include <iostream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <cmath>
#include <chrono>

using namespace std;





class Matrix {
public:

	int size;
	int* data;


	 Matrix(int s) {
	 	size = s;
	 	data = new int[s * s];
	 }

	int* operator[](int index) {
		return &data[index * size];
	}

	int get_size() {
		return size;
	}

	void print_matrix() {
		cout << endl;
		for (auto i = 0; i < size; i++) {
			cout << endl;
			for (auto j = 0; j < size; j++) {
				cout << *(data + i * size + j) << " ";
			}
		}
	}

	void fill_random(int max, int min) {
		srand(time(nullptr));
		for (auto i = 0; i < size; i++) {
			for (auto j = 0; j < size; j++) {
				*(data + i * size + j) = rand() % (max - min + 1) + min;
			}
		}
	}

	void print_submatrix(Matrix& parent, int x_position, int y_position, int size) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) { 
				// cout << parent[y_position + i][x_position + j] << " ";
				std::cout << typeid(parent[y_position + i][x_position + j]).name() << std::endl;
			}
			cout << endl;
		}


	}

	Matrix matrix_addition(Matrix& a, Matrix& b) {
		Matrix c(a.size);
		for (auto i = 0; i < a.size; i++) {
			for (auto j = 0; j < a.size; j++) {
				c[i][j] = a[i][j] + b[i][j];
			}
		}
		return c;
	}

	
};
 
Matrix matrix_multiply(Matrix& first, int a_x_pos, int a_y_pos,
					   Matrix& second, int b_x_pos, int b_y_pos, int size) {
	Matrix result(size);

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			int sum = 0;
			for (int k = 0; k < size; ++k) {
				sum += first[a_x_pos + i][a_y_pos + k] * second[b_x_pos + k][b_y_pos + j];
			}
			result[i][j] = sum;
		}
	}

	return result;
}


Matrix recursion_multiply(Matrix& first, int a_x_pos, int a_y_pos,
						  Matrix& second, int b_x_pos, int b_y_pos, int size) {
	if (size == 4) {
		return matrix_multiply(first, a_x_pos, a_y_pos, second, b_x_pos, b_y_pos, size);
	}

	int middle = size / 2;

	Matrix ret(size);

	Matrix a_e = recursion_multiply(first, a_x_pos, a_y_pos, second, b_x_pos, b_y_pos, middle);
	Matrix b_g = recursion_multiply(first, a_x_pos, a_y_pos + middle, second, b_x_pos + middle, b_y_pos, middle);
	Matrix c_e = recursion_multiply(first, a_x_pos + middle, a_y_pos, second, b_x_pos, b_y_pos, middle);
	Matrix d_g = recursion_multiply(first, a_x_pos + middle, a_y_pos + middle, second, b_x_pos + middle, b_y_pos, middle);
	Matrix a_f = recursion_multiply(first, a_x_pos, a_y_pos, second, b_x_pos, b_y_pos + middle, middle);
	Matrix b_h = recursion_multiply(first, a_x_pos, a_y_pos + middle, second, b_x_pos + middle, b_y_pos + middle, middle);
	Matrix c_f = recursion_multiply(first, a_x_pos + middle, a_y_pos, second, b_x_pos, b_y_pos + middle, middle);
	Matrix d_h = recursion_multiply(first, a_x_pos + middle, a_y_pos + middle, second, b_x_pos + middle, b_y_pos + middle, middle);

	for (int i = 0; i < middle; ++i) {
		for (int j = 0; j < middle; ++j) {
			ret[i][j] = a_e[i][j] + b_g[i][j];
			ret[i][j + middle] = c_e[i][j] + d_g[i][j];
			ret[i + middle][j] = a_f[i][j] + b_h[i][j];
			ret[i + middle][j + middle] = c_f[i][j] + d_h[i][j];
		}
	}

	return ret;
}

int main() {
	Matrix a(pow(2, 10));
	Matrix b(pow(2, 10));

	a.fill_random(5, 0);
	b.fill_random(5, 0);


	auto start_time = std::chrono::high_resolution_clock::now();
	Matrix c = recursion_multiply(a, 0, 0, b, 0, 0, a.size);
	auto end_time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_time = end_time - start_time;
	std::cout << "Elapsed time: " << elapsed_time.count() << " s" << std::endl;

}
