/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:33:45 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/03 18:39:55 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	*ft_vec_add(t_vec **vec, void *item)
{
	void			*tmp;
	t_vec			*p;

	if (!*vec)
		return (NULL);
	p = *vec;
	tmp = p->data;
	if (p->total >= p->capacity)
	{
		if (!(p->data = ft_memalloc(p->capacity * p->type * 2)))
		{
			ft_memdel(&(p->data));
			ft_memdel((void*)&p);
			return (NULL);
		}
		ft_memcpy(p->data, tmp, p->capacity * p->type);
		ft_memdel(&tmp);
		p->capacity *= 2;
	}
	ft_memcpy(p->data + (p->type * p->total), item, p->type);
	p->total++;
	return (p);
}
