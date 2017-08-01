#include "lem_in.h"

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

int 			ft_check_coords(char **arr, char **coords)
{
	int 		counter;
	size_t		i;
	char		**temp;

	i = 0;
	counter = 0;
	while (arr[i] != NULL)
	{
		temp = ft_strsplit(arr[i], ' ');
		if (ft_strcmp(coords[1], temp[1]) == 0 && ft_strcmp(coords[2], temp[2]) == 0)
		{
			counter = 1;
		}
		i++;
		// free(temp[2]);
		// free(temp[1]);
		// free(temp[0]);
		// free(temp);
	}
	// free(coords[1]);
	// free(coords[0]);
	// free(coords);
	return ((counter) ? 1 : 0);
}

int 	ft_push_new_rooms(char **temp, t_lemin *farmer, int flag, t_validation *valid)
{
	size_t		i;
	int 		counter;

	counter = 1;
	if (ft_is_numeric(temp[1]) && ft_is_numeric(temp[2]))
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
		{
			farmer->rooms_arr[i] = ft_strdup(temp[0]);
			farmer->rooms_arr[i + 1] = NULL;
		}
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
			if (!ft_push_new_rooms(ft_strsplit(line, ' '), farmer, 0, valid))
				return (ft_strsplit(line, ' ')[0]);
			return (NULL);
		}
		else
			return (NULL);
	}
	return (NULL);
}

static	int 	ft_hash_case(char *line, t_validation *valid, t_lemin *farmer, t_bonus *bonus)
{
	if (SNG_HASH_CMNT && (ft_strstr(line, "#start") || ft_strstr(line, "#end") || ft_strstr(line, "#cpaths_")
  || ft_strstr(line, "#cmap_") || ft_strstr(line, "#cants_") || ft_strstr(line, "#cerror_") ))
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
	   	else if (ft_strstr(line, "#cmap_") || ft_strstr(line, "#cants_") || ft_strstr(line, "#cerror_") || ft_strstr(line, "#cpaths_"))
	      return (ft_set_colors(bonus, line));
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
		temp[y] = ft_strnew(sizeof(char) *  size + 1);
		ft_memset(temp[y], (int)c, size);
		temp[y++][size + 1] = '\0';
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

int				lem_in_validation(t_validation *valid, t_lemin *farmer, t_bonus *bonus, char *line)
{
	int 		status;

	while ((status = get_next_line(0, &line, valid)) > 0)
	{
		if (ft_is_numeric(line))
			valid->errors += (farmer->ants_num == -1) ? ft_validate_ants_num(line, farmer) : 1;
		else if (line[0] == '#')
			valid->errors += ft_hash_case(line + 1, valid, farmer, bonus);
		else if (ft_words_count(line, ' ') == 3)
			valid->errors += ft_push_new_rooms(ft_strsplit(line, ' '), farmer, 1, valid);
		else if (ft_words_count(line, '-') == 2 && ENTRY_ROOMS)
			valid->errors += ft_find_rooms(ft_strsplit(line, '-'), farmer);
		else
		{
			if (NO_ERRORS)
			{
				ft_errors_handling(1, bonus);
				break ;
			}
			valid->errors += 1;
		}
		if (valid->errors != 0)
			return (0);
	}
	return ((NO_ERRORS) ? dfs_iter(farmer, 0, 0, ft_strnew(0)) : 0);
}
