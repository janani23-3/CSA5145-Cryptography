#include <stdio.h>
#include <string.h>
#include <ctype.h>

char playfair[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void find_position(char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (playfair[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt_playfair(char message[]) {
    int len = strlen(message);
    int i, row1, col1, row2, col2;
    char ch1, ch2;
    char encrypted_message[100];
    int index = 0;

    for (i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            message[index++] = toupper(message[i]);
        }
    }
    message[index] = '\0';
    len = index;

    index = 0;
    while (index < len) {
        ch1 = message[index++];
        ch2 = (index < len) ? message[index] : 'X'; 
        if (ch1 == ch2) {
            ch2 = 'X';
            index--; 
        }
        encrypted_message[index - 1] = ch1;
        encrypted_message[index] = ch2;
        index++;
    }
    encrypted_message[index] = '\0';

    len = strlen(encrypted_message);
    index = 0;
    while (index < len) {
        ch1 = encrypted_message[index++];
        ch2 = encrypted_message[index++];
        
        find_position(ch1, &row1, &col1);
        find_position(ch2, &row2, &col2);

        if (row1 == row2) { 
            printf("%c%c", playfair[row1][(col1 + 1) % 5], playfair[row2][(col2 + 1) % 5]);
        } else if (col1 == col2) { 
            printf("%c%c", playfair[(row1 + 1) % 5][col1], playfair[(row2 + 1) % 5][col2]);
        } else { 
            printf("%c%c", playfair[row1][col2], playfair[row2][col1]);
        }
    }
    printf("\n");
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";
    
    printf("Original message:\n%s\n", message);
    printf("Encrypted message:\n");
    encrypt_playfair(message);
    
    return 0;
}

