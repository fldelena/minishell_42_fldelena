#include "../includes/minishell.h"

void ft_echo(int fd, char **arguments)
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
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ft_env(t_env *env)
{
	int i;

	i = 0;
	while (env->envp[i] != NULL)
	{
		if (ft_strncmp(env->var[i], "?", ft_strlen("?")) != 0)
			if (env->f_equal[i] == 2)
				printf("%s\n", env->envp[i]);
		i++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ft_cd(char **arguments, t_env *env)
{
	int i;

	i = 0;
	if (arguments[1] == NULL || !(strcmp(arguments[1], "~")))
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
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ft_export(t_env *env, char **arguments)
{
	char **sort_envp;
	char **sort_var;
	char **sort_val;
	int *f_equal;
	char **var_val;
	int i;

	i = 0;
	if (*(arguments + 1) != NULL)
	{
		add_variable(env, arguments);
	}
	else
	{
		sort_envp = arr_copy(env->envp);
		line_sort(sort_envp);
		while (sort_envp[i] != NULL)
			i++;
		sort_var = malloc(sizeof(char *) * (i + 1));
		sort_val = malloc(sizeof(char *) * (i + 1));
		f_equal = malloc(sizeof(int) * (i + 1));
		i = 0;
		while (sort_envp[i] != NULL) // сортировочка по алфавиту (заключить в кавычки все то что идет после знака равно!!!!)
		{
			if (ft_strchr(sort_envp[i], '='))
			{
				var_val = ft_split(sort_envp[i], '=');
				sort_var[i] = var_val[0];
				sort_val[i] = var_val[1];
				f_equal[i] = 2;
			}
			else
			{
				sort_var[i] = ft_strdup(sort_envp[i]);
				sort_val[i] = ft_strdup("");
				f_equal[i] = 1;
			}
			if (!var_val)
				free(var_val);
			i++;
		}
		i = 0;
		while (*(sort_envp + i))
		{
			if (ft_strncmp(sort_var[i], "?", ft_strlen("?")) != 0)
			{
				printf("declare -x %s", sort_var[i]);
				if (f_equal[i] == 2)
					printf("=\"%s\"", sort_val[i]);
				printf("\n");
			}
			i++;
		}
		free_arr(sort_envp);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ft_unset(t_env *env, char **arguments)
{
	if (*(arguments + 1) != NULL)
		del_variable(env, arguments);
	else
	{
		//вроде тут ничего не должно быть, на всякий случай оставлю
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ft_exit(char **arguments)
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
		exit(errno);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ft_work_old(char **arguments, t_all *all, int i)
{
	pid_t pid;

	if (ft_strncmp(arguments[i], "pwd", ft_strlen("pwd")) == 0)
		printf("%s\n", getcwd(0, 0));
	else if (ft_strncmp(arguments[i], "ls", ft_strlen("ls")) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve("/bin/ls", &arguments[i], 0);
		waitpid(pid, 0, 0);
	}
	// else if (ft_strncmp(arguments[i], "cat", ft_strlen("cat")) == 0)
	// {
	// 	pid = fork();
	// 	if (pid == 0)
	// 		execve("/bin/ls", arguments, 0);
	// 	waitpid(pid, 0, 0);
	// }
	else if (ft_strncmp(arguments[i], "echo", ft_strlen("echo")) == 0)
		ft_echo(1, arguments);
	else if (ft_strncmp(arguments[i], "cd", ft_strlen("cd")) == 0)
		ft_cd(arguments, all->env);
	else if (ft_strncmp(arguments[i], "env", ft_strlen("env")) == 0)
		ft_env(all->env);
	else if (ft_strncmp(arguments[i], "export", ft_strlen("export")) == 0)
		ft_export(all->env, arguments);
	else if (ft_strncmp(arguments[i], "unset", ft_strlen("unset")) == 0)
		ft_unset(all->env, arguments);
	else if (ft_strncmp(arguments[i], "exit", ft_strlen("exit")) == 0) // gvenonat
		ft_exit(arguments);
	else
	{
		printf("YA DOCHKA\n");
		// pid = fork();
		// if (pid == 0)
		execve(arguments[i], &arguments[i], 0);
		// waitpid(pid, 0, 0);
	}
	return (errno);
}

int ft_work_command(char **arguments, t_all *all)
{
	if (all->pipe->f_pipe == -1)
	{
		ft_work_old(arguments, all, 0);
	}
	else // нужно попробовать убрать tmp чтобы в work_old исполнять нужную команду
	{
		t_lst_pipe *tmp;

		tmp = all->pipe;
		pipe(tmp->fd_pid);
		tmp->pid = fork();
		if (!tmp->pid && tmp->prev == NULL) // если отдаём
		{

			// dup2(tmp->fd_pid[1], 1);
			// close(tmp->fd_pid[1]);
			// close(tmp->fd_pid[0]);
			printf("%s\n", arguments[all->pipe->arg_p]);
			execve(arguments[all->pipe->arg_p], &arguments[all->pipe->arg_p], 0);
			//ft_work_old(arguments, all, all->pipe->arg_p);
			//execve(yes[0], yes, env);
		}
		close(tmp->fd_pid[1]);
		waitpid(tmp->pid, 0, 0);
		// tmp = tmp->next;
		// if (!tmp->pid && tmp->prev != NULL && tmp->next != NULL)
		// {
		// 	dup2(tmp->fd_pid[1], 1); // если отдаём
		// 	close(tmp->fd_pid[1]);
		// 	close(tmp->fd_pid[0]);

		// 	tmp = tmp->prev;

		// 	dup2(tmp->fd_pid[0], 0); //если берем
		// 	close(tmp->fd_pid[0]);
		// 	close(tmp->fd_pid[1]);

		// 	tmp = tmp->next;
		// 	ft_work_old(arguments, all);
		// 	// execve(head[0], head, env);
		// }
	}
	return (errno);
}
