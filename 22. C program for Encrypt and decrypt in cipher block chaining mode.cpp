#include <stdio.h>
#include <stdint.h>

uint8_t IP(uint8_t input);
uint8_t IP_inv(uint8_t input);
uint8_t F(uint8_t r, uint8_t sk);
uint8_t sdes_encrypt(uint8_t plaintext, uint8_t sk1, uint8_t sk2);
uint8_t sdes_decrypt(uint8_t ciphertext, uint8_t sk1, uint8_t sk2);
void key_schedule(uint8_t key, uint8_t* sk1, uint8_t* sk2);

void cbc_encrypt(uint8_t* plaintext, uint8_t* ciphertext, uint8_t key, uint8_t iv, size_t length);
void cbc_decrypt(uint8_t* ciphertext, uint8_t* plaintext, uint8_t key, uint8_t iv, size_t length);

int main() {
    uint8_t key = 0x7D;  
    uint8_t iv = 0xAA;  

    uint8_t plaintext[2] = {0x01, 0x23};  
    uint8_t ciphertext[2];
    uint8_t decryptedtext[2];

    cbc_encrypt(plaintext, ciphertext, key, iv, 2);
    cbc_decrypt(ciphertext, decryptedtext, key, iv, 2);

    printf("Plaintext: 0000 0001 0010 0011\n");
    printf("Ciphertext: ");
    for (int i = 0; i < 2; ++i) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\nDecrypted text: ");
    for (int i = 0; i < 2; ++i) {
        printf("%02X ", decryptedtext[i]);
    }
    printf("\n");

    return 0;
}

uint8_t IP(uint8_t input) {
    uint8_t output = 0;
    output |= ((input >> 1) & 0x01) << 7;
    output |= ((input >> 5) & 0x01) << 6;
    output |= ((input >> 2) & 0x01) << 5;
    output |= ((input >> 0) & 0x01) << 4;
    output |= ((input >> 3) & 0x01) << 3;
    output |= ((input >> 7) & 0x01) << 2;
    output |= ((input >> 4) & 0x01) << 1;
    output |= ((input >> 6) & 0x01) << 0;
    return output;
}

uint8_t IP_inv(uint8_t input) {
    uint8_t output = 0;
    output |= ((input >> 7) & 0x01) << 1;
    output |= ((input >> 6) & 0x01) << 5;
    output |= ((input >> 5) & 0x01) << 2;
    output |= ((input >> 4) & 0x01) << 0;
    output |= ((input >> 3) & 0x01) << 3;
    output |= ((input >> 2) & 0x01) << 7;
    output |= ((input >> 1) & 0x01) << 4;
    output |= ((input >> 0) & 0x01) << 6;
    return output;
}

uint8_t F(uint8_t r, uint8_t sk) {
    uint8_t e_p = 0;
    e_p |= ((r >> 0) & 0x01) << 7;
    e_p |= ((r >> 1) & 0x01) << 6;
    e_p |= ((r >> 3) & 0x01) << 5;
    e_p |= ((r >> 2) & 0x01) << 4;
    e_p |= ((r >> 3) & 0x01) << 3;
    e_p |= ((r >> 2) & 0x01) << 2;
    e_p |= ((r >> 0) & 0x01) << 1;
    e_p |= ((r >> 1) & 0x01) << 0;
    e_p ^= sk;

    uint8_t s0[4][4] = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };
    uint8_t s1[4][4] = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    };

    uint8_t row0 = ((e_p >> 7) & 0x01) << 1 | ((e_p >> 4) & 0x01);
    uint8_t col0 = ((e_p >> 6) & 0x01) << 1 | ((e_p >> 5) & 0x01);
    uint8_t s0_val = s0[row0][col0];

    uint8_t row1 = ((e_p >> 3) & 0x01) << 1 | ((e_p >> 0) & 0x01);
    uint8_t col1 = ((e_p >> 2) & 0x01) << 1 | ((e_p >> 1) & 0x01);
    uint8_t s1_val = s1[row1][col1];

    uint8_t p4 = 0;
    p4 |= ((s0_val >> 1) & 0x01) << 3;
    p4 |= ((s1_val >> 1) & 0x01) << 2;
    p4 |= ((s1_val >> 0) & 0x01) << 1;
    p4 |= ((s0_val >> 0) & 0x01) << 0;

    return p4;
}

