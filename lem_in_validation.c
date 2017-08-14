#include "lem_in.h"

int 		ft_push_rooms(char **temp, t_lemin *farmer, int flag, t_valid *valid)
{
	size_t		i;
	int 		counter;

	counter = 1;
	if (ft_is_numeric(temp[1]) && ft_is_numeric(temp[2]) && (temp[0][0] != '#' && temp[0][0] != 'L'))
	{
		counter = 0;
		i = 0;
		if (ft_strcmp(temp[0], farmer->start) == 0 || ft_strcmp(temp[0], farmer->end) == 0)
			counter = 1;
		while (farmer->rooms_arr[++i] != NULL)
			(CHECK_ROOMS(0, i) == 0) ? counter = 1 : 0;
		counter = (ft_check_coords(temp[1], temp[2], farmer)) ? counter : 1;
		if (flag == 1 && counter == 0)
			ft_add_room_coords(temp[0], farmer, i);
		(counter == 0) ? ft_add_room_coords(temp[1], farmer, -2) : 0;
		(counter == 0) ? ft_add_room_coords(temp[2], farmer, -1) : 0;
	}
	free(temp[2]);
	free(temp[1]);
	free(temp[0]);
	free(temp);
	return ((counter) ? 1 : 0);
}

static	int 	ft_hash_case(char *line, t_valid *valid, t_lemin *farmer, t_bonus *bonus)
{
	char		*temp;

	temp = NULL;
	if (SNG_HASH_CMNT && (ft_strstr(line, "#start") || ft_strstr(line, "#end") || COLOR_CASES))
	{
		if (ft_strcmp(line, "#start") == 0 || ft_strcmp(line, "#end") == 0)
		{
			(ft_strcmp(line, "#start") == 0) ? valid->start++ : valid->end++;
			if ((temp = get_in_out_rooms(farmer, valid, NULL)) != NULL)
			{
				(ft_strcmp(line, "#start") == 0) ? DEL(farmer->start) : DEL(farmer->end);
				if (ft_strcmp(line, "#start") == 0)
					farmer->start = temp;
				else
					farmer->end = temp;
				return (0);
			}
		}
		else if (COLOR_CASES)
			return (ft_set_colors(bonus, line));
		DEL(temp);
		return (1);
	}
	// DEL(temp); // check it out
	return (0);
}

static	int 	ft_find_rooms(char **temp, t_lemin *farmer)
{
	size_t		i;
	int 		counter;

	i = 0;
	counter = 0;
	((ft_bidlen(farmer->adj_matrix)) == 0) ? ft_init_adj_matrix(farmer) : 0;
	while (farmer->rooms_arr[i])
	{
		if (!CHECK_ROOMS(0, i))
			counter++;
		if (!CHECK_ROOMS(1, i))
			counter++;
		i++;
	}
	(counter == 2) ? ft_push_link(temp[0], temp[1], farmer) : 0;
	free(temp[1]);
	free(temp[0]);
	free(temp);
	return ((counter == 2) ?  (0) : (1));
}

static	int 	ft_validate_ants_num(char *line, t_lemin *farmer)
{
	intmax_t	temp;

	temp = ft_atoi_base(line, 10);
	if (temp >= 1 && temp <= 2147483647)
	{
		farmer->ants_num = temp;
		return (0);
	}
	return (1);
}

int				lem_in_validation(t_valid *valid, t_lemin *farmer, t_bonus *bonus, char *line)
{
	int 		status;

	while ((status = get_next_line(0, &line, valid)) > 0)
	{
		if (ft_is_numeric(line))
			valid->errors += (farmer->ants_num == -1) ? ft_validate_ants_num(line, farmer) : 1;
		else if (line[0] == '#')
			valid->errors += ft_hash_case(line + 1, valid, farmer, bonus);
		else if (ft_words_count(line, ' ') == 3)
			valid->errors += ft_push_rooms(ft_strsplit(line, ' '), farmer, 1, valid);
		else if (ft_words_count(line, '-') == 2 && ENTRY_ROOMS && farmer->ants_num != -1)
			valid->errors += ft_find_rooms(ft_strsplit(line, '-'), farmer);
		else
		{
			if (NO_ERRORS)
			{
				ft_errors_handling(1, bonus);
				break ;
			}
			valid->errors += 1;
		}
		if (valid->errors != 0)
			break ;
	}
	DEL(line);
	return ((NO_ERRORS) ? (dfs_iter(farmer, 0, 0, ft_strnew(0))) : (0));
}
