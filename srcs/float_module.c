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

long					itoa_double(long double dnum, unsigned char *p, int precision)
{
	int 				i;
	char 				t;
	unsigned char		*ptr;

	ptr = p;
	i = precision;
	dnum = dnum;

	if (dnum < 0)
	{
		dnum = -dnum;
		*p++ = '-';
	}

	while ((int)dnum > 0)
	{
		dnum /= 10;
		i++;
	}
	dnum *= 10;
	while (i > 0)
	{
		t = (int)dnum;
		*p++ = t | 0x30;
		i--;
		if (i == precision && precision > 0)
			*p++ = '.';
		dnum = dnum - (double)t;
		dnum *= 10;
	}
	*p++ = '\0';
	return (ptr - p);
}

long					get_dnum(long double dnum, t_fmt *fmt)
{
	char 	buf[100];
	char 	*p = buf;

	if (fmt->precision == -1)
		fmt->precision = 6;
	itoa_double(dnum, p, fmt->precision);
	printf("%s", p);
}
