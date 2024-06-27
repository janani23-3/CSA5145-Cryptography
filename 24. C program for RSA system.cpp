#include <stdio.h>

int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int e, int phi) {
    int d = 0, x = 0, y = 1, lastx = 1, lasty = 0, temp;
    int original_phi = phi;

    while (phi != 0) {
        int quotient = e / phi;
        int remainder = e % phi;

        e = phi;
        phi = remainder;

        temp = x;
        x = lastx - quotient * x;
        lastx = temp;

        temp = y;
        y = lasty - quotient * y;
        lasty = temp;
    }

    d = lastx;

    if (d < 0) {
        d += original_phi;
    }

    return d;
}

int main() {
    int e = 31;
    int n = 3599;
    int p, q;
    int phi;
    int d;

    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    phi = (p - 1) * (q - 1);

    d = modInverse(e, phi);

    printf("Private key d = %d\n", d);

    return 0;
}

