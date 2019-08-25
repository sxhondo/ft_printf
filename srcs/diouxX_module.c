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

char		 		*itoa_base(uint64_t num, char s[], int sig, unsigned base)
{
	char 			hex_table[17] = "0123456789abcdef";
	uint64_t 		rmndr;
	char 			*ptr;
	char 			*p;
	int 			save;

	ptr = s;
	rmndr = 1;
	if ((save = num) < 0 && sig == 1)
		num = -num;
	while ((rmndr * base) >= base)
	{
		rmndr = num / base;
		if (base == 10 || base == 8 || base == 2)
			*ptr++ = (num - (rmndr * base)) % 10 + '0';
		if (base == 16)
			*ptr++ = hex_table[num - (rmndr * base)];
		num = rmndr;
	}
	*ptr++ = '\0';
	ft_strrev(s);
	return (s); // ?
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

	p_tmp = tmp;
		/* applying SHARP */
	if (fmt->flags & SHARP && num != 0)
	{
		if (fmt->flags & ZERO)
		{
			*fmt->buf_ptr++ = '0';
			fmt->width--;
			if (fmt->base == 16)
			{
				*fmt->buf_ptr++ = fmt->flags & CASE ? 'X' : 'x';
				fmt->width--;
			}
		}
		else
		{
			*p_tmp++ = '0';
			if (fmt->base == 16)
				*p_tmp++ = fmt->flags & CASE ? 'X' : 'x';
		}
	}
	itoa_base(num, p_tmp, sig, fmt->base);

	/* If '0x' or '0' was written, move pointer back */
	if (p_tmp - tmp)
	{
		if (fmt->base == 8)
			p_tmp -= 1;
		else if (fmt->base == 16)
			p_tmp -= 2;
	}

	nblen = ft_strlen(tmp);
	/* applying uppercase */
	i = 0;
	while (*fmt->iter == 'X' && tmp[i])
	{
		tmp[i] = ft_toupper(tmp[i]);
		i++;
	}

	/* applying flag ' ' */
	sign = 0;
	if (fmt->flags & SPACE && num > 0)
		sign = ' ';

		/* getting flag '+' */
	/* decreasing width and checking it in 'if' - is not very good */
	if (fmt->flags & PLUS && fmt->width--)
		sign = num < 0 ? '-' : '+';
	else if (num < 0 && fmt->width--)
		sign = '-';

		/* getting precision */
	/* if precision is set but like this "." or ".0" and num is 0 - don't print anything */
	prec = 0;
	if (fmt->precision == 0 && num == 0)
	{
		nblen = 0;
		fmt->width -= 1;
	}
	/* else get precision */
	else if (fmt->precision > -1)
		while (fmt->precision-- > nblen && ++prec)
			fmt->width--;


	/* applying flag '-' */
	/* If 'LEFT' first write num, then width */
	while (fmt->flags & LEFT && *p_tmp)
		*fmt->buf_ptr++ = *p_tmp++;

	/* applying width */
	while (fmt->width > -1 && --fmt->width >= nblen)
		*fmt->buf_ptr++ = (fmt->flags & ZERO) && !(fmt->flags & LEFT) ? '0' : ' ';

		/* applying precision */
	while (prec-- > 0)
		*fmt->buf_ptr++ = '0';
		/* applying sign */
	if (sign)
		*fmt->buf_ptr++ = sign;

		/* writing buf */
		/* Only if buf wasnt already written by 'LEFT' */

	while (nblen-- && !(fmt->flags & LEFT))
		*fmt->buf_ptr++ = *p_tmp++;
	fmt->iter += 1;
//	print_collected_data(&fmt);
	return (0);
}
