#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

const float english_frequencies[ALPHABET_SIZE] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 
    0.0609, 0.0697, 0.0015, 0.0077, 0.0402, 0.0241, 0.0675, 
    0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906, 0.0276, 
    0.0098, 0.0236, 0.0015, 0.0197, 0.0007                   
};

double calculate_chi_square(const int observed_counts[], int total_count) {
    double chi_square = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        double expected_count = english_frequencies[i] * total_count;
        if (expected_count > 0) {
            double diff = observed_counts[i] - expected_count;
            chi_square += (diff * diff) / expected_count;
        }
    }
    return chi_square;
}

void decrypt_with_key(const char ciphertext[], const char key[], char plaintext[]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; ++i) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = key[ciphertext[i] - base];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

void frequency_attack(const char ciphertext[], int top_results) {
    int cipher_counts[ALPHABET_SIZE] = {0};
    int total_letters = 0;

    for (const char *p = ciphertext; *p; ++p) {
        if (isalpha(*p)) {
            ++cipher_counts[tolower(*p) - 'a'];
            ++total_letters;
        }
    }

    char plaintext[1000];  
    char key[ALPHABET_SIZE + 1];  
    double chi_squares[top_results];
    char best_plaintexts[top_results][1000];  

    for (int shift = 0; shift < ALPHABET_SIZE; ++shift) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            key[i] = 'a' + (i + shift) % ALPHABET_SIZE;
        }
        key[ALPHABET_SIZE] = '\0'; 

        decrypt_with_key(ciphertext, key, plaintext);

        double chi_square = calculate_chi_square(cipher_counts, total_letters);

        for (int i = 0; i < top_results; ++i) {
            if (chi_square < chi_squares[i] || i == 0) {
                for (int j = top_results - 1; j > i; --j) {
                    chi_squares[j] = chi_squares[j - 1];
                    strcpy(best_plaintexts[j], best_plaintexts[j - 1]);
                }
                chi_squares[i] = chi_square;
                strcpy(best_plaintexts[i], plaintext);
                break;
            }
        }
    }

    printf("Top %d possible plaintexts (in order of likelihood):\n", top_results);
    for (int i = 0; i < top_results; ++i) {
        printf("Rank %d:\n", i + 1);
        printf("%s\n", best_plaintexts[i]);
        printf("Chi-square value: %.2f\n", chi_squares[i]);
        printf("\n");
    }
}

int main() {
    char ciphertext[1000];  
    int top_results;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_results);

    frequency_attack(ciphertext, top_results);

    return 0;
}

