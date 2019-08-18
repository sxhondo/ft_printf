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

int 			process_flags(t_fmt *node)
{
	node->flags = 0;
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
			node->flags |= ZERO;
			continue;
		}
	}
	return (0);
}

int				process_width(t_fmt *node, va_list args)
{
	node->width = -1;
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

int				process_precision(t_fmt *node, va_list args)
{
	node->precision = -1;
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

void			process_conversion_qualifier(t_fmt	*node, va_list args)
{
	node->qualifier = -1;
	if (*node->iter == 'h' || *node->iter == 'l' || *node->iter == 'L')
	{
		node->qualifier = *node->iter;
		node->iter++;
		if (*node->iter == 'h')
		{
			node->qualifier *= 2;
			node->iter++;
		}
	}
}