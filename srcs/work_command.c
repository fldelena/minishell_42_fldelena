#include "../includes/minishell.h"

void	ft_init_ft_pid(t_all *all)
{
	t_lst_pipe	*begin;

	begin = all->pipe;
	while (begin->next)
	{
		begin->pid = 1;
		begin->fd_pid[0] = 0;
		begin->fd_pid[1] = 0;
		begin = begin->next;
	}
}

void	ft_init_flag_pipe(t_lst_pipe *tmp)
{
	if (tmp->f_red_pip == 2)
	{
		close (tmp->fd_pid[1]);
		tmp->fd_pid[1] = tmp->fd_redirect;
		close(tmp->fd_pid[0]);
	}
	if (tmp->fd_redirect != -1 || tmp->f_red_pip >= 0)
	{
		tmp->pid = fork();
		g_pid = tmp->pid;
	}
}

void	ft_tmp_pid(t_all *all, t_lst_pipe *tmp, t_lst_pipe *prev)
{
	ft_init_flag_pipe(tmp);
	if (!tmp->pid)
	{
		if (tmp->f_red_pip == 1 || tmp->f_red_pip == 2)
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
		if (ft_work_old(tmp->command, all) != 0)
			exit(0);
	}
}

int	ft_wait_pid(t_lst_pipe *tmp)
{
	while (tmp->next)
	{
		if (tmp->fd_redirect != -1 || tmp->f_red_pip >= 0)
		{
			waitpid(tmp->pid, &errno, 0);
			errno = WEXITSTATUS(errno);
			if (errno != 0)
				return (errno);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_work_command(char **arguments, t_all *all)
{
	t_lst_pipe	*tmp;
	t_lst_pipe	*prev;

	if (all->pipe->count_red_pip == -1)
		return (ft_work_old(arguments, all));
	else
	{
		tmp = all->pipe;
		ft_init_ft_pid(all);
		while (tmp->next)
		{
			if (tmp->next != NULL )
				pipe(tmp->fd_pid);
			prev = tmp->prev;
			ft_tmp_pid(all, tmp, prev);
			if (tmp->f_red_pip >= 0)
				close(tmp->fd_pid[1]);
			if (prev && prev->f_red_pip >= 0)
				close(prev->fd_pid[0]);
			tmp = tmp->next;
		}
		tmp = all->pipe;
		return (ft_wait_pid(tmp));
	}
	return (errno);
}
