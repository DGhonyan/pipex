#include <stdlib.h>

int	ptr_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

// type 0 is for ft_split, 1 is for pipe array
void	free_ptr_arr(void **ptr, int size, int type)
{
	int i = 0;

	if (type == 0)
	{
		while (i < size)
		{
			free(((char **)ptr)[i]);
			i++;
		}
	}
	else if (type == 1)
	{
		while (i < size)
		{
			free(((int **)ptr)[i]);
			i++;
		}
	}
	free(ptr);
}

