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

long double						roundd(long double dnum)
{
	long double					tmp;

	tmp = (uint64_t)(dnum * 100 + .5);
	return (tmp / 100);
}

char 							get_dsign(long double dnum, t_fmt *fmt)
{
	char 						sign;

	sign = 0;
	if (fmt->flags & PLUS)
		sign = dnum < 0 ? '-' : '+';
	else if (dnum < 0)
		sign = '-';
	else if (fmt->flags & SPACE)
		sign = ' ';
	return (sign);
}

long double						handle_exp(t_fmt *fmt, t_num *num,
															long double dnum)
{
	int		 					i;
	long double					save;

	save = dnum;
	i = 0;
	if ((*fmt->iter == 'e' || *fmt->iter == 'E') && dnum != 0)
		while ((uint64_t)save == 0 && --i)
			save *= 10;
	num->exp = i;
	return (save);
}

int								zero(t_fmt *fmt, unsigned char *p)
{
	int 	i;

	i = 0;
	*p++ = '0';
	i++;
	if (fmt->precision > 0 || fmt->flags & SHARP)
	{
		*p++ = '.';
		i++;
	}
	return (i);
}

void							put_exp(char *exp, t_num *num)
{
	char 						tmp[99];
	char 						*p_tmp;
	char 						*p_exp;

	p_exp = exp;
	if (num->exp < 0)
	{
		*p_exp++ = '-';
		num->exp = -num->exp;
	}
	else
		*p_exp++ = '+';
	if (num->exp < 10)
	{
		*p_exp++ = '0';
		*p_exp++ = (char)(num->exp + 0x30);
	}
	p_tmp = tmp;
	if (num->exp >= 10)
	{
		while (num->exp > 0)
		{
			*p_tmp++ = (char)(num->exp % 10 + '0');
			num->exp /= 10;
		}
		ft_strrev(tmp);
		ft_strcat(exp, tmp);
	}
}


unsigned int				print_dnum(t_fmt *fmt, t_vec *buf, t_num *num,
									   unsigned char digits[])
{
	unsigned char 			*p_dig;
	char					*p_exp;
	char					exp[99];
	unsigned int			nblen;
	unsigned char			e;

	fmt->flags &= ~ZERO;
	nblen = num->nblen;
	p_exp = exp;
	p_dig = digits;
	if (num->sign && num->nblen--)
		ft_vec_add(&buf, &num->sign);
	while (num->nblen--)
		ft_vec_add(&buf, &*p_dig++);
	if (*fmt->iter == 'e' || *fmt->iter == 'E')
	{
		e = fmt->flags & CASE ? 'E' : 'e';
		put_exp(p_exp, num);
		ft_vec_add(&buf, &e);
		while (*p_exp)
			ft_vec_add(&buf, &*p_exp++);
	}
	return (nblen);
}

int 							dtoa_exp(long double dnum, unsigned char *p,
												t_fmt *fmt, t_num *num)
{
	int 						i;
	uint64_t 					tmp;
	unsigned char				*ptr;
	int 						j;

	ptr = p;
	j = i = fmt->precision;
	GET_ABS(dnum);
	dnum = (uint64_t)dnum == 0 ? handle_exp(fmt, num, dnum) : dnum;
	while ((uint64_t)dnum > 0 && ++i)
		dnum /= 10;
	dnum *= 10;
	num->exp = num->exp < 0 ? num->exp : i - fmt->precision - 1;
	j += num->exp > 0 ? num->exp : 0;
	while (i-- > 0)
	{
		*p++ = (tmp = roundd(dnum)) | (unsigned)0x30;
		if (j == i && (fmt->precision > 0 || fmt->flags & SHARP))
		{
			*p++ = '.';
			if (i > fmt->precision)
				i -= i - fmt->precision;
		}
		dnum = dnum - (long double)tmp;
		dnum *= 10;
	}
	fmt->width -= 4;
	*p++ = '\0';
	return ((int)(p - ptr - 1));
}

int								dtoa(long double dnum, unsigned char digits[],
											t_fmt *fmt, t_num *num)
{
	int 						i;
	uint64_t 					tmp;
	unsigned char				*ptr;
	unsigned char				*p;

	p = ptr = digits;
	i = fmt->precision;
	GET_ABS(dnum);
	if ((uint64_t)dnum == 0)
		ptr += zero(fmt, ptr);
	while ((uint64_t)dnum > 0 && ++i)
		dnum /= 10;
	dnum *= 10;
	while (i-- > 0)
	{
		*ptr++ = (tmp = roundd(dnum)) | (unsigned)0x30;
		if (i == fmt->precision && (fmt->precision > 0 || fmt->flags & SHARP))
			*ptr++ = '.';
		dnum = dnum - (long double)tmp;
		dnum *= 10;
	}
	*ptr++ = '\0';
	return ((int)(ptr - p - 1));
}

void						get_dnum(long double dnum, t_fmt *fmt, t_vec *buf)
{
	unsigned char 			digits[100];
	char 					tmp;
	t_num					*num;

	num = ft_memalloc(sizeof(t_num));
	fmt->precision = fmt->precision == -1 ? 6 : fmt->precision;
	num->nblen += (*fmt->iter == 'e' || *fmt->iter == 'E') ?
			dtoa_exp(dnum, digits, fmt, num) : dtoa(dnum, digits, fmt, num);
	if ((num->sign = get_dsign(dnum, fmt)))
		num->nblen++;
	num->nblen = fmt->flags & LEFT ? print_dnum(fmt, buf, num, digits) :
			num->nblen;
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (--fmt->width >= num->nblen && fmt->width > -1)
		ft_vec_add(&buf, &tmp);
	if (!(fmt->flags & LEFT))
		print_dnum(fmt, buf, num, digits);
	fmt->iter += 1;
	free (num);
}
