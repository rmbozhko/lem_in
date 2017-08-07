/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 15:58:24 by rbozhko           #+#    #+#             */
/*   Updated: 2017/02/22 15:58:27 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_node	*ft_create(void)
{
	t_node	*temp;

	temp = (t_node*)malloc(sizeof(t_node));
	temp->str = ft_strnew(0);
	return (temp);
}

static int		ft_rtn_line(t_node *temp, char buff[], char **line, t_validation *valid)
{
	if (NL_CODE)
	{	
		*line = ft_strsub(temp->str, 0, S_C_SUB);
		valid->file = ft_strjoin(valid->file, *line);
		valid->file = ft_strjoin(valid->file, "\n");
		temp->str += S_C_SUB;
		return (1);
	}
	else if ((!(NL_CODE)) && ft_strlen(buff) == 0)
	{
		valid->file = ft_strjoin(valid->file, temp->str);
		valid->file = ft_strjoin(valid->file, "\n");
		*line = ft_strdup(temp->str);
		ft_memset(temp->str, 0, ft_strlen(temp->str));
		return (1);
	}
	return (0);
	/*
	if (NL_CODE)
	{
		valid->file = ft_strjoin(valid->file, ft_strsub(temp->str, 0, S_C_SUB + 1));
		*line = ft_strsub(temp->str, 0, S_C_SUB);
		temp->str += S_C_SUB;
		return (1);
	}
	else if ((!(NL_CODE)) && ft_strlen(buff) == 0)
	{
		valid->file = ft_strjoin(valid->file, ft_strdup(temp->str));
		*line = ft_strdup(temp->str);
		ft_memset(temp->str, 0, ft_strlen(temp->str));
		return (1);
	}
	return (0);*/
}

int				get_next_line(const int fd, char **line, t_validation *valid)
{
	static	t_node		*head = NULL;
	t_node				*temp;
	int					bytes;
	char				buff[BUFF_SIZE + 1];

	if (IF_FP || IF_SP)
		return (-1);
	!(head) ? head = ft_create() : 0;
	temp = head;
	while ((bytes = read(fd, buff, BUFF_SIZE)) >= 0)
	{
		(bytes < BUFF_SIZE) ? buff[bytes] = '\0' : 0;
		temp->str = ft_strjoin(temp->str, buff);
		(temp->str[0] == '\n') ? temp->str += 1 : 0;
		if (ft_strlen(temp->str) > 0)
		{
			if ((NL_CODE) || (!NL_CODE && ft_strlen(buff) == 0))
				if (ft_rtn_line(temp, buff, line, valid) == 1)
					return (1);
		}
		else if (bytes == 0 || (bytes == 1 && buff[0] == '\n'))
			return (0);
	}
	return (0);
}
