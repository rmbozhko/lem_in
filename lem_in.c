#include "lem_in.h"

void		ft_errors_handling(int flag)
{
	if (flag)
		ft_putstr("ERROR\n");
	else
		ft_putstr(strerror(errno));
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

static	void		ft_help_ants(t_lemin *farmer, t_validation *valid, t_bonus *bonus)
{
	if (lem_in_validation(valid, farmer, bonus))
	{
		// ft_putstr(bonus->color_arr[bonus->cmap]);
		ft_putstr(valid->file);
		ft_putstr("\n");
		// ft_putstr("\033[0m");
		// ft_putstr(bonus->color_arr[bonus->cants]);
		ants_travel(farmer);
		// ft_putstr("\033[0m");
	}
	else
	{
		// ft_putstr(bonus->color_arr[bonus->cerror]);
		ft_errors_handling(1);
		// ft_putstr("\033[0m");
		// exit(0);
		return ;
	}
}

int					main(void)
{
	t_lemin 		farmer;
	t_validation	valid;
	t_bonus			bonus;

	bonus.cerror = 0;
	bonus.cants = 0;
	bonus.cmap = 0;
	valid.errors = 0;
	valid.file = ft_strdup("\0");
	valid.start_point = 0;
	valid.end_point = 0;
	valid.coords_arr = (char**)malloc(sizeof(char*) * 1000000);
	valid.coords_arr[0] = ft_strdup("\0");
	valid.coords_arr[1] = NULL;
	farmer.rooms_counter = 0;
	farmer.ants_num = -1;
	farmer.start_room = ft_strdup("\0");
	farmer.end_room = ft_strdup("\0");
	farmer.rooms_arr = (char**)malloc(sizeof(char*) * 1000000);
	farmer.rooms_arr[0] = ft_strdup("\0");
	farmer.rooms_arr[1] = NULL;
	farmer.adj_matrix = (char**)malloc(sizeof(char*));
	farmer.adj_matrix[0] = NULL;
	farmer.paths = (t_graph**)malloc(sizeof(t_graph**));
	// farmer.paths[0] = NULL;
	bonus.color_arr = ft_init_colors_arr();
	ft_help_ants(&farmer, &valid, &bonus);
	return (0);
}
