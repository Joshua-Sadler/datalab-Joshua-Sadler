/*
 * CS:APP Data Lab 
 *
 * <Joshua Sadler, 101979465>
 *
 */

/*
 * copyLSB - set all bits of result to least significant bit of x.
 * - Shift LSB into sign bit, then arithmetic right shift
 *   spreads it across all 32 bits.
 */
int copyLSB(int x) {
    return (x << 31) >> 31;
}

/*
 * evenBits - return word with all even-numbered bits set to 1.
 * - Build mask by starting with 0x55 (01010101) and replicating it across 
 *   32 bits with shifts and ORs.
 */
int evenBits(void) {
    int mask = 0x55;
    mask = mask | (mask << 8);
    mask = mask | (mask << 16);
    return mask;
}

/*
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 * - A float’s sign is the top bit. Mask with 0x7FFFFFFF to clear it.
 * - Extract exponent (bits 30–23) and fraction (bits 22–0).
 * - If exponent = 0xFF and fraction ≠ 0, uf is NaN then return uf.
 * - Otherwise return uf with the sign bit cleared (the absolute value).
 */
unsigned float_abs(unsigned uf) {
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    return (exp == 0xFF && frac != 0) ? uf : (uf & 0x7FFFFFFF);
}

/*
 * isTmin - returns 1 if x is the minimum, two's complement number, and 
 *  0 Otherwise
 * - ~x + 1 computes -x.
 * - Since Tmin is the only nonzero value where x == -x.
 * - Use XOR to test if x  and -x are equal, then !!x to rule out 0, since 
 *   0 == -0.
 */
int isTmin(int x) {
    return !(x ^ (~x + 1)) & !!x;
}
