#include <stdint.h>
#include <stdbool.h>
extern int __VERIFIER_nondet_int(void);
int32_t sub_segura(int32_t c, int32_t d, bool* teve_overflow) {
    *teve_overflow = false;
    int32_t sinal_c = (c >> 31) & 1;
    int32_t sinal_d = (d >> 31) & 1;
    int32_t resultado = c - d;
    int32_t sinal_resultado = (resultado >> 31) & 1;
    if (sinal_c != sinal_d && sinal_c != sinal_resultado) {
        *teve_overflow = true;
    }
    return resultado;
}
int main() {
    int32_t c = __VERIFIER_nondet_int();
    int32_t d = __VERIFIER_nondet_int();
    bool overflow;
    int32_t r = sub_segura(c, d, &overflow);
    return 0;
}
