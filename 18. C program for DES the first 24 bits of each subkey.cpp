#include <stdio.h>

void initialPermutation(unsigned long long *data);
void finalPermutation(unsigned long long *data);
unsigned long long expansionPermutation(unsigned long long data);
unsigned long long sBoxSubstitution(unsigned long long data);
unsigned long long permutationFunction(unsigned long long data);

unsigned long long generateSubkey(unsigned long long key, int round) {
    unsigned long long leftHalf = (key >> 28) & 0xFFFFFFFFF; 
    unsigned long long rightHalf = (key << (round * 2)) & 0xFFFFFFFFF; 

    switch (round) {
        case 1: rightHalf = (rightHalf << 1) | ((rightHalf >> 27) & 1); break;
        case 2: rightHalf = (rightHalf << 2) | ((rightHalf >> 26) & 3); break;
        default: break;
    }

    return (leftHalf << 24) | rightHalf; 
}

int main() {
    unsigned long long key = 0x123456789ABCDEF0; 

    for (int round = 1; round <= 16; round++) {
        unsigned long long subkey = generateSubkey(key, round);
        printf("Subkey %d: %016llX\n", round, subkey);
    }

    return 0;
}

