#include "lem_in.h"

void		ft_errors_handling(int flag)
{
	if (flag)
		ft_putstr("ERROR\n");
	else
		ft_putstr(strerror(errno));
	exit(0);
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
	return ((!(counter % 2)) ? 1 : 0);
}

static	void		ft_help_ants(t_lemin *farmer, t_validation *valid)
{
	int 		res;

	if ((res = lem_in_validation(valid, farmer)))
	{
		printf("Hura! Now we can print out everything we have read.");
		ft_putbidstr(valid->file);
	}
	else
	{
		printf("%d\n", res);
		ft_errors_handling(1);
	}
}

int					main(void)
{
	t_lemin 		farmer;
	t_validation	valid;
	
	valid.errors = 0;
	valid.file = ft_strdup("\0");
	valid.start_point = 0;
	valid.end_point = 0;
	farmer.ants_num = -1;
	farmer.start_room = ft_strdup("\0");
	farmer.end_room = ft_strdup("\0");
	farmer.rooms_arr = (char**)malloc(sizeof(char*) * 2);
	farmer.rooms_arr[0] = ft_strdup("\0");
	farmer.rooms_arr[1] = NULL;
	//farmer.adj_matrix = (char**)malloc(sizeof(char*));
	farmer.adj_matrix[0] = NULL;
	ft_help_ants(&farmer, &valid);
	return (0);
}
