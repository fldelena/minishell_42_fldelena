#include "../includes/minishell.h"

char	*ft_help1(char *m_str, int *i, int count)
{
	int		j;
	char	*now_env;

	j = 0;
	now_env = malloc(count + 1);
	while (m_str[*i - count] != '}')
	{
		now_env[j] = m_str[*i - count];
		j++;
		count--;
	}
	now_env[j] = '\0';
	return (now_env);
}

char	*ft_help2(char *m_str, int *i, int count)
{
	int		j;
	char	*now_env;

	j = 0;
	now_env = malloc(count + 1);
	while (m_str[*i - count] != '\0' && m_str[*i - count] != ' ' \
			&& m_str[*i - count] != '"')
	{
		now_env[j] = m_str[*i - count];
		j++;
		count--;
	}
	now_env[j] = '\0';
	return (now_env);
}

int	ft_count_env(char *m_str, int *i, int l_dollar)
{
	int	count;

	count = 0;
	if (m_str[*i] == '{')
		(*i)++;
	if (l_dollar == 1)
	{
		while (m_str[*i] != '\0' && m_str[*i] != '}')
		{
			(*i)++;
			count++;
		}
	}
	else
	{
		while (m_str[*i] != '\0' && m_str[*i] != ' ' && m_str[*i] != ',' && \
			m_str[*i] != '"' && m_str[*i] != '\'' && m_str[*i] != '-' \
			&& m_str[*i] != '_')
		{
			(*i)++;
			count++;
		}
	}
	return (count);
}

int	ft_count_befor(int count, char *m_str, char *now_env, int i)
{
	int	count2;

	count2 = 0;
	while (count2 != count && m_str[i + count2] != '\0')
	{
		if (m_str[i + count2] == now_env[count2])
			count2++;
		else
			break ;
	}
	return (count2);
}

int	ft_before_env(char *m_str, char *now_env, int count, char *m2)
{
	int	j;
	int	i;
	int	count2;

	i = 0;
	j = 0;
	while (m_str[i] != '\0')
	{
		count2 = ft_count_befor(count, m_str, now_env, i);
		if (i > 0 && count2 > 0 && m_str[i + count2 - 1] == \
				now_env[count2 - 1] && count2 == count)
		{
			if (m_str[i - 1] == '$')
				return (i - 1);
			else
				return (i - 2);
		}
		m2[j] = m_str[i];
		j++;
		i++;
	}
	return (i - 1);
}
