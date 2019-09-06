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

void				apply_upcase(char *tmp)
{
	while (*tmp)
	{
		if (*tmp >= 'a' && *tmp <= 'z')
			*tmp -= 32;
		tmp++;
	}
}

long		 		itoa_base(uint64_t num, char s[], unsigned base)
{
	const char 			hex_table[17] = "0123456789abcdef";
	uint64_t 			rmndr;
	int64_t 			save;
	char 				*ptr;

	ptr = s;
	rmndr = 1;
	if ((save = num) < 0)
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

int 				get_num(int64_t num, t_fmt *fmt, t_vec *buf)
{
	unsigned int	nblen;
	char 			digits[60];
	char 			*p_dig;


	p_dig = digits;
	nblen = (unsigned int)itoa_base(num, digits, fmt->base);

	//todo: now its time to manipulate buff

	while (nblen--)
		ft_vec_add(&buf, &*p_dig++);
	fmt->iter += 1;
	return (0);
}
