#include <stdint.h>
#include <stdbool.h>

extern int __VERIFIER_nondet_int(void);

int32_t soma_segura(int32_t a, int32_t b, bool* teve_overflow) {
    *teve_overflow = false;
    int32_t sinal_a = (a >> 31) & 1;
    int32_t sinal_b = (b >> 31) & 1;
    int32_t resultado = a + b;
    int32_t sinal_resultado = (resultado >> 31) & 1;
    if (sinal_a == sinal_b && sinal_a != sinal_resultado) {
        *teve_overflow = true;
    }
    return resultado;
}

int main() {
    int32_t a = __VERIFIER_nondet_int();
    int32_t b = __VERIFIER_nondet_int();
    bool overflow;
    int32_t r = soma_segura(a, b, &overflow);
    return 0;
}
