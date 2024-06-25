#include <stdio.h>
#include <math.h>

unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

int main() {
    unsigned long long total_possible_keys = factorial(25);
    printf("Total possible keys (ignoring redundancy): %llu\n", total_possible_keys);

    unsigned long long effective_unique_keys = (unsigned long long) pow(10, 14);
    printf("Effective unique keys (considering redundancy): %llu\n", effective_unique_keys);

    int power_of_2 = (int) (log2(effective_unique_keys));
    printf("Effective unique keys expressed as power of 2: 2^%d\n", power_of_2);

    return 0;
}

