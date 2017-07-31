#include "lem_in.h"

int 	ft_validate_ants_num(char *line, t_lemin *farmer)
{
	int		temp;

	temp = ft_atoi(line);
	if (temp >= 1 && temp <= 2147483647)
	{
		farmer->ants_num = temp;
		return (0);
	}
	return (1);
}