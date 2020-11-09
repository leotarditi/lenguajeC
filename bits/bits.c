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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return (~(~x & ~y)) & (~(x & y));
}
//2
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  //En complemento a dos, la negación es solo una negación bit a bit más uno por definición.
  
  return (~(x) + 1);
}
/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    
  int a = 0xFF; // Un byte de unos, se usará para copiar bytes individuales.
 
  /* 
   *  << 3 es lo mismo que multiplicar por 2^3 = 8
   *  nShift y mShift contiene el numero de bit necesarios para el cambio
  */
  int nShift = n << 3; 
  int mShift = m << 3;

  // Cambie al byte deseado en x, & con x.
  int nByte = (a << nShift) & x;
  int mByte = (a << mShift) & x;
  int combo = (a << nShift) | (a << mShift); // 1 en los bytes de intercambio.

  // Desplazo los bytes de intercambio de nuevo a la izquierda.
  nByte = (nByte >> nShift) & a;
  mByte = (mByte >> mShift) & a;
  // Cambio los bytes de intercambio a su nueva posición.
  nByte = nByte << mShift;
  mByte = mByte << nShift;
  // Almaceno la parte que no cambia de el int (x) en "combo".
  combo = ~combo & x;
   
  return (combo | mByte | nByte); // Combine las tres partes.
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // Construyo la mascara: 0xAAAAAAAA
  int mask = (0xAA << 8) + 0xAA;
  mask = (mask << 16) + mask;

  return (!((x & mask) ^ mask));
}
//3
/*
 * bitMask - Generate a mask consisting of all 1's
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
   /*
  * Creo una máscara de unos debajo del bit mas bajo y una máscara de unos por arriba del bit mas alto.
  * Estos dos se combinan usando el operador 'or' y 
  * se niegan para que solo los ceros entre las dos máscaras se conviertan en unos.
  */
  
  int MSB = ~(1 << 31); // Yields 0x7fffffff
  int LSB = ~1; // Yileds 0xfffffffe
 
  int lowMask = (MSB) >> (31 + (~lowbit + 1));
  int highMask = (LSB) << highbit;
  
  return (~(highMask | lowMask));
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  
  x = !!x; // Pongo x en 0 o 1.
  x = ~x + 1; // x es ahora todos 1s o todos 0s.

  return ((x & y) | (~x & z)); 
}
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int sign = 1 << 31;
  int upperBound = ~(sign | 0x39); // Si lo agregado es mayor a 0x39, el resultado es negativo.
  int lowerBound = ~0x30; // Cuando lo agregado es menos a 0x30, el resultado es negativo.

  // Ahora agrego x y chequeo el bit de signo de cada uno
  upperBound = sign & (upperBound+x) >> 31;
  lowerBound = sign & (lowerBound+1+x) >> 31; 
  
  // Si cualquiera de los resultados es negativo, no está en el rango deseado.
  return (!(upperBound | lowerBound));
}
//4
/*
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int isNonZero(int x) {
  /*
  * Usando los métodos de arriba y abajo, reimplementamos y simplemente afirmamos que 
  * si cualquiera devuelve verdadero, entonces esta función debe devolver falso.
  */

  int isNegative = ((x >> 31) & 0x00000001);

  int isPositive = (((x + ~0) >> 31) & 0x00000001) ^ 1;

  return (isNegative | isPositive);
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
  /*
  * La comprensión de este proceso depende del principio de que la negación aritmética de cero es cero
  * en el complemento a dos. Lo que se quiere decir con esto es que si la operación (~x + 1) se usa en 
  * cualquier número normal, resultará en que ese número sea negativo. En el caso de cero, no termina como negativo,
  * sino como cero de nuevo. Con esta noción, podemos encontrar la negación de cualquier número, y hay una garantía de que
  * para todos estos pares, uno de los dos números es negativo, y por lo tanto tiene su bit más significativo como un 1.
  * Usando el operador | en los miembros del par, el resultado siempre tendrá su bit más significativo como un 1 también. 
  * Entonces podemos cambiar esto al bit menos significativo, negarlo y devolverlo como resultado. En el caso de cero, 
  * el par es cero y cero como dijimos antes, en lugar de un número positivo y negativo, y el resultado de (0 | 0) es cero.
  * También será desplazado y negado, y dará el valor de retorno opuesto.
  */

  x = x | (~x + 1);
  x = ~(x >> 31);
  x &= 1;
  return x;
}
//float
/*
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
  
  int nanCheck = 0x000000FF << 23; // 1 esta en los 8 bits exp.
  int frac = 0x7FFFFF & uf; // Contiene solo el valor de la fracción.

  // Devuelve el argumento si los bits exp son todos de 1 y frac no es cero
  if((nanCheck & uf) == nanCheck && frac) {
    return uf;
  }

  // De lo contrario, sólo hay que dar vuelta el bit de signo.
  return (uf ^ (1 << 31));
}
/*
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  
  /*
  * El primer paso es cambiar el bit de signo, luego verifique si la entrada es NaN. 
  * Si es así, solo devuelve ese mismo número. Si no es así, devuelve el resultado.
  */
  unsigned t = uf & 0x7fffffff;

  // Si es NaN
  if (t > 0x7f800000) {
    return uf;
  }

  
  return t;
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
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  /*
  * Considero 4 condiciones:
  *   Demasiado pequeño para ser representado como desnormalizado
  *   Desnormalizado
  *   Normalizado
  *   Demasiado grande
  * Tengo 1 bit para signo, 8 bits para exp y 23 bits para frac en un solo número de precisión, puedo calcular el rango de esas 4 condiciones.
  *    En la representación normalizada, el valor máximo para el campo exp es 254 (ya que no podemos tener todos) entonces el exponente máximo 
  *    debe ser (254 - Bias = 254 - 127 = 127). El valor mínimo para el campo exp es 1 (no podemos tener todos los ceros también), entonces el 
  *    valor mínimo del exponente debe ser (1 - Bias = 1 - 127 = -126).
  *    En la representación desnormalizada, el campo exp es siempre 0 (dando un exponente de -126) y las potencias de dos están representados 
  *    por el campo frac. El valor mínimo en nuestro caso es (2 ^ -150) mientras que el valor máximo es (2 ^ -127).
  *    Por lo tanto, todo con un exponente menor que -150 debe considerarse como 0, y todo con un exponente mayor que 127 debe ser + INF.
  *    Después de conocer el rango de cada representación, podemos configurar una declaración condicional y componer el resultado.
  *    Las potencias de 2 en la representación desnormalizada se calculan manipulando los bits en el campo frac. Por lo tanto, simplemente 
  *    podemos cambiar el 1 en el campo frac por la cantidad correcta para obtener el resultado.
  *    Para la representación normalizada, cambiamos el valor del campo exp para obtener una potencia de 2, pero ademas desplazo todo el 
  *    campo exp a la posición correcta (23 a la izquierda). Dejo el campo frac vacío para que se interprete como 1.0.
  * Ademas quiero agregar que si no utilizo la condicion del desnormalizado tambien funciona y cumple con lo pedido pero decidi usarlo para
  *    poder demostras todos los casos que pueden suceder.
  */

  if(x >= -150 && x <= -127) {
    //denorm
    int shiftAmount = (-x - 127);
    int frac = 1 << shiftAmount;
    return frac;
  }
  if(x >= -126 && x <= 127) {
    //norm
    int e = (x + 127) << 23;
    return e;
  }
  if(x >= 128) {
    //inf
    int e = 0xFF << 23;
    return e;
  }
  return 0;
}
