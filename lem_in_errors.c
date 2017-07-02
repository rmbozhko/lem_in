#include "lem_in.h"

void		ft_errors_handling(int flag)
{
	if (flag)
		perror("ERROR\n");
	else
		ft_putstr(strerror(errno));
	exit(0);
}