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

double			round(double dnum)
{
	unsigned char	t;

	// 37.66666 * 100 =3766.66
	// 3766.66 + .5 =3767.16    for rounding off value
	// then type cast to int so value is 3767
	// then divided by 100 so the value converted into 37.67

	float value = (int)(dnum * 100 + .5);
	return ((double)value / 100);
}

long					itoa_double(long double dnum, unsigned char *p, int precision)
{
	int 				i;
	unsigned char 				t;
	unsigned char		*ptr;

	ptr = p;
	i = precision;
	dnum = dnum;

	if (dnum < 0)
	{
		dnum = -dnum;
		*p++ = '-';
	}

	while ((uint64_t)dnum > 0)
	{
		dnum /= 10;
		i++;
	}
	dnum *= 10;
	while (i > 0)
	{
		t = round(dnum);
		*p++ = t | 0x30;
		i--;
		if (i == precision && precision > 0)
			*p++ = '.';
		dnum = dnum - (double)t;
		dnum *= 10;
	}
	*p++ = '\0';
	return (p - ptr - 1); // ?
}

long					get_dnum(long double dnum, t_fmt *fmt)
{
	unsigned  char 	tmp[100];
	unsigned char 	*p_tmp = tmp;
	char 			sign;
	int 			nblen;

	if (fmt->precision == -1)
		fmt->precision = 6;

		/* jump after written digits */
	p_tmp += itoa_double(dnum, p_tmp, fmt->precision);
		/* if SHARP promoted print dot anyway */
	if (fmt->flags & SHARP && fmt->precision <= 0)
		*p_tmp++ = '.';
	nblen = ft_strlen((char *)tmp);
	sign = 0;
	if (fmt->flags & SPACE && dnum > 0)
	{
		sign = ' ';
		fmt->width--;
	}

		/* apply sign */
	/* if ZERO or LEFT promoted we can already write sign in buf */
	if (sign && (fmt->flags & ZERO || fmt->flags & LEFT))
	{
		*fmt->buf_ptr++ = sign;
		sign = 0;
	}

		/* apply flag left alignment ('-') */
	/* if LEFT promoted we can already write num in buf */
	while (fmt->flags & LEFT && *p_tmp)
		*fmt->buf_ptr++ = *p_tmp++;

		/* apply width */
	/* if flag zero promoted fill the field with '0' else with ' '.
	 * Original printf ignores zero-filling when the precision promoted. Dunno why */
	while (fmt->width > -1 && --fmt->width >= nblen) // !(fmt->flags & LEFT) ?
		*fmt->buf_ptr++ = (fmt->flags & ZERO) && !(fmt->flags & LEFT) ? '0' : ' ';

	/* apply sign */
	/* if previous sign-check was not made write in buf sign */
	if (sign)
		*fmt->buf_ptr++ = sign;

	/* write buf */
	/* if buf was not already written by 'LEFT' */
	p_tmp = tmp;
	while (nblen-- && !(fmt->flags & LEFT))
		*fmt->buf_ptr++ = *p_tmp++;
	fmt->iter += 1;
	return (0);
}
