 #include "lem_in.h"

// static int			ft_dfs_visit(t_lemin *farmer, int vertex, int counter)
// {
// 	char		*str;
// 	int			i;

// 	i = 0;
// 	str = farmer->adj_matrix[vertex];
// 	while (ft_strchr((str + i), '1'))
// 	{
// 		if (ft_get_rooms_coord(farmer->rooms_arr[ft_strchr(str + i, '1') - str], farmer->visited_rooms) == -1)
// 		{
// 			farmer->visited_rooms[counter] = farmer->rooms_arr[ft_strchr(str + i, '1') - str];
// 			if (ft_get_rooms_coord(farmer->rooms_arr[ft_bidlen(farmer->rooms_arr) - 1], farmer->visited_rooms) != -1)
// 			    return (1);
// 			ft_dfs_visit(farmer, ft_strchr(str + i, '1') - str, ++counter);
// 			//ft_get_rooms_coord(farmer->rooms_arr[ft_strchr(str + i, '1') - str], farmer->rooms_arr), ++counter));
// 		}
// 		if (ft_strchr(str + 1 + i, '1') != NULL)
// 			i =  ft_strchr(str + 1 + i, '1') - str;
// 		else
// 			break ;
// 	}
// 	return ((ft_get_rooms_coord(farmer->end_room, farmer->visited_rooms) != - 1) ? (1) : (0));
// }

// int			dfs(t_lemin *farmer)
// {
// 	if (ft_strchr(farmer->adj_matrix[0], '1'))
// 	{
// 		farmer->visited_rooms = (char**)malloc(sizeof(char*) * ft_bidlen(farmer->rooms_arr) + 1);
// 		farmer->visited_rooms[0] = farmer->rooms_arr[0];
// 		if (ft_dfs_visit(farmer, 0, 1))
// 		{
// 			ft_memdel((void**)&farmer->visited_rooms);
// 			return (1);
// 		}
// 		// free(farmer->visited_rooms);
// 	}
// 	return (0);
// }