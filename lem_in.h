#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

typedef	struct	s_node
{
	char			*str;
}				t_node;

typedef   struct    s_bonus
{
  int         cerror;
  int         cmap;
  int         cants;
  int 		  cpaths;
  char        **color_arr;
}					t_bonus;

typedef	struct 	s_graph
{
	char			*path_str;
	size_t			path_len;
}				t_graph;

typedef	struct 	s_lemin
{
	char		**x_coords;
	int			ants_num;
	int 		rooms_counter;
	char		*start_room;
	char		*end_room;
	char		**rooms_arr;
	char		**adj_matrix;
	char		**y_coords;
	t_graph		**paths;
}				t_lemin;

typedef	struct s_validation
{
	char		*file;
	int			errors;
	int			start_point;
	int			end_point;
}				t_validation;

/*
//MACROS fo GNL with leaks
# define BUFF_SIZE 9999
# define NL_CODE ft_strchr(temp->str, 10)
# define S_C_SUB (NL_CODE - temp->str)
# define IF_FP ((fd < 0 || fd > 4096) || ((read(fd, buff, 0)) == -1 && !(head)))
# define IF_SP (!(line) || !(ft_memset(buff, 0, BUFF_SIZE + 1)))
*/

# define BUFF_SIZE 1
# define NL_CODE ft_strchr(temp, '\n')
# define S_C_SUB (NL_CODE - temp)
# define IF_FP ((fd < 0 || fd > 4096) || ((read(fd, buff, 0)) == -1 && !(head)))
# define IF_SP (!(line) || !(ft_memset(buff, 0, BUFF_SIZE + 1)))

# define CHECKING_ROOMS(x, i) ft_strcmp(temp[x], farmer->rooms_arr[i])
# define SNG_HASH_CMNT (line[0] == '#' && line[1] != '#')
# define RESV_COMMD (line[0] == '#' && line[1] == '#')
# define TRPL_HASH_CMNT (line[0] == '#' && line[1] == '#' && line[2] == '#')

# define ENTRY_POINTS (valid->start_point == 1 && valid->end_point == 1)
# define ENTRY_ROOMS (ft_strlen(farmer->start_room) > 0 && ft_strlen(farmer->end_room) > 0 /*&& ft_strcmp(farmer->start_room, farmer->end_room) != 0*/)
# define NO_ERRORS (status != -1 && ENTRY_ROOMS && farmer->ants_num != -1 && ENTRY_POINTS && ((ft_bidcount(farmer->adj_matrix, '1') % 2 == 0) ? 1 : 0))

// # define NO_ENTRY_POINTS (valid->start_point != 1 || valid->end_point != 1)
// # define NO_ENTRY_ROOMS (ft_strlen(farmer->start_room) == 0 && ft_strlen(farmer->end_room) == 0)
// # define ERRORS (status == -1 || NO_ENTRY_ROOMS || farmer->ants_num == -1 || NO_ENTRY_POINTS || ft_bidcount(farmer->adj_matrix, '1') == 0)

void				ft_errors_handling(int flag, t_bonus *bonus);
int					lem_in_validation(t_validation *valid, t_lemin *farmer, t_bonus *bonus, char *line);
int					get_next_line(const int fd, char **line, t_validation *valid);
int					ft_bidcount(char **link, char c);
int					dfs_iter(t_lemin *farmer, int i, int j, char *str);
int					ft_get_rooms_coord(char *room, char **temp);
void      			ants_travel(t_lemin *farmer, t_bonus *bonus);
int           		ft_get_color(char *str);
char      			**ft_init_colors_arr(void);
int 				ft_push_new_rooms(char **temp, t_lemin *farmer, int flag, t_validation *valid);
int            		ft_set_colors(t_bonus *bonus, char *line);
int					dfs(t_lemin *farmer);
void				ft_print_paths(t_graph **paths, t_bonus *bonus, int flag);
void				ft_handle_path(char *str);
int					ft_count_char(char *str, char c);
size_t				ft_factorial(size_t size);
#endif
