/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:03:47 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 13:05:45 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	int		ft_no_nl_line(char *temp, char **line, t_valid *valid)
{
	char		*str;
	char		*string;
	char		*def;

	def = valid->file;
	str = temp;
	string = *line;
	ft_memdel((void**)&string);
	valid->file = ft_strjoin(valid->file, temp);
	ft_memdel((void**)&def);
	def = valid->file;
	valid->file = ft_strjoin(valid->file, "\n");
	ft_memdel((void**)&def);
	*line = ft_strdup(temp);
	ft_memset(temp, 0, ft_strlen(temp));
	ft_memdel((void**)&str);
	ft_memdel((void**)&def);
	return (1);
}

static int		ft_rtn_line(char *temp, char **line, t_valid *valid)
{
	char		*str;
	char		*string;
	char		*def;

	def = valid->file;
	str = temp;
	string = *line;
	if (NL_CODE)
	{
		*line = ft_strsub(temp, 0, S_C_SUB);
		ft_memdel((void**)&string);
		string = *line;
		def = valid->file;
		valid->file = ft_strjoin(valid->file, *line);
		ft_memdel((void**)&def);
		def = valid->file;
		valid->file = ft_strjoin(valid->file, "\n");
		ft_memdel((void**)&def);
		def = valid->file;
		ft_memdel((void**)&str);
		return (1);
	}
	else
		return (ft_no_nl_line(temp, line, valid));
}

int				gnl(const int fd, char **line, t_valid *valid, char *str)
{
	static	char		*head = NULL;
	char				*temp;
	int					bytes;
	char				buff[BUFF_SIZE + 1];

	if (IF_FP || IF_SP)
		return (-1);
	!(head) ? head = ft_strnew(BUFF_SIZE + 1) : 0;
	temp = head;
	while ((bytes = read(fd, buff, BUFF_SIZE)) >= 0)
	{
		DEL(str);
		(bytes < BUFF_SIZE) ? buff[bytes] = '\0' : 0;
		temp = ft_strjoin(temp, buff);
		str = temp;
		if (ft_strlen(temp) > 0)
		{
			if ((NL_CODE) || (!NL_CODE && ft_strlen(buff) == 0))
				return (ft_rtn_line(temp, line, valid));
		}
		else if (bytes == 0 || (bytes == 1 && buff[0] == '\n'))
			break ;
	}
	DEL(str);
	return (0);
}
