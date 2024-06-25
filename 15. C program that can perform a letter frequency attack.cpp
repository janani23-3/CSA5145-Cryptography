#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void calculate_frequencies(char *text, int *freq) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        char c = tolower(text[i]);
        if (isalpha(c)) {
            freq[c - 'a']++;
        }
    }
}

void decrypt(char *ciphertext, int key, char *plaintext) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        char c = tolower(ciphertext[i]);
        if (isalpha(c)) {
            int original_pos = c - 'a';
            int shifted_pos = (original_pos - key + ALPHABET_SIZE) % ALPHABET_SIZE;
            plaintext[i] = (isupper(ciphertext[i])) ? toupper(shifted_pos + 'a') : shifted_pos + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

void frequency_attack(char *ciphertext, int top_count) {
    int frequencies[ALPHABET_SIZE] = {0};
    calculate_frequencies(ciphertext, frequencies);

    int max_frequency = 0;
    int most_frequent_letter = 0;
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (frequencies[i] > max_frequency) {
            max_frequency = frequencies[i];
            most_frequent_letter = i;
        }
    }

    printf("Most frequent letter in ciphertext: %c (%d occurrences)\n", most_frequent_letter + 'a', max_frequency);
    printf("Performing letter frequency attack...\n");

    printf("Top %d possible plaintexts:\n", top_count);
    for (i = 0; i < ALPHABET_SIZE; i++) {
        char plaintext[strlen(ciphertext) + 1];
        decrypt(ciphertext, i, plaintext);
        printf("Key %d: %s\n", i, plaintext);
        if (i >= top_count - 1) {
            break;
        }
    }
}

int main() {
    char ciphertext[] = "Tqxxa iqd ymnx fr qna uqfdab imj rwjw st xyfwjx zwj bnsl ymj gjknw ny qna jytwwjx.";
    int top_count = 10; 

    printf("Ciphertext:\n%s\n\n", ciphertext);
    frequency_attack(ciphertext, top_count);

    return 0;
}

