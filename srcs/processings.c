/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:15:47 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/04 17:15:50 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

#define ZEROPAD	1		/* pad with zero */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	64		/* 0x */

int 			process_flags(t_fmt *node)
{
	while (*node->iter++ && ft_isspecial(*node->iter))
	{
		if (*node->iter == '-')
		{
			node->flags |= LEFT;
			continue;
		}
		if (*node->iter == '+')
		{
			node->flags |= PLUS;
			continue;
		}
		if (*node->iter == ' ')
		{
			node->flags |= SPACE;
			continue;
		}
		if (*node->iter == '#')
		{
			node->flags |= SPECIAL;
			continue;
		}
		if (*node->iter == '0')
		{
			node->flags |= ZEROPAD;
			continue;
		}
	}
	return (0);
}

unsigned int		process_width(t_fmt *node, va_list args)
{
	if (ft_isdigit(*node->iter))
	{
		node->width = skip_atoi(node->iter);
		node->iter += ft_nblen(node->width);
	}
	else if (*node->iter == '*')
	{
		++node->iter;
		node->width = va_arg(args, int);
	}
	return (0);
}

unsigned int		process_precision(t_fmt *node, va_list args)
{
	if (*node->iter == '.')
		node->iter++;
	if (ft_isdigit(*node->iter))
	{
		node->precision = skip_atoi(node->iter);
		node->iter += ft_nblen(node->precision);
	}
	else if (*node->iter == '*')
	{
		node->iter++;
		node->precision = va_arg(args, int);
	}
	return (0);
}

void					process_datatype(t_fmt *fmt, va_list args)
{
	int 	i;
	char 	str[3];

	i = 0;
	while (*fmt->iter)
	{
		if (i >= 3)
			;
		str[i] = *fmt->iter;
		if (*fmt->iter == 'c' || *fmt->iter == 's' || *fmt->iter == 'p'
			|| *fmt->iter == 'd' || *fmt->iter == 'i' || *fmt->iter == 'o'
			|| *fmt->iter == 'u' || *fmt->iter == 'x' || *fmt->iter == 'X')
			break;
		fmt->iter++;
		i++;
	}
	fmt->iter++; // kostyl sorry
	str[i + 1] = '\0';
	fmt->type = ft_strdup(str);
}