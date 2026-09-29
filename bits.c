/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    /* Zero is a separate sign category. */
    if (!x)
        return !y;
    if (!y)
        return 0;
    return !((x ^ y) >> 31);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    /* Locate the highest set bit in blocks of 16, 8, 4, 2, 1. */
    int step = (v > 0xFFFF) << 4;
    int result = step;
    v = v >> step;
    step = (v > 0xFF) << 3;
    result = result | step;
    v = v >> step;
    step = (v > 0xF) << 2;
    result = result | step;
    v = v >> step;
    step = (v > 3) << 1;
    result = result | step;
    v = v >> step;
    return result | (v > 1);
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    /* XOR exactly the bits that differ in the selected bytes. */
    int ns = n << 3;
    int ms = m << 3;
    int delta = ((x >> ns) ^ (x >> ms)) & 0xFF;
    /* Unsigned byte masks make shifts into bit 31 well-defined. */
    return x ^ ((delta & 0xFFu) << ns) ^ ((delta & 0xFFu) << ms);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    /* Swap neighboring groups, doubling the group width each time. */
    v = ((v >> 1) & 0x55555555u) | ((v & 0x55555555u) << 1);
    v = ((v >> 2) & 0x33333333u) | ((v & 0x33333333u) << 2);
    v = ((v >> 4) & 0x0F0F0F0Fu) | ((v & 0x0F0F0F0Fu) << 4);
    v = ((v >> 8) & 0x00FF00FFu) | ((v & 0x00FF00FFu) << 8);
    return (v >> 16) | (v << 16);
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    /* n == 0 selects all bits; otherwise keep the lowest 32 - n. */
    int isZero = !n;
    int mask = (~isZero + 1) | (0x7FFFFFFF >> ((n + 31) & 31));
    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    /* Count leading zeros of ~x via the highest nonzero bit. */
    int v = ~x;
    int allOnes = !v;
    int step = (!!(v >> 16)) << 4;
    int highest = step;
    v = v >> step;
    step = (!!(v >> 8)) << 3;
    highest = highest | step;
    v = v >> step;
    step = (!!(v >> 4)) << 2;
    highest = highest | step;
    v = v >> step;
    step = (!!(v >> 2)) << 1;
    highest = highest | step;
    v = v >> step;
    highest = highest | (!!(v >> 1));
    return (31 ^ highest) + allOnes;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = 0;
    unsigned magnitude;
    unsigned significand;
    unsigned remainder;
    int exponent = 158;

    if (!x)
        return 0;
    if (x < 0) {
        sign = 0x80000000u;
        /* ~x is nonnegative, including for INT_MIN. */
        magnitude = ~x;
        magnitude = magnitude + 1u;
    } else {
        magnitude = x;
    }
    while (!(magnitude & 0x80000000u)) {
        magnitude = magnitude << 1;
        exponent = exponent - 1;
    }
    significand = magnitude >> 8;
    remainder = magnitude & 0xFFu;
    /* Round to nearest, with exact ties rounded to an even result. */
    if (remainder > 0x80u)
        significand = significand + 1u;
    else if (remainder == 0x80u)
        significand = significand + (significand & 1u);
    /* The hidden leading one also carries into the exponent. */
    return sign | (((exponent - 1) << 23) + significand);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000u;
    unsigned exponent = (uf >> 23) & 0xFFu;
    unsigned fraction = uf & 0x7FFFFFu;
    if (exponent == 0xFFu)
        return uf;
    if (!exponent)
        return sign | (fraction << 1);
    exponent = exponent + 1u;
    if (exponent == 0xFFu)
        return sign | 0x7F800000u;
    return sign | (exponent << 23) | fraction;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int exponent = (uf2 >> 20) & 0x7FFu;
    int sign = uf2 >> 31;
    unsigned high = (uf2 & 0xFFFFFu) | 0x100000u;
    unsigned magnitude;
    int value;
    exponent = exponent - 1023;
    if (exponent < 0)
        return 0;
    /* INT_MIN and the required overflow marker have identical bits. */
    if (exponent > 30)
        return ~0x7FFFFFFF;
    if (exponent <= 20)
        magnitude = high >> (20 - exponent);
    else
        magnitude = (high << (exponent - 20)) | (uf1 >> (52 - exponent));
    /* Here magnitude <= INT_MAX, so this assignment is exact. */
    value = magnitude;
    if (sign)
        return -value;
    return value;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149)
        return 0;
    if (x < -126)
        return 1u << (x + 149);
    if (x > 127)
        return 0x7F800000u;
    return (x + 127) << 23;
}
