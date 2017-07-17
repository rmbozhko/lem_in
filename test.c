/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 15:58:24 by rbozhko           #+#    #+#             */
/*   Updated: 2017/02/22 15:58:27 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	t_graph		*ft_create_path_node(char *str)
{
	t_graph		*path;

	path = (t_graph*)malloc(sizeof(t_graph*));
	path->path_str = ft_strdup(str);
	path->path_len = ft_bidlen(ft_strsplit(str, ' '));//0;
	//free(str);
	return (path);
}

static	int		ft_count_char(char *str, char c)
{
	int			i;
	int			counter;

	counter = 0;
	i = -1;
	while (str[++i])
		counter += (str[i] == c) ? 1 : 0;
	return (counter);
}	

static int			ft_count_visited(char *str, char **temp)
{
	int			i;
	int			counter;

	counter = 0;
	i = 0;
	while (temp[i] != NULL)
	{
		if (ft_strstr(str, temp[i]))
			counter++;
		i++;
	}
	printf("%d\n", counter);
	return (counter);
}

static int			ft_update_room(t_lemin *farmer, char *str, int i)
{
	char 		*room;
	int			j;

	j = 0;
	room = farmer->adj_matrix[i];
	while (farmer->adj_matrix[i][j])
	{
		if (farmer->adj_matrix[i][j] == '1')
		{
			if (!ft_strstr(str, farmer->rooms_arr[j]))
				break ;
		}
		j++;
	}
	return (j);
}

static int			dfs(t_lemin *farmer, char *str, int counter, int i)
{

	/// WE don't need temp, paths_counter and all that fancy stuff inside first if except dfs_visit call
	// as all possible paths creation will occure in dfs_visit function and in its if,
	// where we check that end_room is somewhere nereby
	int			j;
	char 		*temp;
	int			paths_counter;

	paths_counter = counter;
	j = ft_update_room(farmer, str, i);
	str = ft_strjoin(str, farmer->rooms_arr[i]);
	str = ft_strjoin(str, " ");
	while (ft_strchr(farmer->adj_matrix[i] + j, '1'))
	{
		if (ft_strchr(farmer->adj_matrix[i] + j, '1'))
		{
			// str = ft_strjoin(str, farmer->rooms_arr[j]);
			// str = ft_strjoin(str, " ");
			printf("YO! What's up?\n");
			//temp = dfs_visit(farmer, j, counter, ...); // create a copy of str to allow each possible path to have the same begining
			if (ft_strstr(temp, farmer->end_room))//(ft_strlen(temp) > ft_strlen(str))
			{
				farmer->paths[counter++] = ft_create_path_node(temp);
			}
			free(temp);
		}
		if (ft_strchr(farmer->adj_matrix[i] + j + 1, '1') != NULL)
			j = ft_strchr(farmer->adj_matrix[i] + j + 1, '1') - farmer->adj_matrix[i];
		else
			break ;// do break in this case
		//j = ft_update_room(farmer, str, i); 
	}
	
	// we will place room inside dfs visi on counter place and NULL on counter + 1
	//(paths_counter < counter) ? farmer->paths[counter] = NULL : 0;
	
	return (ft_bidlen(farmer->paths));
	//return (counter);
}

int			dfs_iter(t_lemin *farmer)
{
	char 		*str;
	int			i;
	int			j;
	int			counter;

	counter = 0; // we can omit this variable as it can't be possible\
	// to have several answers in case of one direction
	i = 0;
	j = 0;
	str = ft_strnew(0);
	while (ft_strchr(farmer->adj_matrix[i] + j, '1'))
	{
		printf("I am inside!\n");
		//This down here isn't the proper one

		//str = ft_strjoin(str, farmer->rooms_arr[i]);
		//if (ft_strcmp(farmer->rooms_arr[i], farmer->end_room) == 0)
		//	break ;
		//str = ft_strjoin(str, " ");

		if ((ft_count_char(farmer->adj_matrix[i] + j, '1') - ft_count_visited(str, farmer->rooms_arr)) == 1)
		{

			//Check this out 
			str = ft_strjoin(str, farmer->rooms_arr[i]);
			if (ft_strstr(str, farmer->end_room))
				break ;
			str = ft_strjoin(str, " ");
			////
			j = (ft_count_char(farmer->adj_matrix[i] + j, '1') == 2) ? ft_update_room(farmer, str, i) : j;
			i = ft_strchr(farmer->adj_matrix[i] + j, '1') - farmer->adj_matrix[i];
			j = 0;
		}
		else //if ((ft_count_char(farmer->adj_matrix[i] + j, '1') - ft_count_visited(str, farmer->rooms_arr)) > 1)
		{
			break ;
		}
		//else
			//return (0);
	}
	if (ft_strstr(str, farmer->end_room))
	{
		farmer->paths[counter] = ft_create_path_node(str);
		return (1);
	}
	// extract already visited - write a function
	//check wether we need to return 0 (zero) one line further
	if (ft_strchr(farmer->adj_matrix[i], '1'))
		return ((dfs(farmer, str, counter, i) > counter) ? 1 : 0);
	return (0);
}
