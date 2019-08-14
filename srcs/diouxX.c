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

void			print_diouxX(t_fmt **fmt, va_list args, int fd)
{
	t_fmt		*tmp;
	int 		num;
	uint32_t 	unum;

	tmp = *fmt;

	/* if no modifiers INT is displayed  */
	if (tmp->type[0] == 'd') // TODO: create container for flags/precision/width
	{
		num = va_arg(args, int);
		ft_putnbr_fd(num, fd);
	}
//	if (tmp->type[0] == 'u')
//	{
//		unum = va_arg(args, void *);
//		printf("%u", num);
////		ft_putnbr(num);
//	}


}