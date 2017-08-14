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

static int		ft_rtn_line(char *temp, char buff[], char **line, t_valid *valid)
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
	else if ((!(NL_CODE)) && ft_strlen(buff) == 0)
	{
		// printf("HERE_OLAOALOALOA_____________________!\n");
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
	return (0);
}

int				get_next_line(const int fd, char **line, t_valid *valid)
{
	static	char		*head = NULL;
	char				*temp;
	int					bytes;
	char				buff[BUFF_SIZE + 1];																																													
	char				*str; // passed as the forth parameter

	if (IF_FP || IF_SP)
		return (-1);
	!(head) ? head = ft_strnew(BUFF_SIZE + 1) : 0;
	temp = head;
	str = ft_strnew(0); // passed as the forth parameter
	while ((bytes = read(fd, buff, BUFF_SIZE)) >= 0)					
	{
		ft_memdel((void**)&str);
		//str = temp; // check it
		(bytes < BUFF_SIZE) ? buff[bytes] = '\0' : 0;
		temp = ft_strjoin(temp, buff);
		str = temp;
		if (ft_strlen(temp) > 0)
		{
			if ((NL_CODE) || (!NL_CODE && ft_strlen(buff) == 0))
				if (ft_rtn_line(temp, buff, line, valid) == 1)
					return (1);
		}
		else if (bytes == 0 || (bytes == 1 && buff[0] == '\n'))
		{
			ft_memdel((void**)&str);
			return (0);
		}
	}
	return (0);
}
