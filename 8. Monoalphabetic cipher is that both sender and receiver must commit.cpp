#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to generate the cipher sequence based on the keyword
void generateCipherSequence(char *keyword, char *cipherSeq) {
    int used[ALPHABET_SIZE] = {0}; // Array to keep track of used letters
    int index = 0;

    // Add keyword letters to the cipher sequence
    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (!used[ch - 'A']) {
            cipherSeq[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    // Add remaining unused letters in alphabetical order
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipherSeq[index++] = ch;
        }
    }

    // Null-terminate the cipher sequence
    cipherSeq[index] = '\0';
}

// Function to create the reverse cipher sequence for decryption
void generateReverseCipherSequence(char *cipherSeq, char *reverseCipherSeq) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        reverseCipherSeq[cipherSeq[i] - 'A'] = 'A' + i;
    }
    reverseCipherSeq[ALPHABET_SIZE] = '\0';
}

// Function to encrypt the plaintext using the cipher sequence
void encrypt(char *plaintext, char *cipherSeq, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            ciphertext[i] = cipherSeq[ch - 'A'];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Function to decrypt the ciphertext using the reverse cipher sequence
void decrypt(char *ciphertext, char *reverseCipherSeq, char *decryptedText) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            decryptedText[i] = reverseCipherSeq[ch - 'A'];
        } else {
            decryptedText[i] = ciphertext[i];
        }
    }
    decryptedText[strlen(ciphertext)] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char cipherSeq[ALPHABET_SIZE + 1];
    char reverseCipherSeq[ALPHABET_SIZE + 1];

    // Generate the cipher sequence based on the keyword
    generateCipherSequence(keyword, cipherSeq);

    // Print the generated cipher sequence
    printf("Cipher Sequence: %s\n", cipherSeq);

    // Generate the reverse cipher sequence for decryption
    generateReverseCipherSequence(cipherSeq, reverseCipherSeq);

    // Example plaintext
    char plaintext[] = "hello world";
    char ciphertext[strlen(plaintext) + 1];
    char decryptedText[strlen(plaintext) + 1];

    // Encrypt the plaintext
    encrypt(plaintext, cipherSeq, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, reverseCipherSeq, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

