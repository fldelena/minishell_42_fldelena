#include "../includes/minishell.h"

void	ft_write_env(int i, char *m2, t_all *all, int *j_m)
{
	int	k;

	k = 0;
	while (all->env->val[i][k] != '\0')
	{
		m2[*j_m] = all->env->val[i][k];
		(*j_m)++;
		k++;
	}
}

void	ft_end_rewrite(char *m2, char *m_str, int j_m, int j_str)
{
	while ((int)ft_strlen(m_str) > j_str && m_str[j_str] != '\0')
	{
		m2[j_m] = m_str[j_str];
		j_str++;
		j_m++;
	}
	m2[j_m] = '\0';
}

int	find_env_in_all(t_all *all, char *now_env)
{
	int	i;

	i = 0;
	while (all->env->var[i])
	{
		if (ft_strncmp(all->env->var[i], now_env, \
				ft_strlen(now_env)) == 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_rewrite(char **m_str, char *now_env, t_all *all, int count)
{
	int		i;
	int		j_m;
	int		j_str;
	char	*m2;

	i = find_env_in_all(all, now_env);
	if (all->env->val[i])
	{
		m2 = malloc(ft_strlen(*m_str) - count + \
				ft_strlen(all->env->val[i]) + 1);
		j_m = ft_before_env(*m_str, now_env, count, m2);
		if (m_str[0][j_m + 1] != '{')
			j_str = j_m + count + 1;
		else
			j_str = j_m + count + 3;
		ft_write_env(i, m2, all, &j_m);
		ft_end_rewrite(m2, *m_str, j_m, j_str);
		*m_str = m2;
	}
	else
		return (-1);
	return (0);
}

int	ft_dollar(char **m_str, int *i, t_all *all)
{
	char	*now_env;
	int		l_dollar;
	int		count;
	int		i2;

	i2 = *i;
	l_dollar = 0;
	count = 0;
	if (m_str[0][*i] == '$')
	{
		(*i)++;
		if (m_str[0][*i] == '{')
			(l_dollar)++;
		count = ft_count_env(m_str[0], i, l_dollar);
		if (l_dollar == 1 && m_str[0][*i] != '\0')
			now_env = ft_help1(m_str[0], i, count);
		else if (l_dollar == 0)
			now_env = ft_help2(m_str[0], i, count);
		else
			return (-1);
		if (ft_rewrite(m_str, now_env, all, count) == -1)
			return (-1);
		*i = i2 + ft_strlen(all->env->val[find_env_in_all(all, now_env)]) - 1;
	}
	return (0);
}