uint8_t sdes_encrypt(uint8_t plaintext, uint8_t sk1, uint8_t sk2) {
    uint8_t ip = IP(plaintext);

    uint8_t l = (ip >> 4) & 0x0F;
    uint8_t r = ip & 0x0F;

    uint8_t f_output = F(r, sk1);
    uint8_t l_next = r;
    uint8_t r_next = l ^ f_output;

    l = l_next;
    r = r_next;

    f_output = F(r, sk2);
    l_next = r;
    r_next = l ^ f_output;

    uint8_t pre_output = (r_next << 4) | l_next;

    uint8_t ciphertext = IP_inv(pre_output);
    return ciphertext;
}

uint8_t sdes_decrypt(uint8_t ciphertext, uint8_t sk1, uint8_t sk2) {
    uint8_t ip = IP(ciphertext);

    uint8_t l = (ip >> 4) & 0x0F;
    uint8_t r = ip & 0x0F;

    uint8_t f_output = F(r, sk2);
    uint8_t l_next = r;
    uint8_t r_next = l ^ f_output;

    l = l_next;
    r = r_next;

    f_output = F(r, sk1);
    l_next = r;
    r_next = l ^ f_output;

    uint8_t pre_output = (r_next << 4) | l_next;

    uint8_t plaintext = IP_inv(pre_output);
    return plaintext;
}

void key_schedule(uint8_t key, uint8_t* sk1, uint8_t* sk2) {
    uint8_t p10 = 0;
    p10 |= ((key >> 4) & 0x01) << 9;
    p10 |= ((key >> 7) & 0x01) << 8;
    p10 |= ((key >> 2) & 0x01) << 7;
    p10 |= ((key >> 6) & 0x01) << 6;
    p10 |= ((key >> 3) & 0x01) << 5;
    p10 |= ((key >> 9) & 0x01) << 4;
    p10 |= ((key >> 0) & 0x01) << 3;
    p10 |= ((key >> 8) & 0x01) << 2;
    p10 |= ((key >> 1) & 0x01) << 1;
    p10 |= ((key >> 5) & 0x01) << 0;

    uint8_t ls1 = ((p10 << 1) & 0x3E0) | ((p10 >> 4) & 0x01F);

    *sk1 = 0;
    *sk1 |= ((ls1 >> 0) & 0x01) << 7;
    *sk1 |= ((ls1 >> 2) & 0x01) << 6;
    *sk1 |= ((ls1 >> 1) & 0x01) << 5;
    *sk1 |= ((ls1 >> 3) & 0x01) << 4;
    *sk1 |= ((ls1 >> 4) & 0x01) << 3;
    *sk1 |= ((ls1 >> 9) & 0x01) << 2;
    *sk1 |= ((ls1 >> 6) & 0x01) << 1;
    *sk1 |= ((ls1 >> 8) & 0x01) << 0;

    uint8_t ls2 = ((ls1 << 2) & 0x3E0) | ((ls1 >> 3) & 0x01F);

    *sk2 = 0;
    *sk2 |= ((ls2 >> 0) & 0x01) << 7;
    *sk2 |= ((ls2 >> 2) & 0x01) << 6;
    *sk2 |= ((ls2 >> 1) & 0x01) << 5;
    *sk2 |= ((ls2 >> 3) & 0x01) << 4;
    *sk2 |= ((ls2 >> 4) & 0x01) << 3;
    *sk2 |= ((ls2 >> 9) & 0x01) << 2;
    *sk2 |= ((ls2 >> 6) & 0x01) << 1;
    *sk2 |= ((ls2 >> 8) & 0x01) << 0;
}

void cbc_encrypt(uint8_t* plaintext, uint8_t* ciphertext, uint8_t key, uint8_t iv, size_t length) {
    uint8_t sk1, sk2;
    key_schedule(key, &sk1, &sk2);

    uint8_t prev_block = iv;
    for (size_t i = 0; i < length; ++i) {
        uint8_t input_block = plaintext[i] ^ prev_block;
        ciphertext[i] = sdes_encrypt(input_block, sk1, sk2);
        prev_block = ciphertext[i];
    }
}

void cbc_decrypt(uint8_t* ciphertext, uint8_t* plaintext, uint8_t key, uint8_t iv, size_t length) {
    uint8_t sk1, sk2;
    key_schedule(key, &sk1, &sk2);

    uint8_t prev_block = iv;
    for (size_t i = 0; i < length; ++i) {
        uint8_t decrypted_block = sdes_decrypt(ciphertext[i], sk1, sk2);
        plaintext[i] = decrypted_block ^ prev_block;
        prev_block = ciphertext[i];
    }
}

