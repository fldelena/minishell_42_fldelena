#include "../includes/minishell.h"

int exception(char **arguments)
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

int ft_help(char *pathway)
{
	struct stat buf;

	if (lstat(pathway, &buf) == -1) // собираем сведенья о файле
		errno = 0;
	if ((buf.st_mode & S_IFMT) == S_IFREG) // это ультромега не правильно, но работает
		return (1);						   // найдя нужный нам путь мы выходим
	return (0);
}

int binary_work(t_all *all, char **arguments)
{
	char **pathways; // массив из разных путей взятых из PATH
	char *pathway;	 // сюда я сохряняю путь по одному на каждую итерацию
	pid_t pidor;
	int i;

	i = 0;
	// if (idx != 0)
	// 	ft()
	// else

	if (exception(arguments) == 1)
		return (0);
	while (ft_strncmp(all->env->var[i], "PATH", ft_strlen("PATH")) != 0) // ищем PATH
		i++;
	pathways = ft_split(all->env->val[i], ':'); // делим PATH на разные пути
	i = 0;
	while (pathways[i] != NULL) // перебираем пути пока не найдем тот в котором лежит наш аргумент
	{
		pathway = ft_strdup(pathways[i]);			 // копируем в отдельную переменную
		pathway = ft_strjoin(pathway, "/");			 // прямо по кусочкам собираем путь
		pathway = ft_strjoin(pathway, arguments[0]); // и добавляем название файла
		if (ft_help(pathway) == 1)
			break;
		free(pathway); // картофель free
		i++;
	}
	pidor = fork();
	if (!pidor)
	{
		if (pathways[i] != NULL)
			execve(pathway, arguments, 0); // запускаем нашу программку
		else if (ft_help(arguments[0]))
			execve(arguments[0], arguments, 0);
		else
			return (127);
	}
	waitpid(pidor, 0, 0);
	return (errno);
}
