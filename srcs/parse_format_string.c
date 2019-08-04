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

void			print_data(t_fmt **fmt)
{
	t_fmt		*curr;

	curr = *fmt;
	while (curr)
	{

		printf("\n--------arg----------\n");
		printf("FLAGS: \t\t\t[%d]\n", curr->flags);
		printf("WIDTH: \t\t\t[%d]\n", curr->width);
		printf("PRECISION: \t\t[%d]\n", curr->precision);
		printf("DATA_TYPE: \t\t[%c]\n", curr->type);
		printf("-------output---------\n");
		curr = curr->next;
	}
}

void			free_data(t_fmt **fmt)
{
	t_fmt		*curr;
	t_fmt		*next;

	curr = *fmt;
	while (curr)
	{
		next = curr->next;
		free (curr);
		curr = next;
	}
}

void			add_data_refresh_node(t_fmt **data, t_fmt *node)
{
	t_fmt		*tmp;
	t_fmt		*new;

	tmp = *data;
	new = ft_memalloc(sizeof(t_fmt));
	new->flags = node->flags;
	new->type = node->type;
	new->precision = node->precision;
	new->width = node->width;
	new->iter = node->iter;

//	node->flags = 0;
	node->width = 0;
	node->precision = -1;

	if (!*data)
		*data = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
}

static int 		skip_atoi(const char *s)
{
	int 		i;

	i = 0;
	while (ft_isdigit(*s))
		i = i * 10 + *s++ - '0';
	return (i);
}

static int		ft_isspecial(char ch)
{
	if (ch == '*' || ch == '.')
		return (0);
	if (ch >= ' ' && ch <= '0')
		return (1);
	return (0);
}

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