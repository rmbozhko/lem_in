#include "lem_in.h"

void		ft_errors_handling(int flag)
{
	if (flag)
		ft_putstr("ERROR\n");
	else
		ft_putstr(strerror(errno));
	exit(0);
}

static	void		ft_help_ants(t_lemin *farmer, t_validation *valid)
{
	int 		res;

	if ((res = lem_in_validation(valid, farmer)))
	{
		printf("Hura! Now we can print out everything we have read.");
		// GO ON !!
	}
	else
	{
		printf("%d\n", res);
		ft_errors_handling(1);
	}
}

int					main(void)
{
	t_lemin 		farmer;
	t_validation	valid;

	valid.start_point = 0;
	valid.end_point = 0;
	farmer.ants_num = -1;
	farmer.start_room = ft_strdup("\0");
	farmer.end_room = ft_strdup("\0");
	farmer.rooms_arr = (char**)malloc(sizeof(char*));
	farmer.rooms_arr[0] = NULL;
	valid.file = ft_strdup("\0");
	ft_help_ants(&farmer, &valid);
	return (0);
}