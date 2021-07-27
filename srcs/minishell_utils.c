#include "../includes/minishell.h"

void	ft_print_error_2(char *command, int my_error)
{
	if (my_error == -8)
		write(2, "minishell: syntax error near unexpected token `<<'\n", 51);
	else if (my_error == 127)
		printf("minishell: %s: command not found\n", command);
	else if (my_error == -9)
		write(2, "minishell: Not valid\n", 21);
	else if (my_error == 1)
		return ;
	else
		printf("%s\n", strerror(errno));
}

void	print_error(char *command, int my_error)
{
	if (my_error > 0)
		errno = my_error;
	else
		errno = -1;
	if (my_error == -1)
		write(2, "minishell: too much arguments\n", 30);
	else if (my_error == -2)
		write(2, "minishell: Too much command in one string\n", 42);
	else if (my_error == -3)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	else if (my_error == -4)
		write(2, "minishell: syntax error near unexpected token `||'\n", 51);
	else if (my_error == -5)
		write(2, "minishell: syntax error near unexpected token `>'\n", 51);
	else if (my_error == -6)
		write(2, "minishell: syntax error near unexpected token `>>'\n", 51);
	else if (my_error == -7)
		write(2, "minishell: syntax error near unexpected token `<'\n", 51);
	else
		ft_print_error_2(command, my_error);
}

void	init_errno(t_all *all)
{
	char	**arguments;
	char	*error_my;
	char	*dollar;

	dollar = malloc(3);
	dollar[0] = '?';
	dollar[1] = '=';
	dollar[2] = '\0';
	error_my = ft_itoa(errno);
	dollar = ft_strjoin(dollar, error_my);
	arguments = malloc(sizeof(char *) * 3);
	arguments[0] = "hi\0";
	arguments[1] = dollar;
	arguments[2] = NULL;
	add_variable(all->env, arguments);
	all->parser.count = 0;
	all->parser.o_l_quote = 0;
	all->parser.t_l_quote = 0;
	errno = 0;
	g_pid = 0;
}

void	ft_launch_arg_n(t_all *all, char **arguments)
{
	t_lst_pipe	*tmp_123;
	int			k;

	k = 0;
	tmp_123 = all->pipe;
	while (tmp_123->next)
	{
		tmp_123->command = ft_make_arg_n(arguments, all, k);
		tmp_123 = tmp_123->next;
		k++;
	}
}

int	ft_check_line(char *m_str)
{
	int	i;

	i = 0;
	while (m_str[i] != '\0')
	{
		if (m_str[i] != ';' && m_str[i] != ' ' && m_str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
