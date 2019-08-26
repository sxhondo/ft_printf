/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:08:28 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/16 15:08:29 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ft_printf.h>
#include "../incs/ft_printf.h"

void			print_collected_data(t_fmt **fmt)
{
	t_fmt		*f;

	f = *fmt;
	printf("\n--------FORMAT----------\n");
	printf("FLAGS: \t\t\t\t[%d]\n", f->flags);
	printf("WIDTH: \t\t\t\t[%d]\n", f->width);
	printf("PRECISION: \t\t\t[%d]\n", f->precision);
	printf("L_MODIFIER: \t\t[%d] or [%c]\n", f->lmodifier, f->lmodifier);
	printf("BASE: \t\t\t\t[%u]\n", f->base);
	printf("ITERATOR: \t\t\t[%s]\n", f->iter);
	printf("------------------------\n");
}
