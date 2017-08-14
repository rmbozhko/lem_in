#include "lem_in.h"

void		ft_handle_path(char *str)
{
	size_t		i;

	i = 0;
	ft_putchar('[');
	while (str[i])
	{
		if (str[i] > 33 && str[i] < 127)
			ft_putchar(str[i]);
		else if (str[i] == ' ')
			ft_putstr("]-[");
		i++;
	}
	ft_putstr("]\n");
}

void		ft_print_paths(t_graph **paths, t_bonus *bonus)
{
	size_t		i;

	i = 0;
	ft_putstr("\n\033[36;1;4;5mFound ways:\033[0m\n");
	ft_putstr(bonus->color_arr[bonus->cpaths]);
	while (paths[i])
	{
		ft_handle_path(paths[i]->path_str);
		i++;
	}
	ft_putstr("\033[0m\n");
}	

void		ft_print_adj_matrix(char **arr)
{
	size_t		i;

	i = 0;
	ft_putstr("\n\033[35;1mAdjecency matrix\033[0m\n\t\033[34m|");
	ft_countdown(ft_bidlen(arr));
	ft_putstr("\033[0m\n");
	while (arr[i])
	{
		ft_putstr("\033[33m");
		ft_putnbr(i);
		ft_putstr("\t|");
		ft_putstr(arr[i++]);
		ft_putstr("\033[0m\n");
	}
}