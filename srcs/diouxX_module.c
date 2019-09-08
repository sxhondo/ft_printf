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
	if (fmt->flags & SHARP && fmt->base != 10 && num != 0)
	{
		i++;
		if (fmt->base & (unsigned)16)
			i++;
	}
	return (i);
}

int						put_before(t_fmt *fmt, t_vec *buf, int64_t num, char sign)
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
	if (fmt->flags & PLUS)
	{
		if ((sign))
			ft_vec_add(&buf, &sign);
		fmt->flags &= ~PLUS;
		len++;
	}
	fmt->flags &= ~SHARP;
	fmt->width -= len;
	return (len);
}

unsigned int			put_precision(t_fmt *fmt, t_vec *buf, int prec,
											int64_t num, unsigned int nblen, char f)
{
	unsigned int	i;

	i = 0;
	if (fmt->precision == 0 && num == 0)
		i = 1;
	while (prec--)
		ft_vec_add(&buf, &f);
	if (i)
		return (i);
	return (i);
}

unsigned int			print_num(t_fmt *fmt, t_vec *buf, unsigned int nblen,
										int64_t num, char digits[], int prec,
										char sign)
{
	char 				*p_dig;
	char 				*p_form;

	p_form = "0x";
	p_dig = digits;

	if (fmt->flags & ZERO)
		fmt->flags &= ~ZERO;
	if (fmt->flags & CASE)
	{
		p_form = "0X";
		apply_upcase(p_dig);
	}
	if (fmt->flags & SHARP && fmt->base != 10 && num != 0)
	{
		nblen--;
		ft_vec_add(&buf, &p_form[0]);
		if (fmt->base & (unsigned)16 && nblen--)
			ft_vec_add(&buf, &p_form[1]);
	}
	if (sign)
		ft_vec_add(&buf, &sign);
	nblen -= put_precision(fmt, buf, prec, num, nblen, p_form[0]);
	while (nblen--)
		ft_vec_add(&buf, &*p_dig++);
	return (0);
}

int 					count_precision(t_fmt *fmt, unsigned int nblen, int64_t num)
{
	int 	prec;

	prec = 0;
	if (fmt->precision > -1)
	{
		fmt->flags &= ~ZERO;
		while (fmt->precision > nblen)
		{
			prec++;
			fmt->precision--;
			fmt->width--;
		}
	}
	return (prec);
}

char 					decide_sign(t_fmt *fmt, t_vec *buf, unsigned int nblen, int64_t num, char sign)
{
	if (sign && nblen-- && fmt->width-- && fmt->flags & ZERO && fmt->width > -1)
	{
		ft_vec_add(&buf, &sign);
		return (0);
	}
	return (sign);
}

int						get_num(int64_t num, t_fmt *fmt, t_vec *buf)
{
	unsigned int		nblen;
	char 				digits[60];
	char 				tmp;
	int 				prec;
	char 				sign;

	prec = 0;
	nblen = (unsigned int)itoa_base(num, digits, fmt->base);
	nblen += recount_nblen(fmt, num);
	sign = decide_sign(fmt, buf, nblen, num, (char)get_sign(fmt, num));
	nblen -= num && (fmt->flags & PLUS || fmt->flags & SPACE || num < 0) ? 1 :
		num == 0 && (fmt->flags & PLUS || fmt->flags & SPACE) ? 1 : 0;
	if (fmt->precision > -1)
		prec = count_precision(fmt, nblen, num);
	if (fmt->flags & LEFT)
		print_num(fmt, buf, nblen, num, digits, prec, sign);
	if (fmt->flags & ZERO && fmt->flags & SHARP)
		nblen -= put_before(fmt, buf, num, sign);
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (--fmt->width >= nblen && fmt->width > -1)
		ft_vec_add(&buf, &tmp);
	if (!(fmt->flags & LEFT))
		print_num(fmt, buf, nblen, num, digits, prec, sign);
	fmt->iter += 1;
	return (0);
}
