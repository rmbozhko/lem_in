static void      ft_free_ndarr(void **arr, size_t i)
{
  while (arr[i] != NULL)
    ft_memdel(arr[i++]);
}

void      ft_determine_best_path(t_lemin *farmer, size_t len) //  len = ft_bidlen(farmer->paths)
{
  size_t      i;
  char        *path;
  size_t      p_len;

  i = 0;
  while (i < (len - 1))
  {
    if (farmer->paths[i]->path_len > farmer->paths[i + 1]->path_len)
    {
      path = farmer->paths[i]->path_str;
      p_len = farmer->paths[i]->path_len;
      farmer->paths[i]->path_str = farmer->paths[i + 1]->path_str;
      farmer->paths[i]->path_len = farmer->paths[i + 1]->path_len;
      farmer->paths[i + 1]->path_str = path;
      farmer->paths[i + 1]->path_len = p_len;
      i = 0;
    }
    else
      i++;
  }
  ft_free_ndarr(farmer->paths, 1);
}

void      ft_mv_ants(char **rm_arr, char *path, size_t ant_num, size_t room_num)
{
  size_t      temp;

  temp = 1;//0;
  while (ant_num)
  {
    ft_putstr("L");
    ft_putstr(ft_itoa(ant_num));
    ft_putstr("-");
    ft_putstr(rm_arr[temp++]);
    temp = (temp == room_num) ? 1/*0*/ : temp;
    ant_num--;
  }
}

void      ants_travel(t_lemin *farmer)
{
  size_t      counter;
  size_t      temp;

  counter = 1;
  temp = 1;//0;
  while (counter <= farmer->ants_num)
  {
      ft_mv_ants(farmer->rooms_arr, farmer->path[0]->path_str, counter, temp++);
      temp = (temp == farmer->paths[0]->path_len) ? 1/*0*/ : temp;
      counter++;
  }
}
