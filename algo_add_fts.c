#include "lem_in.h"

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

int			ft_count_visited(char *str, char *temp, char **arr)
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

int			ft_check_repeating_paths(t_graph **graps, char *path)
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

void		ft_push_path_node(char *str, t_lemin *farmer, int flag)
{
	farmer->paths[farmer->rooms_counter++] = ft_create_path_node(str, flag);
	farmer->paths[farmer->rooms_counter] = NULL;
}