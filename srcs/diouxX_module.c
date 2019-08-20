/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:34:01 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/14 18:34:02 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			 		itoa_pf(int n, char s[])
{
	int 			sign;
	char 			*ptr;

	ptr = s;
	if ((sign = n) < 0)
		n = -n;
	if (n == 0)
		*ptr++ = '0';
	while (n != 0)
	{
		*ptr++ = n % 10 + '0';
		n /= 10;
	}
//	if (sign < 0)
//		*ptr++ = '-';
	*ptr++ = '\0';
	ft_strrev(s);
	return (0);
}

int 				get_num(int64_t num, t_fmt	*fmt)
{
	int 			i;
	char 			sign;
	char 			tmp[20];
	char 			*p_tmp;
	unsigned int 	nblen;

	i = 0;
	sign = 0;
	p_tmp = tmp;
	itoa_pf(num, p_tmp);
	nblen = ft_strlen(tmp);

		/* applying flag ' ' */
	if (fmt->flags & SPACE && num > 0)
		sign = ' ';

		/* applying flag '+' */
	/* printf("%+04d", 42) - gives you +042
	* but printf("%+4d, 42) - gives _+42
 	* So, in case '0' its before width. Without '0' its after...
 	* P.S. - decreasing width and checking it in 'if' - is not very good */

	if (fmt->flags & PLUS && fmt->width--)
		sign = num < 0 ? '-' : '+';
	else if (num < 0 && fmt->width--)
		sign = '-';

	/* applying width */
	while (fmt->width > -1 && --fmt->width >= nblen && !(fmt->flags & LEFT))
		*fmt->buf_ptr++ = fmt->flags & ZERO ? '0' : ' ';
	if (sign)
		*fmt->buf_ptr++ = sign;
	while (i < nblen)
		*fmt->buf_ptr++ = tmp[i++];
	fmt->iter += 1;
	return 0;
}
