#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateMatrix(char key[], char matrix[SIZE][SIZE]) {
    int used[26] = {0}, k = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]) == 'J' ? 'I' : toupper(key[i]);
        if (!used[ch - 'A'] && isalpha(ch)) {
            matrix[k / SIZE][k % SIZE] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!used[ch - 'A']) {
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }
}

void findPosition(char ch, char matrix[SIZE][SIZE], int *row, int *col) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
}

void encryptDigraph(char digraph[], char matrix[SIZE][SIZE], char encrypted[]) {
    int row1, col1, row2, col2;
    findPosition(digraph[0], matrix, &row1, &col1);
    findPosition(digraph[1], matrix, &row2, &col2);
    if (row1 == row2) {
        encrypted[0] = matrix[row1][(col1 + 1) % SIZE];
        encrypted[1] = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        encrypted[0] = matrix[(row1 + 1) % SIZE][col1];
        encrypted[1] = matrix[(row2 + 1) % SIZE][col2];
    } else {
        encrypted[0] = matrix[row1][col2];
        encrypted[1] = matrix[row2][col1];
    }
}

void preprocessPlaintext(char plaintext[], char processed[]) {
    int k = 0;
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = toupper(plaintext[i]) == 'J' ? 'I' : toupper(plaintext[i]);
        if (isalpha(ch)) processed[k++] = ch;
    }
    for (int i = 0; i < k; i += 2) {
        if (i + 1 == k || processed[i] == processed[i + 1]) {
            memmove(processed + i + 2, processed + i + 1, k - i - 1);
            processed[i + 1] = 'X';
            k++;
        }
    }
    processed[k] = '\0';
}

int main() {
    char key[100], plaintext[100], processed[200], encrypted[200] = {0};
    char matrix[SIZE][SIZE];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    generateMatrix(key, matrix);
    preprocessPlaintext(plaintext, processed);

    int len = strlen(processed);
    for (int i = 0; i < len; i += 2) {
        char digraph[3] = {processed[i], processed[i + 1], '\0'};
        char encryptedDigraph[3] = {0};
        encryptDigraph(digraph, matrix, encryptedDigraph);
        strncat(encrypted, encryptedDigraph, 2);
    }

    printf("Encrypted text: %s\n", encrypted);
    return 0;
}

