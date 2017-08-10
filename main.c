/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 14:00:00 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/10 14:02:53 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lem_in.h"

int		main(void)
{
	int				fd;
	char			*line;
	t_validation	node;

	fd = open("tests/test2", O_RDONLY);
	while (get_next_line(fd, &line, &node) > 0)
	{
		// printf("%s\n", line);
	}
	printf("%s\n", node.file);
	while (1);
	return (0);
}
