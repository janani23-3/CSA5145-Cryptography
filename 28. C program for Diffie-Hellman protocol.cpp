#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long int mod_exp(long long int base, long long int exp, long long int mod) {
    long long int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long int q = 23;   
    long long int a = 5;    

    long long int x = 4;    

    long long int y = 3;   

    long long int A = mod_exp(a, x, q); 
    long long int B = mod_exp(a, y, q); 

    long long int shared_secret_Alice = mod_exp(B, x, q); 
    long long int shared_secret_Bob = mod_exp(A, y, q);   

    printf("Alice's shared secret: %lld\n", shared_secret_Alice);
    printf("Bob's shared secret: %lld\n", shared_secret_Bob);

    return 0;
}

