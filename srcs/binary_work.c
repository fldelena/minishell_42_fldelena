#include "../includes/minishell.h"

int	exception(char **arguments)
{
	if (ft_strncmp(arguments[0], "echo", ft_strlen("echo")) == 0)
		return (1);
	else if (ft_strncmp(arguments[0], "cd", ft_strlen("cd")) == 0)
		return (1);
	else if (ft_strncmp(arguments[0], "pwd", ft_strlen("pwd")) == 0)
		return (1);
	else if (ft_strncmp(arguments[0], "export", ft_strlen("export")) == 0)
		return (1);
	else if (ft_strncmp(arguments[0], "unset", ft_strlen("unset")) == 0)
		return (1);
	else if (ft_strncmp(arguments[0], "env", ft_strlen("env")) == 0)
		return (1);
	else if (ft_strncmp(arguments[0], "exit", ft_strlen("exit")) == 0)
		return (1);
	else if (ft_strncmp(arguments[0], "/.", ft_strlen("/.")) == 0)
		return (1);
	else
		return (0);
}

int	ft_help(char *pathway)
{
	struct stat	buf;

	if (lstat(pathway, &buf) == -1)
		errno = 0;
	if ((buf.st_mode & S_IFMT) == S_IFREG)
		return (1);
	return (0);
}

int	ft_make_path(char **arguments, char **pathway, char **pathways)
{
	int	i;

	i = 0;
	while (pathways[i] != NULL)
	{
		pathway[0] = ft_strdup(pathways[i]);
		pathway[0] = ft_strjoin(pathway[0], "/");
		pathway[0] = ft_strjoin(pathway[0], arguments[0]);
		if (ft_help(pathway[0]) == 1)
			break ;
		free(pathway[0]);
		i++;
	}
	return (i);
}

int	ft_launch(char **arguments, char **pathways, char *pathway, int i)
{
	pid_t	pidor;

	if (pathways[i] != NULL)
	{
		pidor = fork();
		g_pid = pidor;
		if (!pidor)
			execve(pathway, arguments, 0);
	}
	else if (ft_help(arguments[0]))
	{
		pidor = fork();
		g_pid = pidor;
		if (!pidor)
			execve(arguments[0], arguments, 0);
	}
	else
		return (127);
	waitpid(pidor, &errno, 0);
	errno = WEXITSTATUS(errno);
	return (errno);
}

int	binary_work(t_all *all, char **arguments)
{
	char	**pathways;
	char	*pathway;
	int		i;

	i = 0;
	if (exception(arguments) == 1)
		return (0);
	while (ft_strncmp(all->env->var[i], "PATH", ft_strlen("PATH")) != 0)
		i++;
	pathways = ft_split(all->env->val[i], ':');
	i = ft_make_path(arguments, &pathway, pathways);
	if (all->pipe->next == NULL)
	{
		i = ft_launch(arguments, pathways, pathway, i);
		if (i != 0)
			return (i);
	}
	else
		execve(pathway, arguments, 0);
	return (errno);
}
