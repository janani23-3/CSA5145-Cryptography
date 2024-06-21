#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

char encryptChar(char p, int a, int b) {
    if (isalpha(p)) {
        char base = islower(p) ? 'a' : 'A';
        return (char) ((((a * (p - base)) + b) % 26) + base);
    }
    return p;
}

char decryptChar(char c, int a, int b) {
    if (isalpha(c)) {
        char base = islower(c) ? 'a' : 'A';
        int a_inv = modInverse(a, 26);
        return (char) (((a_inv * ((c - base - b + 26)) % 26)) + base);
    }
    return c;
}

int main() {
    char plaintext[100], ciphertext[100], decryptedText[100];
    int a, b;

    printf("Enter the value of a (must be coprime with 26): ");
    scanf("%d", &a);
    if (gcd(a, 26) != 1) {
        printf("Invalid value of a. It must be coprime with 26.\n");
        return 1;
    }

    printf("Enter the value of b: ");
    scanf("%d", &b);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]%*c", plaintext); 

    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = encryptChar(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedText[i] = decryptChar(ciphertext[i], a, b);
    }
    decryptedText[strlen(ciphertext)] = '\0';

    printf("Encrypted text: %s\n", ciphertext);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}

