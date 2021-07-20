#include "../includes/minishell.h"

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ft_env(t_env *env)
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
	return (0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ft_cd(char **arguments, t_env *env)
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
	return (errno);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ft_export(t_env *env, char **arguments)
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
	return (0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ft_unset(t_env *env, char **arguments)
{
	if (*(arguments + 1) != NULL)
		del_variable(env, arguments);
	else
	{
		//вроде тут ничего не должно быть, на всякий случай оставлю
	}
	return (0);
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

char **ft_make_arg_n(char **arguments, t_all *all, int num)  // с нормой этого дерьма пусть возится gvenonat
{
	int count; // количество сргументов команды
	int count_tmp_arg;
	int i;
	char **arg_now;
	t_lst_pipe *tmp;
	t_lst_pipe *tmp_help;

	count_tmp_arg = 0;
	tmp = all->pipe;
	if (num != 0)
	{
		while (tmp->next)
		{
			if (tmp->num == num)
				break ;
			tmp = tmp->next;
		}
		count = tmp->start_arg;
		tmp_help = tmp->next;
		if (tmp->next && tmp_help->next)		// сюда захожу когда средние пайпы
		{
			tmp = tmp->next;
			count = tmp->start_arg - count;
		}
		else			// когда самый последнйи пайп
		{
			i = 0;
			while (arguments[count])		// ls ls | cat cat | me me | pwd pwd pwd pwd	
			{
				count++;
				i++;
			}
			count = i;
		}
		if (tmp->prev && tmp->next && tmp_help->next)
		{
			tmp = tmp->prev;
			count_tmp_arg = tmp->start_arg;
		}
		else
			count_tmp_arg = tmp->start_arg;
	}
	else
		count = tmp->start_arg;
	arg_now = malloc(sizeof(char *) * count + 1);
	i = 0;
	while (i != count)
	{
		arg_now[i] = arguments[i + count_tmp_arg];
		i++;
	}
	arg_now[i] = NULL;
	return (arg_now);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ft_work_old(char **arguments, t_all *all, int num)
{
	char **arg_now;

	if (num != -1)
		arg_now = ft_make_arg_n(arguments, all, num);
	else
		arg_now = arguments;
	/////
	// for (int i = 0; arg_now[i]; i++)			// тут выводим получившиеся строки
	// 	printf("--%s\n", arg_now[i]);
	// return (0);
	/////
	if (ft_strncmp(arg_now[0], "pwd", ft_strlen("pwd")) == 0)
	{
		printf("%s\n", getcwd(0, 0));
		return (errno);
	}
	else if (ft_strncmp(arg_now[0], "echo", ft_strlen("echo")) == 0)
		return (ft_echo(1, arg_now));
	else if (ft_strncmp(arg_now[0], "cd", ft_strlen("cd")) == 0)
		return (ft_cd(arg_now, all->env));
	else if (ft_strncmp(arg_now[0], "env", ft_strlen("env")) == 0)
		return (ft_env(all->env));
	else if (ft_strncmp(arg_now[0], "export", ft_strlen("export")) == 0)
		return (ft_export(all->env, arg_now));
	else if (ft_strncmp(arg_now[0], "unset", ft_strlen("unset")) == 0)
		return (ft_unset(all->env, arg_now));
	else if (ft_strncmp(arg_now[0], "exit", ft_strlen("exit")) == 0) // gvenonat
		ft_exit(arg_now);
	else
		return (binary_work(all, arg_now));
	return (127);
}

int ft_work_command(char **arguments, t_all *all)	// asdfas asdas | asd asd >> asdasd << asf asd asd asd | ls
{
	if (all->pipe->count_red_pip == -1)
		return (ft_work_old(arguments, all, -1));
	else
	{
		t_lst_pipe *tmp;
		tmp = all->pipe;
		////////////////////					то, как правильно подавать пайпы в функцию
		// while (tmp->next)
		// {
		// 	ft_work_old(arguments, all, tmp->num - 1);
		// 	printf("\n");
		// 	tmp = tmp->next;
		// }
		// tmp = tmp->prev;
		// ft_work_old(arguments, all, tmp->num);	// ls ls | cat cat | me me | pwd pwd pwd pwd	
		// return (0);
		////////////////////
		while (tmp->next)
		{
			pipe(tmp->fd_pid);
			tmp->pid = fork();
			if (!tmp->pid) // если отдаём
			{
				if (tmp->prev == NULL)
				{
					dup2(tmp->fd_pid[1], 1);
					close(tmp->fd_pid[1]);
					close(tmp->fd_pid[0]);
					ft_work_old(arguments, all, tmp->num - 1);
				}
				if (tmp->prev != NULL && tmp->next != NULL)
				{
					dup2(tmp->fd_pid[1], 1);
					close(tmp->fd_pid[1]);
					close(tmp->fd_pid[0]);

					dup2(tmp->prev->fd_pid[0], 0);
					close(tmp->prev->fd_pid[0]);
					close(tmp->prev->fd_pid[1]);
					ft_work_old(arguments, all, tmp->num - 1);
				}
				if (tmp->prev != NULL && tmp->next == NULL)
				{
					dup2(tmp->fd_pid[0], 0);
					close(tmp->fd_pid[0]);
					close(tmp->fd_pid[1]);
					tmp = tmp->prev;			// мб так, а мб и не так :) см вывод пайпов сверху
					ft_work_old(arguments, all, tmp->num);
					tmp = tmp->next;
				}
			}
			if (tmp->prev == NULL)
				close(tmp->fd_pid[1]);
			if (tmp->prev != NULL && tmp->next != NULL)
			{
				close(tmp->prev->fd_pid[0]);
				close(tmp->fd_pid[1]);
			}
			if (tmp->prev != NULL && tmp->next == NULL)
				close(tmp->fd_pid[0]);

			tmp = tmp->next;
		}
	}
	return (errno);
}
