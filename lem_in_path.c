ft_get_room // get real number of the room its index in rooms_arr 

int			DFS_VISIT(t_ants *farmer, int vertex, int i)
{
	char		*str;

	if (vertex == (ft_bidlen(farmer->rooms_arr) - 1))
		return (1);
	str = farmer->adj_matrix[vertex];
	while (ft_strchr(str, '1'))
	{
		if (!ft_bidchr(farmer->visited_roms, ft_get_room(farmer->rooms_arr[ft_strchr(str, '1') - str])))
		{
			farmer->visited_rooms[i] = farmer->rooms_arr[ft_strchr(str, '1') - str];
			return (DFS_VISIT(farmer,
				ft_get_rooms_coord(farmer->rooms_arr[ft_strchr(str, '1') - str], farmer->rooms_arr), ++i));
		}
		str = ft_strchr(str, '1') - str;
	}
	return (0);
}

int			DFS(t_ants *farmer)
{
	if (ft_strchr(farmer->adj_matrix[0], '1'))
	{
		farmer->visited_rooms[0] = farmer->rooms_arr[0];
		return (DFS_VISIT(farmer, 0, 1));
	}
	else
		return (0);
}