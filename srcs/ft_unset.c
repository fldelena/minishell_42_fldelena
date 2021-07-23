#include "../includes/minishell.h"

char	**del(char **var, char **envp, char **arguments, int words)
{
	char	**new_envp;
	int		i;
	int		j;
	int		k;

	new_envp = malloc(sizeof(char *) * (words + 1));
	i = 0;
	k = 0;
	while (envp[i] != NULL)
	{
		j = 1;
		while (arguments[j] != NULL)
		{
			if (strcmp(var[i], arguments[j]) == 0)
				i++;
			j++;
		}
		new_envp[k] = envp[i];
		if (new_envp[k] == NULL)
			return (new_envp);
		k++;
		i++;
	}
	new_envp[k] = NULL;
	return (new_envp);
}

int	*del_f_equal(t_env *env, char **arguments, int words)
{
	int		*arr;
	int		i;
	int		j;
	int		k;

	arr = malloc(sizeof(int) * (words + 1));
	i = 0;
	k = 0;
	while (env->envp[i] != NULL)
	{
		j = 1;
		while (arguments[j] != NULL)
		{
			if (strcmp(env->var[i], arguments[j]) == 0)
				i++;
			j++;
		}
		if (ft_strchr(env->envp[i], '='))
			arr[k] = 2;
		else
			arr[k] = 1;
		if (env->envp[i] == NULL)
		{
			arr[k] = '\0';
			return (arr);
		}
		i++;
		k++;
	}
	arr[k] = '\0';
	return (arr);
}

void	del_variable(t_env *env, char **arguments)
{
	int	word_count;
	int	args_count;
	int	i;

	word_count = 0;
	args_count = 0;
	i = 1;
	while (env->envp[word_count])
		word_count++;
	while (*(arguments + i))
	{
		args_count++;
		i++;
	}
	env->envp = del(env->var, env->envp, arguments, (word_count - args_count));
	env->val = del(env->var, env->val, arguments, (word_count - args_count));
	env->var = del(env->var, env->var, arguments, (word_count - args_count));
	env->f_equal = del_f_equal(env, arguments, (word_count - args_count));
}

int	ft_unset(t_all *all, char **arguments)
{
	if (*(arguments + 1) != NULL)
		del_variable(all->env, arguments);
	if (all->pipe->next != NULL)
		exit(0);
	return (0);
}
