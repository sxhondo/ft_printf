///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   main.c                                             :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2019/08/04 20:32:45 by sxhondo           #+#    #+#             */
///*   Updated: 2019/08/27 00:30:46 by sxhondo          ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
////int64_t					power_of(int num, int pow)
////{
////	int64_t				res;
////
////	res = 1;
////	while (pow--)
////		res = res * num;
////	return (res);
////}
////
////size_t 					len_bin(char str[])
////{
////	size_t 	i;
////
////	i = 0;
////	while (str[i])
////	{
////		if (str[i] != '0' && str[i] != '1')
////			return (0);
////		i++;
////	}
////	return (i);
////}
////
////
////unsigned  int			bin_to_dec(char *str)
////{
////	unsigned  int 		res;
////	char 				buf[24];
////	int 				len;
////	int 				i = 0;
////
////	i = 0;
////	res = 0;
////	ft_memcpy(buf, str, 23);
////	len = len_bin(buf);
////
////	while (len--)
////		res += ((unsigned int)buf[i++] - '0') * power_of(2, len);
////	return (res);
////}
////
////void		 			fraction_to_bin(double num, unsigned char s[])
////{
////	int 				i;
////	unsigned char 				*p;
////
////	p = s;
////	i = 0;
////	while (i < 8)
////	{
////		num = num * 2; // multiplicate fraction part by two
////		*p++ = (unsigned int)num | (unsigned)0x30; // save result
////		if ((int)num >= 1)
////			num -= (int)num;
////		i++;
////	}
////	*p = '\0';
////}
////
////typedef union				u_double
////{
////	long double				dnum;
////	struct
////	{
////		unsigned long int	mantisa : 64;
////		unsigned int		exponent : 15;
////		unsigned int		sign : 1;
////	}						s_parts;
////}							t_double;
////
////
////long 				put_dnum(long double dnum)
////{
//////	union					u_double	*d;
////	unsigned char 			whole[100];
////	unsigned char 			fract[100];
////
////	// check 'n' bit in num
////	//	printf("%u", (int)dnum >> n & 1);
////
////	unsigned int	exp_len;
////	exp_len = itoa_base((int)dnum, whole, 2, 0); //bin representation of whole part
////	fraction_to_bin((double)dnum - (int)dnum, fract); // bin representation of fractional part
////	printf("b2 whole, b2 fract: \t\t");
////	printf("%s,%s\n", whole, fract);
////
////	/* normalized exp form */
////	exp_len -= 1;
////	unsigned char *p_w = whole;
////	printf("normilized exp form: \t\t");
////	printf("%c,%s%s * 2^%d\n", whole[0], p_w + exp_len, fract, exp_len);
////
////	/* смещенный порядок */
////	/* исходная экспонента + (2^k - 1) - 1 , k - количество бит для хранения эксп */
//////	offset = exp_len + (unsigned int)power_of(2, k - 1) - 1;
//////  для 32 это половина байта (127 бит), для 64 это (1023 бит)
////	unsigned int offset = exp_len + 127;
////	char 		 exp_off_bin[100];
////	itoa_base(offset, exp_off_bin, 2, 0);
////	printf("offseted exp \t\t\t\t%d = %sb2\n", offset, exp_off_bin);
////
////	unsigned int sign = dnum > 0 ? 1 : 0;
////
////	printf("\ns exp\t\tmant\n");
////	printf("%d %s %s%s", sign, exp_off_bin, p_w + exp_len, fract);
////}

#include <stdio.h>
#include "incs/ft_printf.h"

int 	main()
{
//	put_dnum(3.1513);



	ft_printf("%k\n");


}
