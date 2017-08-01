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

char        **ft_init_ants(char *path, int ants_num)
{
    int         i;
    char        **temp;
    
    temp = (char**)malloc(sizeof(char*) * ants_num);
    i = 0;
    while (i < ants_num)
        temp[i++] = ft_strdup(path);
    temp[i] = NULL;
    return (temp);
}

size_t          ft_update_ants_arr(char **arr)
{
    size_t      i;
    
    i = 0;
    while (arr[i] == NULL)
        i++;
    return (i);
}       

void            ft_mv_ants(char **ants_arr, size_t ant_num)
{
  size_t      temp;
  size_t      j;
  
  j = ft_update_ants_arr(ants_arr);
  temp = 0;
  while (temp <= ant_num)
  {
    ft_putchar('L');
    ft_putstr(ft_itoa(temp + 1));
    ft_putchar('-');
    ants_arr[j] += 2;
    ft_putchar(&ants_arr[j]);
    (ants_arr[j][1] == '\0') ? ft_memdel((void**)&ants_arr[j]) : 0;
    ((++temp) <= ant_num) ? ft_putchar(' ') : 0;
    j++;
  }
  ft_putchar('\n');
}

void      ants_travel(t_lemin *farmer)
{
  size_t    ants_num;
  char      **ants_arr;
  
  ants_num = 0;
  ants_arr = ft_init_ants(farmer->path[0]->path_str, farmer->ants_num);
  while (ants_num < farmer->ants_num)
  {
      ft_mv_ants(ants_arr, ants_num++);
  }
}