/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 12:59:54 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 13:01:06 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				ft_push_rooms(char **temp, t_lemin *farmer, int flag)
{
	size_t		i;
	int			counter;

	counter = 1;
	if (ft_is_numeric(temp[1]) && ft_is_numeric(temp[2]) && FORBIDDEN_CHARS)
	{
		counter = 0;
		i = 0;
		if (ft_strcmp(temp[0], farmer->start) == 0
			|| ft_strcmp(temp[0], farmer->end) == 0)
			counter = 1;
		while (farmer->rooms_arr[++i] != NULL)
			(CHECK_ROOMS(0, i) == 0) ? counter = 1 : 0;
		counter = (ft_check_coords(temp[1], temp[2], farmer)) ? counter : 1;
		if (flag == 1 && counter == 0)
			ft_add_room_coords(temp[0], farmer, i);
		(counter == 0) ? ft_add_room_coords(temp[1], farmer, -2) : 0;
		(counter == 0) ? ft_add_room_coords(temp[2], farmer, -1) : 0;
	}
	free(temp[2]);
	free(temp[1]);
	free(temp[0]);
	free(temp);
	return ((counter) ? 1 : 0);
}

static	int		hash_case(char *line, t_valid *v, t_lemin *farmer, t_bonus *b)
{
	char		*temp;

	temp = NULL;
	if (SNG_HASH_CMNT && (GEN_ROOMS_CHECK || COLOR_CASES))
	{
		if (ft_strcmp(line, "#start") == 0 || ft_strcmp(line, "#end") == 0)
		{
			(ft_strcmp(line, "#start") == 0) ? v->start++ : v->end++;
			if ((temp = get_in_out_rooms(farmer, v, NULL)) != NULL)
			{
				(ft_strcmp(line, "#start") == 0)
					? DEL(farmer->start) : DEL(farmer->end);
				if (ft_strcmp(line, "#start") == 0)
					farmer->start = temp;
				else
					farmer->end = temp;
				return (0);
			}
		}
		else if (COLOR_CASES)
			return (ft_set_colors(b, line));
		DEL(temp);
		return (1);
	}
	return (0);
}

static	int		ft_find_rooms(char **temp, t_lemin *farmer)
{
	size_t		i;
	int			counter;

	i = 0;
	counter = 0;
	((ft_bidlen(farmer->adj_matrix)) == 0) ? ft_init_adj_matrix(farmer) : 0;
	while (farmer->rooms_arr[i])
	{
		if (!CHECK_ROOMS(0, i))
			counter++;
		if (!CHECK_ROOMS(1, i))
			counter++;
		i++;
	}
	(counter == 2) ? ft_push_link(temp[0], temp[1], farmer) : 0;
	free(temp[1]);
	free(temp[0]);
	free(temp);
	return ((counter == 2) ? (0) : (1));
}

static	int		ants_num(char *line, t_lemin *farmer)
{
	intmax_t	temp;

	temp = ft_atoi_base(line, 10);
	if (temp >= 1 && temp <= 2147483647)
	{
		farmer->ants = temp;
		return (0);
	}
	return (1);
}

int				validate(t_valid *valid, t_lemin *farmer, t_bonus *b, char *l)
{
	while ((valid->status = gnl(0, &l, valid, ft_strnew(0))) > 0)
	{
		if (ft_is_numeric(l))
			valid->errors += (farmer->ants == -1) ? ants_num(l, farmer) : 1;
		else if (l[0] == '#')
			valid->errors += hash_case(l + 1, valid, farmer, b);
		else if (ft_words_count(l, ' ') == 3)
			valid->errors += ft_push_rooms(ft_strsplit(l, ' '), farmer, 1);
		else if (ft_words_count(l, '-') == 2 && GEN_ROOMS && farmer->ants != -1)
			valid->errors += ft_find_rooms(ft_strsplit(l, '-'), farmer);
		else
		{
			if (NO_ERRORS)
			{
				ft_errors_handling(1, b);
				break ;
			}
			valid->errors += 1;
		}
		if (valid->errors != 0)
			break ;
	}
	DEL(l);
	return ((NO_ERRORS) ? (dfs_iter(farmer, 0, 0, ft_strnew(0))) : (0));
}
