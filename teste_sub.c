#include <stdint.h>
extern int __VERIFIER_nondet_int(void);
int32_t sub(int32_t c, int32_t d) { return c - d; }
int main() {
    int32_t c = __VERIFIER_nondet_int();
    int32_t d = __VERIFIER_nondet_int();
    int32_t r = sub(c, d);
    return 0;
}
