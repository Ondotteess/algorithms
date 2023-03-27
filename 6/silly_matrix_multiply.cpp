#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

typedef vector<vector<int>> matrix;

matrix matrix_multiplication(matrix A, matrix B) {
    int n = A.size(), m = B.size(), p = B[0].size();
    matrix C(n, vector<int>(p, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

matrix matrix_addition(matrix& A, matrix& B) {
    int n = A.size(), m = A[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = A[i][j] + B[i][j];
        }
    }
    return A;
}

matrix matrix_substract(matrix& A, matrix& B) {
    int n = A.size(), m = A[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = A[i][j] - B[i][j];
        }
    }
    return A;
}

void print_matrix(matrix A) {
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

void matrix_partition(matrix& A, matrix& A11, matrix& A12, matrix& A21, matrix& A22) {
    int n = A.size();
    int n2 = n / 2;

    A11.resize(n2);
    A12.resize(n2);
    A21.resize(n2);
    A22.resize(n2);

    for (int i = 0; i < n2; i++) {
        A11[i].resize(n2);
        A12[i].resize(n2);
        A21[i].resize(n2);
        A22[i].resize(n2);

        for (int j = 0; j < n2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n2];
            A21[i][j] = A[i + n2][j];
            A22[i][j] = A[i + n2][j + n2];
        }
    }
}

matrix matrix_merge(matrix A, matrix B, matrix C, matrix D) {
    int n = A.size() * 2; 
    matrix M(n, vector<int>(n));
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n / 2; j++) {
            M[i][j] = A[i][j];
            M[i][j + n / 2] = B[i][j];
            M[i + n / 2][j] = C[i][j];
            M[i + n / 2][j + n / 2] = D[i][j];
        }
    }
    return M;
}

matrix matrix_recursion_multiply(matrix _A, matrix _B) {
    if (_A.size() <= 16) {
        matrix M = matrix_multiplication(_A, _B);
        return M;
    }

    matrix A, B, C, D;
    matrix_partition(_A, A, B, C, D);

    matrix E, F, G, H;
    matrix_partition(_B, E, F, G, H);

    matrix A_E = matrix_recursion_multiply(A, E);
    matrix B_G = matrix_recursion_multiply(B, G);
    matrix A_F = matrix_recursion_multiply(A, F);
    matrix B_H = matrix_recursion_multiply(B, H);
    matrix C_E = matrix_recursion_multiply(C, E);
    matrix D_G = matrix_recursion_multiply(D, G);
    matrix C_F = matrix_recursion_multiply(C, F);
    matrix D_H = matrix_recursion_multiply(D, H);

    matrix M1 = matrix_addition(A_E, B_G);
    matrix M2 = matrix_addition(A_F, B_H);
    matrix M3 = matrix_addition(C_E, D_G);
    matrix M4 = matrix_addition(C_F, D_H);

    matrix M = matrix_merge(M1, M2, M3, M4);
    return M;
}

matrix generate_random_matrix(matrix& A) {
    srand(time(NULL));
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            A[i][j] = rand() % 30;
        }
    }
    return A;
}

matrix strassen_multiply(matrix _A, matrix _B) {
    if (_A.size() <= 16) {
        matrix M = matrix_multiplication(_A, _B);
        return M;
    }

    matrix A, B, C, D;
    matrix_partition(_A, A, B, C, D);

    matrix E, F, G, H;
    matrix_partition(_B, E, F, G, H);

    matrix P1 = strassen_multiply(A, matrix_substract(F, H));
    matrix P2 = strassen_multiply(matrix_addition(A, B), H);
    matrix P3 = strassen_multiply(matrix_addition(C, D), E);
    matrix P4 = strassen_multiply(D, matrix_substract(G, E));
    matrix P5 = strassen_multiply(matrix_addition(A, D), matrix_addition(E, H));
    matrix P6 = strassen_multiply(matrix_substract(B, D), matrix_addition(G, H));
    matrix P7 = strassen_multiply(matrix_substract(A, C), matrix_addition(E, F));

    matrix P5_P4 = matrix_addition(P5, P4);
    matrix P2_P6 = matrix_addition(P2, P6);
    matrix P1_P5 = matrix_addition(P1, P5);
    matrix P3_P7 = matrix_addition(P3, P7);

    matrix Q1 = matrix_substract(P5_P4, P2_P6);
    matrix Q2 = matrix_addition(P1, P2);
    matrix Q3 = matrix_addition(P3, P4);
    matrix Q4 = matrix_substract(P1_P5, P3_P7);

    matrix M = matrix_merge(Q1, Q2, Q3, Q4);

    return M;
}

int main() {

    int degree;
    cout << "matrix size: ";
    cin >> degree;

    int size = pow(2, degree);

    matrix A(size, vector<int>(size));
    matrix B(size, vector<int>(size));

    A = generate_random_matrix(A);
    B = generate_random_matrix(B);

    clock_t start_time_1 = clock();
    matrix D = matrix_multiplication(A, B);
    int start_2 = clock();
    cout << (std::clock() - start_time_1) / (double)CLOCKS_PER_SEC <<  " ";

    clock_t start_time_2 = clock();
    matrix F = matrix_recursion_multiply(A, B);
    cout << (clock() - start_time_2) / (double)CLOCKS_PER_SEC << " ";

    clock_t start_time_3 = clock();
    matrix C = strassen_multiply(A, B);
    cout << (clock() - start_time_3) / (double)CLOCKS_PER_SEC << " ";


}
