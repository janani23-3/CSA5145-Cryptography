#include <stdio.h>
#include <stdint.h>

// Initial permutation table (IP)
const int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final permutation table (IP^-1)
const int IP_INV[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Expansion permutation table (E)
const int E[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// Permutation table (P)
const int P[] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// S-boxes (S1 to S8)
const int S[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    // Remaining S-boxes omitted for brevity
};

// Function prototypes
void des_decrypt(uint64_t ciphertext, uint64_t *plaintext, uint64_t subkeys[]);
void generate_subkeys(uint64_t key, uint64_t subkeys[]);
uint32_t f_function(uint32_t R, uint64_t key);

// Perform DES decryption
void des_decrypt(uint64_t ciphertext, uint64_t *plaintext, uint64_t subkeys[]) {
    uint64_t ip = 0, L = 0, R = 0;
    // Initial permutation (IP)
    for (int i = 0; i < 64; i++) {
        ip |= ((ciphertext >> (64 - IP[i])) & 1) << (63 - i);
    }
    L = ip >> 32;
    R = ip & 0xFFFFFFFF;

    // 16 rounds of DES
    for (int round = 15; round >= 0; round--) {
        uint32_t temp = R;
        R = L ^ f_function(R, subkeys[round]);
        L = temp;
    }

    // Final permutation (IP^-1)
    *plaintext = 0;
    uint64_t inv_ip = ((uint64_t)R << 32) | L;
    for (int i = 0; i < 64; i++) {
        *plaintext |= ((inv_ip >> (64 - IP_INV[i])) & 1) << (63 - i);
    }
}

// Function to generate 16 subkeys for decryption
void generate_subkeys(uint64_t key, uint64_t subkeys[]) {
    uint64_t C = 0, D = 0, CD = 0;
    // Permuted choice 1 (PC1) omitted for brevity

    // Generate 16 subkeys in reverse order
    for (int round = 0; round < 16; round++) {
        // Apply the key schedule
        if (round > 0 && (round == 1 || round == 8 || round == 15)) {
            C = ((C << 1) & 0xFFFFFFF) | ((C >> 27) & 1);
            D = ((D << 1) & 0xFFFFFFF) | ((D >> 27) & 1);
        } else {
            C = ((C << 2) & 0xFFFFFFF) | ((C >> 26) & 3);
            D = ((D << 2) & 0xFFFFFFF) | ((D >> 26) & 3);
        }
        CD = (C << 28) | D;

        // Permuted choice 2 (PC2) omitted for brevity
    }
}

// Function to compute the output of the f-function
uint32_t f_function(uint32_t R, uint64_t key) {
    // Expansion permutation (E) omitted for brevity

    // XOR with key omitted for brevity

    // S-box substitutions and straight permutation (P) omitted for brevity

    return 0; // Dummy return; actual implementation omitted for brevity
}

int main() {
    uint64_t key = 0x133457799BBCDFF1; // Example 64-bit key
    uint64_t ciphertext = 0x85E813540F0AB405; // Example 64-bit ciphertext
    uint64_t plaintext = 0;
    uint64_t subkeys[16];

    // Generate subkeys for decryption
    generate_subkeys(key, subkeys);

    // Perform decryption
    des_decrypt(ciphertext, &plaintext, subkeys);

    // Print the decrypted plaintext
    printf("Decrypted plaintext: 0x%llx\n", plaintext);

    return 0;
}

