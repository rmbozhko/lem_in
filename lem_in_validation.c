#include "lem_in.h"

void		ft_putbidstr(char **temp)
{
	size_t		y;
	
	y  = 0;
	while (temp[y])
	{
		ft_putstr(temp[y]);
		ft_putstr("\n");
		y++;
	}
		
}

static	int 	ft_str_num(char *str)
{
	int 		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

size_t	ft_bidlen(char **temp)
{
	size_t		i;
	
	i = 0;
	while (temp[i])
		i++;
	return (i);
}

int	ft_get_rooms_coord(char *room, char **temp)
{
	size_t		i;
	
	i = 0;

	while (temp[i])
	{
		if (ft_strcmp(room, temp[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static	int 	ft_push_new_rooms(char **temp, t_lemin *farmer, int flag)
{
	size_t		i;
	int 		counter;

	counter = 1;
	if (ft_str_num(temp[1]) && ft_str_num(temp[2]))
	{
		counter = 0;
		i = 1;
		while (farmer->rooms_arr[i] != NULL)
		{
			if (CHECKING_ROOMS(0) == 0)
				return (1);
			i++;
		}
		if (flag == 1)
			counter = (!(farmer->rooms_arr[i] = ft_strdup(temp[0]))) ? 1 : 0;
		if (flag == 1)
			farmer->rooms_arr[i + 1] = NULL;
	}
	free(temp[2]);
	free(temp[1]);
	free(temp[0]);
	free(temp);
	return ((counter) ? 1 : 0);
}

static	char	*get_in_out_rooms(t_lemin *farmer, t_validation *valid)
{
	char		*line;

	line = ft_strdup("\0");
	while (get_next_line(0, &line, valid))
	{
		if (line[0] == '#')
			continue ;
		else if (line[0] != '#' && (ft_words_count(line, ' ') == 3))
		{
			if (!ft_push_new_rooms(ft_strsplit(line, ' '), farmer, 0))
				return (ft_strsplit(line, ' ')[0]);
			return (NULL);
		}
		else
		{
			return (NULL);
		}
	}
	return (NULL);
}

static	int 	ft_hash_case(char *line, t_validation *valid, t_lemin *farmer)
{
	if (SNG_HASH_CMNT && (ft_strstr(line, "start") || ft_strstr(line, "end")))
	{
		if (ft_strcmp(line, "#start") == 0)
		{
			valid->start_point += 1;
			return (((farmer->start_room = get_in_out_rooms(farmer, valid)) == NULL) ? (1) : (0));
		}
		else if (ft_strcmp(line, "#end") == 0)
		{
			valid->end_point += 1;
			return (((farmer->end_room = get_in_out_rooms(farmer, valid)) == NULL) ? (1) : (0));
		}
		return (1);
	}
	return (0);
}

static	char	**ft_create_adjecent_matrix(size_t size, char c)
{
	char		**temp;
	size_t		x;
	size_t		y;
	
	y = 0;
	temp = (char**)malloc(sizeof(char*) * size + 1);
	while (y < size)
	{
		temp[y] = (char*)malloc(sizeof(char) * size + 1);
		x = 0;
		while (x <  size)
		{
			temp[y][x] = c;
			x++;
		}
		temp[y][x] = '\0';
		y++;
	}
	temp[y] = NULL;
	return (temp);
}

static	int	ft_push_link(char *link1, char *link2, t_lemin *farmer)
{
	int		x;
	int		y;

	x = ft_get_rooms_coord(link1, farmer->rooms_arr);
	y = ft_get_rooms_coord(link2, farmer->rooms_arr);
	farmer->adj_matrix[x][y] = '1';
	farmer->adj_matrix[y][x] = '1';
	return (0);
}

static	int		ft_initialize_adj_matrix(t_lemin *farmer)
{
	free(farmer->rooms_arr[0]);
	farmer->rooms_arr[0] = ft_strdup(farmer->start_room);
	farmer->rooms_arr[ft_bidlen(farmer->rooms_arr)] = ft_strdup(farmer->end_room);
	farmer->rooms_arr[ft_bidlen(farmer->rooms_arr) + 1] = NULL;
	free(farmer->adj_matrix);
	farmer->adj_matrix = ft_create_adjecent_matrix(ft_bidlen(farmer->rooms_arr), '0');
	return (0);
}

static	int 	ft_find_rooms(char **temp, t_lemin *farmer)
{
	size_t		i;
	int 		counter;

	i = 0;
	counter = 0;
	counter += ((ft_bidlen(farmer->adj_matrix)) == 0) ? ft_initialize_adj_matrix(farmer) : 0;
	while (farmer->rooms_arr[i])
	{
		if (!CHECKING_ROOMS(0) || !CHECKING_ROOMS(1))
			counter++;
		i++;
	}
	counter += (counter == 2) ? ft_push_link(temp[0], temp[1], farmer) : 0;
	free(temp[1]);
	free(temp[0]);
	free(temp);
	return ((counter == 2) ?  (0) : (1));
}

static	int 	ft_validate_ants_num(char *line, t_lemin *farmer)
{
	int		temp;

	temp = ft_atoi(line);
	if (temp >= 1 && temp <= 2147483647)
	{
		farmer->ants_num = temp;
		return (0);
	}
	return (1);
}

int				lem_in_validation(t_validation *valid, t_lemin *farmer)
{
	char		*line;
	int 		status;

	line = ft_strdup("\0");
	while ((status = get_next_line(0, &line, valid)) > 0)
	{
		if (ft_str_num(line))
		{
			// printf("OLA!\n");
			valid->errors += (farmer->ants_num != -1) ? 1 : ft_validate_ants_num(line, farmer);
		}
		else if (line[0] == '#')
		{
			// printf("HEY!\n");
			valid->errors += ft_hash_case(line + 1, valid, farmer);
			// printf("%d\n", valid->errors);
		}
		else if (ft_words_count(line, ' ') == 3)
		{
			// printf("WTF?!\n");
			valid->errors += ft_push_new_rooms(ft_strsplit(line, ' '), farmer, 1);
		}
		else if (ft_words_count(line, '-') == 2 && !NO_ENTRY_ROOMS)
		{
			// printf("GRINGO!\n");
			valid->errors += ft_find_rooms(ft_strsplit(line, '-'), farmer);
		}
		else
		{
			// printf("FUCK OFF!\n");
			valid->errors += 1;
		}
		if (valid->errors != 0)
		{
			// printf("HERE!\n");
			return (0);
		}
	}
	return ((ERRORS) ? 0 : dfs_iter(farmer, 0, 0));
}
