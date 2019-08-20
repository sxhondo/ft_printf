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
	unsigned int 	len;

	len = ft_nblen(n);
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
	if (sign < 0)
		*ptr++ = '-';
	*ptr++ = '\0';
	ft_strrev(s);
	return (len);
}

int 		get_num(int64_t num, t_fmt	*fmt)
{
	int 			i;
	t_fmt			*f;
	char 			tmp[20];
	unsigned int 	nblen;
	char 			*p_tmp = tmp;

	/* 1. Write num in buf_ptr
	 * 2. According to flags */

	i = 0;
	nblen = itoa_pf(num, p_tmp);
	while (i < nblen)
		*fmt->buf_ptr++ = tmp[i++];
	fmt->iter += 1;
	return 0;
//	fmt->iter += 1;
//	print_collected_data(&fmt);
}
