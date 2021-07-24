#include "../includes/minishell.h"

char	**arr_copy(char **envp)
{
	char	**my_envp;
	int		i;

	i = 0;
	while (*(envp + i))
		i++;
	my_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (*(envp + i))
	{
		my_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	my_envp[i] = NULL;
	return (my_envp);
}

void	null_element(t_all *all, int i)
{
	all->env->envp[i] = NULL;
	all->env->var[i] = NULL;
	all->env->val[i] = NULL;
	all->env->f_equal[i] = '\0';
}

void	make_envp(t_all *all, char **envp)
{
	char	**arr;
	int		i;

	i = 0;
	while (envp[i])
	{
		all->env->envp[i] = ft_strdup(*(envp + i));
		if (ft_strchr(all->env->envp[i], '='))
		{
			all->env->f_equal[i] = 2;
			arr = ft_split(*(envp + i), '=');
			all->env->var[i] = ft_strdup(arr[0]);
			all->env->val[i] = ft_strdup(arr[1]);
		}
		else
		{
			all->env->f_equal[i] = 1;
			all->env->var[i] = ft_strdup(*(envp + i));
			all->env->val[i] = ft_strdup("");
		}
		free_arr(arr);
		i++;
	}
	null_element(all, i);
}
