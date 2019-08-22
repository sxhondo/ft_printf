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
	return (0); // ?
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
	i = 0;
	prec = 0;
	sign = 0;

	itoa_base(num, tmp, sig, fmt->base);
	nblen = ft_strlen(tmp);

		/* getting 'S.P.E.C.I.A.L.' */
		/*  */
	nblen += (fmt->flags & SPECIAL && ft_strcmp(tmp, "0")) ? 2 : 0;

	/* applying uppercase */
	while (*fmt->iter == 'X' && tmp[i])
	{
		tmp[i] = ft_toupper(tmp[i]);
		i++;
	}

	/* applying flag ' ' */
	if (fmt->flags & SPACE && num > 0)
		sign = ' ';

		/* getting flag '+' */
	/* printf("%+04d", 42) - gives you +042
	* but printf("%+4d, 42) - gives _+42
 	* So, in case '0' its before width. Without '0' its after...
 	* P.S. - decreasing width and checking it in 'if' - is not very good */

	if (fmt->flags & PLUS && fmt->width--)
		sign = num < 0 ? '-' : '+';
	else if (num < 0 && fmt->width--)
		sign = '-';

		/* getting precision */
	while (fmt->precision-- > nblen && fmt->precision > -1 && ++prec)
		fmt->width--;

		/* applying flag '-' */
		/* If 'LEFT' first write num, then width */
	while (fmt->flags & LEFT && *p_tmp)
		*fmt->buf_ptr++ = *p_tmp++;

		/* applying width */
	while (fmt->width > -1 && --fmt->width >= nblen)
		*fmt->buf_ptr++ = fmt->flags & ZERO ? '0' : ' ';

	/* applying special */
	if (fmt->flags & SPECIAL && (fmt->base == 8 || fmt->base == 16) && ft_strcmp(tmp, "0"))
	{
		*fmt->buf_ptr++ = '0';
		if (fmt->base == 16)
			*fmt->buf_ptr++ = fmt->flags & CASE ? 'X' : 'x';
		nblen -= 2;
	}
		/* applying precision */
	while (prec-- > 0)
		*fmt->buf_ptr++ = '0';

		/* applying sign */
	if (sign)
		*fmt->buf_ptr++ = sign;

		/* writing buf */
		/* Only if buf wasnt already written by 'LEFT'*/
	while (nblen-- && !(fmt->flags & LEFT))
		*fmt->buf_ptr++ = *p_tmp++;
	*fmt->buf_ptr = '\0';
	fmt->iter += 1;
	return (0); // ?
}
