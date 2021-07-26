#include "../includes/minishell.h"

int	is_n_flag(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[++i])
	{
		if (s[i] != 'n' || s[0] != '-')
			return (0);
	}
	if (ft_strlen(s) == 1)
		return (0);
	return (1);
}

int	ft_echo(t_all *all, int fd, char **arguments)
{
	int	i;
	int	n;

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
	if (all->pipe->next != NULL)
		exit(0);
	return (0);
}
