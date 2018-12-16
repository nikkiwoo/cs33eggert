/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "return" statement in each function with one
or more lines of C code that implements the function. Your code
must conform to the following style:

int Funct(arg1, arg2, ...) {
    /* brief description of how your implementation works */
    int var1 = Expr1;
    ...
    int varM = ExprM;
    
    varJ = ExprJ;
    ...
    varN = ExprN;
    return ExprR;
}

Each "Expr" is an expression using ONLY the following:
1. Integer constants 0 through 255 (0xFF), inclusive. You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables (no global variables).
3. Unary integer operations ! ~
4. Binary integer operations & ^ | + << >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators. You are not restricted to
one operator per line.

You are expressly forbidden to:
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, ||, -, or ?:
6. Use any form of casting.
7. Use any data type other than int.  This implies that you
cannot use arrays, structs, or unions.


You may assume that your machine:
1. Uses 2s complement, 32-bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
/*
 * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
 */
int pow2plus1(int x) {
    /* exploit ability of shifts to compute powers of 2 */
    return (1 << x) + 1;
}

/*
 * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
 */
int pow2plus4(int x) {
    /* exploit ability of shifts to compute powers of 2 */
    int result = (1 << x);
    result += 4;
    return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
1. Define or use any macros.
2. Define any additional functions in this file.
3. Call any functions.
4. Use any form of casting.
5. Use any data type other than int or unsigned.  This means that you
cannot use arrays, structs, or unions.
6. Use any floating point data types, operations, or constants.


NOTES:
1. Use the dlc (data lab checker) compiler (described in the handout) to
check the legality of your solutions.
2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
that you are allowed to use for your implementation of the function.
The max operator count is checked by dlc. Note that '=' is not
counted; you may use as many of these as you want without penalty.
3. Use the btest test harness to check your functions for correctness.
4. Use the BDD checker to formally verify your functions
5. The maximum number of ops for each function is given in the
header comment for each function. If there are any inconsistencies
between the maximum ops in the writeup and in this file, consider
this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
    // number of ops = 6
    
    // only 0 will have the first bit of itself and its negative as 0
    int comp = x | (~x + 1);
    int same = ~(comp >> 31);
    return (same & 1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    //split 32 bit integer into 4 8-bit parts --> create a mask with a 1 as the
    //rightmost value of each part
    //shift the mask to the left 8 times to add together the bits
    //add the values of all 4 parts together to find total number of ones
    int halfmask = 1 | (1 << 8);
    int mask = halfmask | (halfmask << 16);
    int bits = x & mask;
    int sum = 0;
    bits = bits + ((x >> 1) & mask);
    bits = bits + ((x >> 2) & mask);
    bits = bits + ((x >> 3) & mask);
    bits = bits + ((x >> 4) & mask);
    bits = bits + ((x >> 5) & mask);
    bits = bits + ((x >> 6) & mask);
    bits = bits + ((x >> 7) & mask);
    sum = (bits & 255) + ((bits >> 8) & 255) + ((bits >> 16) & 255) + ((bits >> 24) & 255);
    return sum;
    
}
/*
 * bitOr - x|y using only ~ and &
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
    // number of ops = 4
    
    return (~(~x & ~y));
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
    // this method exploits the sum of a geometric series
    //test if n = 32
    int test32 = !(32 - n); //returns 1 if n = 32, 0 otherwise
    int n1 = n - test32;
    int div = (32 / n1);
    int mod = (32 % n1);
    int endmask = ((1 << n1) - 1);
    int end = x & endmask;
    int modmask = ((1 << mod) + (~0));
    int p = (modmask & end) << (div * n1);
    int p2 = end * (((1 << ((div - 1) * n1)) + (~0)) / ((1 << n1) + (~0)));
    int p3 = end * (1 << ((div - 1) * n1));
    return ((!test32)*(p + p2 + p3)) + ((test32)*x);
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                l5
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    // number of ops = 10
    
    int test = x >> (n + (~0));
    return ((!(~test)) | (!test) );
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    // number of ops = 6
    
    int s = n << 3; // multiply n by 8
    int newton = x >> s;   // shift number over 8*n times
    int comp = (1 << 8) + (~0); // 8 ones on right, 0's everywhere else
    return newton & comp;  // extract rightmost 8 bits from newton
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // number of ops = 20
    
    //operates on the basis that, if both y and x are positive, then if x <= y then y - x
    //should always be positive
    //if y is negative and x is positive, then y is definitely NOT greater than x
    //if x is negative and y is positive, then y is definitely greater than x
    
    int xfirst = x >> 31; // compute first bit of x
    int yfirst = y >> 31; // compute first bit of y
    int comp1 = xfirst & yfirst;  // compute if leftmost bit of both is one (if both are negative)
    // produces -1 if both are negative, 0000 if not
    int comp2 = (~xfirst) & (~yfirst); // compute if leftmost bit of both is zero (both positive)
    // produces -1 if both are negative, 0000 if not
    int same = !!(comp1) | !!(comp2); // produces 1 if either both positive or both negative
    int sum = y + (~x + 1); // essentially takes y - x
    int sumfront = sum >> 31; //should be 0 if y - x is positive
    int sumsign = !sumfront; // produces 1 if y - x is positive, 0 otherwise
    int test1 = (sumsign & same);
    //if test1 fails, then either x is negative and y is positive or x is positive and y is neg
    //in the case that x is neg and y is pos, test should still return 1
    //thus, test2 sees if y is pos
    int ytest2 = yfirst & 1;  //produces 1 if y is negative, 0 if y is positive
    int test2 = !ytest2;    //produces 1 if y is positive, 0 if y is negative
    int test22 = test2 & (!!xfirst); //1 if y is positive and x is negative
    return (test1 | test22);
    
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    // number of ops = 5
    
    //first, test if x is negative
    int neg = (x >> 31) & 1; // returns 1 if x is negative, 0 otherwise
    //then, test if x is 0
    int zero = !x;  //returns 1 if x is zero, 0 otherwise
    return !(neg | zero);
    //if one of the conditions above gives 1 as an answer, then return 0
    //if both conditions return 0, then the function returns 1
    
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
    // number of ops = 12
    
    //based off of hw1 answer
    /*int aritshift = x >> n; // produces arithmetic shift of x
    int wo = 32;    //indicates length of int
    //must account for case that n = 0
    //if so, make test variable equal to 1
    int test = !n;  //if 0, test becomes 1, if n is not zero, test = 0
    int w = wo + ((~test) + 1);
    //make a mask consisting of all 0's and then (32 - n) 1's at the left
    int mask = ((1 << (w + ((~n) + 1))) + (~0));
    return (mask & aritshift);*/
    
     int aritshift = x >> n; // produces arithmetic shift of x
     int wo = 31;    //1 less than length of int
     int mask1 = ((1 << (wo + ((~n) + 1))) + (~0));
     int mask2 = 1 << (31 + (~n) + 1);
    int mask = mask1 + mask2;
     return (mask & aritshift);
                
}
    /*
     * tmin - return minimum two's complement integer
     *   Legal ops: ! ~ & ^ | + << >>
     *   Max ops: 4
     *   Rating: 1
     */
                int tmin(void) {
                    // number of ops = 1
                    
                    return 1 << 31;
                }

