#include "lem_in.h"

static	t_graph		*ft_create_path_node(char *str)
{
	t_graph		*path;

	path = (t_graph*)malloc(sizeof(t_graph*));
	path->path_str = ft_strdup(str);
	path->path_len = ft_bidlen(ft_strsplit(str, ' '));//0;
	//free(str);
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

static int			ft_update_room(t_lemin *farmer, char *str, int i)
{
	char 		*room;
	int			j;

	j = -1;
	room = farmer->adj_matrix[i];
	while (farmer->adj_matrix[i][++j])
	{
		if (farmer->adj_matrix[i][j] == '1')
		{
			if (!ft_strstr(str, farmer->rooms_arr[j]))
				break ;
		}
	}
	return (j);
}


static int			ft_count_visited(char *str, char *temp, char **arr)
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
			{
				// printf("str:%s && temp[i]:%s\n", str, arr[i]);
				counter++;
			}
		}
		i++;
	}
	return (counter);
}

static void			dfs(t_lemin *farmer, int i, char *str)
{
	int			j;

	j = ft_update_room(farmer, str, i);
	while (42)//(ft_strchr(farmer->adj_matrix[i] + j , '1'))
	{
		if (ft_strstr(str, farmer->end_room) || (farmer->adj_matrix[i][ft_strlen(farmer->adj_matrix[i]) - 1] == '1'))
		{
			if (farmer->adj_matrix[i][ft_strlen(farmer->adj_matrix[i]) - 1] == '1')
			{
				str = ft_strjoin(str, " ");
				str = ft_strjoin(str, farmer->end_room);
			}
			farmer->paths[farmer->rooms_counter++] = ft_create_path_node(str);
			farmer->paths[farmer->rooms_counter] = NULL;
			ft_memdel((void**)&str);
			return ;
		}
		else
		{
			if ((ft_count_char(farmer->adj_matrix[i], '1') - ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr)) == 0)
			{
				ft_memdel((void**)&str);
				return ;
			}
			else if (ft_strchr(farmer->adj_matrix[i] + j, '1'))
			{
				str = (str[ft_strlen(str) - 1] != ' ') ? ft_strjoin(str, " ") : str;
				dfs(farmer, j, ft_strjoin(str, farmer->rooms_arr[j]));
			}
		}
		if (ft_strchr(farmer->adj_matrix[i] + j + 1, '1') != NULL)
			j = ft_strchr(farmer->adj_matrix[i] + j + 1, '1') - farmer->adj_matrix[i];
		else
			break ;
	}
	ft_memdel((void**)&str);
	return ;
}

int			dfs_iter(t_lemin *farmer, int i, int j, char *str)
{
	while (ft_strchr(farmer->adj_matrix[i] + j, '1'))
	{
		str = ft_strjoin(str, farmer->rooms_arr[i]);
		if (ft_strcmp(farmer->rooms_arr[i], farmer->end_room) == 0)
			break ;
		str = ft_strjoin(str, " ");
		if ((ft_count_char(farmer->adj_matrix[i] + j, '1') - ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr)) == 1)
		{
			j = (ft_count_char(farmer->adj_matrix[i] + j, '1') == 2) ? ft_update_room(farmer, str, i) : j;
			i = ft_strchr(farmer->adj_matrix[i] + j, '1') - farmer->adj_matrix[i];
			j = 0;
		}
		else //if ((ft_count_char(farmer->adj_matrix[i] + j, '1') - ft_count_visited(str, farmer->rooms_arr)) > 1)
			break ;
	}
	if (ft_strstr(str, farmer->end_room))
	{
		farmer->paths[farmer->rooms_counter++] = ft_create_path_node(str);
		return (1);
	}
	else if (ft_strchr(farmer->adj_matrix[i], '1'))
	{
		dfs(farmer, i, str);
		return ((farmer->rooms_counter > 0) ? 1 : 0);
	}
	return (0);
}
