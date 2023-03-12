import random
import time

def multiplyClassic(A, B):
    n = len(A)
    C = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i][j] += A[i][k] * B[k][j]
    return C

def matrix_addition(__A, __B):
        n = len(__A)
        C = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                C[i][j] = __A[i][j] + __B[i][j]
        return C

def subtract_matrices(matrix1, matrix2):
    n = len(matrix1)
    result = [[0 for j in range(n)] for i in range(n)]
    for i in range(n):
        for j in range(n):
            result[i][j] = matrix1[i][j] - matrix2[i][j]
    return result

def matrix_partition(A):
        n = len(A)

        half_n = n // 2
        A11 = [row[:half_n] for row in A[:half_n]]
        A12 = [row[half_n:] for row in A[:half_n]]
        A21 = [row[:half_n] for row in A[half_n:]]
        A22 = [row[half_n:] for row in A[half_n:]]
        return A11, A12, A21, A22

def matrix_merge(A11, A12, A21, A22):
        n = len(A11)
        B = [[0] * (2 * n) for _ in range(2 * n)]
        for i in range(n):
            for j in range(n):
                B[i][j] = A11[i][j]
                B[i][j + n] = A12[i][j]
                B[i + n][j] = A21[i][j]
                B[i + n][j + n] = A22[i][j]
        return B

def multiplyRecursion(_A, _B):

    if len(_A) == 2:
        return multiplyClassic(_A, _B)

    A, B, C, D = matrix_partition(_A)
    E, F, G, H = matrix_partition(_B)

    M1 = matrix_addition(multiplyRecursion(A, E), multiplyRecursion(B, G))
    M2 = matrix_addition(multiplyRecursion(A, F), multiplyRecursion(B, H))
    M3 = matrix_addition(multiplyRecursion(C, E), multiplyRecursion(D, G))
    M4 = matrix_addition(multiplyRecursion(C, F), multiplyRecursion(D, H))

    return matrix_merge(M1, M2, M3, M4)

def generate_matrix(n):
    matrix = []
    for i in range(n):
        row = []
        for j in range(n):
            row.append(random.randint(0, 9))
        matrix.append(row)
    return matrix

def print_matrix(matrix):
    n = len(matrix)
    for i in range(n):
        for j in range(n):
            print(matrix[i][j], end=" ")
        print()

def strassen_multiply(X, Y):
    if len(X) == 2:
        return multiplyClassic(X, Y)

    A, B, C, D = matrix_partition(X)
    E, F, G, H = matrix_partition(Y)

    P1 = strassen_multiply(A, subtract_matrices(F, H))
    P2 = strassen_multiply(matrix_addition(A, B), H)
    P3 = strassen_multiply(matrix_addition(C, D), E)
    P4 = strassen_multiply(D, subtract_matrices(G, E))
    P5 = strassen_multiply(matrix_addition(A, D), matrix_addition(E, H))
    P6 = strassen_multiply(subtract_matrices(B, D), matrix_addition(G, H))
    P7 = strassen_multiply(subtract_matrices(A, C), matrix_addition(E, F))

    Q1 = subtract_matrices(matrix_addition(P5, P4), subtract_matrices(P2, P6))
    Q2 = matrix_addition(P1, P2)
    Q3 = matrix_addition(P3, P4)
    Q4 = subtract_matrices(matrix_addition(P1, P5), matrix_addition(P3, P7))

    return matrix_merge(Q1, Q2, Q3, Q4)

degree = int(input())

size = 2 ** degree

A = generate_matrix(size)
B = generate_matrix(size)

start_time = time.time()
D = multiplyClassic(A, B)
end_time = time.time()
classic_time = end_time - start_time

start_time = time.time()
C = multiplyRecursion(A, B)
end_time = time.time()
recursion_time = end_time - start_time

start_time = time.time()
F = strassen_multiply(A, B)
end_time = time.time()
strassen_time = end_time - start_time

print(f'{round(classic_time, 5)} {round(recursion_time, 5)} {round(strassen_time, 5)}')
