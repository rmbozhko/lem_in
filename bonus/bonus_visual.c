/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_visual.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 14:41:26 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 14:41:27 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_bonus.h"

static	void		ft_print_line(char *line, int i)
{
	while (line[++i])
	{
		if (line[i] == '0')
			printf("%c%c%c%c", 0x30, 0xE2, 0x83, 0xA3);
		else if (line[i] == '1')
			printf("%c%c%c%c", 0x31, 0xE2, 0x83, 0xA3);
		else if (line[i] == '2')
			printf("%c%c%c%c", 0x32, 0xE2, 0x83, 0xA3);
		else if (line[i] == '3')
			printf("%c%c%c%c", 0x33, 0xE2, 0x83, 0xA3);
		else if (line[i] == '4')
			printf("%c%c%c%c", 0x34, 0xE2, 0x83, 0xA3);
		else if (line[i] == '5')
			printf("%c%c%c%c", 0x35, 0xE2, 0x83, 0xA3);
		else if (line[i] == '6')
			printf("%c%c%c%c", 0x36, 0xE2, 0x83, 0xA3);
		else if (line[i] == '7')
			printf("%c%c%c%c", 0x37, 0xE2, 0x83, 0xA3);
		else if (line[i] == '8')
			printf("%c%c%c%c", 0x38, 0xE2, 0x83, 0xA3);
		else if (line[i] == '9')
			printf("%c%c%c%c", 0x39, 0xE2, 0x83, 0xA3);
		else
			printf("%c", line[i]);
	}
}

static	void		ft_l_r_a(char *line, int flag, int sub_flag, int i)
{
	if (flag == 1)
	{
		printf("%c%c%c%c  ", 0xF0, 0x9F, 0x9B, 0xA3);
		while (line[++i])
			(line[i] == '-') ? printf(LINK) : printf("%c", line[i]);
	}
	else if (flag == 2 && (line[0] == '#' && line[1] != '#'))
	{
		(ft_strcmp(line + 1, "start") == 0) ? printf(ST_FLAG) : 0;
		(ft_strcmp(line + 1, "end") == 0) ? printf(FINISH) : 0;
		printf("#");
		ft_print_line(line, -1);
		(ft_strcmp(line + 1, "start") == 0) ? printf(ST_FLAG) : 0;
		(ft_strcmp(line + 1, "end") == 0) ? printf(FINISH) : 0;
		printf("\n");
	}
	else if (flag == 0)
	{
		(sub_flag == 0) ? printf(ANT) : 0;
		(sub_flag == 1) ? printf(HOUSE) : 0;
		ft_print_line(line, -1);
		(sub_flag == 0) ? printf(ANT) : 0;
		(sub_flag == 1) ? printf(HOUSE) : 0;
		printf("\n");
	}
}

static	void		ft_handle_ansi_color_codes(char *line)
{
	if (ft_words_count(line, '-') > 1)
	{
		ft_l_r_a(line, 1, 0, -1);
		printf("\n");
	}
	else if (ft_is_numeric(ft_strchr(line, 'm') + 1))
		ft_l_r_a(ft_strchr(line, 'm') + 1, 0, 0, -1);
	else if (ft_strstr((ft_strchr(line, 'm') + 1), "ERROR"))
		ft_handle_error();
	else
		printf("%s\n", line);
}

static	void		ft_handle_raw_input(char *line)
{
	char		**arr;

	arr = ft_strsplit(line, ' ');
	if (line[0] == '#')
		ft_l_r_a(line + 1, 2, 0, -1);
	else if (ft_words_count(line, ' ') == 3
		&& ft_is_numeric(arr[1])
		&& ft_is_numeric(arr[2]))
		ft_l_r_a(line, 0, 1, -1);
	else if (ft_words_count(line, '-') > 1)
	{
		ft_l_r_a(line, 1, 0, -1);
		printf("\n");
	}
	else if (ft_strstr(line, "ERROR"))
		ft_handle_error();
	else
		printf("%s\n", line);
	ft_free_bidarr(arr, ft_bidlen(arr));
}

int					main(void)
{
	char		*line;

	line = ft_strnew(0);
	while (get_next_line(0, &line, ft_strnew(0)) > 0)
	{
		if (ft_strchr(line, 'm'))
			ft_handle_ansi_color_codes(line);
		else
			ft_handle_raw_input(line);
	}
	ft_memdel((void**)&line);
	return (0);
}
