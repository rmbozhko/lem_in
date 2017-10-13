/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_add_fts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 12:50:17 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 12:51:24 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char			*get_in_out_rooms(t_lemin *farmer, t_valid *valid, char *temp)
{
	char		*l;

	l = NULL;
	while (gnl(0, &l, valid, ft_strnew(0)) > 0)
	{
		if (l[0] == '#')
		{
			DEL(l);
			continue ;
		}
		else if ((ft_words_count(l, ' ') == 3) && (ft_count_char(l, ' ') == 2))
		{
			if (!ft_push_rooms(ft_strsplit(l, ' '), farmer, 0))
			{
				temp = ft_strsub(l, 0, ft_strchr(l, ' ') - l);
				DEL(l);
				return (temp);
			}
			break ;
		}
		else
			break ;
	}
	DEL(l);
	return (NULL);
}

void			ft_push_link(char *link1, char *link2, t_lemin *farmer)
{
	int		x;
	int		y;

	x = ft_bid_findstr(link1, farmer->rooms_arr);
	y = ft_bid_findstr(link2, farmer->rooms_arr);
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
	temp = ft_memset(ft_strnew(sizeof(char) * ft_bidlen(farmer->rooms_arr) + 1),
			'0', ft_bidlen(farmer->rooms_arr));
	farmer->adj_matrix = ft_create_bid_arr(ft_bidlen(farmer->rooms_arr), temp);
	DEL(temp);
}

int				ft_check_coords(char *x_coord, char *y_coord, t_lemin *farmer)
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
