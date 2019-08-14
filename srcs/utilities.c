#include <ft_printf.h>

int 		skip_atoi(const char *s)
{
	int 		i;

	i = 0;
	while (ft_isdigit(*s))
		i = i * 10 + *s++ - '0';
	return (i);
}

int			ft_isspecial(char ch)
{
	if (ch == '*' || ch == '.')
		return (0);
	if (ch >= ' ' && ch <= '0')
		return (1);
	return (0);
}

void			add_data_refresh_node(t_fmt **data, t_fmt *node)
{
	t_fmt		*tmp;
	t_fmt		*new;

	tmp = *data;
	new = ft_memalloc(sizeof(t_fmt));
	new->flags = node->flags;
	new->type = ft_strdup(node->type);
	new->precision = node->precision;
	new->width = node->width;
	new->iter = node->iter;

	node->width = 0;
	node->precision = -1;
	ft_strdel(&node->type);
	if (!*data)
		*data = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
}

void			free_data(t_fmt **fmt)
{
	t_fmt		*curr;
	t_fmt		*next;

	curr = *fmt;
	while (curr)
	{
		next = curr->next;
		ft_strdel(&curr->type);
		free (curr);
		curr = next;
	}
}


void			print_collected_data(t_fmt **fmt)
{
	t_fmt		*curr;

	curr = *fmt;
	while (curr)
	{

		printf("\n--------arg----------\n");
		printf("FLAGS: \t\t\t[%d]\n", curr->flags);
		printf("WIDTH: \t\t\t[%d]\n", curr->width);
		printf("PRECISION: \t\t[%d]\n", curr->precision);
		printf("DATA_TYPE: \t\t[%s]\n", curr->type);
		printf("-------output---------\n");
		curr = curr->next;
	}
}
