/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:34:01 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/14 18:34:02 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_diu(t_fmt **fmt, va_list args, int fd)
{
	unsigned int	un;
	int 			n;

	if (search_spec((*fmt)->type, 'd') || search_spec((*fmt)->type, 'i'))
	{
		n = va_arg(args, int);
		ft_putnbr_fd(n, fd);
	}
	if (search_spec((*fmt)->type, 'u'))
	{
		un = va_arg(args, unsigned int);
		put_uns_number((unsigned int)un, fd);
	}
}

char 				*print_oxX(t_fmt **fmt, va_list args, int fd)
{
	int 		i;
	t_fmt		*tmp;
	int		  	*nb;
	char 		*number;

	i = 0;
	tmp = *fmt;
	nb = va_arg(args, void *);
	if (search_spec(tmp->type, 'o'))
	{
		number = base_any(nb, 8);
		ft_putstr(number);
		ft_strdel(&number);
	}
	else if (search_spec(tmp->type, 'x') || search_spec(tmp->type, 'X'))
	{
		number = base_any(nb, 16);
		if (search_spec(tmp->type, 'X'))
			while (number[i++])
				number[i] = ft_toupper(number[i]);
		ft_putstr(number);
		ft_strdel(&number);
	}
	return (NULL);

}
