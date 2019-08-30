/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_module.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:37:57 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/29 16:37:59 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"
//
//int			 		itoa_bas(uint64_t num, char s[], int sig, unsigned base)
//{
//	char 			hex_table[17] = "0123456789abcdef";
//	uint64_t 		rmndr;
//	char 			*ptr;
//	char 			*p;
////	int				save;
//	int64_t 		save;
//
//	ptr = s;
//	rmndr = 1;
//	if ((save = num) < 0 && sig == 1)
//		num = -num;
//	while ((rmndr * base) >= base)
//	{
//		rmndr = num / base;
//		if (base == 10 || base == 8 || base == 2)
//			*ptr++ = (num - (rmndr * base)) % 10 + '0';
//		if (base == 16)
//			*ptr++ = hex_table[num - (rmndr * base)];
//		num = rmndr;
//	}
//	*ptr++ = '\0';
//	ft_strrev(s);
//	return (ft_strlen(s));
//}

void		 			fraction(double num, char s[])
{
	uint64_t			res;
	int 				whole[52];
	int 				i;

	i = 0;
	while (i < 52)
	{
		num = (double)num * 2; // последовательно умножаем дробную часть на основание 2
		whole[i] = (int)num; // получаем целую часть
		if (i == 0)
			num += 0.0005; // смещение
		if ((int)num >= 1)
			num -= (int)num;
		i++;
	}
	i = -1;
	while (++i < 52)
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

void 					get_dnum(double dnum, t_fmt	*fmt)
{
	char 			mas[100];
	char 			norm_mant[23];
	char 			*m = mas;
	int 			exp_len;
	unsigned int 	sign = dnum > 0 ? 0 : 1;

		/* get mant */
//	printf("%llu", itoa_base((int)dnum, m, 0, 2));
//	exit (0);
	exp_len = itoa_base((int)dnum, m, 0, 2); // 1. get whole part of dnum 2. put bin in mas[]
	m += exp_len;  // get bin whole part
//	*m++ = '.'; //show bin of whole part and bin of fract part separated by '.'. Result will be wrong
	fraction(dnum - (int)dnum, m); // 1. get fract part, 2. get bin fract part
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


	//formula to get number back for 32x (aka floats)
		//F = (-1)^S * 2^(E-127) * (1 + M / 2^23)

		//	left half of formula
		//	(-1)^S * 2^(E-127)
	int64_t  res1 = power_of(-1, (int)sign) * power_of(2, exp_len - 1 + 255 / 2 - 127);

		//	right half of formula
		//	(1 + M / 2^23)
	double f1 = (double)mant;
	double f2 = (double)power_of(2, 23);
	double res2 = 1 + f1 / f2; // losed precision = 0.000244 ???

		//multiplication
	double res = res1 * res2; // - 0.000244;
	printf("Result: %f\n", res);




}