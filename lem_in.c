#include "lem_in.h"

void		ft_errors_handling(int flag, t_bonus *bonus)
{
	ft_putstr(bonus->color_arr[bonus->cerror]);
	if (flag)
		ft_putstr("ERROR");
	else
	{
		ft_putstr(strerror(errno));
		ft_putstr("\033[0m");
		exit(0);
	}
	ft_putstr("\033[0m\n");
}

int		ft_any_links(char **link, char c)
{
	int		counter;
	size_t		y;
	size_t		x;
	
	y = 0;
	x = 0;
	counter = 0;
	while (link[y])
	{
		x = 0;
		while (link[y][x])
		{
			if (link[y][x] == c)
				counter++;
			x++;
		}
		y++;
	}
	return (((counter % 2 == 0) && counter != 0) ? 1 : 0);
}

static	void		ft_handle_path(char *str)
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

static	void		ft_print_paths(t_graph **paths, t_bonus *bonus)
{
	size_t		i;

	i = 0;
	ft_putstr("\n\033[36;5;1;3mFound ways:\033[0m\n");
	ft_putstr(bonus->color_arr[bonus->cpaths]);
	while (paths[i])
	{
		ft_handle_path(paths[i++]->path_str);
	}
	ft_putstr((i > 1) ? "\033[0m\n" : "\033[0m");
}

static	void		ft_count_down(int end)
{
	int 		i;

	i = 0;
	while (i < end)
		ft_putnbr(i++);
}

static	void		ft_print_adj_matrix(char **arr)
{
	size_t		len;
	size_t		i;

	ft_putstr("\n\033[35;1mAdjecency matrix\033[0m\n");
	len = ft_bidlen(arr);
	i = 0;
	ft_putstr("\t|");
	ft_putstr("\033[34m");
	ft_count_down(len);
	ft_putstr("\033[0m");
	ft_putchar('\n');
	while (arr[i])
	{
		ft_putstr("\033[33m");
		ft_putnbr(i);
		ft_putstr("\t|");
		ft_putstr(arr[i++]);
		ft_putstr("\033[0m");
		ft_putchar('\n');
	}
}

// IF there is short path(2 rooms: start and end room) lem-in got fucked up :( 

static	void		ft_help_ants(t_lemin *farmer, t_validation *valid, t_bonus *bonus)
{
	if (lem_in_validation(valid, farmer, bonus, ft_strdup("\0")))
	{
		ft_putstr(bonus->color_arr[bonus->cmap]);
		ft_putstr(valid->file);
		ft_putstr("\033[0m\n");
		ft_print_adj_matrix(farmer->adj_matrix);
		dfs_iter(farmer, 0, 0, ft_strnew(0)); // determine whether to use dfs_iter here and raw dfs in validation or throw raw dfs away
		ft_print_paths(farmer->paths, bonus);
		ants_travel(farmer, bonus);
	}
	else
		ft_errors_handling(1, bonus);
}

static	void				ft_init_valid_farmer(t_validation *valid, t_lemin *farmer)
{
	valid->errors = 0;
	valid->file = ft_strdup("\0");
	valid->start_point = 0;
	valid->end_point = 0;
	farmer->rooms_counter = 0;
	farmer->ants_num = -1;
	farmer->start_room = ft_strdup("\0");
	farmer->end_room = ft_strdup("\0");
	farmer->rooms_arr = (char**)malloc(sizeof(char*) * 1000000);
	farmer->rooms_arr[0] = ft_strdup("\0");
	farmer->rooms_arr[1] = NULL;
	farmer->adj_matrix = (char**)malloc(sizeof(char*));
	farmer->adj_matrix[0] = NULL;
	farmer->paths = (t_graph**)malloc(sizeof(t_graph**));
	farmer->paths[0] = NULL;
}

int					main(void)
{
	t_lemin 		farmer;
	t_validation	valid;
	t_bonus			bonus;

	bonus.cerror = 0;
	bonus.cants = 0;
	bonus.cmap = 0;
	bonus.cpaths = 0;
	bonus.color_arr = ft_init_colors_arr();
	ft_init_valid_farmer(&valid, &farmer);
	ft_help_ants(&farmer, &valid, &bonus);
	return (0);
}
