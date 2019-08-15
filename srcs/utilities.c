#include <ft_printf.h>

int			search_spec(char *str, char ch)
{
	int 	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

char 		small_itoa(int nb)
{
	return (nb % 10 + '0');
}

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

void			refresh_node(t_fmt *node)
{
	node->width = 0;
	node->precision = -1;
	ft_strdel(&node->type);
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
