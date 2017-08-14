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
	size_t		ants_num;
	int 		rooms_counter;
	char		*start;
	char		*end;
	char		**rooms_arr;
	char		**adj_matrix;
	char		**y_coords;
	t_graph		**paths;
}				t_lemin;

typedef	struct s_validation
{
	char		*file;
	int			errors;
	int			start;
	int			end;
}				t_valid;

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

# define CHECK_ROOMS(x, i) ft_strcmp(temp[x], farmer->rooms_arr[i])
# define SNG_HASH_CMNT (line[0] == '#' && line[1] != '#')
# define RESV_COMMD (line[0] == '#' && line[1] == '#')
# define TRPL_HASH_CMNT (line[0] == '#' && line[1] == '#' && line[2] == '#')
# define IN_LINE(x) ft_strstr(line, x)
# define F_PART  IN_LINE("#cpaths_") || IN_LINE("#cmap_")
# define S_PART	 IN_LINE("#cants_") || IN_LINE("#cerror_")
# define COLOR_CASES (F_PART || S_PART)
# define DEL(x)	ft_memdel((void**)&x)

# define ENTRY_POINTS (valid->start == 1 && valid->end == 1)
# define ENTRY_ROOMS (ft_strlen(farmer->start) > 0 && ft_strlen(farmer->end) > 0 /*&& ft_strcmp(farmer->start, farmer->end) != 0*/)
# define F_ERRORS status != -1 && ENTRY_ROOMS && farmer->ants_num != -1
# define S_ERRORS ENTRY_POINTS && ((ft_bidcharcount(farmer->adj_matrix, '1') % 2 == 0) ? 1 : 0)
# define NO_ERRORS (F_ERRORS && S_ERRORS && valid->errors == 0)

// # define NO_ENTRY_POINTS (valid->start != 1 || valid->end != 1)
// # define NO_ENTRY_ROOMS (ft_strlen(farmer->start) == 0 && ft_strlen(farmer->end) == 0)
// # define ERRORS (status == -1 || NO_ENTRY_ROOMS || farmer->ants_num == -1 || NO_ENTRY_POINTS || ft_bidcharcount(farmer->adj_matrix, '1') == 0)

void				ft_errors_handling(int flag, t_bonus *bonus);
int					lem_in_validation(t_valid *valid, t_lemin *farmer, t_bonus *bonus, char *line);
int					get_next_line(const int fd, char **line, t_valid *valid);
int					ft_bidcharcount(char **link, char c);
int					dfs_iter(t_lemin *farmer, int i, int j, char *str);
int					ft_get_rooms_coord(char *room, char **temp);
void      			ants_travel(t_lemin *farmer, t_bonus *bonus, size_t ant_num);
int           		ft_get_color(char *str);
char      			**ft_init_colors_arr(void);
int 				ft_push_rooms(char **temp, t_lemin *farmer, int flag, t_valid *valid);
int            		ft_set_colors(t_bonus *bonus, char *line);
char				*get_in_out_rooms(t_lemin *farmer, t_valid *valid, char *temp);
void				ft_handle_path(char *str);
int					ft_count_char(char *str, char c);
void				ft_free_bidarr(char **arr, size_t len);
void				ft_push_link(char *link1, char *link2, t_lemin *farmer);
char        		**ft_create_bid_arr(size_t size, char *str);
int 				ft_get_rooms_coord(char *room, char **temp);
int 				ft_check_coords(char *x_coord, char *y_coord, t_lemin *farmer);
void				ft_add_room_coords(char *elem, t_lemin *farmer, int i);
void				ft_handle_path(char *str);
void				ft_print_paths(t_graph **paths, t_bonus *bonus);
void				ft_print_adj_matrix(char **arr);
void				ft_init_adj_matrix(t_lemin *farmer);
#endif
