#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  
}

/void decryptAffineCipher(char* ciphertext, int a, int b) {
    int m = 26; 

    int a_inverse = modInverse(a, m);
    if (a_inverse == -1) {
        printf("Error: Invalid key 'a'. Modular inverse does not exist.\n");
        return;
    }

    printf("Decrypted message:\n");
    while (*ciphertext) {
        char c = *ciphertext;
        if (isalpha(c)) {
            int index = tolower(c) - 'a';
            int decrypted_index = (a_inverse * (index - b + m)) % m;
            if (decrypted_index < 0) {
                decrypted_index += m;  
            }
            char decrypted_char = decrypted_index + 'a';
            if (isupper(c)) {
                decrypted_char = toupper(decrypted_char);
            }
            printf("%c", decrypted_char);
        } else {
            printf("%c", c);  
        }
        ciphertext++;
    }
    printf("\n");
}

int main() {
    char ciphertext[] = "your ciphertext here";  

    char most_frequent = 'B';
    char second_most_frequent = 'U';

    int y1 = tolower(most_frequent) - 'a';
    int y2 = tolower(second_most_frequent) - 'a';

    int x1 = 'E' - 'A';  
    int x2 = 'T' - 'A';  
    
    int m = 26;  
    int a = (y1 - y2 + m) % m;  
    int a_inverse = modInverse(a, m);
    int b = (a_inverse * ((x1 - x2 + m) % m)) % m; 

    decryptAffineCipher(ciphertext, a, b);

    return 0;
}

