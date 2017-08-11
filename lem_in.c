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

int		ft_bidcount(char **link, char c)
{
	int		counter;
	size_t		y;
	
	y = 0;
	counter = 0;
	while (link[y])
		counter += ft_count_char(link[y++], c);
	return ((counter == 0) ? (1) : (counter));
}

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

void		ft_print_paths(t_graph **paths, t_bonus *bonus, int flag)
{
	size_t		i;

	i = 0;
	ft_putstr("\n\033[36;5;1;3mFound ways:\033[0m\n");
	ft_putstr(bonus->color_arr[bonus->cpaths]);
	while (paths[i])
	{
		ft_handle_path(paths[i]->path_str);
		i++;
	}
	ft_putstr("\033[0m\n");
}	

static	void		ft_print_adj_matrix(char **arr)
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

static	size_t		ft_len(void	**resource)
{
	size_t		i;

	i = 0;
	while (resource[i])
		i++;
	return (i);
}

static	void		ft_help_ants(t_lemin *farmer, t_validation *valid, t_bonus *bonus)
{
	char 		*line;

	if (lem_in_validation(valid, farmer, bonus, ft_strnew(0)))
	{
		ft_putstr(bonus->color_arr[bonus->cmap]);
		ft_putstr(valid->file);
		ft_putstr("\033[0m");
		ft_print_adj_matrix(farmer->adj_matrix);
		dfs_iter(farmer, 0, 0, ft_strnew(0)); // determine whether to use dfs_iter here and raw dfs in validation or throw raw dfs away
		ft_print_paths(farmer->paths, bonus, 1);
		ants_travel(farmer, bonus);
	}
	else
	{
		ft_errors_handling(1, bonus);
	}
	// while (1);
}

static	void				ft_init_valid_farmer(t_validation *valid, t_lemin *farmer)
{
	valid->errors = 0;
	valid->file = ft_strnew(0);
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
	farmer->paths = (t_graph**)malloc(sizeof(t_graph**) * 1000000);
	farmer->paths[0] = NULL;
	farmer->x_coords = (char**)malloc(sizeof(char*) * 1000000);
	farmer->y_coords = (char**)malloc(sizeof(char*) * 1000000);
	farmer->x_coords[0] = NULL;
	farmer->y_coords[0] = NULL;
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
	// printf("HERE we are!\n");
	while (1);
	return (0);
}
