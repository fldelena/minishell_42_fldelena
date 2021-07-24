#include "../includes/minishell.h"

int	ft_env(t_all *all)
{
	int i;

	i = 0;
	while (all->env->envp[i] != NULL)
	{
		if (ft_strncmp(all->env->var[i], "?", ft_strlen("?")) != 0)
			if (all->env->f_equal[i] == 2)
			{
				printf("%s\n", all->env->envp[i]);
				// write (1, all->env->envp[i], ft_strlen(all->env->envp[i]));
				// write (1, "\n", 1);
			}
		i++;
	}
	if (all->pipe->next != NULL)
		exit(0);
	return (0);
}
