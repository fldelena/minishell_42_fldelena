#include "../includes/minishell.h"

static void ft_first(char *m_str, int *t_l_quote, int *o_l_quote, int *i)
{
	if ((m_str[*i] == '"' && *t_l_quote == 0 && (*i > 0 && m_str[*i - 1] != '\\') && *o_l_quote == 0) || (m_str[*i] == '"' && *i == 0))
	{
		(*t_l_quote)++;
		(*i)++;
	}
	if ((m_str[*i] == '\'' && *o_l_quote == 0 && (i > 0 && m_str[*i - 1] != '\\') && *t_l_quote == 0) || (m_str[*i] == '"' && *i == 0))
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

static int ft_count_env(char *m_str, int *i, int l_dollar)
{
	int count;

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
		while (m_str[*i] != '\0' && m_str[*i] != ' ' && m_str[*i] != ',' && m_str[*i] != '"' && m_str[*i] != '\'' && m_str[*i] != '-' && m_str[*i] != '_')
		/*  сделать по таблице askii m_str[*i] > < числа т.к. много символов (+ других) прерывает имя переменной */
		{
			(*i)++;
			count++;
		}
	}
	return (count);
}

static char *ft_help1(char *m_str, int *i, int count)
{
	int j;
	char *now_env;

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

static char *ft_help2(char *m_str, int *i, int count)
{
	int j;
	char *now_env;

	j = 0;
	now_env = malloc(count + 1);
	while (m_str[*i - count] != '\0' && m_str[*i - count] != ' ' && m_str[*i - count] != '"') /* тут '"' является костылём для кейса "$PWD" */
	{
		now_env[j] = m_str[*i - count];
		j++;
		count--;
	}
	now_env[j] = '\0';
	return (now_env);
}

static int ft_before_env(char *m_str, char *now_env, int count, char *m2)
{
	int j;
	int i;
	int count2;

	i = 0;
	j = 0;
	while (m_str[i] != '\0')
	{
		count2 = 0;
		while (count2 != count && m_str[i + count2] != '\0')
			if (m_str[i + count2] == now_env[count2]) /*&& (i == 0 || (m_str[i - 1] == '$' || m_str[i - 1] == '{'))*/
				count2++;
			else
				break;
		if (i > 0 && m_str[i + count2 - 1] == now_env[count2 - 1] && count2 == count) // sega
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

static void ft_write_env(int i, char *m2, t_all *all, int *j_m)
{
	int k;

	k = 0;
	while (all->env->val[i][k] != '\0')
	{
		m2[*j_m] = all->env->val[i][k];
		(*j_m)++;
		k++;
	}
}

static void ft_end_rewrite(char *m2, char *m_str, int j_m, int j_str)
{
	while ((int)ft_strlen(m_str) > j_str && m_str[j_str] != '\0')
	{
		m2[j_m] = m_str[j_str];
		j_str++;
		j_m++;
	}
	m2[j_m] = '\0';
}

static int ft_rewrite(char **m_str, char *now_env, t_all *all, int count)
{
	int i;
	int j_m;
	int j_str;
	char *m2;

	i = 0;
	while (all->env->var[i]) /* проверка есть ли такая env */
	{
		if (strcmp(all->env->var[i], now_env) == 0)
			break;
		i++;
	}
	if (all->env->val[i])
	{
		m2 = malloc(ft_strlen(*m_str) - count + ft_strlen(all->env->val[i]) + 1);
		j_m = ft_before_env(*m_str, now_env, count, m2); // переписывает до переменной - вернёт символ, где начинается нужная переменная
		if (m_str[0][j_m + 1] != '{')
			j_str = j_m + count + 1; // можно вынести в отсдельную функцию    // после env от куда m_str переписывать
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

static int ft_dollar(char **m_str, int *i, t_all *all) // можно перенести это в обработку аргументов
{
	char *now_env;
	int l_dollar;
	int count; // длина названия переменной

	l_dollar = 0;
	count = 0;
	if (m_str[0][*i] == '$')
	{
		(*i)++;
		if (m_str[0][*i] == '{') // если у нас после доллара идут скобки, нужно найти вторую
			(l_dollar)++;
		count = ft_count_env(m_str[0], i, l_dollar);
		if (l_dollar == 1 && m_str[*i] != '\0') // тут записываем имя переменной если была скобка
			now_env = ft_help1(m_str[0], i, count);
		else if (l_dollar == 0) // тут записываем имя переменной если скобки не было
			now_env = ft_help2(m_str[0], i, count);
		else
			return (-1);
		if (ft_rewrite(m_str, now_env, all, count) == -1) // заменяем переменную env на её значение если такое есть (если нет значения не предусмотренно) !!!!!!!!
			return (-1);
		//(*i)--;
	}
	return (0);
}

static int ft_add_lst(t_all *all, int c_pip, int count, int f_dir)
{
	t_lst_pipe *tmp;
	t_lst_pipe *tmp2;
	int num2;

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
	num2 = 0;

	tmp = all->pipe;
	while (tmp->next != NULL)
	{
		num2++;
		tmp = tmp->next;
	}

	if (tmp->num == -1)
	{
		tmp->num = num2++;
		tmp->start_arg = 0;
		tmp->count_red_pip = 0;
		tmp->prev = NULL;
		tmp->next = malloc(sizeof(t_lst_pipe));
		tmp2 = tmp;
		tmp = tmp->next;
		tmp->prev = tmp2;
		tmp->next = NULL;
	}

	// tmp = all->pipe;
	// while (tmp->next != NULL)
	// {
	// 	num2++;
	// 	tmp = tmp->next;
	// }

	tmp->f_red_pip = f_dir;
	tmp->num = num2;
	tmp->count_red_pip = c_pip;
	tmp->start_arg = count;
	tmp->next = malloc(sizeof(t_lst_pipe));
	tmp2 = tmp;
	tmp = tmp->next;
	tmp->prev = tmp2;
	tmp->next = NULL;
	tmp->num = -2;
	tmp->start_arg = -1;
	return (0);
}

int ft_check_command(char **m_str, t_all *all)
{
	int i;
	int o_l_quote;
	int t_l_quote;
	int count;
	int c_pip;

	count = 0;
	i = 0;
	o_l_quote = 0;
	t_l_quote = 0;
	while (m_str[0][i] != '\0')
	{
		c_pip = 0;
		while (m_str[0][i] == ' ' || m_str[0][i] == '\t' || m_str[0][i] == '|' || (m_str[0][i] == '>') || (m_str[0][i] == '<'))
		{
			if (t_l_quote == 0 && o_l_quote == 0)
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
		ft_first(*m_str, &t_l_quote, &o_l_quote, &i); // определяем кавычки
		// proverka открыта кавычка то мы не заходим в доллар
		if (o_l_quote == 0 && ft_dollar(m_str, &i, all) == -1) // проверка $
			return (1);
		i++;
	}
	if (o_l_quote != 0 || t_l_quote != 0) // проверка к концу команды - закрыта ли кавычка?
		return (1);
	return (0);
}
