#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void encrypt(char *text, int k) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            text[i] = (ch - base + k) % 26 + base;
        }
    }
}

int main() {
    char text[100];
    int k;

    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the value of k (1-25): ");
    scanf("%d", &k);

    if (k < 1 || k > 25) {
        printf("Invalid value of k. Please enter a value between 1 and 25.\n");
        return 1;
    }

    encrypt(text, k);
    printf("Encrypted text: %s\n", text);

    return 0;
}

