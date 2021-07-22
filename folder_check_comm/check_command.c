#include "../includes/minishell.h"

void	ft_first(char *m_str, int *t_l_quote, int *o_l_quote, int *i)
{
	if ((m_str[*i] == '"' && *t_l_quote == 0 && (*i > 0 && m_str[*i - 1] != '\\') \
				&& *o_l_quote == 0) || (m_str[*i] == '"' && *i == 0))
	{
		(*t_l_quote)++;
		(*i)++;
	}
	if ((m_str[*i] == '\'' && *o_l_quote == 0 && (i > 0 && m_str[*i - 1] != '\\') \
				&& *t_l_quote == 0) || (m_str[*i] == '"' && *i == 0))
	{
		(*o_l_quote)++;
		(*i)++;
	}
	if (m_str[*i] == '"' && *t_l_quote == 1 && m_str[(*i) - 1] != '\\')
	{
		*t_l_quote = 0;
		if (m_str[(*i) + 1] == ' ')
			m_str[(*i) + 1] = ';';
	}
	if (m_str[*i] == '\'' && *o_l_quote == 1 && m_str[*i - 1] != '\\')
	{
		*o_l_quote = 0;
		if (m_str[*i + 1] == ' ')
			m_str[*i + 1] = ';';
	}
}

int	ft_check_error(int c_pip, int f_dir)
{
	if (c_pip >= 3 && f_dir == 1)
		return (-4);
	if (c_pip >= 2 && f_dir == 1)
		return (-3);
	if (c_pip >= 4 && f_dir == 2)
		return (-6);
	if (c_pip >= 3 && f_dir == 2)
		return (-5);
	if (c_pip >= 4 && f_dir == 3)
		return (-8);
	if (c_pip >= 3 && f_dir == 3)
		return (-7);
	return (0);
}

void	ft_lst_null(t_lst_pipe **tmp, int *num2)
{
	t_lst_pipe	*begin2;

	(*tmp)->num = (*num2)++;
	(*tmp)->start_arg = 0;
	(*tmp)->count_red_pip = 0;
	(*tmp)->prev = NULL;
	(*tmp)->next = malloc(sizeof(t_lst_pipe));
	begin2 = (*tmp);
	(*tmp)->command = NULL;
	(*tmp) = (*tmp)->next;
	(*tmp)->prev = begin2;
	(*tmp)->next = NULL;
	(*tmp)->command = NULL;
}

void	ft_add_lst_2(t_lst_pipe *tmp, int c_pip, int count, int f_dir)
{
	t_lst_pipe	*begin2;

	tmp->prev->f_red_pip = f_dir;
	tmp->f_red_pip = 0;
	tmp->count_red_pip = c_pip;
	tmp->start_arg = count;
	tmp->next = malloc(sizeof(t_lst_pipe));
	begin2 = tmp;
	tmp = tmp->next;
	tmp->prev = begin2;
	tmp->next = NULL;
	tmp->command = NULL;
	tmp->num = -2;
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

// int	ft_pip_red_1()
// {

// }

int	ft_check_command(char **m_str, t_all *all) // more than 25 line
{
	int	i;
	int	count;
	int	c_pip;

	count = 0;
	i = 0;
	all->o_l_quote = 0;
	all->t_l_quote = 0;
	while (m_str[0][i] != '\0')
	{
		c_pip = 0;
		while (m_str[0][i] == ' ' || m_str[0][i] == '\t' || m_str[0][i] == '|' \
			|| (m_str[0][i] == '>') || (m_str[0][i] == '<'))
		{
			if (all->t_l_quote == 0 && all->o_l_quote == 0)
			{
				/*//////////*/
				if (m_str[0][i] == '|')
				{
					while (m_str[0][i] == '|')
					{
						c_pip++;
						i++;
					}
					if (ft_add_lst(all, c_pip, count, 1) != 0)
						return (ft_add_lst(all, c_pip, count, 1));
					i = i - c_pip;
				}
				/*///////////*/
				if (m_str[0][i] == '>')
				{
					while (m_str[0][i] == '>')
					{
						/* printf("m_str[0][%i] = [%c], c_pip = %i\n", i, m_str[0][i], c_pip);*/
						c_pip++;
						i++;
					}
					if (ft_add_lst(all, c_pip, count, 2) != 0)
						return (ft_add_lst(all, c_pip, count, 2));
					i = i - c_pip;
				}
				/* ////////////// */
				if (m_str[0][i] == '<')
				{
					while (m_str[0][i] == '<')
					{
						c_pip++;
						i++;
					}
					if (ft_add_lst(all, c_pip, count, 3) != 0)
						return (ft_add_lst(all, c_pip, count, 3));
					i = i - c_pip;
				}
				//////////////////////
				while (c_pip > 1) // что бы пропустить если идёт два редиректа
				{
					m_str[0][i] = ';';
					if (i > 0 && m_str[0][i - 1] != ';')
						count++;
					i++;
					c_pip--;
				}
				m_str[0][i] = ';';
				if (i > 0 && m_str[0][i - 1] != ';')
					count++;
			}
			i++;
		}
		ft_first(*m_str, &all->t_l_quote, &all->o_l_quote, &i); // определяем кавычки
		if (all->o_l_quote == 0 && ft_dollar(m_str, &i, all) == -1) // проверка $
			return (1);
		i++;
	}
	if (all->o_l_quote != 0 || all->t_l_quote != 0) // проверка к концу команды - закрыта ли кавычка?
		return (1);
	return (0);
}
