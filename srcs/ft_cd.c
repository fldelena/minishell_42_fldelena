#include "../includes/minishell.h"

int ft_cd(char **arguments, t_env *env)
{
	int i;

	i = 0;
	if (arguments[1] == NULL || !(ft_strncmp(arguments[1], "~", ft_strlen("~"))))
	{
		while (ft_strncmp(env->var[i], "HOME", ft_strlen("HOME")) != 0)
		{
			i++;
		}
		chdir(env->val[i]); // в будущем сюда будет помещена переменная окружения HOME
	}
	else if (*(arguments + 1) != NULL)
		chdir(arguments[1]);
	if (errno != 0)
		printf("minishell: cd: %s: %s\n", arguments[1], strerror(errno));
	return (errno);
}
