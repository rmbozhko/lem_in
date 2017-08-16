/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_add_fts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 12:51:37 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 12:53:20 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	t_graph		*ft_create_path_node(char *str, int flag)
{
	t_graph		*path;
	char		**arr;

	path = (t_graph*)malloc(sizeof(t_graph*));
	path->path_str = ft_strdup(str);
	arr = ft_strsplit(str, ' ');
	path->path_len = ft_bidlen(arr);
	ft_free_bidarr(arr, path->path_len);
	(flag) ? ft_memdel((void**)&str) : 0;
	return (path);
}

int					ft_count_visited(char *str, char *temp, char **arr)
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

int					ft_check_repeating_paths(t_graph **graps, char *path)
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

void				ft_push_path_node(char *str, t_lemin *farmer, int flag)
{
	farmer->paths[farmer->rooms_counter++] = ft_create_path_node(str, flag);
	farmer->paths[farmer->rooms_counter] = NULL;
}
