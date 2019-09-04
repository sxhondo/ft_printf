

/* me trying to understand why I need mant and exp : */

#include "ft_printf.h"

void		 			fraction(double num, char s[])
{
	uint64_t			res;
	int 				whole[52];
	int 				i;

	i = 0;
	while (i < 52)
	{
		num = (double)num * 2; // multiplicate fraction part by two
		whole[i] = (int)num; // save whole part
		if (i == 0)
			num += 0.0005; // offset ???
		if ((int)num >= 1)
			num -= (int)num;
		i++;
	}
	i = -1;
	while (++i < 52) // write in str
		*s++ = whole[i] + '0';
}

int64_t					power_of(int num, int pow)
{
	int64_t				res;

	res = 1;
	while (pow--)
		res = res * num;
	return (res);
}

size_t 					len_bin(char str[])
{
	size_t 	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1')
			return (0);
		i++;
	}
	return (i);
}

unsigned  int			bin_to_dec(char *str)
{
	unsigned  int 		res;
	char 				buf[24];
	int 				len;
	int 				i = 0;

	i = 0;
	res = 0;
	ft_memcpy(buf, str, 23);
	len = len_bin(buf);

	while (len--)
		res += ((unsigned int)buf[i++] - '0') * power_of(2, len);
	return (res);
}

void 					dnum(long double dnum)
{
	char 			mas[100]; //for whole part and fract part (in binary)
	char 			*m = mas;
	char 			norm_mant[200]; //for normalized mantissa [52] for x64
	long	 		exp_len; // length of exponenta
	unsigned int 	sign = dnum > 0 ? 0 : 1;

		/* get mant */
	exp_len = itoa_base((int)dnum, m, 0, 2); // 1. get whole part of dnum 2. put bin in mas[]
	m += exp_len;  // get bin whole part
//	*m++ = '.'; //show bin of whole part and bin of fract part separated by '.'. Result will be wrong
	fraction((double)dnum - (int)dnum, m); // 1. get fract part, 2. get bin fract part
	printf("full mant: %s\n", mas);

		/* get norm mant (23 symb, no first symb)*/
	ft_memcpy(norm_mant, mas + 1, 23);
	printf("norm mant:  %s\n", norm_mant);

		/* get decimal mant */
	unsigned int	mant = bin_to_dec(norm_mant);
	printf("b10  mant: %d\n\n", mant);

		/* get exp */
	uint64_t 		dec_exp;
	char 			bin_exp[8]; //[16] for 64x

	/* get decimal exp */
		/* amount of bits in whole part + ...*/
	dec_exp = exp_len - 1 + 255 / 2; // 8 + 127 = 135 (32x) 8 + 1023 = 1031 (64x)
	printf("b10 exp: %9llu\n", dec_exp);

	/* get bin exp */
	itoa_base(dec_exp, bin_exp, 0, 2);
	printf("b2 exp: %10s\n", bin_exp);


	/* formula to get number back for 32x */
//		F = (-1)^S * 2^(E-127) * (1 + M / 2^23)

		//	left half of formula
		//	(-1)^S * 2^(E-127)
	int64_t  res1 = power_of(-1, (int)sign) * power_of(2, exp_len - 1 + 255 / 2 - 127);

		//	right half of formula
		//	(1 + M / 2^23)
	double res2 = 1 + (double)mant / (double)power_of(2, 23); // losed precision = 0.000244 ???
	double res = res1 * res2 - 0.000244;

//	char 	buf[100];
//	char 	*p = buf;
//	int 	precision = 3;
//	itoa_double(dnum, p, precision);
//	printf("%s", buf);

	printf("\nres: %13f\n", res);
}
