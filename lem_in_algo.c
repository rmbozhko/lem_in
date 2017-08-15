#include "lem_in.h"

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

static	char		**ft_add_smth(char **str, t_lemin *farmer, int flag)
{
	char 		*temp;

	temp = *str;
	(flag == 2) ? ft_memdel((void**)&temp) : 0;
	*str = ft_strjoin(*str, " ");
	(flag == 2) ? 0 : ft_memdel((void**)&temp);
	if (flag == 1)
	{
		temp = *str;
		*str = ft_strjoin(*str, farmer->end);
		ft_memdel((void**)&temp);
	}
	return (str);
}

static void			dfs_rec(t_lemin *farmer, int i, char *str)
{
	int			j;

	j = ft_update_room(farmer, str, i, 0);
	while (42)
	{
		if (ft_strstr(str, farmer->end) || (farmer->adj_matrix[i][ft_strlen(farmer->adj_matrix[i]) - 1] == '1'))
		{
			(farmer->adj_matrix[i][ft_strlen(farmer->adj_matrix[i]) - 1] == '1') ? ft_add_smth(&str, farmer, 1) : 0;
			(ft_check_repeating_paths(farmer->paths, str)) ? ft_push_path_node(str, farmer, 0) : 0;
		 	return (ft_memdel((void**)&str));
		}
		else if ((ft_count_char(farmer->adj_matrix[i], '1') - ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr)) == 0)
			return (ft_memdel((void**)&str));
		else if (ft_strchr(farmer->adj_matrix[i] + j, '1'))
			dfs_rec(farmer, j, ft_strjoin((str[ft_strlen(str) - 1] != ' ') ? *(ft_add_smth(&str, farmer, 0)) : str, farmer->rooms_arr[j]));
		if (ft_strchr(farmer->adj_matrix[i] + j + 1, '1') != NULL)
		{
			j = ft_strchr(farmer->adj_matrix[i] + j + 1, '1') - farmer->adj_matrix[i];
			if ((j = ft_update_room(farmer, str, i, j)) == -1)
				break ;
		}
		else
			break ;
	}
	return (ft_memdel((void**)&str));
}

int					dfs_iter(t_lemin *farmer, int i, int j, char *str)
{
	char 		*temp;

	temp = str;
	while (ft_strchr(farmer->adj_matrix[i] + j, '1'))
	{
		ft_memdel((void**)&temp);
		str = ft_strjoin(str, farmer->rooms_arr[i]);
		temp = str;
		if (ft_strcmp(farmer->rooms_arr[i], farmer->end) == 0 || (ft_count_char(farmer->adj_matrix[i] + j, '1') - ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr)) != 1)
			break ;
		else if (ft_count_char(farmer->adj_matrix[i] + j, '1') - ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr) == 1)
		{
			temp = *(ft_add_smth(&str, farmer, 2));
			j = (ft_count_char(farmer->adj_matrix[i] + j, '1') == 2) ? ft_update_room(farmer, str, i, 0) : j;
			i = ft_strchr(farmer->adj_matrix[i] + j, '1') - farmer->adj_matrix[i];
			j = 0;
		}
	}
	if (ft_strstr(str, farmer->end))
		ft_push_path_node(str, farmer, 1);
	else if (ft_strchr(farmer->adj_matrix[i], '1'))
		dfs_rec(farmer, i, str);
	else
		ft_memdel((void**)&temp);
	return ((farmer->rooms_counter > 0) ? 1 : 0);
}
