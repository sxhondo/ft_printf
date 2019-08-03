/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:34:12 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/03 18:39:48 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	*ft_vec_init(size_t size, int type)
{
	t_vec	*vec;

	if (!size || !(vec = (t_vec*)malloc(sizeof(t_vec))))
		return (NULL);
	vec->capacity = size;
	vec->total = 0;
	vec->type = type;
	if (!(vec->data = ft_memalloc(size * type)))
	{
		free(vec);
		return (NULL);
	}
	return (vec);
}
