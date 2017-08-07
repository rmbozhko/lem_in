#include "lem_in.h"

static	t_graph		*ft_create_path_node(char *str)
{
	t_graph		*path;

	path = (t_graph*)malloc(sizeof(t_graph*));
	path->path_str = ft_strdup(str);
	path->path_len = ft_bidlen(ft_strsplit(str, ' '));
	return (path);
}

static	int		ft_count_char(char *str, char c)
{
	int			i;
	int			counter;

	counter = 0;
	i = -1;
	while (str[++i])
		counter += (str[i] == c) ? 1 : 0;
	return (counter);
}	

static int			ft_update_room(t_lemin *farmer, char *str, int i, int step)
{
	char 		*room;
	int			j;

	j = step - 1;
	room = farmer->adj_matrix[i];
	while (farmer->adj_matrix[i][++j])
	{
		if (farmer->adj_matrix[i][j] == '1')
		{
			if (!ft_strstr(str, farmer->rooms_arr[j]))
			{
				return (j);
				// break ;
			}
		}
	}
	// printf("room:%s, vertex:%d, new_vertex:%d, visited:%s\n", room, i, j, str);
	// return (j);
	return (-1);
}

static	int			ft_push_path_node(char *str, t_lemin *farmer)
{
	farmer->paths[farmer->rooms_counter++] = ft_create_path_node(str);
	farmer->paths[farmer->rooms_counter] = NULL;
	return (1);
}


static	int			ft_count_visited(char *str, char *temp, char **arr)
{
	int			i;
	int			counter;

	counter = 0;
	i = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == '1')
		{
			if (ft_strstr(str, arr[i]))
				counter++;
		}
		i++;
	}
	return (counter);
}

static	int			ft_check_repeating_paths(t_graph **graps, char *path)
{
	size_t		i;

	i = 0;
	while (graps[i] != NULL)
	{
		if (ft_strcmp(graps[i]->path_str, path) == 0)
			return (0);
		i++;
	}
	return (1);
}

static void			dfs_rec(t_lemin *farmer, int i, char *str)
{
	int			j;

	j = ft_update_room(farmer, str, i, 0);
	while (42)//&& farmer->adj_matrix[i][j] == '1')
	{
		if (ft_strstr(str, farmer->end_room) || (farmer->adj_matrix[i][ft_strlen(farmer->adj_matrix[i]) - 1] == '1'))
		{
			if (farmer->adj_matrix[i][ft_strlen(farmer->adj_matrix[i]) - 1] == '1')
			{
				str = ft_strjoin(str, " ");
				str = ft_strjoin(str, farmer->end_room);
			}
			(ft_check_repeating_paths(farmer->paths, str)) ? ft_push_path_node(str, farmer) : 0;
		 	return (ft_memdel((void**)&str));
		}
		else if ((ft_count_char(farmer->adj_matrix[i], '1') - ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr)) == 0)
			return (ft_memdel((void**)&str));
		else if (ft_strchr(farmer->adj_matrix[i] + j, '1'))
		{
			str = (str[ft_strlen(str) - 1] != ' ') ? ft_strjoin(str, " ") : str;
			dfs_rec(farmer, j, ft_strjoin(str, farmer->rooms_arr[j]));
		}
		// else
		// {
		// 	if ((ft_count_char(farmer->adj_matrix[i], '1') - ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr)) == 0)
		// 	{
		// 		return (ft_memdel((void**)&str));
		// 	}
		// 	else if (ft_strchr(farmer->adj_matrix[i] + j, '1'))
		// 	{
		// 		str = (str[ft_strlen(str) - 1] != ' ') ? ft_strjoin(str, " ") : str;
		// 		// printf("previous1:%d:current1:%d:previous1:%s:current1:%s\n", j, i, ft_strjoin(str, farmer->rooms_arr[j]), str);
		// 		dfs_rec(farmer, j, ft_strjoin(str, farmer->rooms_arr[j]));
		// 		// printf("previous:%d:current%d:previous:%s:current:%s\n", j, i, ft_strjoin(str, farmer->rooms_arr[j]), str);
		// 	}
		// }
		if (ft_strchr(farmer->adj_matrix[i] + j + 1, '1') != NULL)
		{
			j = ft_strchr(farmer->adj_matrix[i] + j + 1, '1') - farmer->adj_matrix[i];
			// printf("new_one1:%d:current_one1:%d:new_one1:%s:current_one1:%s\n", j, i, ft_strjoin(str, farmer->rooms_arr[j]), str);
			j = ft_update_room(farmer, str, i, j);
			// printf("j:%d\n", j);
			if (j == -1)
				break ;
			// printf("new_one:%d:current_one%d:new_one:%s:current_one:%s\n", j, i, ft_strjoin(str, farmer->rooms_arr[j]), str);
		}
		else
		{
			break ;
		}
		// printf("HERE!\n");
	}
	return (ft_memdel((void**)&str));
}

int			dfs_iter(t_lemin *farmer, int i, int j, char *str)
{
	while (ft_strchr(farmer->adj_matrix[i] + j, '1'))
	{
		str = ft_strjoin(str, farmer->rooms_arr[i]);
		if (ft_strcmp(farmer->rooms_arr[i], farmer->end_room) == 0)
			break ;
		//str = ft_strjoin(str, " ");
		if ((ft_count_char(farmer->adj_matrix[i] + j, '1') - ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr)) == 1)
		{
			str = ft_strjoin(str, " ");
			j = (ft_count_char(farmer->adj_matrix[i] + j, '1') == 2) ? ft_update_room(farmer, str, i, 0) : j;
			i = ft_strchr(farmer->adj_matrix[i] + j, '1') - farmer->adj_matrix[i];
			j = 0;
		}
		else
			break ;
	}
	if (ft_strstr(str, farmer->end_room))
		return (ft_push_path_node(str, farmer));
	else if (ft_strchr(farmer->adj_matrix[i], '1'))
	{
		dfs_rec(farmer, i, str);
		return ((farmer->rooms_counter > 0) ? 1 : 0);
	}
	return (0);
}
