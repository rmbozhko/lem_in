/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:21:51 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 13:25:49 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char			**ft_init_colors_arr(void)
{
	char		**temp;

	temp = (char**)malloc((sizeof(char*) * 13) + 1);
	temp[0] = "\033[0;30m";
	temp[1] = "\033[0;31m";
	temp[2] = "\033[0;30;41m";
	temp[3] = "\033[0;32m";
	temp[4] = "\033[0;30;42m";
	temp[5] = "\033[0;33m";
	temp[6] = "\033[0;30;43m";
	temp[7] = "\033[0;34m";
	temp[8] = "\033[0;30;44m";
	temp[9] = "\033[0;35m";
	temp[10] = "\033[0;30;45m";
	temp[11] = "\033[0;36m";
	temp[12] = "\033[0;30;46m";
	temp[13] = NULL;
	return (temp);
}

static	int		ft_get_forground_color(char *str)
{
	if ((ft_strcmp(str, "fred") == 0))
		return (1);
	else if ((ft_strcmp(str, "fgreen") == 0))
		return (3);
	else if ((ft_strcmp(str, "fyellow") == 0))
		return (5);
	else if ((ft_strcmp(str, "fblue") == 0))
		return (7);
	else if ((ft_strcmp(str, "fmagenta") == 0))
		return (9);
	else if ((ft_strcmp(str, "fcyan") == 0))
		return (11);
	return (0);
}

static	int		ft_get_background_color(char *str)
{
	if ((ft_strcmp(str, "bred") == 0))
		return (2);
	else if ((ft_strcmp(str, "bgreen") == 0))
		return (4);
	else if ((ft_strcmp(str, "byellow") == 0))
		return (6);
	else if ((ft_strcmp(str, "bblue") == 0))
		return (8);
	else if ((ft_strcmp(str, "bmagenta") == 0))
		return (10);
	else if ((ft_strcmp(str, "bcyan") == 0))
		return (12);
	return (0);
}

static	int		ft_get_color(char *str)
{
	if (str[0] == 'f')
		return (ft_get_forground_color(str));
	else if (str[0] == 'b')
		return (ft_get_background_color(str));
	else
		return (0);
}

int				ft_set_colors(t_bonus *bonus, char *line)
{
	if (ft_strstr(line, "#cmap_"))
		bonus->cmap = ft_get_color(line + 6);
	else if (ft_strstr(line, "#cants_"))
		bonus->cants = ft_get_color(line + 7);
	else if (ft_strstr(line, "#cerror_"))
		bonus->cerror = ft_get_color(line + 8);
	else if (ft_strstr(line, "#cpaths_"))
		bonus->cpaths = ft_get_color(line + 8);
	return (0);
}
