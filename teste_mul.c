#include <stdint.h>
extern int __VERIFIER_nondet_int(void);
int32_t mul(int32_t e, int32_t f) { return e * f; }
int main() {
    int32_t e = __VERIFIER_nondet_int();
    int32_t f = __VERIFIER_nondet_int();
    int32_t r = mul(e, f);
    return 0;
}
