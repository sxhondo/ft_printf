/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:33:01 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/03 18:40:02 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	*ft_vec_resize(t_vec **vec)
{
	void	*data;

	data = (*vec)->data;
	if (!((*vec)->data = ft_memalloc((*vec)->total * (*vec)->type)))
		return (NULL);
	(*vec)->data = ft_memcpy((*vec)->data, data, (*vec)->total * (*vec)->type);
	(*vec)->capacity = (*vec)->total;
	free(data);
	return (*vec);
}
