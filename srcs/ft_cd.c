#include "../includes/minishell.h"

int ft_cd(char **arguments, t_all *all)
{
	int i;

	i = 0;
	if (arguments[1] == NULL || !(ft_strncmp(arguments[1], "~", ft_strlen("~"))))
	{
		while (ft_strncmp(all->env->var[i], "HOME", ft_strlen("HOME")) != 0)
		{
			i++;
		}
		chdir(all->env->val[i]);
	}
	else if (*(arguments + 1) != NULL)
		chdir(arguments[1]);
	if (errno != 0)
		printf("minishell: cd: %s: %s\n", arguments[1], strerror(errno));
	if (all->pipe->next != NULL)
		exit(0);
	return (errno);
}
