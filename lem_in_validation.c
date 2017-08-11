#include "lem_in.h"

int 		ft_get_rooms_coord(char *room, char **temp)
{
	int		i;
	
	i = 0;
	while (temp[i])
	{
		if (ft_strcmp(room, temp[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int 		ft_check_coords(char *x_coord, char *y_coord, t_lemin *farmer)
{
	size_t			i;

	i = 0;
	while (farmer->x_coords[i] && farmer->y_coords[i])
	{
		if (ft_strcmp(x_coord, farmer->x_coords[i]) == 0 &&
			ft_strcmp(y_coord, farmer->y_coords[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

// size_t		ft_update_arr(char **arr)
// {
// 	size_t		i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

void		ft_add_room_coords(char *elem, t_lemin *farmer, int i)
{
	int 		temp;

	if (i == -2)
	{
		// temp = ft_update_arr(farmer->x_coords);
		// farmer->x_coords[temp] = ft_strdup(elem);
		// farmer->x_coords[temp + 1] = NULL;
		farmer->x_coords[ft_bidlen(farmer->x_coords)] = ft_strdup(elem);
		farmer->x_coords[ft_bidlen(farmer->x_coords) + 1] = NULL;
	}
	else if (i == -1)
	{
		// temp = ft_update_arr(farmer->y_coords);
		// farmer->y_coords[temp] = ft_strdup(elem);
		// farmer->y_coords[temp + 1] = NULL;
		farmer->y_coords[ft_bidlen(farmer->y_coords)] = ft_strdup(elem);
		farmer->y_coords[ft_bidlen(farmer->y_coords) + 1] = NULL;
	}
	else
	{
		farmer->rooms_arr[i] = ft_strdup(elem);
		farmer->rooms_arr[i + 1] = NULL;
	}
}

int 		ft_push_new_rooms(char **temp, t_lemin *farmer, int flag, t_validation *valid)
{
	size_t		i;
	int 		counter;

	counter = 1;
	// printf("temp[1]:%s|temp[2]:%s|temp[0]%s\n", temp[1], temp[2], temp[0]);
	if (ft_is_numeric(temp[1]) && ft_is_numeric(temp[2]) && (temp[0][0] != '#' && temp[0][0] != 'L'))
	{
		counter = 0;
		i = 0;
		if (ft_strcmp(temp[0], farmer->start_room) == 0 || ft_strcmp(temp[0], farmer->end_room) == 0)
			return (1);
		while (farmer->rooms_arr[++i] != NULL)
		{
			if (CHECKING_ROOMS(0, i) == 0 || ft_strcmp(temp[0], farmer->start_room) == 0
				|| ft_strcmp(temp[0], farmer->end_room) == 0)
				return (1);
		}
		counter = (ft_check_coords(temp[1], temp[2], farmer)) ? counter : 1;
		if (flag == 1 && counter == 0)
			ft_add_room_coords(temp[0], farmer, i);
		(counter == 0) ? ft_add_room_coords(temp[1], farmer, -2) : 0;
		(counter == 0) ? ft_add_room_coords(temp[2], farmer, -1) : 0;
		// printf("OVER HERE:%d\n", counter);
	}
	free(temp[2]);
	free(temp[1]);
	free(temp[0]);
	free(temp);
	// printf("TOTAL COUNTER:%d\n", counter);
	return ((counter) ? 1 : 0);
}

static	char	*get_in_out_rooms(t_lemin *farmer, t_validation *valid)
{
	char		*line;
	char		*temp;

	// line = ft_strnew(0);
	temp = NULL;
	line = NULL;
	while (get_next_line(0, &line, valid) > 0)
	{
		if (line[0] == '#')
		{
			ft_memdel((void**)&line);
			continue ;
		}
		else if (line[0] != '#' && (ft_words_count(line, ' ') == 3)) // ft_words_count(line, ' ') == 3) //is better than current one, as we check [0] char in line in ft_push_new_room function
		{
			if (!ft_push_new_rooms(ft_strsplit(line, ' '), farmer, 0, valid))
			{
			 	temp = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
			 	ft_memdel((void**)&line);
			 	return (temp);
			}
			ft_memdel((void**)&line);
			return (NULL);
		}
		else
		{
			ft_memdel((void**)&line);
			return (NULL);
		}
	}
	ft_memdel((void**)&line);
	return (NULL);
}

static	int 	ft_hash_case(char *line, t_validation *valid, t_lemin *farmer, t_bonus *bonus)
{
	char		*temp;

	temp = NULL;
	if (SNG_HASH_CMNT && (ft_strstr(line, "#start") || ft_strstr(line, "#end") || ft_strstr(line, "#cpaths_")
  || ft_strstr(line, "#cmap_") || ft_strstr(line, "#cants_") || ft_strstr(line, "#cerror_") ))
	{
		// if (ft_strcmp(line, "#start") == 0)
		// {
		// 	valid->start_point += 1;
		// 	if ((temp = get_in_out_rooms(farmer, valid)) != NULL)
		// 	{
		// 		ft_memdel((void**)&farmer->start_room);
		// 		farmer->start_room = temp;
		// 		return (0);
		// 	}
		// 	// return (((farmer->start_room = get_in_out_rooms(farmer, valid)) != NULL) ? 0 : 1);
		// }
		// else if (ft_strcmp(line, "#end") == 0)
		// {
		// 	valid->end_point += 1;
		// 	// // ft_memdel((void**)&farmer->end_room);
		// 	// // return (((farmer->end_room = get_in_out_rooms(farmer, valid)) != NULL) ? 0 : 1);
		// 	if ((temp = get_in_out_rooms(farmer, valid)) != NULL)
		// 	{

		// 		ft_memdel((void**)&farmer->end_room);
		// 		farmer->end_room = temp;
		// 		// return (0);
		// 	}
		// }
		if (ft_strcmp(line, "#start") == 0 || ft_strcmp(line, "#end") == 0)
		{
			(ft_strcmp(line, "#start") == 0) ? valid->start_point++ : valid->end_point++;
			if ((temp = get_in_out_rooms(farmer, valid)) != NULL)
			{
				(ft_strcmp(line, "#start") == 0) ? ft_memdel((void**)&farmer->start_room) : ft_memdel((void**)&farmer->end_room);
				if (ft_strcmp(line, "#start") == 0)
					farmer->start_room = temp;
				else
					farmer->end_room = temp;
				// ft_memdel((void**)&temp);
				return (0);
			}
		}
		// else if (ft_strstr(line, "#cmap_") || ft_strstr(line, "#cants_") || ft_strstr(line, "#cerror_") || ft_strstr(line, "#cpaths_"))
			// return (ft_set_colors(bonus, line));
		ft_memdel((void**)&temp);
		return (1);
	}
	ft_memdel((void**)&temp);
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
	if (x != y)
	{
		farmer->adj_matrix[x][y] = '1';
		farmer->adj_matrix[y][x] = '1';
	}
	// printf("link1-%s|link2-%s|BUGAGAGA:%d|links:%d\n", link1, link2, temp++, ft_any_links(farmer->adj_matrix, '1'));
	return (0);
}

static	int		ft_init_adj_matrix(t_lemin *farmer)
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
	((ft_bidlen(farmer->adj_matrix)) == 0) ? ft_init_adj_matrix(farmer) : 0;
	// printf("temp[0]-%s:temp[1]:%s\n", temp[0], temp[1]);
	while (farmer->rooms_arr[i])
	{
		// if (!CHECKING_ROOMS(0, i) || !CHECKING_ROOMS(1, i)) // i have commented it, as if there are links like 3-3 or start-start we got ERROR as counter is incremented only once
		//	counter++;
		if (!CHECKING_ROOMS(0, i))
			counter++;
		if (!CHECKING_ROOMS(1, i))
			counter++;
		i++;
	}
	// printf("counter:%d\n", counter);
	counter += (counter == 2) ? ft_push_link(temp[0], temp[1], farmer) : 0;
	free(temp[1]);
	free(temp[0]);
	free(temp);
	return ((counter == 2) ?  (0) : (1));
}

static	int 	ft_validate_ants_num(char *line, t_lemin *farmer)
{
	intmax_t	temp;

	temp = ft_atoi_base(line, 10);
	if (temp >= 1 && temp <= 2147483647)
	{
		farmer->ants_num = temp;
		// printf("BamBoleio!\n");
		return (0);
	}
	// printf("NIGGA!\n");
	return (1);
}

size_t	ft_factorial(size_t size)
{
	if (size == 1)
		return (size);
	return (size * ft_factorial(1 - size));
}

int				lem_in_validation(t_validation *valid, t_lemin *farmer, t_bonus *bonus, char *line)
{
	int 		status;
	char		*temp;

	while ((status = get_next_line(0, &line, valid)) > 0)
	{
		if (ft_is_numeric(line))
		{
			// printf("ants_num error:%d%s\n", valid->errors, line);
			valid->errors += (farmer->ants_num == -1) ? ft_validate_ants_num(line, farmer) : 1;
			// printf("ants_num error:%d%s\n", valid->errors, line);
		}
		else if (line[0] == '#')
		{
			// printf("errors:%d\n", valid->errors);
			valid->errors += ft_hash_case(line + 1, valid, farmer, bonus);
			// printf("errors:%d:%s:%s\n", valid->errors, farmer->end_room, farmer->start_room);
		}
		else if (ft_words_count(line, ' ') == 3)
		{
			// printf("old_errors:%d|%s\n", valid->errors, line);
			valid->errors += ft_push_new_rooms(ft_strsplit(line, ' '), farmer, 1, valid);
			// printf("errors:%d|%s\n", valid->errors, line);
		}
		// else if (ft_words_count(line, '-') == 2 && ENTRY_ROOMS)
		// {
		// 	// printf("ERRORS:%d%s\n", valid->errors, line);
		// 	valid->errors += ft_find_rooms(ft_strsplit(line, '-'), farmer);
		// 	// printf("UPDATED ERRORS:%d\n", valid->errors);
		// }
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
		{
			ft_memdel((void**)&valid->file);
			ft_memdel((void**)&line);
			return (0);
		}
	}
	// printf("status:%d|start_room:%s|end_room:%s|ants_num:%d|start_point:%d|end_point:%d|adj_matrix:%d\n", status, farmer->start_room, farmer->end_room, farmer->ants_num, valid->start_point, valid->end_point, ft_any_links(farmer->adj_matrix, '1'));
	if (NO_ERRORS)
	{
		// free(farmer->paths);
		// farmer->paths = (t_graph**)malloc(sizeof(t_graph**) * ft_factorial(ft_bidlen(farmer->rooms_arr)) * ft_factorial(ft_any_links(farmer->adj_matrix, '1') / 2));
		// farmer->paths[0] = NULL;
		// return (dfs_iter(farmer, 0, 0, ft_strnew(0)));
		ft_memdel((void**)&line);
		return (1);
	}
	else
	{
		ft_memdel((void**)&valid->file);
		ft_memdel((void**)&line);
		return (0);
	}
	// return ((NO_ERRORS) ? dfs(farmer) : 0);
}
