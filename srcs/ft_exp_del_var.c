#include "../includes/minishell.h"

char	**del_by_index(char **src, int index)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i] != NULL)
		i++;
	arr = malloc(sizeof(char *) * i);
	i = -1;
	while (src[++i] != NULL)
	{
		if (i == index)
			i++;
		arr[j] = src[i];
		if (arr[j] == NULL)
		{
			free (src);
			return (arr);
		}
		j++;
	}
	arr[j] = NULL;
	free (src);
	return (arr);
}

int	*del_int_by_index(int *src, int index)
{
	int	*arr;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
		i++;
	arr = malloc(sizeof(int) * i);
	i = -1;
	while (src[++i] != '\0')
	{
		if (i == index)
			i++;
		arr[j] = src[i];
		if (arr[j] == '\0')
		{
			free (src);
			return (arr);
		}
		j++;
	}
	arr[j] = '\0';
	free (src);
	return (arr);
}

void	del_similar_var(t_env *env, int index)
{
	env->envp = del_by_index(env->envp, index);
	env->var = del_by_index(env->var, index);
	env->val = del_by_index(env->val, index);
	env->f_equal = del_int_by_index(env->f_equal, index);
}
