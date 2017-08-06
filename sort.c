char		**ft_sort_fixed_position(char **stack, char *needle, size_t pos)
{
	size_t				i;
	size_t				j;
	char				**arr;

	i = 0;
	j = 0;
	arr = (char**)malloc(sizeof(char*) * ft_bidlen(stack) + 1);
	arr[pos] = ft_strdup(needle);
	while (stack[i])
	{
		(pos != i) ? arr[i++] = stack[j++] : 0;
	}
	arr[i] = NULL;
	free(stack);
	return (arr);
}