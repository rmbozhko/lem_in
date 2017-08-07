#include "lem_in_bonus.h"

static	void		ft_handle_numbers(int num)
{
	if (num == '0')
		printf("%c%c%c%c", 0x30, 0xE2, 0x83, 0xA3);
	else if (num == '1')
		printf("%c%c%c%c", 0x31, 0xE2, 0x83, 0xA3);
	else if (num == '2')
		printf("%c%c%c%c", 0x32, 0xE2, 0x83, 0xA3);
	else if (num == '3')
		printf("%c%c%c%c", 0x33, 0xE2, 0x83, 0xA3);
	else if (num == '4')
		printf("%c%c%c%c", 0x34, 0xE2, 0x83, 0xA3);
	else if (num == '5')
		printf("%c%c%c%c", 0x35, 0xE2, 0x83, 0xA3);
	else if (num == '6')
		printf("%c%c%c%c", 0x36, 0xE2, 0x83, 0xA3);
	else if (num == '7')
		printf("%c%c%c%c", 0x37, 0xE2, 0x83, 0xA3);
	else if (num == '8')
		printf("%c%c%c%c", 0x38, 0xE2, 0x83, 0xA3);
	else if (num == '9')
		printf("%c%c%c%c", 0x39, 0xE2, 0x83, 0xA3);
}

static	void		ft_print_line(char *line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= 48 && line[i] <= 57)
			ft_handle_numbers(line[i]);
		else
			printf("%c", line[i]);
		i++;
	}
}

static void		ft_l_r_a(char *line, int flag, int sub_flag, int i)
{
	if (flag == 1)
	{
		printf("%c%c%c%c  ", 0xF0, 0x9F, 0x9B, 0xA3);
		while (line[++i])
			(line[i] == '-') ? printf("%c%c%c%c", 0xF0, 0x9F, 0x94, 0x97) : printf("%c", line[i]);
	}
	else if (flag == 2 && (line[0] == '#' && line[1] != '#'))
	{
		(ft_strcmp(line + 1, "start") == 0) ? printf("%c%c%c%c", 0xF0, 0x9F, 0x9A, 0xA9) : 0;
		(ft_strcmp(line + 1, "end") == 0) ? printf("%c%c%c%c", 0xF0, 0x9F, 0x8F, 0x81) : 0;
		printf("#");
		ft_print_line(line);
		(ft_strcmp(line + 1, "start") == 0) ? printf("%c%c%c%c", 0xF0, 0x9F, 0x9A, 0xA9) : 0;
		(ft_strcmp(line + 1, "end") == 0) ? printf("%c%c%c%c", 0xF0, 0x9F, 0x8F, 0x81) : 0;
		printf("\n");
	}
	else if (flag == 0)
	{
		(sub_flag == 0) ? printf("%c%c%c%c", 0xF0, 0x9F, 0x90, 0x9C) : 0;
		(sub_flag == 1) ? printf("%c%c%c%c", 0xF0, 0x9F, 0x8F, 0xA0) : 0;
		ft_print_line(line);
		(sub_flag == 0) ? printf("%c%c%c%c\n", 0xF0, 0x9F, 0x90, 0x9C) : 0;
		(sub_flag == 1) ? printf("%c%c%c%c\n", 0xF0, 0x9F, 0x8F, 0xA0) : 0;
	}
}

void		ft_handle_ansi_color_codes(char *line)
{
	if (ft_words_count(line, '-') > 1)
	{
		ft_l_r_a(line, 1, 0, -1);
		printf("\n");
	}
	else if (ft_is_numeric(ft_strchr(line, 'm') + 1))
		ft_l_r_a(ft_strchr(line, 'm') + 1, 0, 0, -1);
	else if (ft_strstr((ft_strchr(line, 'm') + 1), "ERROR"))
	{
		ft_handle_error();
		printf("\n");
	}
	else
		printf("%s\n", line);
}

int			main(void)
{
	char		*line;

	while (get_next_line(0, &line) > 0)
	{
		if (ft_strchr(line, 'm'))
			ft_handle_ansi_color_codes(line);
		else if (line[0] == '#')
			ft_l_r_a(line + 1, 2, 0, -1);
		else if (ft_words_count(line, ' ') == 3 && ft_is_numeric(ft_strsplit(line, ' ')[1])
			&& ft_is_numeric(ft_strsplit(line, ' ')[2]))
			ft_l_r_a(line, 0, 1, -1);
		else if (ft_words_count(line, '-') > 1)
		{
			ft_l_r_a(line, 1, 0, -1);
			printf("\n");
		}
		else if (ft_strstr(line, "ERROR"))
		{
			ft_handle_error();
			printf("\n");
		}
		else
			printf("%s\n", line);
	}
	return (0);
}