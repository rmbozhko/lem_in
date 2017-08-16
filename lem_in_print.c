/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:17:39 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 13:19:19 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	char		*ft_best_path(t_lemin *farmer)
{
	size_t		i;
	char		*path;

	i = 0;
	path = farmer->paths[i++]->path_str;
	while (farmer->paths[i])
	{
		if (ft_strlen(farmer->paths[i]->path_str) < ft_strlen(path))
			path = farmer->paths[i]->path_str;
		i++;
	}
	return (path);
}

static	size_t		ft_update_ants_arr(char **arr)
{
	size_t		i;

	i = 0;
	while (ft_strcmp(arr[i], "\0") == 0)
		i++;
	return (i);
}

static	size_t		ft_count_unfinished(char **arr)
{
	size_t		i;
	size_t		counter;

	counter = 0;
	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], "\0") != 0)
			counter++;
		i++;
	}
	return (counter);
}

static	void		ft_mv_ants(char **arr, size_t ants, int flag, char *temp)
{
	size_t		j;

	j = ft_update_ants_arr(arr);
	(flag == 1) ? ants += j - 1 : 0;
	while (j <= ants)
	{
		ft_putchar('L');
		temp = ft_itoa(j + 1);
		ft_putstr(temp);
		DEL(temp);
		ft_putchar('-');
		if (ft_strchr(arr[j], ' '))
		{
			temp = UPDATE_WAY(0, ANTS_MOVE);
			ft_putstr(temp);
			ft_memdel((void**)&temp);
		}
		else
			ft_putstr(arr[j]);
		temp = arr[j];
		arr[j] = (!ft_strchr(arr[j], ' '))
			? "\0" : UPDATE_WAY(ANTS_MOVE + 1, ft_strlen(arr[j]));
		DEL(temp);
		((++j) <= ants) ? ft_putchar(' ') : 0;
	}
}

void				ants_travel(t_lemin *farmer, t_bonus *bonus, int ants_num)
{
	char		**arr;
	char		*temp;

	temp = NULL;
	ft_putstr("\033[35;3;2;3mRun Forest run:\033[0m\n");
	arr = ft_create_bid_arr(farmer->ants,
				ft_strchr(ft_best_path(farmer), ' ') + 1);
	while (ants_num < farmer->ants)
	{
		ft_putstr(bonus->color_arr[bonus->cants]);
		ft_mv_ants(arr, ants_num++, 0, temp);
		ft_putstr("\033[0m\n");
	}
	ants_num = ft_count_unfinished(arr);
	while (ants_num != 0)
	{
		ft_putstr(bonus->color_arr[bonus->cants]);
		ft_mv_ants(arr, ants_num, 1, temp);
		ft_putstr("\033[0m\n");
		ants_num = ft_count_unfinished(arr);
	}
	free(arr);
}
