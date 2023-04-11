#include <iostream>
#include <cstdlib>
#include <ctime>


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


	
};


class Submartix {

public:

	int parent_size;
	int size;
	int* data;
	int x_position;
	int y_position;

	Submartix(Matrix parent, int x_pos, int y_pos, int s) {
		size = s;
		x_position = x_pos;
		y_position = y_pos;
		data = parent.data;
		parent_size = parent.size;
	}

	void print_submatrix() {
		for (auto i = x_position; i < x_position + size; i++) {
			cout << endl;
			for (auto j = y_position; j < y_position + size; j++) {
				cout << *(data + i * parent_size + j) << " ";
			}
		}
	}

	int* operator[](int index) {
		return &data[x_position * parent_size + y_position + index * size];
	}
	  
};

int main() {
	Matrix m(10);

	m.fill_random(100, 0);

	Submartix a(m, 2, 2, 3);

	a.print_submatrix();

	cout << endl;

	m.print_matrix();

	cout << endl << endl;

	a.print_submatrix(); cout << endl;

	a[0][0] = -100; a[1][1] = -100; a[0][1] = -100; a[1][0] = -100;
	m.print_matrix();
	

}
