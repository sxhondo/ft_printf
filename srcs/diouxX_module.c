/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diouxX_module.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:21:21 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/27 00:27:18 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ft_printf.h>
#include "../incs/ft_printf.h"

long		 		itoa_base(uint64_t num, char s[], int sig, unsigned base)
{
	char 			hex_table[17] = "0123456789abcdef";
	uint64_t 		rmndr;
	int64_t 		save;
	char 			*ptr;

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
	*ptr = '\0';
	ft_strrev(s);
	return (ptr - s);
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


		/* apply SHARP */
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
		else if (fmt->precision > -1)
		{
			*fmt->buf_ptr++ = '0';
			fmt->base == 16 ? fmt->precision++ : fmt->precision--;
			if (fmt->base == 16)
			{
				*fmt->buf_ptr++ = fmt->flags & CASE ? 'X' : 'x';
				fmt->precision--;
			}
		}
		else
		{
			*p_tmp++ = '0';
//			*fmt->buf_ptr++ = '0';
			if (fmt->base == 16)
			{
				*p_tmp++ = fmt->flags & CASE ? 'X' : 'x';
			}
		}
	}

	itoa_base(num, p_tmp, sig, fmt->base);
	nblen = ft_strlen(tmp);

		/* apply width */
	/* for negative width */
	if (fmt->width < -nblen && fmt->width < 0)
	{
		while (*p_tmp)
			*fmt->buf_ptr++ = *p_tmp++;
		while (++fmt->width <= -nblen)
			*fmt->buf_ptr++ = ' ';
		nblen = 0;
	}
		/* if '0x' or '0' was written(pointer to buf - buf > 0), move pointer back */
	if (p_tmp - tmp)
	{
		if (fmt->base == 8)
			p_tmp -= 1;
		else if (fmt->base == 16)
			p_tmp -= 2;
	}

		/* apply uppercase */
	i = 0;
	while (*fmt->iter == 'X' && tmp[i])
	{
		tmp[i] = ft_toupper(tmp[i]);
		i++;
	}

		/* apply flag ' '. Write space in var sign. */
	sign = 0;
	if (fmt->flags & SPACE && num >= 0 && num != UINT32_MAX)
	{
		sign = ' ';
		fmt->width--;
	}
		/* get flag '+' */
	/* if flags 'plus' write +/- in var sign. Else only for negative nums */
	if (fmt->flags & PLUS && fmt->width-- && num != UINT32_MAX)
		sign = num < 0 ? '-' : '+';
	else if (num < 0 && fmt->width-- && sig != 0)
		sign = '-';

		/* get precision */
	/* precision like this "." or ".0" and num is 0 - don't print anything */
	prec = 0;
	if (fmt->precision == 0 && num == 0)
	{
		nblen = 0;
		fmt->width -= 1;
		/* #.o or #.0o with arguments '0', '0' - prints: 0 0 */
		if (fmt->base == 8 && fmt->flags & SHARP)
			*fmt->buf_ptr++ = *p_tmp++;
	}
	/* else get precision and decrease width */
	else if (fmt->precision > -1)
		while (fmt->precision-- > nblen && ++prec)
			fmt->width--;

		/* apply sign */
	/* if ZERO or LEFT promoted we can already write sign in buf */
	if (sign && (fmt->flags & ZERO || fmt->flags & LEFT))
	{
		*fmt->buf_ptr++ = sign;
		sign = 0;
	}
		/* apply precision */
	/* if LEFT promoted we can already write precision in buf */
	while (fmt->flags & LEFT && prec-- > 0)
		*fmt->buf_ptr++ = '0';

		/* apply flag left alignment ('-') */
	/* if LEFT promoted we can already write num in buf */
	while (fmt->flags & LEFT && *p_tmp)
		*fmt->buf_ptr++ = *p_tmp++;

		/* apply width */
	/* if flag zero promoted fill the field with '0' else with ' '. 
	 * Original printf ignores zero-filling when the precision promoted. Dunno why */
	while (fmt->width > -1 && --fmt->width >= nblen) // !(fmt->flags & LEFT) ?
		*fmt->buf_ptr++ = (fmt->flags & ZERO) && !(fmt->flags & LEFT) && prec < 1 ? '0' : ' ';

		/* apply sign */
	/* if previous sign-check was not made write in buf sign */
	if (sign)
		*fmt->buf_ptr++ = sign;

		/* apply precision */
	/* If previous check was not made write in buf '0's */
	while (prec-- > 0)
		*fmt->buf_ptr++ = '0';

//	if (fmt->width <= -nblen)
//		while (++fmt->width <= -nblen)
//			*fmt->buf_ptr++ = (fmt->flags & ZERO) && !(fmt->flags & LEFT) && prec < 1 ? '0' : ' ';

	/* write buf */
	/* if buf was not already written by 'LEFT' */
	while (nblen-- && !(fmt->flags & LEFT))
		*fmt->buf_ptr++ = *p_tmp++;
	fmt->iter += 1;
//	print_collected_data(&fmt);
	return (0);
}
