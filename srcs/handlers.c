/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:34:11 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/17 16:34:12 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void 	handle_wrong_flags(t_fmt *fmt)
{
	int 	i;

	i = 0;
//	while (fmt->iter[i] != )
	printf("ITER: %s\n", fmt->iter);
	printf("TYPE %s\n", fmt->type);
}