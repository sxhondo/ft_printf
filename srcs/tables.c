/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:30:42 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/16 18:30:43 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char					*reverse(char buf[], int size)
{
	char 	*s;
	char 	*str;
	int		i;

	s = buf;
	i = 0;
	str = (char *)malloc(sizeof(char) * size + 1);
	while (--size >= 0)
		str[i++] = s[size];
	str[i] = '\0';
	return (str);
}

char 					*base_any(uint64_t  num, int base)
{
	char 		hex_table[17] = "0123456789abcdef";
	char 		buf[100];
	uint64_t 	next;
	uint64_t 	save;
	int 		i;

	i = 0;
	save = base;
	while (save > (base - 1))
	{
		next = num / base;
		save = next * base;
		if (base == 16)
			buf[i++] = hex_table[num - save];
//		if (base == 8)
//			*p++ = (small_itoa(num - save));
//		if (base == 2)
//			*p++ = small_itoa(num - save);
		num = next;
	}
	buf[i] = '\0';
	return (reverse(buf, i));
}