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
	t_fmt			*f;
	char 			tmp[20];
	unsigned int 	nblen;
	char 			*p_tmp = tmp;

	i = 0;
	itoa_pf(num, p_tmp);
	nblen = ft_strlen(tmp);

	/* applying width */
	while (fmt->width > -1 && --fmt->width >= nblen && !(fmt->flags & LEFT))
		*fmt->buf_ptr++ = fmt->flags & ZERO ? '0' : ' ';
	/* applying flag '+' */

//	if (fmt->flags & PLUS)
//		*fmt->buf_ptr++ = num < 0 ? '-' : '+';
//	else if (num < 0)
//		*fmt->buf_ptr++ = '-';

	while (i < nblen)
		*fmt->buf_ptr++ = tmp[i++];
	fmt->iter += 1;
	return 0;
}
