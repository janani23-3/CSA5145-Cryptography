#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define MAX_TEXT 1024

void toUpperCaseAndFilter(char *input, char *output) {
    int i, j = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[j++] = toupper(input[i]);
        }
    }
    output[j] = '\0';
}

void generateKeyTable(char *key, char table[SIZE][SIZE]) {
    int used[26] = {0};
    int i, j, k = 0;

    for (i = 0; key[i] != '\0'; i++) {
        if (key[i] == 'J') {
            key[i] = 'I'; 
        }
        if (!used[key[i] - 'A']) {
            table[k / SIZE][k % SIZE] = key[i];
            used[key[i] - 'A'] = 1;
            k++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (!used[i] && i != ('J' - 'A')) {
            table[k / SIZE][k % SIZE] = 'A' + i;
            k++;
        }
    }
}

void findPosition(char table[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (table[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decryptPair(char table[SIZE][SIZE], char in1, char in2, char *out1, char *out2) {
    int row1, col1, row2, col2;
    findPosition(table, in1, &row1, &col1);
    findPosition(table, in2, &row2, &col2);

    if (row1 == row2) {
        *out1 = table[row1][(col1 + SIZE - 1) % SIZE];
        *out2 = table[row2][(col2 + SIZE - 1) % SIZE];
    } else if (col1 == col2) {
        *out1 = table[(row1 + SIZE - 1) % SIZE][col1];
        *out2 = table[(row2 + SIZE - 1) % SIZE][col2];
    } else {
        *out1 = table[row1][col2];
        *out2 = table[row2][col1];
    }
}

void decryptPlayfair(char *ciphertext, char table[SIZE][SIZE], char *plaintext) {
    char a, b;
    int i, j = 0;
    for (i = 0; ciphertext[i] != '\0'; i += 2) {
        a = ciphertext[i];
        b = ciphertext[i + 1];
        decryptPair(table, a, b, &plaintext[j], &plaintext[j + 1]);
        j += 2;
    }
    plaintext[j] = '\0';
}

int main() {
    char key[] = "MONARCHY";  
    char table[SIZE][SIZE];
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCURZWGDSONSXBOUYWRHEBAAHYUSEDQ";
    char filteredCiphertext[MAX_TEXT];
    char plaintext[MAX_TEXT];

    generateKeyTable(key, table);

    toUpperCaseAndFilter(ciphertext, filteredCiphertext);

    decryptPlayfair(filteredCiphertext, table, plaintext);

    printf("Decrypted Text: %s\n", plaintext);

    return 0;
}

