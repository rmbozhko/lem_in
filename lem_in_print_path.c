#include "lem_in.h"

static char      *ft_determine_best_path(t_lemin *farmer, int len)
{
  size_t      i;
  char        *path;
  size_t      p_len;

  i = 0;
  path = farmer->paths[i++]->path_str;
  while (farmer->paths[i])
  {
    if (ft_strlen(farmer->paths[i]->path_str) < ft_strlen(path))
      path = farmer->paths[i]->path_str;
    i++;
  }
  return (path);
}

size_t          ft_update_ants_arr(char **arr)
{
    size_t      i;
    
    i = 0;
    while (ft_strcmp(arr[i], "\0") == 0)
      i++;
    return (i);
}     

size_t      ft_count_unfinished(char **arr)
{
    size_t      i;
    size_t      counter;
    
    counter = 0;
    i = 0;
    while (arr[i])
    {
        if (ft_strcmp(arr[i], "\0") != 0)
            counter++;
        i++;
    }
    return (counter);
}

void            ft_mv_ants(char **ants_arr, size_t ant_num, int flag)
{
  size_t      j;
  char        *temp;
  
  j = ft_update_ants_arr(ants_arr);
  (flag == 1) ? ant_num += j - 1 : 0;
  while (j <= ant_num)
  {
    ft_putchar('L');
    temp = ft_itoa(j + 1);
    ft_putstr(temp);
    ft_memdel((void**)&temp);
    ft_putchar('-');
    if (ft_strchr(ants_arr[j], ' '))
    {
      temp = ft_strsub(ants_arr[j], 0, ft_strchr(ants_arr[j], ' ') - ants_arr[j]);
      ft_putstr(temp);
      ft_memdel((void**)&temp);
    }
    else
      ft_putstr(ants_arr[j]);
    temp = ants_arr[j];
    ants_arr[j] = (ft_strchr(ants_arr[j] , ' ') == NULL) ? "\0" : ft_strsub(ants_arr[j], ft_strchr(ants_arr[j], ' ') - ants_arr[j] + 1, ft_strlen(ants_arr[j]));
    ft_memdel((void**)&temp);
    ((++j) <= ant_num) ? ft_putchar(' ') : 0;
  }
}

void      ants_travel(t_lemin *farmer, t_bonus *bonus, size_t ants_num)
{
  char      **ants_arr;
  
  ft_putstr("\033[35;3;2;3mRun Forest run:\033[0m\n");
  ants_arr = ft_create_bid_arr(farmer->ants_num, ft_strchr(ft_determine_best_path(farmer, farmer->rooms_counter), ' ') + 1);
  while (ants_num < farmer->ants_num)
  {
      ft_putstr(bonus->color_arr[bonus->cants]);
      ft_mv_ants(ants_arr, ants_num++, 0);
      ft_putstr("\033[0m\n");
  }
  ants_num = ft_count_unfinished(ants_arr);
  while (ants_num != 0)
  {
    ft_putstr(bonus->color_arr[bonus->cants]);
    ft_mv_ants(ants_arr, ants_num, 1);
    ft_putstr("\033[0m\n");
    ants_num = ft_count_unfinished(ants_arr);
  }
  free(ants_arr);
}
