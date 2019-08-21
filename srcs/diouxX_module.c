/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diouxX_module.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:21:21 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/21 20:21:22 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		 		*itoa_pf(uint64_t num, char *s, int sig, unsigned base)
{
	char 			hex_table[17] = "0123456789abcdef";
	uint64_t 		next;
	uint64_t 		save;
	char 			*ptr;

	save = base;
	ptr = s;

	/* This is for unsigned numbers (so 8, 16, 2 - bases) */
	if (base != 10)
	{
		while (save > (base - 1))
		{
			next = num / base;
			save = next * base;
			if (base == 16)
				*ptr++ = hex_table[num - save];
			if (base == 8 || base == 2)
				*ptr++ = (num - save) % 10 + '0';
			num = next;
		}
	}
	/* This is for signed numbers */
	if ((int)num < 0 && sig == 1)
		num = -num;
	if (num == 0 && base == 10) //this is only for base10
		*ptr++ = '0';
	while (num != 0)
	{
		*ptr++ = num % 10 + '0';
		num /= 10;
	}
	*ptr = '\0';
	ft_strrev(s);
	return (0);
}



int 				get_num(int64_t num, t_fmt *fmt, int sig)
{
	/* If num is SIGNED sig == 1. If num is UNSIGNED sig == 0 */
	int 			i;
	int 			prec;
	char 			sign;
	char 			tmp[100]; //what size?
	char 			*p_tmp;
	unsigned int 	nblen;

	i = 0;
	prec = 0;
	sign = 0;
	p_tmp = tmp;

	/* this function should return pointer to a new array (for 'P' conversion) */
	itoa_pf(num, p_tmp, sig, fmt->base);

	/* uppercasing */
	while (*fmt->iter == 'X' && tmp[i])
	{
		tmp[i] = ft_toupper(tmp[i]);
		i++;
	}
	nblen = ft_strlen(tmp);

	/* applying flag ' ' */
	if (fmt->flags & SPACE && num > 0)
		sign = ' ';

		/* getting flag '+' */
	/* printf("%+04d", 42) - gives you +042
	* but printf("%+4d, 42) - gives _+42
 	* So, in case '0' its before width. Without '0' its after...
 	* P.S. - decreasing width and checking it in 'if' - is not very good */

	if (fmt->flags & PLUS && fmt->width--)
		sign = num < 0 ? '-' : '+';
	else if (num < 0 && fmt->width--)
		sign = '-';

		/* getting precision */
	while (fmt->precision-- > nblen && fmt->precision > -1 && ++prec)
		fmt->width--;

	/* applying width */
	while (fmt->width > -1 && --fmt->width >= nblen && !(fmt->flags & LEFT))
		*fmt->buf_ptr++ = fmt->flags & ZERO ? '0' : ' ';

	/* applying precision */
	while (prec-- > 0)
		*fmt->buf_ptr++ = '0';

	/* applying sign */
	if (sign)
		*fmt->buf_ptr++ = sign;

	/* writing buf */
	while (nblen--)
		*fmt->buf_ptr++ = *p_tmp++;
	fmt->iter += 1;
	return (0);
}
