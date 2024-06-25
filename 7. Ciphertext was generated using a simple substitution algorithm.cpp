#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CIPHERTEXT "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;"

#define ALPHABET_SIZE 26

void analyzeFrequency(const char *text, int *freq) {
    while (*text) {
        if (isprint(*text)) {
            freq[*text]++;
        }
        text++;
    }
}

void printFrequency(const int *freq) {
    printf("Character Frequency Analysis:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", i, freq[i]);
        }
    }
}

void decryptWithSubstitution(const char *ciphertext, const char *substitution) {
    char decrypted[strlen(ciphertext) + 1];
    strcpy(decrypted, ciphertext);

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {
            decrypted[i] = substitution[ciphertext[i]];
        }
    }

    printf("\nDecrypted Message:\n%s\n", decrypted);
}

int main() {
    int freq[256] = {0};
    analyzeFrequency(CIPHERTEXT, freq);
    printFrequency(freq);

    char substitution[256];
    for (int i = 0; i < 256; i++) {
        substitution[i] = i;
    }

    substitution['‡'] = 'e';
    substitution['†'] = 't';
    substitution['*'] = 'h';
    substitution[';'] = 'a';
    substitution[')'] = 'o';
    substitution['8'] = 'r';
    substitution['4'] = 'i';
    substitution['6'] = 's';
    substitution['5'] = 'n';
    substitution['0'] = 'm';
    substitution['3'] = 'p';
    substitution['9'] = 'd';
    substitution['('] = 'c';
    substitution['.'] = 'l';
    substitution['¶'] = 'u';
    substitution[':'] = 'y';
    substitution[']'] = 'w';
    substitution['?'] = 'v';
    substitution['—'] = 'f';
    

    decryptWithSubstitution(CIPHERTEXT, substitution);

    return 0;
}

