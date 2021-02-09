/*
 * CS:APP Data Lab
 *
 * <Garipova Yana garip001>
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

//#include <stdio.h>

//if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

/*You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works
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

  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31

  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2
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


//#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    //De morgan's laws
    int p = (~x&y);
    int q = (x&~y);
    return ~(~p & ~q);
}
/*
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
// I chose # 85 because it has the same bit pattern
    int x = 85;
    int y;
    x = x<<8;
    x +=85;
    y = x<<16;
    y +=x;
    return y;
}
/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int leastBitPos(int x) {
    return x& ~(x+(~0));
}

/*
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
    int f = !(x^y);
    return f;
}
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
    // shift x on 32-n bites
    // compare original x and the shifted one. If they're equal, return 1
    // if x is neg, make it pos, subract 1  and compare with shifted x
//    int neg = (x>>31)&1; // 1 if x is negative
    int x1 = x<<(32-n);
    x1 = x1>>(32-n);
    int eq = !(x1^x);
    return eq ;

}

/*
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) {
    // 255 two bytes of 1s
    int mask = 255;
    int m1 = mask<<8;
    int m2 = mask<<16;
    return (x&mask)<<24|(x&m1)<<8|(x&m2)>>8 | ((x>>24)&mask);

}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    int smth = !(x>>31);       //if x is neg, smth is 0
    int notsmth = ~smth+1;
    return !((x+notsmth)>>31)&1;
}
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
    int neg = x >> 31; 			//if x is neg, it adds 7 to round towards 0
    int y = (x+x+x+x+x);
    y = (y + (7 & neg)) >> 3;
    return y;
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int diff_sgn = !(x>>31)^!(y>>31); 		//is 1 when signs are different
    int a = diff_sgn & (x>>31);			 //diff signs and x is neg, gives 1
    int b = !diff_sgn & !((y+(~x+1))>>31); 	//same signs and difference is pos or = 0, gives 1
    int f = a | b;
    return f;
}
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
    int stblzr = ~((x>>31)|((~x+1)>>31)); //returns -1 if x==0, 0 otherwhise
    stblzr = ~stblzr+1;
    int f = x+(~x+1)+ stblzr;
  return f;
}
/*
 * tc2sm - Convert from two's complement to sign-magnitude
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int tc2sm(int x) {
    int sign = (x>>31);       //returns -1 if x is negative
    int nx = ~x+1;               // if x is neg, nx is pos
    int y = (sign& nx) | ((~(!sign)+1) & x);   //if x is neg, y returns pos x; if x is pos, returns x
    int n = (sign<<31)+y;

  return n;
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
    x = ~x;
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    x = ~x;
    int y = (x & 1) + (x >> 1 & 1) + (x >> 2 & 1) + (x >> 3 & 1) + (x >> 4 & 1) +
           (x >> 5 & 1) + (x >> 6 & 1) + (x >> 7 & 1) + (x >> 8 & 1) + (x >> 9 & 1) +
           (x >> 10 & 1) + (x >> 11 & 1) + (x >> 12 & 1) + (x >> 13 & 1) + (x >> 14 & 1) +
           (x >> 15 & 1) + (x >> 16 & 1) + (x >> 17 & 1) + (x >> 18 & 1) + (x >> 19 & 1) +
           (x >> 20 & 1) + (x >> 21 & 1) + (x >> 22 & 1) + (x >> 23 & 1) + (x >> 24 & 1) +
           (x >> 25 & 1) + (x >> 26 & 1) + (x >> 27 & 1) + (x >> 28 & 1) + (x >> 29 & 1) +
           (x >> 30 & 1) + (x >> 31 & 1);
    return  y;
}

/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    unsigned int y;
    unsigned int k;
    unsigned int l;
    k = (uf<<9)!=0;
    l = ((uf<<1)>>24) == 255;
    if ((k&l)==1)
        y = uf;
    else
        y = uf+ (1<<31);
    return y;
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

//get s, get exp part, get fraction part, shift exp and fra by 1 and combine
    int s;
    unsigned int exp;
    unsigned int fra;
    unsigned int y;    //number we're getting

    int l = ((uf<<1)>>24);
    if (l==255)             //if nan/infinity returns uf; 1 if they all are 1s
       return y = uf;

    if ((uf<<1)==0)
       return uf;

    else
	s = (uf>>31)&1;
	exp = uf>>24;		//removed last one, 7 exp bits, 8 in total
	exp = exp<<24;        //positions exp part takes 8
	fra = (uf<<8);
	fra = fra>>8;      //makes 0's everywhere but the fraction part, 24 bits
	s = s<<31;            // positions sign in the beginning
	y = s|((exp+fra)>>1);
	return y;
}
