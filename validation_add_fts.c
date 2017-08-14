#include "lem_in.h"

char			*get_in_out_rooms(t_lemin *farmer, t_valid *valid, char *temp)
{
	char		*line;

	line = NULL;
	while (get_next_line(0, &line, valid) > 0)
	{
		if (line[0] == '#')
		{
			DEL(line);
			continue ;
		}
		else if (/*line[0] != '#' && (*/ft_words_count(line, ' ') == 3) // ft_words_count(line, ' ') == 3) //is better than current one, as we check [0] char in line in ft_push_new_room function
		{
			if (!ft_push_rooms(ft_strsplit(line, ' '), farmer, 0, valid))
			{
			 	temp = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
			 	DEL(line);
			 	return (temp);
			}
			break ;
			// DEL(line);
			// return (NULL);
		}
		else
		{
			break ;
			// DEL(line);
			// return (NULL);
		}
	}
	DEL(line);
	return (NULL);
}

char        **ft_create_bid_arr(size_t size, char *str)
{
    int         i;
    char        **temp;
    
    temp = (char**)malloc(sizeof(char*) * size + 1);
    i = 0;
    while (i < size)
    {
        temp[i] = ft_strdup(str);
        i++;
    }
    temp[i] = NULL;
    return (temp);
}

void			ft_push_link(char *link1, char *link2, t_lemin *farmer)
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
}

void			ft_init_adj_matrix(t_lemin *farmer)
{
	char		*temp;

	DEL(farmer->rooms_arr[0]);
	farmer->rooms_arr[0] = ft_strdup(farmer->start);
	farmer->rooms_arr[ft_bidlen(farmer->rooms_arr)] = ft_strdup(farmer->end);
	farmer->rooms_arr[ft_bidlen(farmer->rooms_arr) + 1] = NULL;
	free(farmer->adj_matrix);
	temp = ft_memset(ft_strnew(sizeof(char) * ft_bidlen(farmer->rooms_arr) + 1), '0', ft_bidlen(farmer->rooms_arr));
	farmer->adj_matrix = ft_create_bid_arr(ft_bidlen(farmer->rooms_arr), temp);
	DEL(temp);
}

int 			ft_get_rooms_coord(char *room, char **temp)
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

int 			ft_check_coords(char *x_coord, char *y_coord, t_lemin *farmer)
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

void			ft_add_room_coords(char *elem, t_lemin *farmer, int i)
{
	int 		temp;

	if (i == -2)
	{
		farmer->x_coords[ft_bidlen(farmer->x_coords)] = ft_strdup(elem);
		farmer->x_coords[ft_bidlen(farmer->x_coords) + 1] = NULL;
	}
	else if (i == -1)
	{
		farmer->y_coords[ft_bidlen(farmer->y_coords)] = ft_strdup(elem);
		farmer->y_coords[ft_bidlen(farmer->y_coords) + 1] = NULL;
	}
	else
	{
		farmer->rooms_arr[i] = ft_strdup(elem);
		farmer->rooms_arr[i + 1] = NULL;
	}
}