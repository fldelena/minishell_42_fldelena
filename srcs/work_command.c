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

void	ft_cd(char **arguments)
{
	if (arguments[1] == NULL || !(strcmp(arguments[1], "~")))
		chdir("/Users/fldelena/");
	else if (*(arguments + 2) == NULL)
		chdir(arguments[1]);

	// по варианту напиши функцию для подсчета строк в двумерном массиве строк
}

// void	ft_export(char **envp) // доделаю!!!!
// {
// 	int i;
// 	i = 0;
// 	while (*(envp + i))
// 	{
// 		printf("%s\n", *(envp + i));
// 		i++;
// 	}
// 	printf("%s\n", "---------------------------------------------------------------------------");
// 	line_sort(envp);
// 	while (*(envp + i))
// 	{
// 		printf("%s\n", *(envp + i));
// 		i++;
// 	}
// }



int ft_work_command(char **arguments, char **envp)
{
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
	if (strcmp(arguments[0], "env") == 0)
		ft_env(envp);
	if (strcmp(arguments[0], "cd") == 0)
		ft_cd(arguments);
	// if (strcmp(arguments[0], "export") == 0)  //  доделаю
	// 	ft_export(envp);
	return(0);
}
