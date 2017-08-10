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

static int		ft_rtn_line(char *temp, char buff[], char **line/*, t_validation *valid*/)
{
	char		*str;
	char		*string;
	static	int		i = 0;

	// printf("ft_rtn_line:%s\n", temp);
	if (i == 0)
	{
		// ft_memdel((void**)&line);
		*line = ft_strnew(0);//(char*)malloc(sizeof(char*));
		// printf("i:%d\n", i);
		string = ft_strnew(0);
	}
	// // str = valid->file;
	str = temp;
	string = *line;
	if (NL_CODE)
	{
		// printf("YO, Wassup?!\n");
		*line = ft_strsub(temp, 0, S_C_SUB);
		ft_memdel((void**)&string);
		string = *line;
		// valid->file = ft_strjoin(valid->file, *line);
		// free(str);
		// str = valid->file;
		// valid->file = ft_strjoin(valid->file, "\n");
		// free(str);
		temp = ft_strsub(temp, S_C_SUB, ft_strlen(temp));
		ft_memdel((void**)&str);
		i++;
		return (1);
	}
	else if ((!(NL_CODE)) && ft_strlen(buff) == 0)
	{
		ft_memdel((void**)&string);
		// valid->file = ft_strjoin(valid->file, temp);
		// free(str);
		// str = valid->file;
		// valid->file = ft_strjoin(valid->file, "\n");
		// free(str);
		*line = ft_strdup(temp);
		ft_memset(temp, 0, ft_strlen(temp));
		ft_memdel((void**)&str);
		i++;
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line/*, t_validation *valid*/)
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
		// printf("str:%s\n", str);
		ft_memdel((void**)&str); // here
		str = temp;
		(bytes < BUFF_SIZE) ? buff[bytes] = '\0' : 0;
		temp = ft_strjoin(temp, buff);
		// printf("temp:%s\n", temp);
		str = temp;
		// ft_memdel((void**)&str); // here but no visible output
		// ft_memdel((void**)&str);
		(temp[0] == '\n') ? temp += 1 : 0;
		if (ft_strlen(temp) > 0)
		{
			if ((NL_CODE) || (!NL_CODE && ft_strlen(buff) == 0))
			{
				// printf("strlen:%s\n", temp);
				if (ft_rtn_line(temp, buff, line/*, valid*/) == 1)
					return (1);
			}
		}
		else if (bytes == 0 || (bytes == 1 && buff[0] == '\n'))
			return (0);
	}
	// return (-1);
	return (0);
}
