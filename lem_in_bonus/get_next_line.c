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

#include "get_next_line.h"

static t_node	*ft_create(int fd)
{
	t_node	*temp;

	temp = (t_node*)malloc(sizeof(t_node));
	(fd >= 0) ? temp->fd = fd : 0;
	temp->str = ft_strnew(0);
	temp->next = NULL;
	return (temp);
}

static t_node	*ft_cmp_fd(int fd, t_node *demo)
{
	t_node	*temp;

	temp = demo;
	while (temp)
	{
		if (temp->fd == fd)
			break ;
		(!(temp->next)) ? temp->next = ft_create(fd) : 0;
		temp = temp->next;
	}
	return (temp);
}

static int		ft_rtn_line(t_node *temp, char buff[], char **line)
{
	if (ft_strchr(temp->str, '\n'))
	{
		*line = ft_strsub(temp->str, 0, S_C_SUB);
		temp->str += S_C_SUB;
		return (1);
	}
	else if ((!(ft_strchr(temp->str, '\n'))) && ft_strlen(buff) == 0)
	{
		*line = ft_strdup(temp->str);
		ft_memset(temp->str, 0, ft_strlen(temp->str));
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static	t_node		*head = NULL;
	t_node				*temp;
	int					bytes;
	char				buff[BUFF_SIZE + 1];

	if (IF_FP || IF_SP)
		return (-1);
	!(head) ? head = ft_create(fd) : 0;
	temp = ft_cmp_fd(fd, head);
	while ((bytes = read(fd, buff, BUFF_SIZE)) >= 0)
	{
		(bytes < BUFF_SIZE) ? buff[bytes] = '\0' : 0;
		temp->str = ft_strjoin(temp->str, buff);
		(temp->str[0] == '\n') ? temp->str += 1 : 0;
		if (ft_strlen(temp->str) > 0)
		{
			if ((ft_strchr(temp->str, 10)) ||
				(!ft_strchr(temp->str, 10) && ft_strlen(buff) == 0))
				if (ft_rtn_line(temp, buff, line) == 1)
					return (1);
		}
		else if (bytes == 0)
			return (0);
	}
	return (0);
}
