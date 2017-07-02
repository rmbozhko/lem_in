#include "lem_in.h"

static	int 	ft_str_num(char *str)
{
	int 		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

static	int 	ft_push_new_rooms(char **temp, t_lemin *farmer)
{
	size_t		i;
	int 		counter;

	counter = 0;
	if (ft_str_num(temp[1]) && ft_str_num(temp[2]))
	{
		i = 0;
		while (farmer->rooms_arr[i] != NULL)
		{
			printf("OLA-LINE:%s\n", temp[0]);
			if (CHECKING_ROOMS(0) == 0)
				return (1);
			i++;
		}
		counter += (!(farmer->rooms_arr[i] = ft_strdup(temp[0]))) ? 1 : 0;
		farmer->rooms_arr[i + 1] = NULL;
		printf("counter:%d\n", counter);
	}
	free(temp[2]);
	free(temp[1]);
	free(temp[0]);
	free(temp);
	return ((counter) ? 1 : 0);
}

static	char	*get_in_out_rooms(t_lemin *farmer, t_validation *valid)
{
	char		*line;

	line = ft_strdup("\0");
	while (get_next_line(0, &line, valid))
	{
		printf("line:%s\n", line);
		if (line[0] == '#')
			continue ;
		else if (line[0] != '#' && (ft_words_count(line, ' ') == 3))
		{
			printf("line_with_coords: %s\n", line);
			if (!ft_push_new_rooms(ft_strsplit(line, ' '), farmer))
				return (ft_strsplit(line, ' ')[0]);
			return (NULL);
		}
		else
		{
			printf("WTF:%s\n", line);
			return (NULL);
		}
	}
	return (NULL);
}

static	int 	ft_hash_case(char *line, t_validation *valid, t_lemin *farmer)
{
	printf("lines:%s\n", line);
	if (SNG_HASH_CMNT && (ft_strstr(line, "start") || ft_strstr(line, "end")))
	{
		printf("lines:%s\n", line);
		if (ft_strcmp(line, "#start"))
		{
			printf("HERE:%s\n", line);
			valid->start_point += 1;
			if ((farmer->start_room = get_in_out_rooms(farmer, valid)) == NULL)
			{
				printf("FUCKED UP\n");
				return (1);
			}
			else
			{
				printf("farmer->start_room:%s\n", farmer->start_room);
				return (0);
			}
		}
		else if (ft_strcmp(line, "#end"))
		{
			printf("HERE:%s\n", line);
			valid->end_point += 1;
			return ((farmer->end_room = get_in_out_rooms(farmer, valid)) == NULL) ? 1 : 0;
		}
		return (1);
	}
	return (0);
}

static	int 	ft_find_rooms(char **temp, t_lemin *farmer)
{
	size_t		i;
	int 		counter;

	i = 0;
	counter = 0;
	printf("%s : %s\n", temp[0], temp[1]);
	while (farmer->rooms_arr[i])
	{
		if (!CHECKING_ROOMS(0) || !CHECKING_ROOMS(1))
		{
			// printf("found:%s : %s : %s\n", farmer->rooms_arr[i], temp[0], temp[]);
			counter++;
		}
		i++;
	}
	free(temp[1]);
	free(temp[0]);
	free(temp);
	printf("counter:%d\n", counter);
	return ((counter == 2) ? 0 : 1);
}

static	int 	ft_validate_ants_num(char *line, t_lemin *farmer)
{
	int		temp;

	temp = ft_atoi(line);
	if (temp > 0 && temp < 2147483647)
	{
		farmer->ants_num = temp;
		return (0);
	}
	return (1);
}

int				lem_in_validation(t_validation *valid, t_lemin *farmer)
{
	char		*line;
	int 		status;

	line = ft_strdup("\0");
	while ((status = get_next_line(0, &line, valid)) > 0)
	{
		printf("buhaha_lines:%s\n", line);
		if (ft_str_num(line) && farmer->ants_num == -1)
			valid->errors += ft_validate_ants_num(line, farmer);
		else if (line[0] == '#')
		{
			// printf("OLA!\n");
			valid->errors += ft_hash_case(line + 1, valid, farmer);
			// printf("%d\n", valid->errors);
		}
		else if (ft_words_count(line, ' ') == 3)
		{
			
			valid->errors += ft_push_new_rooms(ft_strsplit(line, ' '), farmer);
		}
		else if (ft_words_count(line, '-') == 2)
		{
			printf("HERE!\n");
			valid->errors += ft_find_rooms(ft_strsplit(line, '-'), farmer);
		}
		else
			valid->errors += 1;
		// printf("farmer->start_room:%s\n", farmer->start_room);
		// printf("farmer->end_room:%s\n", farmer->end_room);
		if (valid->errors != 0)
		{
			// printf("%s : %d\n", line, valid->errors);
			return (0);
		}
	}
	if (ERRORS)
	{
		printf("valid->errors: %d\n", valid->errors);
		printf("errors:%zu\n", ft_strlen(farmer->end_room));
		return (0);
	}
	else
		return (1);
	// return ((ERRORS) ? 0 : 1);
}