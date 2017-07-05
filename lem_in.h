#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <errno.h>
# include <string.h>
# include <stdio.h>

typedef	struct 	s_lemin
{
	int			ants_num;
	char		*start_room;
	char		*end_room;
	char		**rooms_arr;
	char		**adj_matrix;
}				t_lemin;

typedef	struct s_validation
{
	char		*file;
	int			errors;
	int			start_point;
	int			end_point;
}				t_validation;

# define CHECKING_ROOMS(x) ft_strcmp(temp[x], farmer->rooms_arr[i])
# define SNG_HASH_CMNT (line[0] == '#' && line[1] != '#')
# define RESV_COMMD (line[0] == '#' && line[1] == '#')
# define TRPL_HASH_CMNT (line[0] == '#' && line[1] == '#' && line[2] == '#')
# define NO_ENTRY_POINTS (valid->start_point != 1 || valid->end_point != 1 || !ft_any_links(farmer->adj_matrix, '1'))
# define NO_ENTRY_ROOMS (ft_strlen(farmer->start_room) == 0 && ft_strlen(farmer->end_room) == 0)
# define ERRORS (status == -1 || NO_ENTRY_ROOMS || farmer->ants_num == -1 || NO_ENTRY_POINTS)

void				ft_errors_handling(int flag);
int				lem_in_validation(t_validation *valid, t_lemin *farmer);
int				get_next_line(const int fd, char **line, t_validation *valid);
void				ft_putbidstr(char **temp);
#endif
