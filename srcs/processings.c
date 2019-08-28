/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:21:55 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/21 20:21:57 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ft_printf.h>
#include "../incs/ft_printf.h"

int 		skip_atoi(const char *s)
{
	int 		i;

	i = 0;
	while (ft_isdigit(*s))
		i = i * 10 + *s++ - '0';
	return (i);
}

int			ft_isspecial(char ch)
{
	if (ch == '*' || ch == '.' || ch == '%')
		return (0);
	if (ch >= ' ' && ch <= '0')
		return (1);
	return (0);
}

int 			process_flags(t_fmt *fmt)
{
	fmt->flags = 0;
	while (*fmt->iter++ && ft_isspecial(*fmt->iter))
	{
		if (*fmt->iter == '-')
		{
			fmt->flags |= LEFT;
			continue;
		}
		if (*fmt->iter == '+')
		{
			fmt->flags |= PLUS;
			continue;
		}
		if (*fmt->iter == ' ')
		{
			fmt->flags |= SPACE;
			continue;
		}
		if (*fmt->iter == '#')
		{
			fmt->flags |= SHARP;
			continue;
		}
		if (*fmt->iter == '0')
		{
			fmt->flags |= ZERO;
			continue;
		}
	}
	return (0);
}

int				process_width(t_fmt *fmt, va_list args)
{
	fmt->width = -1;
	if (ft_isdigit(*fmt->iter))
	{
		fmt->width = skip_atoi(fmt->iter);
		fmt->iter += ft_nblen(fmt->width);
	}
	else if (*fmt->iter == '*')
	{
		++fmt->iter;
		fmt->width = va_arg(args, int);
	}
	return (0);
}

int				process_precision(t_fmt *fmt, va_list args)
{
	fmt->precision = -1;
	if (*fmt->iter == '.')
	{
		fmt->iter++;
		fmt->precision++;
	}
	if (ft_isdigit(*fmt->iter))
	{
		fmt->precision = skip_atoi(fmt->iter);
		fmt->iter += ft_nblen(fmt->precision);
	}
	else if (*fmt->iter == '*')
	{
		fmt->iter++;
		fmt->precision = va_arg(args, int);
	}
	return (0);
}

void 			process_lmodifier(t_fmt *fmt)
{
 	fmt->lmodifier = 0;
 	if (*fmt->iter == 'h')
 		fmt->lmodifier |= (*++fmt->iter == 'h') ? CHAR : SHORT;
 	else if (*fmt->iter == 'l')
 		fmt->lmodifier |= (*++fmt->iter == 'l') ? LONG_LONG : LONG;
 	else if (*fmt->iter == 'L')
 		fmt->lmodifier |= LLONG;
 	fmt->iter += fmt->lmodifier & CHAR || fmt->lmodifier & LONG_LONG ? 1 : 0;
}

void			process_base(t_fmt	*fmt)
{
	fmt->base = 10;
	if (*fmt->iter == 'o')
		fmt->base = 8;
	else if (*fmt->iter == 'x' || *fmt->iter == 'X')
	{
		if (*fmt->iter == 'X')
			fmt->flags |= CASE;
		fmt->base = 16;
	}
	else if (*fmt->iter == 'b')
		fmt->base = 2;
}
