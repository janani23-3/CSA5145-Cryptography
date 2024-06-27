#include <stdio.h>
#include <stdlib.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    unsigned long long temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long find_gcd_with_n(unsigned long long n, unsigned long long plaintext_block) {
    return gcd(n, plaintext_block);
}

int main() {
    unsigned long long n = 3233; 
    unsigned long long e = 17;   

    unsigned long long ciphertext_block = 855;

    unsigned long long plaintext_block = find_gcd_with_n(n, ciphertext_block);

    printf("Plaintext block with common factor with n: %llu\n", plaintext_block);

    unsigned long long p = 53;  
    unsigned long long q = 61;

    unsigned long long phi_n = (p - 1) * (q - 1);

    unsigned long long d;
    unsigned long long k = 1;
    while (1) {
        if ((1 + k * phi_n) % e == 0) {
            d = (1 + k * phi_n) / e;
            break;
        }
        k++;
    }

    printf("Private key d: %llu\n", d);

    unsigned long long decrypted_block = 1;
    for (int i = 0; i < d; i++) {
        decrypted_block = (decrypted_block * ciphertext_block) % n;
    }

    printf("Decrypted plaintext block: %llu\n", decrypted_block);

    return 0;
}

