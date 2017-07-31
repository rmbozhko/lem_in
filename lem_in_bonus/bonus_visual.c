#include "lem_in_bonus.h"

static void    ft_handle_error(void)
{
    first_line();
    second_line();
    third_line();
    forth_line();
    fifth_line();
}

static void		ft_handle_rooms_ants(char *line, int flag)
{
	(flag == 0) ? printf("%c%c%c%c", 0xF0, 0x9F, 0x90, 0x9C) : 0;
	(flag == 1) ? printf("%c%c%c%c", 0xF0, 0x9F, 0x8F, 0xA0) : 0;
	printf("%s", line);
	(flag == 0) ? printf("%c%c%c%c\n", 0xF0, 0x9F, 0x90, 0x9C) : 0;
	(flag == 1) ? printf("%c%c%c%c\n", 0xF0, 0x9F, 0x8F, 0xA0) : 0;
}

static void		ft_handle_linkage(char *line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
			printf("%c%c%c%c", 0xF0, 0x9F, 0x94, 0x97);
		else
			printf("%c", line[i]);
		i++;
	}
}

static void		ft_handle_hashes(char *line)
{
	if (line[0] == '#' && line[1] != '#')
	{
		if (ft_strcmp(line + 1, "start") == 0)
		{
			printf("%c%c%c%c", 0xF0, 0x9F, 0x9A, 0xA9);
			printf("#%s", line);
			printf("%c%c%c%c\n", 0xF0, 0x9F, 0x9A, 0xA9);
		}
		else if (ft_strcmp(line + 1, "end") == 0)
		{
			printf("%c%c%c%c", 0xF0, 0x9F, 0x8F, 0x81);
			printf("#%s", line);
			printf("%c%c%c%c\n", 0xF0, 0x9F, 0x94, 0x9A);
		}
	}
}

int			main(void)
{
	char		*line;

	while (get_next_line(0, &line))
	{
		if (ft_is_numeric(line))
			ft_handle_rooms_ants(line, 0);
		else if (line[0] == '#')
			ft_handle_hashes(line + 1);
		else if (ft_words_count(line, ' ') == 3 && ft_is_numeric(ft_strsplit(line, ' ')[1])
			&& ft_is_numeric(ft_strsplit(line, ' ')[2]))
			ft_handle_rooms_ants(line, 1);
		else if (ft_words_count(line, '-') > 1)
		{
			ft_handle_linkage(line);
			printf("\n");
		}
		else if (ft_strcmp(line, "ERROR") == 0)
			ft_handle_error();
		else
			printf("%s\n", line);
	}
	return (0);
}