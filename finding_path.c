#include "lem_in.h"

void		ft_free_bidarr(char **arr, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		ft_memdel((void**)&arr[i]);
		i++;
	}
	free(arr);
}

static	t_graph		*ft_create_path_node(char *str, int flag)
{
	t_graph		*path;
	char 		**arr;

	path = (t_graph*)malloc(sizeof(t_graph*));
	path->path_str = ft_strdup(str);
	path->path_len = ft_bidlen(arr = ft_strsplit(str, ' '));
	ft_free_bidarr(arr, path->path_len);
	(flag) ? ft_memdel((void**)&str) : 0;
	return (path);
}

int		ft_count_char(char *str, char c)
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
	int			j;

	j = step - 1;
	while (farmer->adj_matrix[i][++j])
	{
		if (farmer->adj_matrix[i][j] == '1')
		{
			if (!ft_strstr(str, farmer->rooms_arr[j]))
				return (j);
		}
	}
	return (-1);
}

static	int			ft_push_path_node(char *str, t_lemin *farmer, int flag)
{
	farmer->paths[farmer->rooms_counter++] = ft_create_path_node(str, flag);
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
	char 		*temp;

	temp = NULL;
	j = ft_update_room(farmer, str, i, 0);
	while (42)
	{
		if (ft_strstr(str, farmer->end) || (farmer->adj_matrix[i][ft_strlen(farmer->adj_matrix[i]) - 1] == '1'))
		{
			if (farmer->adj_matrix[i][ft_strlen(farmer->adj_matrix[i]) - 1] == '1')
			{
				temp = str;
				str = ft_strjoin(str, " ");
				ft_memdel((void**)&temp);
				temp = str;
				str = ft_strjoin(str, farmer->end);
				ft_memdel((void**)&temp);
			}

			(ft_check_repeating_paths(farmer->paths, str)) ? ft_push_path_node(str, farmer, 0) : 0;
		 	return (ft_memdel((void**)&str));
		}
		else if ((ft_count_char(farmer->adj_matrix[i], '1') - ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr)) == 0)
			return (ft_memdel((void**)&str));
		else if (ft_strchr(farmer->adj_matrix[i] + j, '1'))
		{
			
			if (str[ft_strlen(str) - 1] != ' ')
			{
				temp = str;
				str = ft_strjoin(str, " ");
				ft_memdel((void**)&temp);
			}
			dfs_rec(farmer, j, ft_strjoin(str, farmer->rooms_arr[j]));
		}
		if (ft_strchr(farmer->adj_matrix[i] + j + 1, '1') != NULL)
		{
			j = ft_strchr(farmer->adj_matrix[i] + j + 1, '1') - farmer->adj_matrix[i];
			j = ft_update_room(farmer, str, i, j);
			if (j == -1)
				break ;
		}
		else
			break ;
	}
	return (ft_memdel((void**)&str));
}

int			dfs_iter(t_lemin *farmer, int i, int j, char *str)
{
	char 		*temp;

	temp = str;
	while (ft_strchr(farmer->adj_matrix[i] + j, '1'))
	{
		ft_memdel((void**)&temp);
		str = ft_strjoin(str, farmer->rooms_arr[i]);
		temp = str;
		if (ft_strcmp(farmer->rooms_arr[i], farmer->end) == 0)
			break ;
		if ((ft_count_char(farmer->adj_matrix[i] + j, '1') - ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr)) == 1)
		{
			ft_memdel((void**)&temp);
			str = ft_strjoin(str, " ");
			temp = str;
			j = (ft_count_char(farmer->adj_matrix[i] + j, '1') == 2) ? ft_update_room(farmer, str, i, 0) : j;
			i = ft_strchr(farmer->adj_matrix[i] + j, '1') - farmer->adj_matrix[i];
			j = 0;
		}
		else
			break ;
	}
	if (ft_strstr(str, farmer->end))
	{
		ft_push_path_node(str, farmer, 1);
		return (1);//(ft_push_path_node(str, farmer));
	}
	else if (ft_strchr(farmer->adj_matrix[i], '1'))
	{
		dfs_rec(farmer, i, str);
		// ft_memdel((void**)&temp);
		return ((farmer->rooms_counter > 0) ? 1 : 0);
	}
	ft_memdel((void**)&temp);
	return (0);
}
