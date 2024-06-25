#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vigenere_decrypt(char *ciphertext, int *key_stream, int key_len, char *plaintext) {
    int len = strlen(ciphertext);
    int i;

    for (i = 0; i < len; i++) {
        int shift = key_stream[i % key_len]; 
        plaintext[i] = (ciphertext[i] - 'a' - shift + 26) % 26 + 'a';
    }
    plaintext[len] = '\0'; 
}

int main() {
    char ciphertext[] = "bqfqlkzsmnbnz";
    int key_stream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_len = sizeof(key_stream) / sizeof(key_stream[0]); 
    char plaintext[strlen(ciphertext) + 1];

    printf("Ciphertext: %s\n", ciphertext);
    
    vigenere_decrypt(ciphertext, key_stream, key_len, plaintext);

    printf("Key stream: ");
    for (int i = 0; i < key_len; i++) {
        printf("%d ", key_stream[i]);
    }
    printf("\n");

    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}

