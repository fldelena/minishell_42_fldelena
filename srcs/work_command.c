#include "../includes/minishell.h"

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

char **ft_make_arg_n(char **arguments, t_all *all, int num) // с нормой этого дерьма пусть возится gvenonat
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
				break;
			tmp = tmp->next;
		}
		count = tmp->start_arg;
		tmp_help = tmp->next;
		if (tmp->next && tmp_help->next) // сюда захожу когда средние пайпы
		{
			tmp = tmp->next;
			count = tmp->start_arg - count;
		}
		else // когда самый последнйи пайп
		{
			i = 0; 
			while (arguments[count]) // ls ls | cat cat | me me | pwd pwd pwd pwd
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
		count = tmp->next->start_arg;
	arg_now = malloc(sizeof(char *) * count + 1);
	i = 0;
	while (i != count)
	{
		// printf("%s\n",arguments[0]); 
		arg_now[i] = arguments[i + count_tmp_arg];
		i++;
	}
	arg_now[i] = NULL;
	return (arg_now);
}

int ft_work_old(char **arg_now, t_all *all)
{
	// if (all->pipe->f_red_pip == 2)
	// 	return (0);
	if (ft_strncmp(arg_now[0], "pwd", ft_strlen("pwd")) == 0)
	{
		printf("%s\n", getcwd(0, 0));
		if (all->pipe->next != NULL)
			exit(0);
		return (errno);
	}
	else if (ft_strncmp(arg_now[0], "echo", ft_strlen("echo")) == 0)
		return (ft_echo(all, 1, arg_now));
	else if (ft_strncmp(arg_now[0], "cd", ft_strlen("cd")) == 0)
		return (ft_cd(arg_now, all));
	else if (ft_strncmp(arg_now[0], "env", ft_strlen("env")) == 0)
		return (ft_env(all));
	else if (ft_strncmp(arg_now[0], "export", ft_strlen("export")) == 0)
		return (ft_export(all, arg_now));
	else if (ft_strncmp(arg_now[0], "unset", ft_strlen("unset")) == 0)
		return (ft_unset(all, arg_now));
	else if (ft_strncmp(arg_now[0], "exit", ft_strlen("exit")) == 0) // gvenonat
		ft_exit(arg_now);
	else
		return (binary_work(all, arg_now));
	return (127);
}

int ft_work_command(char **arguments, t_all *all)
{
	if (all->pipe->count_red_pip == -1)
		return (ft_work_old(arguments, all));
	else
	{
		t_lst_pipe *tmp;
		t_lst_pipe *prev;
		t_lst_pipe *begin;
		
		tmp = all->pipe;
		begin  = all->pipe;
		while (begin->next)
		{
			begin->pid = 1;
			begin->fd_pid[0] = 0;
			begin->fd_pid[1] = 0;
			begin = begin->next;
		}
		
		while (tmp->next)
		{
			// printf("YA ZDESY %D\n",tmp->fd_redirect);
			if (tmp->next != NULL)
				pipe(tmp->fd_pid);
			prev = tmp->prev;
			if (tmp->f_red_pip == 2)
			{
				close (tmp->fd_pid[1]);
				tmp->fd_pid[1] = tmp->fd_redirect;
				close(tmp->fd_pid[0]);
			}
			if (tmp->fd_redirect != -1 || tmp->f_red_pip >= 0) // было !=  не работало yes | head | wc
				tmp->pid = fork();
			if (!tmp->pid )//&& tmp->f_red_pip == 2
			{
				
				if (tmp->f_red_pip == 1 || tmp->f_red_pip == 2)  // если отдаём
				{
					dup2(tmp->fd_pid[1], 1);
					close(tmp->fd_pid[1]);
					close(tmp->fd_pid[0]);
				}
				if (prev && prev->f_red_pip == 1)
				{
					dup2(prev->fd_pid[0], 0);
					close(prev->fd_pid[0]);
					close(prev->fd_pid[1]);
				}
				ft_work_old(tmp->command, all);
			}
			if (tmp->f_red_pip >= 0 && tmp->f_red_pip != 2)
				close(tmp->fd_pid[1]);
			if (prev && prev->f_red_pip >= 0 )
				close(prev->fd_pid[0]);
			tmp = tmp->next;
		}
		tmp = all->pipe;
		while (tmp->next)
		{
			if (tmp->fd_redirect != -1 || tmp->f_red_pip >= 0)	
				waitpid(tmp->pid, 0, 0);
			tmp = tmp->next;
		}
	}
	return (errno);
}
