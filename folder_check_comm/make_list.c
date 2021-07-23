#include "../includes/minishell.h"

void	ft_lst_null(t_lst_pipe **tmp, int *num2)
{
	t_lst_pipe	*begin2;

	(*tmp)->num = (*num2)++;
	(*tmp)->start_arg = 0;
	(*tmp)->fd_redirect = -1;
	(*tmp)->count_red_pip = 0;
	(*tmp)->prev = NULL;
	(*tmp)->next = malloc(sizeof(t_lst_pipe));
	begin2 = (*tmp);
	(*tmp)->command = NULL;
	(*tmp) = (*tmp)->next;
	(*tmp)->prev = begin2;
	(*tmp)->fd_redirect = -1;
	(*tmp)->next = NULL;
	(*tmp)->command = NULL;
}

void	ft_add_lst_2(t_lst_pipe *tmp, int c_pip, int count, int f_dir)
{
	t_lst_pipe	*begin2;

	tmp->prev->f_red_pip = f_dir;
	tmp->f_red_pip = 0;
	tmp->fd_redirect = -1;
	tmp->count_red_pip = c_pip;
	tmp->start_arg = count;
	tmp->next = malloc(sizeof(t_lst_pipe));
	begin2 = tmp;
	tmp = tmp->next;
	tmp->prev = begin2;
	tmp->next = NULL;
	tmp->command = NULL;
	tmp->num = -2;
	tmp->fd_redirect = -1;
	tmp->start_arg = -1;
}

int	ft_add_lst(t_all *all, int c_pip, int count, int f_dir)
{
	t_lst_pipe	*tmp;
	int			num2;

	if (ft_check_error(c_pip, f_dir) != 0)
		return (ft_check_error(c_pip, f_dir));
	num2 = 0;
	tmp = all->pipe;
	while (tmp->next != NULL)
	{
		num2++;
		tmp = tmp->next;
	}
	if (tmp->num == -1)
		ft_lst_null(&tmp, &num2);
	tmp->num = num2;
	ft_add_lst_2(tmp, c_pip, count, f_dir);
	return (0);
}

int	ft_check_pip_red_help1(char **m_str, t_all *all, int *i, int *c_pip)
{
	if (m_str[0][*i] == '|')
	{
		while (m_str[0][*i] == '|')
		{
			(*c_pip)++;
			(*i)++;
		}
		if (ft_add_lst(all, (*c_pip), all->parser.count, 1) != 0)
			return (ft_add_lst(all, (*c_pip), all->parser.count, 1));
		(*i) = (*i) - (*c_pip);
	}
	if (m_str[0][(*i)] == '>')
	{
		while (m_str[0][(*i)] == '>')
		{
			(*c_pip)++;
			(*i)++;
		}
		if (ft_add_lst(all, (*c_pip), all->parser.count, 2) != 0)
			return (ft_add_lst(all, (*c_pip), all->parser.count, 2));
		(*i) = (*i) - (*c_pip);
	}
	return (0);
}

int	ft_check_pip_red_help2(char **m_str, t_all *all, int *i, int *c_pip)
{
	if (m_str[0][*i] == '<')
	{
		while (m_str[0][(*i)] == '<')
		{
			(*c_pip)++;
			(*i)++;
		}
		if (ft_add_lst(all, (*c_pip), all->parser.count, 3) != 0)
			return (ft_add_lst(all, (*c_pip), all->parser.count, 3));
		(*i) = (*i) - (*c_pip);
	}
	return (0);
}
