/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 16:04:36 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 16:10:34 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <errno.h>
# include <string.h>
# include <fcntl.h>

typedef	struct	s_node
{
	char		*str;
}				t_node;

typedef	struct	s_bonus
{
	int			cerror;
	int			cmap;
	int			cants;
	int			cpaths;
	char		**color_arr;
}				t_bonus;

typedef	struct	s_graph
{
	char		*path_str;
	size_t		path_len;
}				t_graph;

typedef	struct	s_lemin
{
	char		**x_coords;
	int			ants;
	int			rooms_counter;
	char		*start;
	char		*end;
	char		**rooms_arr;
	char		**adj_matrix;
	char		**y_coords;
	t_graph		**paths;
}				t_lemin;

typedef	struct	s_validation
{
	int			status;
	char		*file;
	int			errors;
	int			start;
	int			end;
}				t_valid;

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
# define MOVE_RIGHT(arr, i, j, x, c) ft_strchr(arr[i] + j + x, c) - arr[i]
# define SPACE *(ft_add_smth(&str, farmer, 0))
# define IS_NT_SPC (str[ft_strlen(str) - 1] != ' ')
# define JOIN_RM_SPC ft_strjoin(IS_NT_SPC ? SPACE : str, farmer->rooms_arr[j])
# define ACCESS_ELEM(x, i) (x[i][ft_strlen(x[i]) - 1])
# define GO_TO_END (ACCESS_ELEM(farmer->adj_matrix, i) == '1')
# define COUNT_LINKS(j) ft_count_char(farmer->adj_matrix[i] + j, '1')
# define VISITED ft_count_visited(str, farmer->adj_matrix[i], farmer->rooms_arr)
# define UPDATE_WAY(x, y) ft_strsub(arr[j], x, y)
# define FORBIDDEN_CHARS (temp[0][0] != '#' && temp[0][0] != 'L')
# define GEN_ROOMS_CHECK ft_strstr(line, "#start") || ft_strstr(line, "#end")
# define ENTRY_POINTS (valid->start == 1 && valid->end == 1)
# define GEN_ROOMS (ft_strlen(farmer->start) > 0 && ft_strlen(farmer->end) > 0)
# define F_ERRORS valid->status != -1 && GEN_ROOMS && farmer->ants != -1
# define S_ERRORS ENTRY_POINTS && (!(c_count(farmer->adj_matrix, '1') % 2))
# define NO_ERRORS (F_ERRORS && S_ERRORS && valid->errors == 0)
# define ANTS_MOVE MOVE_RIGHT(arr, j, 0, 0, ' ')

void			ft_errors_handling(int flag, t_bonus *bonus);
int				validate(t_valid *v, t_lemin *f, t_bonus *b, char *l);
int				gnl(const int fd, char **line, t_valid *valid, char *str);
int				c_count(char **link, char c);
int				dfs_iter(t_lemin *farmer, int i, int j, char *str);
int				ft_get_rooms_coord(char *room, char **temp);
void			ants_travel(t_lemin *farmer, t_bonus *bonus, int ant_num);
char			**ft_init_colors_arr(void);
int				ft_push_rooms(char **temp, t_lemin *farmer, int flag);
int				ft_set_colors(t_bonus *bonus, char *line);
char			*get_in_out_rooms(t_lemin *a, t_valid *b, char *c);
void			ft_handle_path(char *str);
void			ft_push_link(char *link1, char *link2, t_lemin *farmer);
int				ft_check_coords(char *x, char *y, t_lemin *f);
void			ft_add_room_coords(char *elem, t_lemin *farmer, int i);
void			ft_handle_path(char *str);
void			ft_print_paths(t_graph **paths, t_bonus *bonus);
void			ft_print_adj_matrix(char **arr);
void			ft_init_adj_matrix(t_lemin *farmer);
void			ft_free_bidarr(char **arr, size_t len);
int				ft_count_visited(char *str, char *temp, char **arr);
int				ft_check_repeating_paths(t_graph **graps, char *path);
void			ft_push_path_node(char *str, t_lemin *farmer, int flag);
#endif
