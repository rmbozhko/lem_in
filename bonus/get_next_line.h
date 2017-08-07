/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 12:30:48 by rbozhko           #+#    #+#             */
/*   Updated: 2017/02/22 16:19:46 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1
# define S_C_SUB (ft_strchr(temp->str, 10) - temp->str)
# define IF_FP ((fd < 0 || fd > 4096) || ((read(fd, buff, 0)) == -1 && !(head)))
# define IF_SP (!(line) || !(ft_memset(buff, 0, BUFF_SIZE + 1)))

# include "../libft/libft.h"
# include <fcntl.h>

typedef	struct	s_node
{
	int				fd;
	char			*str;
	struct s_node	*next;
}				t_node;

int				get_next_line(const int fd, char **line);

#endif
