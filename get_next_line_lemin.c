#include "lem_in.h"

static int		ft_rtn_line(t_node *temp, char buff[], char **line, t_validation *valid)
{
	char		*str;

	str = valid->file;
	if (NL_CODE)
	{
		valid->file = ft_strjoin(str, ft_strsub(temp->str, 0, S_C_SUB + 1));
		free(str);
		*line = ft_strsub(temp->str, 0, S_C_SUB);
		temp->str += S_C_SUB;
		return (1);
	}
	else if ((!(NL_CODE)) && ft_strlen(buff) == 0)
	{
		valid->file = ft_strjoin(str, ft_strdup(temp->str));
		free(str);
		*line = ft_strdup(temp->str);
		ft_memset(temp->str, 0, ft_strlen(temp->str));
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line, t_validation *valid)
{
	static	char		*temp = ft_strdup("\0");
	char				*str;
	int					bytes;
	char				buff[BUFF_SIZE + 1];

	free(*line);
	if (IF_FP || IF_SP)
		return (-1);
	ft_memset(buff, '\0', BUFF_SIZE);
	while ((bytes = read(fd, buff, BUFF_SIZE)) >= 0)
	{
		str = temp;
		temp = ft_strjoin(temp, buff);
		free(str);
		(temp[0] == '\n') ? temp += 1 : 0;
		if (ft_strlen(temp) > 0)
		{
			if (ft_strchr(temp->str, 10) || (!ft_strchr(temp->str, 10) && ft_strlen(buff) == 0))
				if (ft_rtn_line(temp, buff, line, valid) == 1)
					return (1);
		}
		else if (bytes == 0)
			return (0);
	}
	return (-1);
}