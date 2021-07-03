#include "../includes/minishell.h"

void	ft_echo(int fd, char **arguments)
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
	while(*(arguments + i))
	{
		write(fd, arguments[i], ft_strlen(arguments[i]));
		if (*(arguments + i + 1) != NULL)
			write(fd, " ", 1);
		i++;
	}
	if (!n)
		write(fd, "\n", 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	ft_env(char **envp)
{
	int i;

	i = 0;
	while (*(envp + i))
	{
		printf("%s\n", *(envp + i));
		i++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	ft_cd(char **arguments)
{
	if (arguments[1] == NULL || !(strcmp(arguments[1], "~")))
		chdir("/Users/fldelena/");								// в будущем сюда будет помещена переменная окружения HOME
	else if (*(arguments + 2) == NULL)
		chdir(arguments[1]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	ft_export(t_env *env, char **arguments)
{
	int		i;
	char	**sort_envp;

	i = 0;
	if (*(arguments + 1) != NULL)
	{
		env->envp = add_variable(env->envp, arguments);	// добавление переменных окружения (найти способ вытащить эту строку за пределы этой функции!!!!!!!!!!!!))
	}
	else
	{
		sort_envp = arr_copy(env->envp);
		line_sort(sort_envp);						// сортировочка по алфавиту (заключить в кавычки все то что идет после знака равно!!!!)
		while (*(sort_envp + i))
		{
			printf("%s", "declare -x ");
			printf("%s\n", *(sort_envp + i));
			i++;
		}
		free_arr(sort_envp);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void	ft_unset(t_env *env, char **arguments)
// {
// 	if (*(arguments + 1) != NULL)
// 		env->envp = del_variable(env, arguments);
// 	else
// 	{
// 		//вроде тут ничего не должно быть, на всякий случай оставлю
// 	}

// 	// написать функцию которая будет создавать массив меньшей длины без некоторых индексов
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int	ft_exit(char **arguments)
{
	int i;

	i = 0;
	while (arguments[i])
		i++;
	if (i > 2)
		return (-1);
	else if (i == 2)
		exit(ft_atoi(arguments[1]));
	else
		exit(0);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ft_work_command(char **arguments, t_all *all)
{
	int res;

	res = 0;
	if (strcmp(arguments[0], "pwd") == 0)
		printf("%s\n", getcwd(0,0));
	if (strcmp(arguments[0], "ls") == 0)
	{
		pid_t pid;
		pid = fork();
		if (pid == 0)
		{
		execve("/bin/ls", arguments, 0);
		}
		waitpid(pid, 0, 0);
	}
	if (strcmp(arguments[0], "echo") == 0)
		ft_echo(1, arguments);
	if (strcmp(arguments[0], "env") == 0)		// не отображать переменные без "="
		ft_env(all->env->envp);
	if (strcmp(arguments[0], "cd") == 0)
		ft_cd(arguments);
	if (strcmp(arguments[0], "export") == 0)  // добавить проверку существование переменной
		ft_export(all->env, arguments);
	// if (strcmp(arguments[0], "unset") == 0)  // доделать
	// 	ft_unset(all->env, arguments);
	if (strcmp(arguments[0], "exit") == 0)			// gvenonat
		res = ft_exit(arguments);
	return(0);
}
