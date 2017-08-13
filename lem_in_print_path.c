#include "lem_in.h"

static void      ft_free_ndarr(t_graph **arr, size_t i)
{
  while (arr[i] != NULL)
    ft_memdel((void**)arr[i++]);
}

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
  // while (i < (len - 1))
  // {
  //   if (farmer->paths[i]->path_len > farmer->paths[i + 1]->path_len)
  //   {
  //     path = farmer->paths[i]->path_str;
  //     p_len = farmer->paths[i]->path_len;
  //     farmer->paths[i]->path_str = farmer->paths[i + 1]->path_str;
  //     farmer->paths[i]->path_len = farmer->paths[i + 1]->path_len;
  //     farmer->paths[i + 1]->path_str = path;
  //     farmer->paths[i + 1]->path_len = p_len;
  //     i = 0;
  //   }
  //   else
  //     i++;
  // }
  // ft_free_ndarr(farmer->paths, 1);  
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

void            ft_print_till(char *str, int c)
{
  int         i;

  i = -1;
  while (str[++i])
  {
    if (str[i] == c)
      break ;
    ft_putchar(str[i]); 
  }
}

char        **ft_init_ants(char *path, int ants_num)
{
    int         i;
    char        **temp;
    
    temp = (char**)malloc(sizeof(char*) * ants_num + 1);
    i = 0;
    while (i < ants_num)
    {
        temp[i] = ft_strdup(path);
        i++;
    }
    temp[i] = NULL;
    return (temp);
}

void            ft_mv_ants(char **ants_arr, size_t ant_num, int flag)
{
  size_t      j;
  char        *temp;
  
  j = ft_update_ants_arr(ants_arr);
  if (flag == 1)
  {
    ant_num += j - 1; //+ ft_count_unfinished(ants_arr);//- 1 : 0;
  }
  // printf("\nAt the beginning ants_num:%zu|j:%zu\n", ant_num, j);
  while (j <= ant_num)
  {
    // printf("\nants_num:%zu|j:%zu\n", ant_num, j);
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
    // ft_putstr((ft_strchr(ants_arr[j], ' ')) ? temp = ft_strsub(ants_arr[j], 0, ft_strchr(ants_arr[j], ' ') - ants_arr[j]) : ants_arr[j]);
    // ants_arr[j] = (ft_strchr(ants_arr[j] , ' ') == NULL) ? "\0" : ft_strchr(ants_arr[j], ' ') + 1;
    if (ft_strchr(ants_arr[j] , ' ') == NULL)
    {
      temp = ants_arr[j];
      ants_arr[j] = "\0";
    }
    else
    {
      temp = ants_arr[j];
      ants_arr[j] = ft_strsub(ants_arr[j], ft_strchr(ants_arr[j], ' ') - ants_arr[j] + 1, ft_strlen(ants_arr[j]));//ft_strchr(ants_arr[j], ' ') + 1;
    }
    ft_memdel((void**)&temp);
    ((++j) <= ant_num) ? ft_putchar(' ') : 0;
  }
}

void      ants_travel(t_lemin *farmer, t_bonus *bonus)
{
  size_t    ants_num;
  char      **ants_arr;
  
  //ft_determine_best_path(farmer, farmer->rooms_counter); //-> we don't sort rest of routes as the only thing we need is the shortest path
  ft_putstr("\033[35;3;2;3mRun Forest run:\033[0m\n");
  // ft_determine_best_path(farmer, farmer->rooms_counter);
  ants_num = 0;
  ants_arr = ft_init_ants(ft_strchr(ft_determine_best_path(farmer, farmer->rooms_counter), ' ') + 1, farmer->ants_num);//ft_init_ants(ft_strchr(farmer->paths[0]->path_str, ' ') + 1, farmer->ants_num);
  
  while (ants_num < farmer->ants_num)
  {
      ft_putstr(bonus->color_arr[bonus->cants]);
      ft_mv_ants(ants_arr, ants_num++, 0);
      ft_putstr("\033[0m\n");
  }
  ants_num = ft_count_unfinished(ants_arr);
  while (ants_num != 0)
  {
    // printf("\nYO!:%zu\n", ants_num);
    ft_putstr(bonus->color_arr[bonus->cants]);
    ft_mv_ants(ants_arr, ants_num, 1);
    ft_putstr("\033[0m\n");
    ants_num = ft_count_unfinished(ants_arr);
  }
  // ft_free_bidarr(farmer->x_coords, ft_bidlen(farmer->x_coords));
  // ft_free_bidarr(farmer->y_coords, ft_bidlen(farmer->y_coords));
  // ft_free_bidarr(ants_arr, ft_bidlen(ants_arr));
  free(ants_arr);
  // ft_putbidstr(ants_arr);
  // while (1);
}
