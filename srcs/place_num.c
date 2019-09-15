/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:59:55 by sxhondo           #+#    #+#             */
/*   Updated: 2019/09/15 16:59:56 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ft_printf.h>
#include "../incs/ft_printf.h"

unsigned					put_precision(t_fmt *fmt, t_vec *buf, t_num *params,
											char f)
{
	unsigned int			i;
	char					sp;

	i = 0;
	sp = ' ';
	if (fmt->precision == 0 && params->num == 0)
	{
		if (fmt->width > -1)
			ft_vec_add(&buf, &sp);
		if (fmt->base & (unsigned)8 && fmt->flags & SHARP)
			i--;
		i++;
	}
	while (params->prec--)
		ft_vec_add(&buf, &f);
	return (i);
}

int							count_precision(t_fmt *fmt, unsigned nblen,
														int64_t num, char sign)
{
	int						prec;

	prec = 0;
	if (fmt->precision > -1)
	{
		if (sign && fmt->precision > nblen && fmt->width--)
			prec++;
		if (fmt->precision > -1)
		{
			fmt->flags &= ~ZERO;
			if (sign && num >= 0)
				fmt->precision++;
			while (fmt->precision > nblen && ++prec && --fmt->precision)
				fmt->width--;
		}
		if (fmt->flags & SHARP && num != 0)
		{
			if (fmt->base == 16)
				prec += 2;
		}
	}
	return (prec);
}

int							put_before(t_fmt *fmt, t_vec *buf, char sign)
{
	int						len;
	char					*p_form;

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

unsigned					print_num(t_fmt *fmt, t_vec *buf, t_num *params,
																	char *dig)
{
	char					*p_form;
	unsigned int			nblen;

	nblen = params->nblen;
	p_form = "0x";
	if (fmt->flags & ZERO)
		fmt->flags &= ~ZERO;
	if (fmt->flags & CASE)
	{
		p_form = "0X";
		apply_upcase(dig);
	}
	if (fmt->flags & SHARP && fmt->base != 10 && params->num != 0)
	{
		nblen--;
		ft_vec_add(&buf, &p_form[0]);
		if (fmt->base & (unsigned)16 && nblen--)
			ft_vec_add(&buf, &p_form[1]);
	}
	if (params->sign && --nblen)
		ft_vec_add(&buf, &params->sign);
	nblen -= put_precision(fmt, buf, params, p_form[0]);
	while (nblen--)
		ft_vec_add(&buf, &*dig++);
	return (params->nblen);
}

void						get_num(int64_t num, t_fmt *fmt,
														t_vec *buf, int sig)
{
	char					digits[60];
	t_num					*params;
	char					tmp;

	params = ft_memalloc(sizeof(t_num));
	params->num = num;
	params->nblen = (unsigned int)itoa_base(num, digits, fmt->base, sig);
	params->nblen += recount_nblen(fmt, num);
	handle_negative(fmt, num);
	if (!(params->sign = get_sign(fmt, buf, num, sig)) && fmt->base == 10)
		params->nblen--;
	params->prec = count_precision(fmt, params->nblen, num, params->sign);
	if (fmt->flags & LEFT)
		params->nblen = print_num(fmt, buf, params, digits);
	if (fmt->flags & ZERO && fmt->flags & SHARP)
		params->nblen -= put_before(fmt, buf, params->sign);
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (--fmt->width >= params->nblen && fmt->width > -1)
		ft_vec_add(&buf, &tmp);
	if (!(fmt->flags & LEFT))
		print_num(fmt, buf, params, digits);
	free(params);
}
