#include "lem_in.h"

void		ft_errors_handling(int flag, t_bonus *bonus)
{
	ft_putstr(bonus->color_arr[bonus->cerror]);
	if (flag)
	{
		ft_putstr("ERROR");
	}
	else
	{
		ft_putstr(strerror(errno));
		ft_putstr("\033[0m");
		exit(0);
	}
	ft_putstr("\033[0m\n");
}

int		ft_bidcharcount(char **link, char c)
{
	int		counter;
	size_t		y;
	
	y = 0;
	counter = 0;
	while (link[y])
		counter += ft_count_char(link[y++], c);
	return ((counter == 0) ? (1) : (counter));
}

static	void		ft_help_ants(t_lemin *farmer, t_valid *valid, t_bonus *bonus)
{
	if (validation(valid, farmer, bonus, ft_strnew(0)))
	{
		ft_putstr(bonus->color_arr[bonus->cmap]);
		ft_putstr(valid->file);
		ft_putstr("\033[0m");
		ft_print_adj_matrix(farmer->adj_matrix);
		ft_print_paths(farmer->paths, bonus);
		ants_travel(farmer, bonus, 0);
	}
	else
		ft_errors_handling(1, bonus);
}

static	void				ft_init_valid_farmer(t_valid *valid, t_lemin *farmer)
{
	valid->errors = 0;
	valid->file = ft_strnew(0);
	valid->start = 0;
	valid->end = 0;
	farmer->rooms_counter = 0;
	farmer->ants_num = -1;
	farmer->start = ft_strdup("\0");
	farmer->end = ft_strdup("\0");
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
	t_valid	valid;
	t_bonus			bonus;

	bonus.cerror = 0;
	bonus.cants = 0;
	bonus.cmap = 0;
	bonus.cpaths = 0;
	bonus.color_arr = ft_init_colors_arr();
	ft_init_valid_farmer(&valid, &farmer);
	ft_help_ants(&farmer, &valid, &bonus);

	/// I HAVE CHANGED ANTS_NUM (FARMER) FROM SIZE_T TO INT! CHECK WHETHER WOULD IT BECOME A PROBLEM SOMEWHERE?
	// printf("HERE we are!\n");
	// while (1);
	return (0);
}
