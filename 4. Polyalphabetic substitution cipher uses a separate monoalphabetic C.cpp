#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char encryptChar(char plainChar, char keyChar) {
    if (isalpha(plainChar)) {
        char base = islower(plainChar) ? 'a' : 'A';
        return (plainChar - base + (tolower(keyChar) - 'a')) % 26 + base;
    }
    return plainChar;
}

void preprocessKey(char *key, int textLen, char *newKey) {
    int keyLen = strlen(key);
    for (int i = 0, j = 0; i < textLen; i++, j++) {
        if (j == keyLen) j = 0;
        newKey[i] = key[j];
    }
    newKey[textLen] = '\0';
}

int main() {
    char plaintext[100], key[100], processedKey[100], encryptedText[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 

    int textLen = strlen(plaintext);

    preprocessKey(key, textLen, processedKey);

    for (int i = 0; i < textLen; i++) {
        encryptedText[i] = encryptChar(plaintext[i], processedKey[i]);
    }
    encryptedText[textLen] = '\0';

    printf("Encrypted text: %s\n", encryptedText);

    return 0;
}

