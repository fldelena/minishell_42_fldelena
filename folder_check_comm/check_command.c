#include "../includes/minishell.h"

void	ft_first(char *m_str, int *t_l_quote, int *o_l_quote, int *i)
{
	if ((m_str[*i] == '"' && *t_l_quote == 0 && \
		(*i > 0 && m_str[*i - 1] != '\\') \
		&& *o_l_quote == 0) || (m_str[*i] == '"' && *i == 0))
	{
		(*t_l_quote)++;
		(*i)++;
	}
	if ((m_str[*i] == '\'' && *o_l_quote == 0 && (i > 0 && m_str[*i - 1] \
		!= '\\') && *t_l_quote == 0) || (m_str[*i] == '"' && *i == 0))
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

int	ft_check_pip_red(char **m_str, t_all *all, int *i)
{
	int	c_pip;
	int	my_error;

	c_pip = 0;
	my_error = ft_check_pip_red_help1(m_str, all, i, &c_pip);
	if (my_error != 0)
		return (my_error);
	my_error = ft_check_pip_red_help2(m_str, all, i, &c_pip);
	if (my_error != 0)
		return (my_error);
	while (c_pip > 1)
	{
		m_str[0][(*i)] = ';';
		if ((*i) > 0 && m_str[0][(*i) - 1] != ';')
			all->parser.count++;
		(*i)++;
		c_pip--;
	}
	m_str[0][(*i)] = ';';
	if ((*i) > 0 && m_str[0][(*i) - 1] != ';')
		all->parser.count++;
	return (0);
}

int	ft_check_command(char **m_str, t_all *all)
{
	int	i;
	int	my_error;

	i = 0;
	while (m_str[0][i] != '\0')
	{
		while (m_str[0][i] == ' ' || m_str[0][i] == '\t' || m_str[0][i] == '|' \
			|| (m_str[0][i] == '>') || (m_str[0][i] == '<'))
		{
			if (all->parser.t_l_quote == 0 && all->parser.o_l_quote == 0)
				my_error = ft_check_pip_red(m_str, all, &i);
			if (my_error != 0)
				return (my_error);
			i++;
		}
		ft_first(*m_str, &all->parser.t_l_quote, &all->parser.o_l_quote, &i);
		if (all->parser.o_l_quote == 0 && ft_dollar(m_str, &i, all) == -1)
			return (1);
		i++;
	}
	if (all->parser.o_l_quote != 0 || all->parser.t_l_quote != 0)
		return (1);
	return (0);
}
