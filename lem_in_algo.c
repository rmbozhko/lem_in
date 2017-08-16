/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 16:03:06 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 16:03:41 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char		*temp;

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
		if (ft_strstr(str, farmer->end) || GO_TO_END)
		{
			(GO_TO_END) ? ft_add_smth(&str, farmer, 1) : 0;
			ft_push_path_node(str, farmer, 0);
			return (ft_memdel((void**)&str));
		}
		else if ((COUNT_LINKS(0) - VISITED) == 0)
			return (ft_memdel((void**)&str));
		else if (ft_strchr(farmer->adj_matrix[i] + j, '1'))
			dfs_rec(farmer, j, JOIN_RM_SPC);
		if (ft_strchr(farmer->adj_matrix[i] + j + 1, '1') != NULL)
		{
			j = MOVE_RIGHT(farmer->adj_matrix, i, j, 1, '1');
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
	char		*temp;

	temp = str;
	while (ft_strchr(farmer->adj_matrix[i] + j, '1'))
	{
		ft_memdel((void**)&temp);
		str = ft_strjoin(str, farmer->rooms_arr[i]);
		temp = str;
		if (ft_strstr(str, farmer->end) || (COUNT_LINKS(j) - VISITED) != 1)
			break ;
		else if ((COUNT_LINKS(j) - VISITED) == 1)
		{
			temp = *(ft_add_smth(&str, farmer, 2));
			j = (COUNT_LINKS(j) == 2) ? ft_update_room(farmer, str, i, 0) : j;
			i = MOVE_RIGHT(farmer->adj_matrix, i, j, 0, '1');
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
