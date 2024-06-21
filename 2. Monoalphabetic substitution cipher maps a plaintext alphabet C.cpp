#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_LENGTH 26

void encrypt(char *plaintext, char *ciphertext) {
    int i;
    int len = strlen(plaintext);
    
    char mapping[ALPHABET_LENGTH];
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    
    char substitution[] = "zyxwvutsrqponmlkjihgfedcba";
    
    for (i = 0; i < ALPHABET_LENGTH; i++) {
        mapping[i] = substitution[i];
    }
    
    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                ciphertext[i] = mapping[plaintext[i] - 'a'];
            } else {
                ciphertext[i] = toupper(mapping[tolower(plaintext[i]) - 'a']);
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0'; 
}

int main() {
    char plaintext[1000];
    char ciphertext[1000];
    
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    plaintext[strcspn(plaintext, "\n")] = 0;
    
    encrypt(plaintext, ciphertext);
    
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}

