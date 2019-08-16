
#include "ft_printf.h"

char 					*base_any(void *p, int base)
{
	uintmax_t 	nb;
	uintmax_t 	minus;
	uintmax_t 	next;
	uintmax_t 	save;
	t_list				*node;
	t_list				*row;

	row = NULL;
	nb = (unsigned long long)p;
	save = base;

	while (save > (base - 1))
	{
		next = nb / base;
		save = next * base;
		minus = nb - save;
		nb = next;
		node = ft_lstnew(&minus, sizeof(unsigned long long));
		ft_lstadd(&row, node);
	}
	if (base == 2)
		return (parse_bin_table(&row));
	if (base == 8)
		return (parse_oct_table(&row));
	if (base == 16)
		return (parse_hex_table(&row));

}

char 			*parse_bin_table(t_list **row)
{
	t_list	*tmp;

	tmp = *row;
	while (tmp)
	{
		ft_putnbr(*(int *)tmp->content);
		tmp = tmp->next;
	}
}

char 			*parse_hex_table(t_list **row)
{

	char 		table[] = "0123456789abcdef";
	char 		*str;
	int 		i;
	t_list		*next;
	t_list		*curr;

	i = 0;
	curr = *row;
	str = ft_strnew(ft_lstlen(&curr));
	while (curr)
	{
		next = curr->next;
		str[i] = table[*(int *)curr->content];
		ft_memdel(&curr->content);
		free(curr);
		curr = next;
		i++;
	}
	return (str);
}

char 			*parse_oct_table(t_list **row)
{
	int 	i;
	char 	*str;
	t_list	*next;
	t_list	*curr;

	i = 0;
	curr = *row;
	str = ft_strnew(ft_lstlen(&curr));
	while (curr)
	{
		next = curr->next;
		str[i] = small_itoa(*(int *)curr->content);
		ft_memdel(&curr->content);
		free (curr);
		curr = next;
		i++;
	}
	return (str);
}