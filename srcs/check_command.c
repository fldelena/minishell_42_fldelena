#include "../includes/minishell.h"

static void     ft_first(char *m_str, int *t_l_quote, int *o_l_quote, int *i)
{
    // определяем какая первая кавычка
    if ((m_str[*i] == '"' && *t_l_quote == 0 && (*i > 0 && m_str[*i - 1] != '\\') && *o_l_quote == 0) \
        || (m_str[*i] == '"' && *i == 0))
    {
        (*t_l_quote)++;
        (*i)++;
    }
    if ((m_str[*i] == '\'' && *o_l_quote == 0 && (i > 0 && m_str[*i - 1] != '\\') && *t_l_quote == 0) \
        || (m_str[*i] == '"' && *i == 0))
    {
        (*o_l_quote)++;
        (*i)++;
    }
    // определяем какая вторая кавычка
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

static int ft_dollar(char *m_str, int *i)       // можно перенести это в обработку аргументов
{
    char    *now_env;
    int     l_dollar;
    int     count;
    int     j;

    l_dollar = 0;
    j = 0;
    count = 0;
    if (m_str[*i] == '$')
    {
        (*i)++;       // заключил *i в скобки
        if (m_str[*i] == '{')
            (l_dollar)++;
        if (l_dollar == 1)
            while (m_str[*i] != '\0' && m_str[*i] != '}')
            {
                (*i)++;
                count++;
            }
        else
            while (m_str[*i] != '\0' && (m_str[*i] != ' ' || m_str[*i] != ',' || m_str[*i] != '"' || m_str[*i] != '\'' || m_str[*i] != '-' || m_str[*i] != '_')) //  сделать по таблице askii m_str[*i] > < числа
            {
                (*i)++;
                count++;
            }
        if (l_dollar == 1 && m_str[*i] != '\0')
        {
            now_env = malloc(count + 1);
            while (m_str[*i - count] != '}')
            {
                now_env[j] = m_str[*i - count];
                j++;
                count--;
            }
            now_env[j] = '\0';
        }
        else if (l_dollar == 1 && m_str[*i] == '\0')
            return (-1);
        else if (l_dollar == 0 && m_str[*i] != '\0')
        {
            now_env = malloc(count + 1);
            while (m_str[*i - count] != ' ')
            {
                now_env[j] = m_str[*i - count];
                j++;
                count--;
            }
            now_env[j] = '\0';
        }
        else
            return (-1);
            // теперь надо заменить now_env на его значение в этой строке.
    }
    return (0);
}

int ft_check_command(char *m_str)
{
    int i;
    int o_l_quote;
    int t_l_quote;

    i = 0;
    o_l_quote = 0;
    t_l_quote = 0;
    while(m_str[i] != '\0')
    {
        while(m_str[i] == ' ' || m_str[i] == '\t')
        {
            if (t_l_quote == 0 && o_l_quote == 0)
                m_str[i] = ';';
            i++;
        }
        // определяем кавычки
        ft_first(m_str, &t_l_quote, &o_l_quote, &i);
        if (ft_dollar(m_str, &i) == -1)  // вывод ошибки? Невалидность кавычек
            return (-1);
        i++;
    }
    // проверка к концу команды - закрыта ли кавычка?
    if (o_l_quote != 0 || t_l_quote != 0)
        return (-1);
    return (0);
}
