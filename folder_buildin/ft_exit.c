#include "../includes/minishell.h"

int	ft_exit(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
		i++;
	if (i > 1)
	{
		printf("exit\n");
		if (arguments[1][0] < '0' || arguments[1][0] > '9')
		{
			write(2, "minishell: exit: ", 17);
			write(2, arguments[1], ft_strlen(arguments[1]));
			write(2, ": numeric argument required\n", 28);
			exit(255);
		}
		exit(ft_atoi(arguments[1]));
	}
	else
	{
		printf("exit\n");
		exit(errno);
	}
}
