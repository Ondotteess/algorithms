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

	

};

Matrix matrix_addition(Matrix& a, Matrix& b) {
	Matrix c(a.size);
	for (auto i = 0; i < a.size; i++) {
		for (auto j = 0; j < a.size; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

Matrix matrix_substract(Matrix& a, Matrix& b) {
	Matrix c(a.size);
	for (auto i = 0; i < a.size; i++) {
		for (auto j = 0; j < a.size; j++) {
			c[i][j] = a[i][j] - b[i][j];
		}
	}
	return c;
}

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

Matrix half_adder(Matrix& first, int a_x_pos, int a_y_pos,
				  Matrix& second, int b_x_pos, int b_y_pos, int size) {

	Matrix ret(size);

	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			ret[i][j] = first[a_x_pos + i][a_y_pos + j] + second[b_x_pos + i][b_y_pos + j];
		}
	}

	return ret;

}

Matrix half_substractor(Matrix& first, int a_x_pos, int a_y_pos,
	Matrix& second, int b_x_pos, int b_y_pos, int size) {

	Matrix ret(size);

	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			ret[i][j] = first[a_x_pos + i][a_y_pos + j] - second[b_x_pos + i][b_y_pos + j];
		}
	}

	return ret;

}


Matrix recursion_multiply(Matrix& first, int a_x_pos, int a_y_pos,
	Matrix& second, int b_x_pos, int b_y_pos, int size) {
	if (size == 16) {
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
			ret[i][j + middle] = a_f[i][j] + b_h[i][j];
			ret[i + middle][j] = c_e[i][j] + d_g[i][j];
			ret[i + middle][j + middle] = c_f[i][j] + d_h[i][j];
		}
	}

	return ret;
}


Matrix strassen_multiply(Matrix& first, int a_x_pos, int a_y_pos, 
						 Matrix& second, int b_x_pos, int b_y_pos, int size){

	if (size == 16) {
		return matrix_multiply(first, a_x_pos, a_y_pos, second, b_x_pos, b_y_pos, size);
	}

	Matrix ret(size);

	int middle = size / 2;

	Matrix f_minus_h(middle);
	Matrix a_plus_b(middle);
	Matrix c_plus_d(middle);
	Matrix g_minus_e(middle);
	Matrix a_plus_d(middle);
	Matrix e_plus_h(middle);
	Matrix b_minus_d(middle);
	Matrix g_plus_h(middle);
	Matrix a_minus_c(middle);
	Matrix e_plus_f(middle);

	f_minus_h = half_substractor(second, b_x_pos + middle, b_y_pos, second, b_x_pos + middle, b_y_pos + middle, middle);
	a_plus_b = half_adder(first, a_x_pos, a_y_pos, first, a_x_pos + middle, a_y_pos, middle);
	c_plus_d = half_adder(first, a_x_pos, a_y_pos + middle, first, a_x_pos + middle, a_y_pos + middle, middle);
	g_minus_e = half_substractor(second, b_x_pos, b_y_pos + middle, second, b_x_pos, b_y_pos, middle);
	a_plus_d = half_adder(first, a_x_pos, a_y_pos, first, a_x_pos + middle, a_y_pos + middle, middle);
	e_plus_h = half_adder(second, b_x_pos, b_y_pos, second, b_x_pos + middle, b_y_pos + middle, middle);
	b_minus_d = half_substractor(first, a_x_pos + middle, a_y_pos, first, a_x_pos + middle, a_y_pos + middle, middle);
	g_plus_h = half_adder(second, b_x_pos, b_y_pos + middle, second, b_x_pos + middle, b_y_pos + middle, middle);
	a_minus_c = half_substractor(first, a_x_pos, a_y_pos, first, a_x_pos, a_x_pos + middle, middle);
	e_plus_f = half_adder(second, b_x_pos, b_y_pos, second, b_x_pos + middle, b_y_pos, middle);


	Matrix P1 = strassen_multiply(first, a_x_pos, a_y_pos, f_minus_h, 0, 0, middle);
	Matrix P2 = strassen_multiply(a_plus_b, 0, 0, second, b_x_pos + middle, b_y_pos + middle, middle);
	Matrix P3 = strassen_multiply(c_plus_d, 0, 0, second, b_x_pos, b_y_pos, middle);
	Matrix P4 = strassen_multiply(first, a_x_pos + middle, a_y_pos + middle, g_minus_e, 0, 0, middle);
	Matrix P5 = strassen_multiply(a_plus_d, 0, 0, e_plus_h, 0, 0, middle);
	Matrix P6 = strassen_multiply(b_minus_d, 0, 0, g_plus_h, 0, 0, middle);
	Matrix P7 = strassen_multiply(a_minus_c, 0, 0, e_plus_f, 0, 0, middle);

	Matrix P5_plus_P4 = matrix_addition(P5, P4);
	Matrix P2_minus_P6 = matrix_substract(P2, P6);

	Matrix P1_plus_P5 = matrix_addition(P1, P5);
	Matrix P3_plus_P7 = matrix_addition(P1, P7);

	Matrix Q1 = matrix_substract(P5_plus_P4, P2_minus_P6);
	Matrix Q2 = matrix_addition(P1, P2);
	Matrix Q3 = matrix_addition(P3, P4);
	Matrix Q4 = matrix_substract(P1_plus_P5, P3_plus_P7);


	for (int i = 0; i < middle; ++i) {
		for (int j = 0; j < middle; ++j) {
			ret[i][j] = Q1[i][j];
			ret[i][j + middle] = Q2[i][j];
			ret[i + middle][j] = Q3[i][j];
			ret[i + middle][j + middle] = Q4[i][j];
		}
	}
	
	return ret;

}

int main() {
	int matrix_size;
	cout << "matrix size: ";
	cin >> matrix_size;
	Matrix a(pow(2, matrix_size));
	Matrix b(pow(2, matrix_size));

	a.fill_random(5, 0);
	b.fill_random(10, 0);

	auto start_time = std::chrono::high_resolution_clock::now();
	Matrix c = strassen_multiply(a, 0, 0, b, 0, 0, a.size);
	auto end_time = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> elapsed_time = end_time - start_time;
	std::cout << "Elapsed time: " << elapsed_time.count() << " s" << std::endl;


}
