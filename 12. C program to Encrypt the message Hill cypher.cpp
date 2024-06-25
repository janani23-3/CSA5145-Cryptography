#include <stdio.h>
#include <string.h>
#include <ctype.h>

void hill_encrypt(char *message, int key[2][2]) {
    int len = strlen(message);
    int i, j;
    int messageVector[2]; 
    int encryptedVector[2];

    int k = 0;
    for (i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            message[k++] = toupper(message[i]);
        }
    }
    message[k] = '\0'; 
    len = k;

    if (len % 2 != 0) {
        message[len++] = 'X';
        message[len] = '\0';
    }

    for (i = 0; i < len; i += 2) {
        messageVector[0] = message[i] - 'A';
        messageVector[1] = message[i+1] - 'A';

        for (j = 0; j < 2; j++) {
            encryptedVector[j] = key[j][0] * messageVector[0] + key[j][1] * messageVector[1];
            encryptedVector[j] %= 26; 
            if (encryptedVector[j] < 0) {
                encryptedVector[j] += 26; 
            }
        }

        printf("%c%c", encryptedVector[0] + 'A', encryptedVector[1] + 'A');
    }
    printf("\n");
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight oclock";
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    printf("Original message:\n%s\n", message);
    printf("Encrypted message:\n");
    hill_encrypt(message, key);

    return 0;
}

