/* 
 * CS:APP Data Lab 
 * 
 * < Name: Joshua Sadler ID: 101979465>
 * 
 */

/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
    /* Spread highest set bit, then isolate it. Special case for sign bit */
    int spread = x;
    spread |= spread >> 1;
    spread |= spread >> 2;
    spread |= spread >> 4;
    spread |= spread >> 8;
    spread |= spread >> 16;
    /* Candidate for non-sign-bit */
    int pos = spread & ~(spread >> 1);
    /* Sign bit mask */
    int highBit = 1 << 31;
    /* If x is negative, return sign bit; else return pos */
    return pos | (x & highBit);
}

/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
    int sum = x + y;
    int signX = x >> 31;
    int signY = y >> 31;
    int signS = sum >> 31;
    int posOverflow = ~signX & ~signY & signS;
    int negOverflow = signX & signY & ~signS;
    int tmax = ~(1 << 31);
    int tmin = 1 << 31;
    return (posOverflow & tmax) | (negOverflow & tmin) | (~(posOverflow | negOverflow) & sum);
}
}

/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
    int doubled = x << 1;
    int overflow = (doubled ^ x) >> 31;
    int tmax = ~(1 << 31);
    int tmin = 1 << 31;
    return (overflow & ((x >> 31) ^ tmax)) | (~overflow & doubled);
}

/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
    int mul2 = x << 1;
    int mul3 = mul2 + x;
    int overflow = ((mul2 ^ x) | (mul3 ^ x)) >> 31;
    int tmax = ~(1 << 31);
    int tmin = 1 << 31;
    return (overflow & ((x >> 31) ^ tmax)) | (~overflow & mul3);
}

/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp  = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF) {
        // NaN or infinity, just return
        return uf;
    } else if (exp == 0 || exp == 1) {
        // Denormalized or very small normalized
        frac |= (exp << 23); // add in the implicit 1 if exp==1
        // add rounding bias: if last two bits are 11, round up
        frac = (frac >> 1) + ((uf & 3) == 3);
        return sign | frac;
    } else {
        // Normalized, just decrement exponent
        exp = exp - 1;
        return sign | (exp << 23) | frac;
    }
}

/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x){
    int q = x >> 2;          // x / 4
    int r = x & 3;           // remainder (x % 4)
    int prod = (q << 1) + q; // q * 3
    int rem = (r << 1) + r;  // r * 3
    // Add bias before shifting remainder for negatives
    int bias = (x >> 31) & 3;
    return prod + ((rem + bias) >> 2);
}


/******************* Unsolved Puzzles *******************/

/*
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  return 2;
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  return 0;
}

/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x) {
  return 2;
}

/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}

/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x)
{
    return 2;
}
