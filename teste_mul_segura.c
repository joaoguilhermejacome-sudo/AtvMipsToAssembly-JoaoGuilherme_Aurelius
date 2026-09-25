#include <stdint.h>
#include <stdbool.h>
extern int __VERIFIER_nondet_int(void);
int32_t mul_segura(int32_t e, int32_t f, bool* teve_overflow) {
    *teve_overflow = false;
    int32_t resultado = e * f;
    if (e == INT32_MIN && f == -1) {
        *teve_overflow = true;
    } else if (f != 0 && resultado / f != e) {
        *teve_overflow = true;
    }
    return resultado;
}
int main() {
    int32_t e = __VERIFIER_nondet_int();
    int32_t f = __VERIFIER_nondet_int();
    bool overflow;
    int32_t r = mul_segura(e, f, &overflow);
    return 0;
}
