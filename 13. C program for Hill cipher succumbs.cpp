#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2 

void matrix_multiply(int A[MATRIX_SIZE][MATRIX_SIZE], int B[MATRIX_SIZE][MATRIX_SIZE], int C[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j, k;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            C[i][j] = 0;
            for (k = 0; k < MATRIX_SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
            C[i][j] %= 26;
            if (C[i][j] < 0) {
                C[i][j] += 26; 
            }
        }
    }
}

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

void solve_hill_cipher(int plaintexts[][MATRIX_SIZE], int ciphertexts[][MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int A[MATRIX_SIZE][MATRIX_SIZE];
    int B[MATRIX_SIZE][MATRIX_SIZE];
    int C[MATRIX_SIZE][MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            A[i][j] = plaintexts[0][j]; 
            B[i][j] = ciphertexts[0][j]; 
        }
    }

    int det_A = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    det_A = (det_A % 26 + 26) % 26; 

    int inv_det_A = mod_inverse(det_A, 26);

    int adj_A[MATRIX_SIZE][MATRIX_SIZE];
    adj_A[0][0] = A[1][1];
    adj_A[0][1] = -A[0][1];
    adj_A[1][0] = -A[1][0];
    adj_A[1][1] = A[0][0];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            adj_A[i][j] = (adj_A[i][j] % 26 + 26) % 26;
        }
    }

    matrix_multiply(adj_A, B, C);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            key[i][j] = (C[i][j] * inv_det_A) % 26;
            if (key[i][j] < 0) {
                key[i][j] += 26; 
            }
        }
    }
}

int main() {
    int plaintexts[3][MATRIX_SIZE] = {
        {0, 4}, 
        {4, 19}, 
        {0, 4}  
    };
    int ciphertexts[3][MATRIX_SIZE] = {
        {3, 22},
        {19, 19},
        {3, 22} 
    };

    int key[MATRIX_SIZE][MATRIX_SIZE];

    solve_hill_cipher(plaintexts, ciphertexts, key);

    printf("Key matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}

