/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:55:42 by sxhondo           #+#    #+#             */
/*   Updated: 2019/09/15 17:55:43 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

int				skip_atoi(const char *s)
{
	int			i;

	i = 0;
	while (ft_isdigit(*s))
		i = i * 10 + *s++ - '0';
	return (i);
}

int				ft_isspecial(char ch)
{
	if (ch == '*' || ch == '.' || ch == '%')
		return (0);
	if (ch >= ' ' && ch <= '0')
		return (1);
	return (0);
}
