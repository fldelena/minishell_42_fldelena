#include "../includes/minishell.h"

int	ft_env(t_env *env)
{
	int i;

	i = 0;
	while (env->envp[i] != NULL)
	{
		if (ft_strncmp(env->var[i], "?", ft_strlen("?")) != 0)
			if (env->f_equal[i] == 2)
			{
				printf("%s\n", env->envp[i]);
				// write (1, env->envp[i], ft_strlen(env->envp[i]));
				// write (1, "\n", 1);
			}
		i++;
	}
	return (0);
}
