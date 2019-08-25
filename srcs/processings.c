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

#include <ft_printf.h>

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
			node->flags |= SHARP;
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
	{
		node->iter++;
		node->precision++;
	}
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

	/* expirimental */
//#define ZERO	(unsigned)1			/* filling with zeroes */
//#define PLUS	(unsigned)4			/* show sign of number */
//#define SPACE	(unsigned)8			/* space if plus */
//#define LEFT	(unsigned)16		/* left alignment */
//#define CASE	(unsigned)32		/* is it 'x' or 'X' (0 if lowcase, 1 if uppercase */
//#define SHARP	(unsigned)64		/* alternative form (0 for %o, 0x for %x) */

// void 			process_lmodifier(t_fmt *fmt)
// {
// 	fmt->lmodifier = 0;
// 	if (fmt->iter == 'h')
// 		fmt->lmodifier |= (fmt->iter++ == 'h') ? 1 : 4; //'h' OR 'hh'
// 	else if (fmt->iter == 'l')
// 		fmt->lmodifier |= (fmt->iter++ == 'l') ? 8 : 16; // 'l' OR 'll'
// 	else if (fmt->Iter == 'L')
// 		fmt->lmofidier |= 32; // 'L'
// }

void			process_length_modifier(t_fmt	*node, va_list args)
{
	node->lmodifier = -1;
	if (*node->iter == 'h' || *node->iter == 'l' || *node->iter == 'L')
	{
		node->lmodifier = *node->iter;
		node->iter++;
		if (*node->iter == 'h' || *node->iter == 'l')
		{
			node->lmodifier *= 2;
			node->iter++;
		}
	}
}

void			process_base(t_fmt	*node, va_list args)
{
	node->base = 10;
	if (*node->iter == 'o')
		node->base = 8;
	else if (*node->iter == 'x' || *node->iter == 'X')
	{
		if (*node->iter == 'X')
			node->flags |= CASE;
		node->base = 16;
	}
	else if (*node->iter == 'b')
		node->base = 2;
}
