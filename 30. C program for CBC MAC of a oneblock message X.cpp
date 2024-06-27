#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char key[16];
} AES_KEY;

void AES_set_encrypt_key(const unsigned char *userKey, const int bits, AES_KEY *key) {
    memcpy(key->key, userKey, 16);
}

void AES_encrypt(const unsigned char *in, unsigned char *out, const AES_KEY *key) {
    for (int i = 0; i < 16; ++i) {
        out[i] = in[i] ^ key->key[i];
    }
}

void cbc_mac(unsigned char *key, unsigned char *message, unsigned char *mac) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    
    unsigned char iv[16] = { 0 }; 
    unsigned char ciphertext[16];
    
    AES_encrypt(message, ciphertext, &aes_key);
    
    memcpy(mac, ciphertext, 16);
}

int main() {
    unsigned char key[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 
                              0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c }; // Example AES key
    unsigned char message[16] = "Hello, World!!!";  // Example message (one block)
    unsigned char mac[16];
    
    cbc_mac(key, message, mac);
    
    printf("MAC for message '%s':\n", message);
    for (int i = 0; i < 16; i++) {
        printf("%02x ", mac[i]);
    }
    printf("\n");
    
    unsigned char modified_message[32];
    memcpy(modified_message, message, 16); 
    for (int i = 0; i < 16; i++) {
        modified_message[16 + i] = message[i] ^ mac[i];  
    }
    
    unsigned char mac_modified[16];
    cbc_mac(key, modified_message, mac_modified);
    
    printf("MAC for modified message 'X || (X ? T)':\n");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", mac_modified[i]);
    }
    printf("\n");
    
    printf("Verification result: ");
    if (memcmp(mac_modified, mac, 16) == 0) {
        printf("MAC matches!\n");
    } else {
        printf("MAC does not match!\n");
    }
    
    return 0;
}

