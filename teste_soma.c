#include <stdint.h>

extern int __VERIFIER_nondet_int(void);

int32_t soma(int32_t a, int32_t b) {
    return a + b;
}

int main() {
    int32_t a = __VERIFIER_nondet_int();
    int32_t b = __VERIFIER_nondet_int();
    int32_t r = soma(a, b);
    return 0;
}
