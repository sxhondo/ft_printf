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

char 				*print_oxX(t_fmt **fmt, va_list args, int fd)
{
	int 		i;
	t_fmt		*tmp;
	uint64_t  	*nb;
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
	else if (search_spec(tmp->type, 'x'))
	{
		number = base_any(nb, 16);
		ft_putstr(number);
		ft_strdel(&number);
	}
	else if (search_spec(tmp->type, 'X'))
	{
		number = base_any(nb, 16);
		while (number[i++])
			number[i] = ft_toupper(number[i]);
		ft_putstr(number);
		ft_strdel(&number);
	}
	return (NULL);

}

void			print_di(t_fmt **fmt, va_list args, int fd)
{
	int 		num;

	num = va_arg(args, int);
	ft_putnbr_fd(num, fd);
}

void			print_u(t_fmt **fmt, va_list args, int fd)
{
	int 	n;
	unsigned int un;

	n = va_arg(args, int);
	un = n;
	ft_putnbr(un);
//	printf("SIGNED NUMBER: %d\n", num);
}