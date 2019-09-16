/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_bonuses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:23:37 by sxhondo           #+#    #+#             */
/*   Updated: 2019/09/16 19:23:38 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static void				put_in_buf(t_fmt *fmt, t_vec *buf, const char *str,
															unsigned lcpy)
{
	char				ast;

	ast = '*';
	fmt->flags &= ~ZERO;
	while (*str && lcpy--)
	{
		if (*str < 33 || *str > 126)
			ft_vec_add(&buf, &ast);
		else
			ft_vec_add(&buf, (void *)&*str);
		str++;
	}
}

void					print_non_printable(t_fmt *fmt, va_list args,
																	t_vec *buf)
{
	unsigned		len;
	unsigned		lcpy;
	const char		*str;
	char			tmp;

	str = va_arg(args, const char *);
	len = ft_strnlen(str, fmt->precision);
	lcpy = len;
	if (fmt->flags & LEFT)
		put_in_buf(fmt, buf, str, lcpy);
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (--fmt->width >= len)
		ft_vec_add(&buf, &tmp);
	if (!(fmt->flags & LEFT))
		put_in_buf(fmt, buf, str, len);
	fmt->iter += 1;
}
