#include "../includes/minishell.h"

int		is_n_flag(char *s)					// функция для корректной работы -n в echo
{
	int i = 0;
	while (s[++i])
	{
		if (s[i] != 'n' || s[0] != '-')
			return (0);
	}
	if (ft_strlen(s) == 1)
		return (0);
	return (1);
}

int ft_echo(int fd, char **arguments)
{
	int i;
	int n;

	i = 1;
	n = 0;
	while (is_n_flag(arguments[i]))
	{
		i++;
		n = 1;
	}
	while (*(arguments + i))
	{
		write(fd, arguments[i], ft_strlen(arguments[i]));
		if (*(arguments + i + 1) != NULL)
			write(fd, " ", 1);
		i++;
	}
	if (!n)
		write(fd, "\n", 1);
	return (0);
}
