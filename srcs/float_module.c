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

long double						roundd(long double dnum)
{
	long double					tmp;

	tmp = (uint64_t)(dnum * 100 + .5);
	return (tmp / 100);
}

int								itoa_double(long double dnum, unsigned char *p, t_fmt *fmt)
{
	int 						i;
	uint64_t 					tmp;
	unsigned char				*ptr;

	ptr = p;
	i = fmt->precision;
	if (dnum < 0)
		dnum = -dnum;
	if ((uint64_t)dnum == 0)
	{
		*p++ = '0';
		if (fmt->precision > 0 || fmt->flags & SHARP)
			*p++ = '.';
	}
	while ((uint64_t)dnum > 0 && ++i)
		dnum /= 10;
	dnum *= 10;
	while (i > 0)
	{
		*p++ = (tmp = roundd(dnum)) | (unsigned)0x30;
		i--;
		if (i == fmt->precision && (fmt->precision > 0 || fmt->flags & SHARP))
			*p++ = '.';
		dnum = dnum - (long double)tmp;
		dnum *= 10;
	}
	*p++ = '\0';
	return ((int)(p - ptr - 1));
}

char 						get_dsign(long double dnum, t_fmt *fmt)
{
	char 					sign;

	sign = 0;
	if (fmt->flags & PLUS)
		sign = dnum < 0 ? '-' : '+';
	else if (dnum < 0)
		sign = '-';
	else if (fmt->flags & SPACE)
		sign = ' ';
	return (sign);
}

void						print_dnum(t_fmt *fmt, t_vec *buf, unsigned int nblen,
										unsigned char digits[], char sign)
{
	unsigned char 			*p_dig;

	p_dig = digits;
	if (sign)
	{
		ft_vec_add(&buf, &sign);
		nblen--;
	}
	while (nblen--)
		ft_vec_add(&buf, &*p_dig++);
}

long 						get_dnum(long double dnum, t_fmt *fmt, t_vec *buf)
{
	unsigned char 			digits[100];
	unsigned int			nblen;
	char 					sign;
	char 					tmp;

	if (fmt->precision == -1)
		fmt->precision = 6;
	nblen = itoa_double(dnum, digits, fmt);
	if ((sign = get_dsign(dnum, fmt)))
		nblen++;
	if (fmt->flags & LEFT)
		print_dnum(fmt, buf, nblen, digits, sign);
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (--fmt->width >= nblen && fmt->width > -1)
		ft_vec_add(&buf, &tmp);
	if (!(fmt->flags & LEFT))
		print_dnum(fmt, buf, nblen, digits, sign);
	fmt->iter += 1;
}
