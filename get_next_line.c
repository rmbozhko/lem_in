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

static int		ft_rtn_line(char *temp, char buff[], char **line, t_validation *valid)
{
	char		*str;
	char		*string;
	char		*def;
	// static	int		i = 0;

	// if (i == 0)
	// {
	// 	// valid->file = ft_strnew(0);
	// 	// ft_memdel((void**)&line);
	// 	// *line = ft_strnew(0); // because lem_in allocate memory for line
	// }
	def = valid->file;
	str = temp;
	string = *line;
	// printf("temp:%s|%zu", temp, ft_strlen(buff));
	if (NL_CODE)
	{
		// ft_memdel((void**)&string);
		*line = ft_strsub(temp, 0, S_C_SUB);
		ft_memdel((void**)&string);
		string = *line;
		// (i == 0) ? ft_memdel((void**)&valid->file) : 0;
		def = valid->file;
		valid->file = ft_strjoin(valid->file, *line);
		ft_memdel((void**)&def);
		def = valid->file;
		valid->file = ft_strjoin(valid->file, "\n");
		ft_memdel((void**)&def);
		def = valid->file;
		// temp = ft_strsub(temp, S_C_SUB, ft_strlen(temp)); // 10 leaks wegen diese Instruktion
		ft_memdel((void**)&str);
		// i++;
		// printf("return\n");
		return (1);
	}
	else if ((!(NL_CODE)) && ft_strlen(buff) == 0)
	{
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
		// i++;
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line, t_validation *valid)
{
	static	char		*head = NULL;
	char				*temp;
	int					bytes;
	char				buff[BUFF_SIZE + 1];																																													
	char				*str;

	if (IF_FP || IF_SP)
		return (-1);
	!(head) ? head = ft_strnew(BUFF_SIZE + 1) : 0;
	temp = head;
	str = ft_strnew(0);
	while ((bytes = read(fd, buff, BUFF_SIZE)) >= 0)					
	{
		ft_memdel((void**)&str); // here
		str = temp;
		// (bytes < BUFF_SIZE) ? buff[bytes] = '\0' : 0;
		temp = ft_strjoin(temp, buff);
		str = temp;
		// ft_memdel((void**)&str); // here but no visible output
		// ft_memdel((void**)&str);
		
		// (temp[0] == '\n') ? temp += 1 : 0; // proper one
		if (temp[0] == '\n')
		{
			ft_memdel((void**)&str);
			temp = ft_strsub(temp, 1, ft_strlen(temp));
			str = temp;
		}
		if (ft_strlen(temp) > 0)
		{
			if ((NL_CODE) || (!NL_CODE && ft_strlen(buff) == 0))
			{
				if (ft_rtn_line(temp, buff, line, valid) == 1)
					return (1);
			}
		}
		else if (bytes == 0 || (bytes == 1 && buff[0] == '\n'))
		{
			// ft_memdel((void**)&valid->file);
			return (0);
		}
	}
	return (-1);
	// return (0);
}
