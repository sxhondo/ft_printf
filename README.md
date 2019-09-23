# ft_printf

Implementation of libc printf function 

Regardless of the programming language considered, the printf function,(or its equivalents) is always highly useful. 
The main reason is the ease of its formatting, and the
support of diverse types in variable numbers. Some variations even propose to be able to
write the resulting string of characters either in a file descriptor or in a particular stream.
Some also propose to recall this string without printing it. In short, undeniably, printf
is a vital function.

# Installing
    make
# Supported Conversions 
**"%c"** - The int argument is converted to an unsigned char, and the resulting character is written.\

**"%s"** - The char * argument is expected to be pointer to a string. Characters from the array are written up to (but not including) a terminating NUL character;\
~ If a precision is specified, no more than the number specified are written.\  
~ If a precision is given, no null character need be present;\
~ if the precision is not specified, or is greater than the size of the array, the array must contain a terminating NUL character.\

**"%k"** - The char * argument is expected to be pointer to a string. Prints non-printable characters (ASCII < 41 or > 176)

**"%k"** - The char * argument is expected to be pointer to a string. Prints non-printable characters (ASCII < 41 or > 176)

**"%p"** - The void * pointer argument is printed in hexadecimal

**"%%"** -A ' %' is written.  No argument is converted.  The complete conversion specification is '%%'.

**"%diouxXb** - The int (or appropriate variant) argument is converted to signed decimal (d and i), unsigned octal (o), unsigned decimal (u), unsigned
             hexadecimal (x and X) or binary (b) notation.\
~ The precision, if any, gives the minimum number of digits that must appear; if the converted value requires fewer digits, it is padded on the left with zeros.

**"%fF"** - The double argument is rounded and converted to decimal notation in the style [-]ddd.ddd, where the number of digits after the decimal-point
character is equal to the precision specification.\
             ~ If the precision is missing, it is taken as 6;\
             ~ If the precision is explicitly zero, no decimal-point character appears.  If a decimal point appears, at least one digit appears before it.

**"%eE"** - The double argument is rounded and converted in the style [-]d.ddde+-dd where there is one digit before the decimal-point character and the
number of digits after it is equal to the precision;\
            ~If the precision is missing, it is taken as 6;\
            ~If the precision is zero, no decimal-point character appears.\
            ~An E conversion uses the letter 'E' (rather than `e') to introduce the exponent.\
            ~if the value is zero, the exponent is 00.

# Usage
    ![Alt text](./pics/example_main.png?raw=true "Example main")
    ![Alt text](./pics/example_output.png?raw=true "Example output")            