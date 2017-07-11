 #include "lem_in.h"

static int			ft_dfs_visit(t_ants *farmer, int vertex, int i)
{
	char		*str;

	str = farmer->adj_matrix[vertex];
	while (ft_strchr(str, '1'))
	{
		if (ft_get_rooms_coord(farmer->visited_roms, farmer->rooms_arr[ft_strchr(str, '1') - str]) == -1)
		{
			farmer->visited_rooms[i] = farmer->rooms_arr[ft_strchr(str, '1') - str];
			if (ft_get_rooms_coord(farmer->visited_rooms, farmer->rooms_arr[ft_bidlen(farmer->rooms_arr)]) != -1)
			    return (1);
			return (ft_dfs_visit(farmer,
				ft_get_rooms_coord(farmer->rooms_arr[ft_strchr(str, '1') - str], farmer->rooms_arr), ++i));
		}
		str = ft_strchr(str, '1') - str + 1; // whether it returns the exact postion or position after the found char.
	}
	return (0);
}

int			dfs(t_ants *farmer)
{
	if (ft_strchr(farmer->adj_matrix[0], '1'))
	{
		farmer->visited_rooms[0] = farmer->rooms_arr[0];
		return (ft_dfs_visit(farmer, 0, 1));
	}
	else
		return (0);
}
