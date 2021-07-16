#include "../includes/minishell.h"

void		free_arr(char **arr)
{
	int i;
	i = -1;

	while (arr[++i])
		free(arr[i]);
	free(arr);
}
