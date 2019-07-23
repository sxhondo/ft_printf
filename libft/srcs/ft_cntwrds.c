/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:31:54 by sxhondo           #+#    #+#             */
/*   Updated: 2019/04/26 20:07:46 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cntwrds(const char *str, const char c)
{
	size_t	i;
	int		cntr;

	cntr = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		if (str[i] != c)
		{
			i++;
			cntr++;
		}
	}
	return (cntr);
}
