#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 10
#define ROUND_KEYS 2
#define NUM_ROUNDS 2

const int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};

const int IP_INV[] = {4, 1, 3, 5, 7, 2, 8, 6};

const int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};

const int P4[] = {2, 4, 3, 1};

const int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

const int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

const int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
const int LS1[] = {1, 2, 3, 4, 0, 6, 7, 8, 9, 5};
const int LS2[] = {2, 3, 4, 0, 1, 7, 8, 9, 5, 6};

void initial_permutation(uint8_t *block) {
    uint8_t temp[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        temp[i] = block[IP[i] - 1];
    }
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        block[i] = temp[i];
    }
}

void final_permutation(uint8_t *block) {
    uint8_t temp[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        temp[i] = block[IP_INV[i] - 1];
    }
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        block[i] = temp[i];
    }
}

void expansion_permutation(uint8_t *block, uint8_t *expanded) {
    for (int i = 0; i < 8; ++i) {
        expanded[i] = block[EP[i] - 1];
    }
}

void permutation_p4(uint8_t *block) {
    uint8_t temp[4];
    for (int i = 0; i < 4; ++i) {
        temp[i] = block[P4[i] - 1];
    }
    for (int i = 0; i < 4; ++i) {
        block[i] = temp[i];
    }
}

void sbox_substitution(uint8_t *block, const int sbox[4][4]) {
    int row = (block[0] << 1) | block[3];
    int col = (block[1] << 1) | block[2];
    int val = sbox[row][col];
    block[0] = (val >> 1) & 0x01;
    block[1] = val & 0x01;
}

void generate_round_keys(uint8_t *key, uint8_t round_keys[ROUND_KEYS][6]) {
    uint8_t temp[10];
    for (int i = 0; i < 10; ++i) {
        temp[i] = key[P10[i] - 1];
    }
    uint8_t left[5], right[5];
    for (int i = 0; i < 5; ++i) {
        left[i] = temp[i];
        right[i] = temp[i + 5];
    }
    for (int round = 0; round < ROUND_KEYS; ++round) {
        uint8_t temp_left = left[0];
        uint8_t temp_right = right[0];
        for (int i = 0; i < 4; ++i) {
            left[i] = left[i + 1];
            right[i] = right[i + 1];
        }
        left[4] = temp_left;
        right[4] = temp_right;
        for (int i = 0; i < 5; ++i) {
            temp[i] = left[i];
            temp[i + 5] = right[i];
        }
        for (int i = 0; i < 8; ++i) {
            round_keys[round][i] = temp[LS2[i] - 1];
        }
    }
}

void feistel(uint8_t *block, uint8_t *subkey) {
    uint8_t expanded[8];
    expansion_permutation(block, expanded);
    for (int i = 0; i < 8; ++i) {
        expanded[i] ^= subkey[i];
    }
    uint8_t left[4], right[4];
    for (int i = 0; i < 4; ++i) {
        left[i] = expanded[i];
        right[i] = expanded[i + 4];
    }
    sbox_substitution(left, S0);
    sbox_substitution(right, S1);
    for (int i = 0; i < 4; ++i) {
        expanded[i] = left[i];
        expanded[i + 4] = right[i];
    }
    permutation_p4(expanded);
    for (int i = 0; i < 4; ++i) {
        block[i] ^= expanded[i];
    }
}

void encrypt(uint8_t *block, uint8_t *key) {
    uint8_t round_keys[ROUND_KEYS][6];
    generate_round_keys(key, round_keys);
    initial_permutation(block);
    for (int round = 0; round < NUM_ROUNDS; ++round) {
        feistel(block, round_keys[round]);
    }
    uint8_t temp;
    for (int i = 0; i < 4; ++i) {
        temp = block[i];
        block[i] = block[i + 4];
        block[i + 4] = temp;
    }
    final_permutation(block);
}

void decrypt(uint8_t *block, uint8_t *key) {
    uint8_t round_keys[ROUND_KEYS][6];
    generate_round_keys(key, round_keys);
    initial_permutation(block);
    uint8_t temp_key[6];
    for (int i = 0; i < 6; ++i) {
        temp_key[i] = round_keys[1][i];
    }
    for (int i = 0; i < 6; ++i) {
        round_keys[1][i] = round_keys[0][i];
    }
    for (int i = 0; i < 6; ++i) {
        round_keys[0][i] = temp_key[i];
    }
    for (int round = 0; round < NUM_ROUNDS; ++round) {
        feistel(block, round_keys[round]);
    }
    uint8_t temp;
    for (int i = 0; i < 4; ++i) {
        temp = block[i];
        block[i] = block[i + 4];
        block[i + 4] = temp;
    }
    final_permutation(block);
}

void binary_string_to_array(const char *binary_string, uint8_t *array) {
    for (int i = 0; i < 8; ++i) {
        array[i] = binary_string[i] - '0';
    }
}

void array_to_binary_string(uint8_t *array, char *binary_string) {
    for (int i = 0; i < 8; ++i) {
        binary_string[i] = array[i] + '0';
    }
    binary_string[8] = '\0';
}

int main() {
    uint8_t plaintext[BLOCK_SIZE];
    uint8_t key[KEY_SIZE];

    const char *plaintext_binary = "000000010000001000000100";
    binary_string_to_array(plaintext_binary, plaintext);

    const char *key_binary = "0111111101";
    binary_string_to_array(key_binary, key);

    printf("Encrypting...\n");
    encrypt(plaintext, key);

    char encrypted_binary[BLOCK_SIZE + 1];
    array_to_binary_string(plaintext, encrypted_binary);
    printf("Encrypted binary: %s\n", encrypted_binary);

    printf("Decrypting...\n");
    decrypt(plaintext, key);

    char decrypted_binary[BLOCK_SIZE + 1];
    array_to_binary_string(plaintext, decrypted_binary);
    printf("Decrypted binary: %s\n", decrypted_binary);

    return 0;
}

