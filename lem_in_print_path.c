#include "lem_in.h"

static void      ft_free_ndarr(t_graph **arr, size_t i)
{
  // while (arr[i] != NULL)
  //   ft_memdel(arr[i++]);
}

static void      ft_determine_best_path(t_lemin *farmer, int len)
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
  // ft_free_ndarr(farmer->paths, 1);  
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
    while (ft_strcmp(arr[i], "\0") == 0)//== NULL)
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
  size_t      temp;
  size_t      j;
  
  j = ft_update_ants_arr(ants_arr);
  temp = 0;
  (flag == 1) ? ant_num += j - 1 : 0;
  while (j <= ant_num)
  {
    ft_putchar('L');
    ft_putstr(ft_itoa(j + 1));
    ft_putchar('-');
    // ants_arr[j] += ft_strchr(ants_arr[j], ' ') - ants_arr[j] + 1;//2;
    ants_arr[j] += 2;
    ft_putchar(ants_arr[j][0]);
    // ft_putstr(ft_strsub(ants_arr[j], 0, ft_strchr(ants_arr[j], ' ') - ants_arr[j]));
    if (ants_arr[j][1] == '\0')
    {
        //free(ants_arr[j]);
        ants_arr[j] = "\0";//NULL;
        //ft_memdel((void**)&ants_arr[j]);
    }
    ((++j) <= ant_num) ? ft_putchar(' ') : 0;
  }
}

void      ants_travel(t_lemin *farmer, t_bonus *bonus) // it doesn't work if names of rooms are words, not just int, and length of those is greater than one
{
  size_t    ants_num;
  char      **ants_arr;
  
  ft_determine_best_path(farmer, farmer->rooms_counter);
  ants_num = 0;
  ants_arr = ft_init_ants(farmer->paths[0]->path_str, farmer->ants_num);
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
    ft_mv_ants(ants_arr, ants_num--, 1);
    ft_putstr("\033[0m\n");
  }
}