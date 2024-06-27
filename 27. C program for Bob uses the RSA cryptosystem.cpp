#include <stdio.h>

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)  
            result = (result * base) % mod;
        base = (base * base) % mod;  
        exp /= 2;  
    }
    return result;
}

int main() {
    unsigned long long n = 3233;  
    unsigned long long e = 17;    

    int plaintext[5] = {0, 18, 2, 11, 14}; 
    unsigned long long ciphertext[5];
    for (int i = 0; i < 5; ++i) {
        ciphertext[i] = mod_exp(plaintext[i], e, n);
        printf("%llu ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

