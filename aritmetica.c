#include <stdint.h>
#include <stdbool.h>

// Macro para exportar a função para o WebAssembly
#define WASM_EXPORT __attribute__((visibility("default")))
#define MAX_INT32 2147483647

// Soma básica (vulnerável a overflow)
WASM_EXPORT int32_t soma(int32_t a, int32_t b) {
    return a + b;
    }

// TODO: Implementar detecção lógica de overflow (como o MIPS faria!)
// Retorna o resultado. Se houver overflow, *teve_overflow = true.
WASM_EXPORT int32_t soma_segura(int32_t a, int32_t b, bool* teve_overflow) {
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

// TODO: Implementar 'sub' e 'sub_segura'
WASM_EXPORT int32_t sub(int32_t c, int32_t d) {
    return c - d;
}
WASM_EXPORT int32_t sub_segura(int32_t c, int32_t d, bool* teve_overflow) {
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

// TODO: Implementar 'mul' e 'mul_segura'
WASM_EXPORT int32_t mul(int32_t e, int32_t f) {
    return e * f;
}

WASM_EXPORT int32_t mul_segura(int32_t e, int32_t f, bool* teve_overflow) {
    *teve_overflow = false;
    int32_t resultado = e * f;

        if (e == INT32_MIN && f == -1) {
            *teve_overflow = true;
        } else
        if (f != 0 && resultado / f != e) {
            *teve_overflow = true;
        }

        return resultado;
    }
