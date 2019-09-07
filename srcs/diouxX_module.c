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

void					apply_upcase(char *tmp)
{
	while (*tmp)
	{
		if (*tmp >= 'a' && *tmp <= 'z')
			*tmp -= 32;
		tmp++;
	}
}

unsigned int			itoa_base(uint64_t num, char s[], unsigned base)
{
	const char			hex_table[17] = "0123456789abcdef";
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
			*ptr++ = (num - (rmndr * base)) % 10 | 0x30;
		if (base == 16)
			*ptr++ = hex_table[num - (rmndr * base)];
		num = rmndr;
	}
	*ptr = '\0';
	ft_strrev(s);
	return ((unsigned int)(ptr - s));
}

int						get_sign(t_fmt *fmt, int64_t num)
{
	char 				sign;

	sign = 0;
	if (fmt->flags & PLUS && num != UINT32_MAX)
		sign = num < 0 ? '-' : '+';
	else if (num < 0)
		sign = '-';
	else if (fmt->flags & SPACE)
		sign = ' ';
	return (sign);
}

unsigned int			recount_nblen(t_fmt *fmt, int64_t num)
{
	int 				i;

	i = 0;
	if (fmt->base == 10 && get_sign(fmt, num))
		i++;
	if (fmt->flags & SHARP && fmt->base != 10)
	{
		i++;
		if (fmt->base & (unsigned)16)
			i++;
	}
	return (i);
}

int						put_alt_form(t_fmt *fmt, t_vec *buf)
{
	int 				len;
	char 				*p_form;

	len = 0;
	p_form = "0x";
	if (fmt->flags & CASE)
		p_form = "0X";
	if (fmt->base != 10)
	{
		ft_vec_add(&buf, &p_form[0]);
		len++;
		if (fmt->base & (unsigned)16 && len++)
			ft_vec_add(&buf, &p_form[1]);
	}
	fmt->flags &= ~SHARP;
	fmt->width -= len;
	return (len);

}

unsigned int			print_num(t_fmt *fmt, t_vec *buf, unsigned int nblen,
										int64_t num, char digits[])
{
	char 				sign;
	char 				*p_dig;
	char 				*p_form;

	p_form = "0x";
	p_dig = digits;
	if (fmt->flags & CASE)
	{
		p_form = "0X";
		apply_upcase(p_dig);
	}
	if (fmt->flags & SHARP && fmt->base != 10 && nblen--)
	{
		ft_vec_add(&buf, &p_form[0]);
		if (fmt->base & (unsigned)16 && nblen--)
			ft_vec_add(&buf, &p_form[1]);
	}
	else if ((sign = (char)get_sign(fmt, num)) && nblen--)
		ft_vec_add(&buf, &sign);
	while (nblen--)
		ft_vec_add(&buf, &*p_dig++);
	return (0);
}


int						get_num(int64_t num, t_fmt *fmt, t_vec *buf)
{
	unsigned int		nblen;
	char 				digits[60];
	char 				*p_dig = digits;
	char 				tmp;
	int 				prec;

	prec = 0;
	nblen = (unsigned int)itoa_base(num, digits, fmt->base);
//	while (fmt->precision > -1 && fmt->precision-- > nblen && ++prec)
//		fmt->width--;
	nblen += recount_nblen(fmt, num);
	if (fmt->flags & LEFT)
	{
		fmt->flags &= ~ZERO;
		print_num(fmt, buf, nblen, num, digits);
	}
	if (fmt->flags & ZERO && fmt->flags & SHARP) // || prec
		nblen -= put_alt_form(fmt, buf); //
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (--fmt->width >= nblen && fmt->width > -1)
		ft_vec_add(&buf, &tmp);

//	while (--prec)
//		ft_vec_add(&buf, )

	if (!(fmt->flags & LEFT))
		print_num(fmt, buf, nblen, num, digits);

	fmt->iter += 1;
	return (0);
}
