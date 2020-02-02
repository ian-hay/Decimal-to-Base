# Assignment One: Decimal to Base Conversion

You are to write a simple C program that will take a decimal number and a base as command line arguments and output the decimal number in that specified base. For example:

    $ ./conv 13 2
    1101
    $ ./conv 236709 8
    716245 
    $ ./conv 1352275 11
    843A91
    $ ./conv 38572856 64
    2J9Cu
    $ ./conv 3232236286 256
    192.168.2.254

    $ ./conv
    Usage: conv <decimal> <base>
    $ ./conv 11111 65
    INVALID BASE

> This is just example output, you should test against as many possible inputs as you can.

1. Your program should be able to handle all bases from 2 to 64 and 256.
1. It must have 4 defined functions:
    * `int main(int argc, char *argv[])` (every C program must have this)
    * `void other_base(unsigned decimal, unsigned base)` (for bases that **are not** a power of 2 or 256)
    * `void power2_base(unsigned decimal, unsigned base)` (for bases that **are** a power of 2 but still not 256)
    * `void base_256(unsigned decimal, unsigned base)` (for base 256 only)
1. Call only one of these functions during the execution of your program using the criteria given in parenthesis above.
1. Submit only the following files (we will cover how to submit assignments on Thursday):
    * Your source code file
    * `Makefile` (we will write this together in class)
1. Attempt to handle errors. See the example output for cases where no arguments are provided or an invalid base is given. _Never trust user input_.
1. Use a buffer of **32 characters**. This will give you 31 locations for characters and the final location should be a null.
1. Remember: you have to put the digits into the buffer _backwards_ and when the algorithm is finished, you have to _`printf()` from the correct location in that buffer_. See the example we did in class for how to accomplish that.

### Converting Integers to Characters

Think about how to use this character array:

```c
char *ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
```

The character `'1'` is _not the same_ as the **number 1**. If you need to know which numeric values correspond to which on screen characters, look at `man ascii` in your terminal.

### Division & Modulo

This algorithm is suitable for any base that is _not a power of two_ and is not **base 256** (`other_base()` function).

Let's see an example of converting the decimal number 29 into base 5. How many different values are there for base 5: `0`, `1`, `2`, `3` and `4`. So you should expect all of our digits to be one of those numbers. Get the first digit by calculating the remainder of 29 / 5:

      __5
    5| 29
       25
      ___
        4

The result of 29 / 5 is 5 with a remainder of 4.

There is a special operator for this in almost all programming languages: `%` (**modulo**) operator. This will give the remainder instead of the quotient.

    29 % 5 = 4

This is the first digit (ones digit) of the base 5 number. To continue, you start from the quotient of this operation. Division in C is integer division (just like in Java), so the remainder is discarded when you do:

    29 / 5 = 5

Now, continue with the algorithm:

      __1
    5|  5
        5
      ___
        0

The result of 5 / 5 is 1 with a remainder of 0.

    5 % 5 = 0

This is the second digit (fives digit) of the base 5 number.

    5 / 5 = 1

The algorithm continue until this division results in 0:

      __0
    5|  1
        0
      ___
        1

Now we have a remainder of 1 and the result of the integer division is 0. 

The number 29 in base 5 is **104**.

### Mask & Shift

This algorithm is suitable for any base that _is a power of two_ and is not **base 256** (`power2_base()` function).

What if you are trying to convert the number 7 into base 4? How many bit patterns are there for base 4: `00`, `01`, `10` and `11` which is 0, 1, 2 and 3. Let's see how masking works:

      0111 = 7
    & 0011 = 3
    __________
      0011 = 3

You've "masked off" the first digit, which is 3, by using the `&` (**bitwise AND**) operator. Now you can shift those bits to the right using the `>>` (**bitwise RIGHT SHIFT**) operator like so:

      7 >> 2 = 01

And continue with the algorithm:

      01 = 1
    & 11 = 3
    ________
      01 = 1

The number 7 in base 4 is **13**.

### Base 256

This algorithm will only be used for **base 256** (`base_256()` function).

It will involve using both previous algorithms. Since this is a power of 2, **mask & shift** must be utilized. However, the values you get will be numbers between 0 and 255. The `ascii` character array doesn't have that many different characters in it, so instead you will represent base 256 numbers in the same format as IP addresses:

    172.16.1.255

Each place value is separated by a `'.'` character (period, dot). The **division & modulo** algorithm will be used to calculate each digit of the decimal number for each place value.

In the above example, the ones place shows the number 255 which would have been calculated using **mask & shift** from the input number. Then that value needs to be placed in the buffer as a three digit decimal number by using the **division & modulo** algorithm.
